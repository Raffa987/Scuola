# Programmazione ad oggetti
### Alcune Definizioni
L’**astrazione** è un procedimento che consente di semplificare la realtà che vogliamo modellare. La semplificazione avviene concentrando l’attenzione solo sugli elementi importanti del sistema complesso che stiamo considerando.

Un **algoritmo** è un insieme di istruzioni che a partire da  dati di input permettono di ottenere i risultati di output.Un algoritmo deve essere riproducibile, deve avere una durata finita e non deve essere ambiguo. Il modo di programmare pone attenzione sulla sequenza di esecuzione.

Un **sistema** è una parte del mondo che si sceglie di considerare come un intero, composto da componenti. Ogni componente è caratterizzata da proprietà rilevanti, e da azioni che creano interazioni tra le proprietà e le altre componenti.

## Classi e Oggetti
La **Classe** (Il **Modello**) è il concetto astratto, lo "stampo" o progetto di base. Una classe incapsula (cioè racchiude e struttura logicamente) le caratteristiche e i comportamenti che avranno le entità che vogliamo rappresentare nel nostro programma.

L'**Oggetto** (L'**Istanza**) è l'elemento base e concreto della OOP, creato fisicamente a partire dalla sua Classe. Ogni oggetto è formato da due componenti fondamentali:

- **Attributi** (Stato): Sono le caratteristiche o proprietà che descrivono l'oggetto.

- **Metodi** (Comportamenti): Sono le funzionalità e le operazioni che l'oggetto è in grado di compiere o che mette a disposizione degli altri.

Il **Sistema** e l'**Interazione**<br>
Un programma a oggetti è essenzialmente un modello di sistema popolato da molteplici oggetti. Questi non sono entità isolate, ma comunicano e interagiscono continuamente tra loro attraverso lo scambio di messaggi (che, in termini pratici, corrisponde all'invocazione dei rispettivi metodi).

### Incapsulamento
Per **incapsulamento** si indica la proprietà degli oggetti di incorporare al loro interno sia ttributi che metodi, in modo da avere tutte le informazioni riguardanti gli oggetti ben localizzate.
### Interfaccia di un oggetto
Un oggetto può avere sia una sezione **privata** che una sezione **publica**:
- nella sezione publica vengono messi tutti gli attributi e i metodi che si vuole rendere visibili all'esterno
- nella sezione privata vengono messi tutti gli attributi e metodi che non sono accessibili e che vengono usati internamente dall'oggetto per implementare i suoi comportamenti.
### Classe
Per rappresentare graficamnete le classi si usano i diagrammi delle classi:

<img src="image.png" alt="alt text" width="150"></img>

### Ereditarietà
se si dispone di una classe simile a quella che si vuole costruire si puà espandere la classe già esistente per riadattarla. L'ereditarietà è lo strumento che permette di costruire nuove classi utilizzando quelle già sviluppate.
Quando una classe viene creata in questo modo,eredita tutti gli attributi ed i metodi della classe  generatrice. La classe che è stata derivata prende il  nome di **sottoclasse**, mentre la classe generatrice si chiama **sopraclasse**.
La nuova classe si può differenziare per:
- **estensione**: aggiungendo nuovi attributi e metodi.
- **ridefinizione**: modificando i metodi ereditati, specificando un'implementazione diversa di un metodo(**override**, **overload**).
Una classe può avere ereditarietà singola(se ha una sola sopraclasse) o ereditarietà multipla(se ha più sopraclassi).
### Relazioni tra classi
**Association**(relazione d'uso)<br>
Diciamo che una classe A utilizza una classe B se un  oggetto di classe A è in grado di inviare dei messaggi ad un oggetto di classe B oppure se un oggetto di classe  A  può creare, ricevere o restituire oggetti di classe B.<br>
**Aggregation**(relazione di contenimento)<br>
Un oggetto di classe A contiene un oggetto di classe B se B è una proprietà (attributo) di A.<br>
**Composizione**<br>
La composizione è una forma di aggregazione ancora più forte che indica che una "parte" può appartenere ad un solo "intero" in un certo istante di tempo.
### Polimorfismo 
Il **polimorfiasmo** indica la possibilità per i metodi di assumere implementazioni diverse all'interno della gerarchia delle classi
### Collegamento dinamico
Il **collegamento dinamico** è lo strumento utilizzato per la realizzazione del polimorfismo. È dinamico perché l’associazione tra l’oggetto e il metodo corretto da eseguire è effettuata a run-time, cioè durante l’esecuzione del programma.

## Classi derivate
## Templates
## Sovraccaricamento degli operatori

# Cenni di complessità e tecniche ricorsive
### Complessità di un Problema Computazionale
La complessità computazionale è il ramo dell'informatica teorica che classifica i problemi computazionali in base all'uso delle risorse necessarie per risolverli. Le due risorse principali analizzate sono:
- **Tempo**: Il numero di operazioni base eseguite da un algoritmo.
- **Spazio**: La quantità di memoria necessaria durante l'esecuzione dell'algoritmo.

È fondamentale distinguere tra:
- **Complessità di un algoritmo**: Valuta l'efficienza di una specifica sequenza di istruzioni.
- **Complessità di un problema**: Corrisponde alla complessità del miglior algoritmo possibile in grado di risolvere quel problema. Se il miglior algoritmo noto ha una certa complessità, essa definisce il limite superiore del problema, ma il limite inferiore teorico potrebbe essere diverso fino a quando non viene dimostrato il contrario.

L'analisi della complessità viene effettuata rispetto alla dimensione dell'input, comunemente denotata con la variabile $n$.

### Notazioni Asintotiche e Limite Superiore
L'analisi asintotica descrive il comportamento di una funzione al limite, ovvero come cresce il consumo di risorse al tendere di $n$ verso l'infinito. Questo approccio permette di ignorare costanti moltiplicative e termini di grado inferiore, concentrandosi sul tasso di crescita dominante.

#### Limite Superiore: La Notazione $O$-grande (Big-O)
La notazione $O$ definisce un limite superiore asintotico. Indica il caso peggiore, ovvero garantisce che l'algoritmo non impiegherà mai più tempo di quanto indicato dalla funzione delimitante, a meno di un fattore costante.<br>
Definizione Formale:<br>
Date due funzioni $f(n)$ e $g(n)$, si dice che $f(n) \in O(g(n))$ (spesso scritto impropriamente come $f(n) = O(g(n))$) se esistono due costanti positive $c$ e $n_0$ tali che:
$$0 \le f(n) \le c \cdot g(n) \quad \text{per ogni } n \ge n_0$$
Questo significa che, superata una certa dimensione dell'input ($n_0$), il tempo di esecuzione $f(n)$ è sempre limitato superiormente da un multiplo scalare della funzione $g(n)$.

### Calcolo del Limite Superiore del Tempo di Esecuzione
Per calcolare il limite superiore del tempo di esecuzione di un blocco di codice, si applicano regole sistematiche basate sulla struttura dell'algoritmo:
1. Operazioni di base: Assegnamenti, operazioni aritmetiche, valutazioni booleane e accessi ad array costano $O(1)$ (tempo costante).
2. Sequenza di istruzioni: Se si hanno istruzioni in sequenza con complessità $O(f(n))$ e $O(g(n))$, la complessità totale è la somma, che asintoticamente equivale al massimo tra le due: $\max(O(f(n)), O(g(n)))$.
3. Costrutti condizionali (if-else): Il tempo di esecuzione è il tempo della valutazione della condizione più il massimo tra i tempi di esecuzione dei blocchi if e else.
4. Cicli (for/while): Il tempo di esecuzione è pari alla somma del tempo di esecuzione del corpo del ciclo per ogni iterazione. Se il corpo costa $O(c)$ e il ciclo viene eseguito $n$ volte, la complessità è $O(n \cdot c)$.
5. Cicli annidati: Si procede dall'interno verso l'esterno, moltiplicando il numero di esecuzioni dei cicli.
<br>
**Regola di semplificazione generale:** 
<br>
Date le regole dell'analisi asintotica, le costanti moltiplicative e i termini di grado inferiore vengono omessi. Esempio: <br>$f(n) = 3n^2 + 5n + 10$ diventa direttamente $O(n^2)$.

### Esempi 
1. Tempo Costante $O(1)$:<br>
Il tempo di esecuzione è indipendente dalla dimensione dell'input.

    ```C++
    #include <vector>

        // Calcolo:
        // Controllo condizione (if) -> O(1)
        // Accesso indice 0 -> O(1)
        // Ritorno valore -> O(1)
        // Totale: O(1) + O(1) + O(1) = O(1)
        int getFirstElement(const std::vector<int>& arr) {
            if (arr.empty()) {
                return -1; 
            }
            return arr[0];
        }
    ```

2. Tempo Lineare $O(n)$
Il tempo di esecuzione cresce in modo direttamente proporzionale alla dimensione dell'input $n$.

    ```C++
    #include <vector>

    // Calcolo:
    // Inizializzazione sum = 0 -> O(1)
    // Ciclo for eseguito n volte (dove n = arr.size())
    // Corpo del ciclo (sum += arr[i]) -> O(1) per iterazione
    // Totale: O(1) + n * O(1) = O(n)
    int sumElements(const std::vector<int>& arr) {
        int sum = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            sum += arr[i];
        }
        return sum;
    }
    ```

3. Tempo Quadratico $O(n^2)$
Tipico di algoritmi con due cicli annidati che iterano entrambi sulla collezione completa.

    ```C++
    #include <vector>

    // Calcolo:
    // Inizializzazione count = 0, n = arr.size() -> O(1)
    // Ciclo esterno eseguito n volte.
    // Ciclo interno eseguito n volte per ogni iterazione del ciclo esterno.
    // Corpo interno (count++) -> O(1)
    // Totale: O(1) + n * (n * O(1)) = O(n^2)
    int countPairs(const std::vector<int>& arr) {
        int count = 0;
        size_t n = arr.size();
        
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                // Operazione costante
                count++;
            }
        }
        return count;
    }
    ```

4. Tempo Logaritmico $O(\log n)$
Il tempo di esecuzione cresce proporzionalmente al logaritmo della dimensione dell'input. Si verifica tipicamente quando l'input viene dimezzato a ogni iterazione.

    ```C++
    // Calcolo:
    // Inizializzazione count = 0 -> O(1)
    // Il ciclo while continua finché n > 1.
    // A ogni passo, n viene diviso per 2.
    // Il numero di volte che si può dividere n per 2 prima di raggiungere 1 è log_2(n).
    // Corpo del ciclo -> O(1)
    // Totale: O(1) + O(log n) * O(1) = O(log n)
    int countDivisions(int n) {
        int count = 0;
        while (n > 1) {
            n = n / 2;
            count++;
        }
        return count;
    }
    ```
## Ricorsione ed algoritmi di ordinamento basati sulla ricorsione
[In questo file](Sortings.md)
# Strutture Dati
## Liste
## Pile e code
## Alberi
## Grafi


