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
## Cenni di complessità asintotica
## Ricorsione ed algoritmi di ordinamento basati sulla ricorsione

# Strutture Dati
## Liste
## Pile e code
## Alberi
## Grafi


