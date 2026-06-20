/*Inverte maiuscole e minuscole in un file
*/

#include "../lib-misc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    char *p;
    long fd;    

    if(argc < 2) {
        exit_with_err_msg("uso %s, <file>\n", argv[0]);
    }
    
    if((fd = open(argv[1], O_RDWR)) == -1) {
        exit_with_sys_err(argv[1]);
    }

    if(fstat(fd, &sb) == -1) {
        exit_with_sys_err("fstat");
    }

    if(!S_ISREG(sb.st_mode)) {
        exit_with_err_msg("%s non è un file", argv[1]);
    }

    if((p = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        exit_with_sys_err("mmap");
    }
    if(close(fd) == -1){
        exit_with_sys_err("close");
    }

    for(int i = 0; i < sb.st_size; i++){
        if(isupper(p[i])) {
            p[i] = tolower(p[i]);
        } else if(islower(p[i])) {
            p[i] = toupper(p[i]);
        }
    }

    printf("Maiuscole e minuscole invertite\n");

    if(munmap(p, sb.st_size) == -1) {
        exit_with_sys_err("munmap");
    }

    exit(EXIT_SUCCESS);
}