/*Pratica per capire gli arogmenti*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

/*Macro per gli errori
il costrutto `do {} while (0)` nella macro serve per forzare il
compilatore a trattarlo come una vera e propria funzione
*/

#define exit_with_sys_error(s)              \
    do{                                     \
        perror((s));                        \
        exit(EXIT_FAILURE);                 \
    } while(0)


//Maschera per i permessi, attiva tutti quelli di read e write
#define RW0RW0RW_MASK (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)


//prototipo della fuzione
int get_lenght(char string[]);

int main(int argc, char *argv[]) {

    //inibisco la umask
    umask(0);

    //variabile dove faccio lo store del file descriptor
    int fd = 0;

    /*open del file, se non esiste lo crea, se esiste lo azzera e lo apre in lettura 
    e scrittura*/
    if((fd = open("prova.txt", O_RDWR | O_CREAT | O_TRUNC, RW0RW0RW_MASK)) < 0)
        exit_with_sys_error("prova.txt");

    char str[] = "Hello World\n";
    int l = get_lenght(str);

    //due write
    if(write(fd, str, l) < 0)
            exit_with_sys_error("Error on  first write");

    char str2[] = "You'll never read this";

    if(write(fd, str2, sizeof(str2)) < 0)
        exit_with_sys_error("Error on  second write");

    //buffer per il read di dimensione 1kB
    char buf[1024];
    //numero di bytes letti
    ssize_t read_bytes;

    //imposta l'offset del file, precedentemente spostato dalle write, a 0
    lseek(fd, 0, SEEK_SET);

    //stesso risultato di una cat
    while((read_bytes = read(fd, buf, sizeof(buf))) > 0) {
        if(write(STDOUT_FILENO, buf, read_bytes) < 0)
            exit_with_sys_error("write error");
    }
    
    close(fd);
    exit(EXIT_SUCCESS);
}

int get_lenght(char string[]) {
    int c = 0;
    while (string[c] != '\0') {
        c++;
    }

    return c;
}