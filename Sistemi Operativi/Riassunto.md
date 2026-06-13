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

## Terminazione degli errori

Un processo può terminare in vari modi (es. arrivando alla fine del main). Tuttavia, per forzare la chiusura o indicare al sistema operativo l'esito dell'esecuzione, si usa la funzione exit.

- Funzione: `void exit(int status)`; (Richiede `<stdlib.h>`)

- Exit Code (Codice di stato): È il numero che il tuo programma restituisce al sistema operativo alla chiusura.

    - `0` (o la costante `EXIT_SUCCESS`): Tutto è andato bene.

    - `>0` (o la costante `EXIT_FAILURE`): Il programma è terminato a causa di un errore.

-  Terminazione "Pulita": Quando chiami `exit()`, il sistema non "uccide" brutalmente il programma, ma prima scrive i buffer di memoria rimasti in sospeso e avvia eventuali procedure di chiusura che hai registrato tramite la funzione `atexit()`.