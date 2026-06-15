# Laboratorio
Nei moderni sistemi operativi possiamo fare due tipi di chiamate:<br>
- **chiamate di sistema**: offerte dal sistema operativo(**modalità kernel**)<br>
- **chiamate di libreria**: funzioni incluse in librerie di sistema(**modalità utente**) 

## Layout della memoria
 Quando un programma viene avviato, il sistema operativo gli assegna uno spazio di memoria suddiviso in segmenti specifici. Comprendere questa divisione è fondamentale per capire dove "vivono" le tue variabili.

Puoi vedere la dimensione di questi segmenti su un file compilato usando il comando da terminale `size nome_eseguibile`.
I Segmenti di Memoria:

- Text (Codice): Contiene le istruzioni del programma compilato in linguaggio macchina.

-  Data (Dati Inizializzati): Contiene le variabili globali (o statiche) a cui hai assegnato un valore nel codice (es. `int max = 100;`).

- BSS (Dati Non Inizializzati): Contiene le variabili globali (o statiche) dichiarate ma senza un valore iniziale (es. `int vector[50];`). Il sistema operativo le inizializza automaticamente a zero quando avvia il programma.

- Heap: Memoria dinamica, gestita manualmente dal programmatore (dove allochi spazio con `malloc` e lo liberi con `free`).

- Stack: Memoria automatica gestita dal sistema. Contiene le variabili locali dichiarate dentro le funzioni e gli argomenti passati alle funzioni stesse.

## Gestione degli errori

In C (su sistemi UNIX), le chiamate di sistema (system call) non "crashano" mostrando finestre di errore, ma segnalano il problema tramite i valori di ritorno.

- Quasi tutte le system call restituiscono -1 se c'è stato un errore.

- La variabile errno: Se una funzione restituisce -1, il sistema imposta automaticamente una variabile globale chiamata errno con un codice numerico che identifica il tipo di errore (es. EPERM per permesso negato, ENOENT se il file non esiste).

- Attenzione: In caso di successo, errno non viene resettata a zero. Devi controllarla solo dopo aver verificato che la funzione ha restituito -1.

### Funzioni per stampare l'errore:
<table border="1" style="border-collapse: collapse; text-align: left;">
  <thead>
    <tr>
      <th>Funzione</th>
      <th>Libreria</th>
      <th>Descrizione</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>perror(const char *s)</code></td>
      <td><code>&lt;stdio.h&gt;</code></td>
      <td>È la più comoda e usata. Stampa a schermo la tua <br>stringa <code>s</code>, seguita dai due punti e dalla descrizione <br> umana dell'errore (es. <code>perror("Errore apertura");</code><br> stampa <em>Errore apertura: No such file or directory</em>).</td>
    </tr>
    <tr>
      <td><code>strerror(int errnum)</code></td>
      <td><code>&lt;string.h&gt;</code></td>
      <td>Prende il numero dell'errore e restituisce solo la stringa <br>descrittiva (utile se vuoi formattare l'output manualmente <br>con una <code>printf</code>).</td>
    </tr>
  </tbody>
</table>

## Terminazione del processo

Un processo può terminare in vari modi (es. arrivando alla fine del main). Tuttavia, per forzare la chiusura o indicare al sistema operativo l'esito dell'esecuzione, si usa la funzione exit.

- Funzione: `void exit(int status)`; (Richiede `<stdlib.h>`)

- Exit Code (Codice di stato): È il numero che il tuo programma restituisce al sistema operativo alla chiusura.

    - `0` (o la costante `EXIT_SUCCESS`): Tutto è andato bene.

    - `>0` (o la costante `EXIT_FAILURE`): Il programma è terminato a causa di un errore.

-  Terminazione "Pulita": Quando chiami `exit()`, il sistema non "uccide" brutalmente il programma, ma prima scrive i buffer di memoria rimasti in sospeso e avvia eventuali procedure di chiusura che hai registrato tramite la funzione `atexit()`.

## Descrittori dei File
In UNIX/Linux, tutto è considerato un file (hardware, terminali, file di testo, connessioni di rete). Per gestire questi "file", il sistema operativo usa i File Descriptors.

- Cos'è: È semplicemente un numero intero non negativo (0, 1, 2, 3...) che il sistema operativo ti "presta" come riferimento quando apri un file. Userai questo numero per tutte le operazioni successive (lettura, scrittura, chiusura).

- Canali Predefiniti: Appena avvii un programma, hai già 3 FD aperti di default (definiti in `<unistd.h>`):

<table border="1" style="border-collapse: collapse; text-align: left; width: 100%;">
  <thead>
    <tr>
      <th style="padding: 8px; text-align: center;">FD</th>
      <th style="padding: 8px;">Costante C</th>
      <th style="padding: 8px;">Significato</th>
      <th style="padding: 8px;">Destinazione tipica</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px; text-align: center;"><code>0</code></td>
      <td style="padding: 8px;"><code>STDIN_FILENO</code></td>
      <td style="padding: 8px;">Standard Input</td>
      <td style="padding: 8px;">Tastiera</td>
    </tr>
    <tr>
      <td style="padding: 8px; text-align: center;"><code>1</code></td>
      <td style="padding: 8px;"><code>STDOUT_FILENO</code></td>
      <td style="padding: 8px;">Standard Output</td>
      <td style="padding: 8px;">Schermo (Terminale)</td>
    </tr>
    <tr>
      <td style="padding: 8px; text-align: center;"><code>2</code></td>
      <td style="padding: 8px;"><code>STDERR_FILENO</code></td>
      <td style="padding: 8px;">Standard Error</td>
      <td style="padding: 8px;">Schermo (Terminale, per gli errori)</td>
    </tr>
  </tbody>
</table>


## Apertura, creazione e chiusura (`open()`, `creat()` e `exit()`)
```C
#include <fcntl.h>
#include <unistd.h>
```

### La funzione `open()`


```C
int open(const char *path, int oflag, [mode_t mode]);
```

Apre un file con percorso `path` e restituisce il file descriptor, ovvero un intero non negativo che fa da indice in una voce della tabella dei file descriptor del processo chiamante. Una chiamata `open()` genera inoltre una nuova voce nella tabella dei file aperti a livello di sistema(system-wide open file table), all'interno della quale vengono registrati l'offset corrente del file e i flag di stato.
L'argomento `flag` deve contenere almeno una modalità di accesso tra:
- `O_RDONLY`: read only
- `O_WRONLY`: write only
- `O_RDWR`: read/write

In aggiunta possono essere cobminate 0 o più flags per l'apertura. <br>Consultare [man](https://man7.org/linux/man-pages/man2/open.2.html) per la lista completa dei flags.<br><br>
In caso di errore la funzione restituisce `-1` e aggiorna `errno` per indicare l'errore. 

### La funzione `creat()`

``` C
int creat(const char *path, mode_t mode ); 
```

Equivalente a `open()`. Infatti si comporta come se venisse chiamata nel seguente modo:
``` C 
 int creat(const char *path, mode_t mode)
  {
    return open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
  } 
```

- `O_WRONLY`: il file viene aperto in sola scrittura
- `O_CREAT`: il file viene creato se non esiste
- `O_TRUNC`: se il file esiste già, la sua lunghezza venga troncata a 0 (sovrascritto)

### La funzione `close()`

```C
int close(int fd);
```
Chiude un file descriptor. Restituisce `0` se ha successo e `-1` aggiornando `errno` in caso di errore.

## Permessi sugli oggetti del File-System UNIX
Nei metadati del file(all'interno dell'inode) il sistema riserva un intero per memorizzare varie informazioni. Gli ultimi 9 bit sono dedicati ai permessi. 
Un bit `1` signfica "permesso accordato" e un bit a `0` vuol dire "permesso negato".
Questi 9 bit sono suddivi in 3 blocchi da 3 bit ciascuno(`R`, `W`, `X`; read, write e execute):
- permessi utente proprietario(USR)
- permessi gruppo proprietario(GRP)
- permessi per gli altri utenti(OTH)

Quindi, un file con tutti i permessi avrà gli ultimi 9 bit dell'inode messi a `111 111 111` in binario o 0777 in rappresentazione ottale. 
Il comando per impostare i permessi è `chmod`. Es. `chmod 0777`.

Questa maschera si può ottenere da costanti definite in `sys/stat.h`
<table border="1" style="border-collapse: collapse; text-align: left; width: 100%;">
  <thead>
    <tr>
      <th style="padding: 8px;">Flag</th>
      <th style="padding: 8px;">Ottale</th>
      <th style="padding: 8px;">Permesso</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;">S_IRUSR</td>
      <td style="padding: 8px;">00400</td>
      <td style="padding: 8px;">owner has read permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IWUSR</td>
      <td style="padding: 8px;">00200</td>
      <td style="padding: 8px;">owner has write permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IXUSR</td>
      <td style="padding: 8px;">00100</td>
      <td style="padding: 8px;">owner has execute permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;"></td>
      <td style="padding: 8px;"></td>
      <td style="padding: 8px;"></td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IRGRP</td>
      <td style="padding: 8px;">00040</td>
      <td style="padding: 8px;">group has read permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IWGRP</td>
      <td style="padding: 8px;">00020</td>
      <td style="padding: 8px;">group has write permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IXGRP</td>
      <td style="padding: 8px;">00010</td>
      <td style="padding: 8px;">group has execute permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;"></td>
      <td style="padding: 8px;"></td>
      <td style="padding: 8px;"></td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IROTH</td>
      <td style="padding: 8px;">00004</td>
      <td style="padding: 8px;">others have read permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IWOTH</td>
      <td style="padding: 8px;">00002</td>
      <td style="padding: 8px;">others have write permission</td>
    </tr>
    <tr>
      <td style="padding: 8px;">S_IXOTH</td>
      <td style="padding: 8px;">00001</td>
      <td style="padding: 8px;">others have execute permission</td>
    </tr>    
  </tbody>
</table>

Per le directory `X` rappresenta il diritto di attraversamento.

## Maschera di Creazione per i Permessi
Per ragioni di sicurezza quando un file(o una directory) viene creato la maschera(dei permessi) specificata viene combinata da una maschera di creazione che inibisce globalmente alcuni permessi.
La maschera dei permessi effettiva è data da: <br>
`effettiva = specificata & (~umask)`<br>

dove 

```c
mode_t umask(mode_t cmask);
```

L'espressione inibisce i permessi di `umask` messi a 1 lasciando gli altri intatti.

Se la directory padre in cui si sta creando il file ha una ACL di default(Access Control List), ovvero una maschera dei permessi, la `umask` del processo chiamante viene ignorata, il nuovo file eredita l'ACL del padre e i permessi effettivi vengono calcolati basandosi sull'ACL ereditata, incrociata con la maschera specificata dal chiamante.


## Posizionamento 
All'interno della System-Wide Open File Table vi è una voce che contiene la posizione attuale all'interno del file(offset), questo serve a simulare l'accesso sequenziale. Viene posto a `0` se durante la chiamata `open()` non si usa il flag `O_APPEND` e viene aggiornato dopo ogni operazione.

```C
off_t lseek(int fd, off_t offset, int whence);
```
Permette di spostare l'offset di un numero di bytes pari al parametro `offset` rispetto al punto `whence` che può assumere i seguenti valori:
- `SEEK_SET`: L'offset è posizionato a `offset` bytes
- `SEEK_CUR`: L'offset è posizionato alla posizione corrente più `offset` bytes
- `SEEK_END`: L' offset è posizionato alla dimensione del file(fine) più `offset` bytes<br>

Dalla versione del Kernel Linux 3.1 supporta anche le seguenti modalità:
- `SEEK_DATA`
- `SEEK_HOLE`<br>

`lseek()` permette di posizionare l'offset oltre la fine del file(questo però non ne cambierà la dimensione).Tuttavia, se si effettua una successiva operazione di `write()`, lo spazio tra la vecchia fine del file e il nuovo testo verrà riempito di byte nulli (`\0`), creando un  file hole. Questi buchi occupano spazio logico ma non consumano necessariamente blocchi fisici sul disco.

 La funzione`lseek()` ritorna `-1` in caso di errore o la nuova posizione all'intenro del file (`≥0`).
 Per ottenere la posizione attuale basta fare:
 ```C
 pos = lseek(fd, 0, SEEK_CUR);
 ```

 ## Lettura e Scrittura

 ### La funzione `read()`
 ```C
ssize_t read(int fd, void *buf, size_t nbytes);
 ```

Cerca di leggere fina a un numero `nbytes` di bytes, dal File Descriptor `fd`, mettendoli nel buffer  `buf`.

Nei File che supportano seeking la lettura inizia dall'offset indicato nella System-Wide Open File Table, e l'offset verrà spostato del numero di byte letti. Se l'offset è alla fine del file o oltre non verranno letti bytes e `read()` restituisce `0`. In caso di successo la funzione restituisce il numero di bytes letto e in caso di errore resituisce `-1` aggiornando `errno`, in questo caso non è specificato se la posizione all'interno file(se esiste) cambi.

> **Differenza tra size_t e ssize:t**
> * **`size_t`**: Intero **senza segno** (*unsigned*). Usato per i parametri di input (come `nbytes`) dove il valore deve essere sempre positivo.
> * **`ssize_t`**: Intero **con segno** (*signed*). Usato per il valore di ritorno perché deve poter restituire `-1` in caso di errore.


### La funzione `write()`
```C
ssize_t write(int fd, const void *buf, size_t nbytes);
```
Scrive fino a `nbytes` byte nel file descriptor `fd` leggendoli dal buffer `buf`.
Il numero di byte scritti può essere minore di quello indicato in `nbytes`se, per esempio, non c'è spazio sufficiente nel supporto fisico, o se incontra il limite di risorsa `RLIMIT_FSIZE`, o se la chiamata è stata interrotta da un segnale dopo aver scritto meno di `nbytes` byte.

Se il file supporta il seeking, la scrittura inizia dall'offset indicato nella System-Wide Open File Table, e l'offset verrà spostato del numero di byte scritti. Se il file è stato aperto con il flag `O_APPEND` l'offset verrà spostato alla fine del file prima di iniziare a scrivere. Il posizionamento dell'offset del file e l'operazione di scrittura verrano eseguite in modo atomico(inscindibile) dal kernel.


La funzione ritorna il numero di byte scritti. In caso di errore ritorna `-1` e aggiorna `errno`.