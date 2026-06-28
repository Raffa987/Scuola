## Funzioni Con Argomenti di Default
Il C++ permette di specificare valori predefiniti per i parametri di una funzione. Se il chiamante non fornisce un valore per quel parametro, viene utilizzato il valore di default. <br>
Tutti i parametri con valore di default devono trovarsi alla fine della lista dei parametri nella firma della funzione.
```C++
void printData(int x, int y = 10, int z = 20);
```

## Sovraccaricamento delle Funzioni (Overloading)
L'overloading consente di definire più funzioni con lo stesso nome nello stesso scope, purché differiscano per la firma (numero, tipo o ordine dei parametri). Il compilatore determina quale funzione chiamare in base agli argomenti passati (risoluzione a tempo di compilazione / Static Binding).
```C++
int calcola(int a, int b);
double calcola(double a, double b);
```

## Specificatori di Accesso e Information Hiding

Gli specificatori controllano la visibilità dei membri della classe:

- `public`: Accessibili da qualsiasi parte del programma.

- `private`: Accessibili solo dall'interno della classe stessa (impostazione predefinita per le classi).

- `protected`: Accessibili dalla classe stessa e dalle classi derivate.

- Information Hiding: Principio dell'ingegneria del software implementato rendendo privati i dati membro e fornendo accesso ad essi solo tramite funzioni pubbliche (getter/setter). Previene modifiche incontrollate allo stato interno.

## Funzioni Inline e Offline
- `Inline`: La parola chiave inline suggerisce al compilatore di sostituire la chiamata a funzione direttamente con il codice della funzione stessa, eliminando l'overhead del salto in memoria. Tipicamente usato per funzioni molto brevi (es. **getter**). Le funzioni definite interamente all'interno della dichiarazione della classe sono implicitamente inline.

- `Offline` (Out-of-line): La funzione viene dichiarata all'interno della classe ma definita all'esterno utilizzando l'operatore di risoluzione dello scope (::).

## Costruttori e Definizione dell'Oggetto

Il costruttore è una funzione membro speciale invocata automaticamente al momento dell'istanziazione di un oggetto. Ha lo stesso nome della classe e non ha tipo di ritorno.

- **Costruttore di Default**: Non accetta parametri.

- **Costruttore Parametrizzato**: Accetta parametri per inizializzare l'oggetto con valori specifici.

```C++
class Punto {
public:
    Punto();          // Default
    Punto(int x);     // Parametrizzato
};
```

## Distruttore
Un metodo speciale invocato automaticamente quando l'oggetto esce dal suo scope o viene distrutto tramite delete. Serve a rilasciare le risorse acquisite dall'oggetto (es. memoria dinamica, file aperti). Il nome è preceduto da una tilde ~.
```C++
~Punto();
```

## Qualificatore `const`
Applicato ai metodi di una classe (inserito dopo la lista dei parametri), il qualificatore `const` garantisce a livello di compilazione che la funzione non modificherà alcuno dei dati membro dell'oggetto.

```C++
int getX() const;
```
## Membri Statici
I membri dichiarati con `static` appartengono alla classe nel suo complesso, non alle singole istanze.

- **Dati statici**: Esiste una sola copia della variabile condivisa tra tutti gli oggetti di quella classe.

- **Funzioni statiche**: Possono essere richiamate senza istanziare un oggetto (usando NomeClasse::Metodo()) ma possono accedere solo a dati membro statici.

## Sovraccaricamento degli Operatori
Permette di ridefinire il comportamento degli operatori standard (es. `+`, `==`, `<<`) quando applicati ai tipi di dato definiti dall'utente (classi). Non è possibile creare nuovi operatori, ma solo sovraccaricare quelli esistenti.

```C++
class Punto {
private:
    int x;
    int y;

public:
    // Costruttore con argomenti di default
    Punto(int x = 0, int y = 0) : x(x), y(y) {}

    // 1. Sovraccaricamento dell'operatore + (Metodo della classe)
    // Passiamo 'altro' per const reference per evitare copie inutili e non modificarlo.
    // Il metodo stesso è 'const' perché sommare due punti non modifica il punto originale.
    Punto operator+(const Punto& altro) const {
        return Punto(this->x + altro.x, this->y + altro.y);
    }

    // 2. Sovraccaricamento dell'operatore == (Metodo della classe)
    bool operator==(const Punto& altro) const {
        return (this->x == altro.x) && (this->y == altro.y);
    }

    // 3. Sovraccaricamento dell'operatore << (Funzione Friend esterna)
    // Viene dichiarata friend perché l'operatore << appartiene alla classe ostream,
    // ma ha bisogno di accedere ai membri privati 'x' e 'y' di Punto.
    friend std::ostream& operator<<(std::ostream& os, const Punto& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os; // Restituiamo lo stream per permettere concatenazioni (es. cout << p1 << p2)
    }
};
```

## `Friend` e incapsulamento
La parola chiave `friend` consente a una funzione esterna o a un'intera classe di accedere ai membri `private` e `protected` della classe in cui la dichiarazione `friend` appare. Costituisce un'eccezione intenzionale all'incapsulamento.protected

## Gestione delle Eccezioni
Meccanismo per intercettare e gestire gli errori a runtime (anomalie) deviando il normale flusso di esecuzione.

- `throw`: Segnala il verificarsi di un'eccezione.

- `try`: Delimita un blocco di codice in cui potrebbe verificarsi un'eccezione.

- `catch`: Cattura l'eccezione lanciata dal blocco `try` corrispondente e definisce la logica di gestione dell'errore.

## Ereditarietà

Meccanismo che permette di creare una nuova classe (Derivata) partendo da una classe esistente (Base), ereditandone attributi e metodi.

- **Livelli di accesso nell'ereditarietà**:

    - `public`: I membri `public` della base restano `public`, i `protected` restano `protected`.

    - `protected` / `private`: Restringono l'accesso dei membri ereditati nella classe derivata.

- **Costruttori e distruttori**: Alla creazione di un oggetto derivato, viene prima eseguito il costruttore della Base, poi quello della Derivata. Alla distruzione, l'ordine si inverte: prima il distruttore della Derivata, poi quello della Base.

- **Override vs. Overload**:

    - **Overload**: Stesso nome, firma diversa, stessa classe (o scope).

    - **Override**: Stessa firma (nome, argomenti e tipo di ritorno), ma ridefinito nella classe derivata per sovrascrivere il comportamento della classe base.

- Principio di Sostituzione di Liskov (LSP): Un oggetto della classe derivata deve poter essere utilizzato ovunque sia richiesto un oggetto della classe base, garantendo la coerenza del programma senza necessità di conoscere l'effettivo tipo derivato.

- Binding Statico vs Dinamico: Il binding (collegamento tra la chiamata a funzione e il codice da eseguire) è statico se risolto dal compilatore (early binding). È dinamico se risolto a runtime in base al tipo effettivo dell'oggetto (late binding).


## Funzioni Virtuali
Metodi dichiarati con la parola chiave `virtual` nella classe base. Indicano al compilatore di utilizzare il Binding Dinamico. Quando viene chiamata una funzione virtuale tramite un puntatore o riferimento alla classe base, il C++ determina a runtime l'implementazione corretta da eseguire (della base o della derivata) consultando la V-Table (Virtual Table).

## Classi Astratte
Una classe si definisce astratta se contiene almeno una funzione virtuale pura (indicata con `= 0`). Una classe astratta non può essere istanziata direttamente; serve esclusivamente come interfaccia o classe base per definire un contratto che le classi derivate devono implementare (eseguendo l'override delle funzioni pure).

## Template (Funzioni e Classi)
I template sono la base della programmazione generica in C++. Permettono di scrivere logica indipendente dal tipo di dato su cui si opera, demandando al compilatore la generazione del codice specifico per i tipi effettivamente utilizzati.

- Template di Funzione: Una singola definizione logica che può operare su diversi tipi di dati (es. una funzione di swap).

- Template di Classe: Permette di definire strutture dati (es. un vettore o una lista) generiche, specificando il tipo degli elementi solo al momento dell'istanziazione.

```C++
template <typename T>
T max(T a, T b);
```