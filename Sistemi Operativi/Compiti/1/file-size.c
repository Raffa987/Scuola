#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH 1024

#define exit_with_sys_err(s)            \
    do {                                \
        perror((s));                    \
        exit(EXIT_FAILURE);             \
    } while(0)

struct my_file {
    char path[MAX_PATH];
    size_t size;
};

struct shared {

    //---PRIMA STRUTTURA (DA DIR-i a STAT)---
    char pathname[10][MAX_PATH];
    int in;
    int out;
    pthread_mutex_t mutex_in;
    sem_t sem_free;
    sem_t sem_full;

    //---SECONDA STRUTTURA (DA STAT a MAIN)---
    struct my_file file_data;
    sem_t sem_main;
    sem_t sem_stat;

    //---GESTIONE NUMERO THREAD---
    int active_thread;
    pthread_mutex_t mutex_counter;
};

struct dir_args {
    int id;
    char *dir_path;
    struct shared *pshared;
};

void *dir_func(void *args);

void *stat_func(void *args);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Correct prorgram usage: \n./file-size <dir-1> <dir-2> ... <dir-n>\n");
        exit(EXIT_FAILURE);
    }

    int n = argc - 1;

    struct shared my_shared;
    
    my_shared.in = 0;
    my_shared.out = 0;
    pthread_mutex_init(&my_shared.mutex_in, NULL);
    pthread_mutex_init(&my_shared.mutex_counter, NULL);

    if(sem_init(&my_shared.sem_free, 0, 10) == -1) {
        exit_with_sys_err("sem_init");
    }
    if(sem_init(&my_shared.sem_full, 0, 0) == -1) {
        exit_with_sys_err("sem_init");
    }

    if(sem_init(&my_shared.sem_main, 0, 0) == -1) {
        exit_with_sys_err("sem_init");
    }
    if(sem_init(&my_shared.sem_stat, 0, 1) == -1) {
        exit_with_sys_err("sem_init");
    }

    my_shared.active_thread = n;

    pthread_t thread_dir[n];
    struct dir_args args[n];

    for(int i = 0; i < n; i++) {
        args[i].id = i + 1;
        args[i].dir_path = argv[i + 1];
        args[i].pshared = &my_shared;

        if(pthread_create(&thread_dir[i], NULL, dir_func, &args[i]) != 0) {
            exit_with_sys_err("pthread_create-DIR");
        }
    }

    pthread_t thread_stat;
    if(pthread_create(&thread_stat, NULL, stat_func, &my_shared) != 0) {
        exit_with_sys_err("pthread_create-STAT");
    }

    size_t tot = 0;
    while(1) {
        sem_wait(&my_shared.sem_main);
        if(strcmp(my_shared.file_data.path, "") != 0) {
            tot += my_shared.file_data.size;
            printf("[MAIN] con il file '%s' il totale parziale è di %zu byte\n", my_shared.file_data.path, tot);
            sem_post(&my_shared.sem_stat);
        }   else {
            break;
        }
    }

    printf("[MAIN] il totale finale è di %zu byte\n", tot);
    return 0;
}

void *dir_func(void *args) {
    struct dir_args *my_args = (struct dir_args *)args;
    char temp_path[MAX_PATH];

    //Apro la cartella
    DIR *input_dir = opendir(my_args->dir_path);
    if(input_dir == NULL) {
        exit_with_sys_err("open_dir");
    }
    

    printf("[D-%d] scansione della cartella '%s'\n", my_args->id, my_args->dir_path);


    struct dirent *entry;
    //Ciclo di lettura e scarto dei file
    while((entry = readdir(input_dir)) != NULL) {
        if(entry->d_type != DT_REG) {
            continue;
        }

        snprintf(temp_path, MAX_PATH, "%s/%s", my_args->dir_path, entry->d_name);
        printf("[D-%d] trovato il file '%s' in '%s'\n", my_args->id, entry->d_name, my_args->dir_path);

        //---INIZIO ZONA CRITICA---
        sem_wait(&my_args->pshared->sem_free);
        pthread_mutex_lock(&my_args->pshared->mutex_in);
        
        strcpy(my_args->pshared->pathname[my_args->pshared->in], temp_path);
        my_args->pshared->in = (my_args->pshared->in +1) % 10;    

        //---FINE ZONA CRITICA---
        pthread_mutex_unlock(&my_args->pshared->mutex_in);
        sem_post(&my_args->pshared->sem_full);        
    }

    //---Gestione dei Threads---
    pthread_mutex_lock(&my_args->pshared->mutex_counter);
    my_args->pshared->active_thread--;

    if(my_args->pshared->active_thread == 0) {
        //---INIZIO ZONA CRITICA---
        sem_wait(&my_args->pshared->sem_free);
        pthread_mutex_lock(&my_args->pshared->mutex_in);
            
        strcpy(my_args->pshared->pathname[my_args->pshared->in], "");
        my_args->pshared->in = (my_args->pshared->in +1) % 10;    
        //---FINE ZONA CRITICA---
        pthread_mutex_unlock(&my_args->pshared->mutex_in);
        sem_post(&my_args->pshared->sem_full);        
    }

    pthread_mutex_unlock(&my_args->pshared->mutex_counter);

    closedir(input_dir);
    pthread_exit(NULL);
}   

void *stat_func(void *args) {
    struct shared *my_args = (struct shared *)args;
    char path[MAX_PATH];

    struct stat sb;

    while(1) {
        sem_wait(&my_args->sem_full);

        strcpy(path, my_args->pathname[my_args->out]);
        my_args->out = (my_args->out + 1) % 10;

        sem_post(&my_args->sem_free);

        if(strcmp(path, "") == 0) {
            break;
        }

        stat(path, &sb); 

        printf("[STAT] il file '%s' ha dimensione %zu byte\n", path, (size_t)sb.st_size);        
        sem_wait(&my_args->sem_stat);
        my_args->file_data.size = (size_t)sb.st_size;
        strcpy(my_args->file_data.path, path);
        sem_post(&my_args->sem_main);
    }

        sem_wait(&my_args->sem_stat);
        strcpy(my_args->file_data.path, "");
        sem_post(&my_args->sem_main);

        pthread_exit(NULL);
}