#include "lib-misc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

//Permessi di R/W solo per il creatore
#define RW_MASK (S_IWUSR | S_IRUSR)
 
int main(int argc, char *argv[]) {
    /*Ricordiamo che i permessi effettivi verrano calcolati secondo:
    effettivi = specificati AND NOT(umask)
    Ponendo umask a 0 possiamo rendere il secondo termine dell'espressione neutro, dunque:
    effettivi = specificati AND NOT(0) = specificati AND 1 = specificati*/
    umask(0);
    
    if(creat("test1.txt", RW_MASK) < 0)
        exit_with_sys_err("test1.txt");

    /*Inibisco gli unici permessi definiti nella macro*/
    umask(S_IRUSR | S_IWUSR);

    if(creat("test2.txt", RW_MASK) < 0)
        exit_with_sys_err("test2.txt");

    exit(EXIT_SUCCESS);
}

/*Se dopo aver eseguito il codice si esegue, ls -l test1.txt test2.txt i permessi saranno
RW------- per test1.txt
--------- per test2.txt(Non si potrà nemmeno aprire)*/