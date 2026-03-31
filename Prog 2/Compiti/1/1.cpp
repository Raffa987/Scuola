#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

class Frutto
{
private:
    string nome;
    string colore;
    string stagione;

public:
    // costruttore
    Frutto(string n, string c, string s)
    {
        nome = n;
        colore = c;
        stagione = s;
    }

    // gets
    string getNome() const { return nome; }
    string getColore() const { return colore; }
    string getStagione() const { return stagione; }

    // stampa
    virtual void stampa() const
    {
        cout << nome << " - " << colore << " - " << stagione << " - " << sapore() << endl;
    }

    virtual string sapore() const = 0;
    virtual ~Frutto() {};
};

class Mela : public Frutto
{
private:
    string sapore_mela;

public:
    Mela(string n, string c, string s, string sap) : Frutto(n, c, s), sapore_mela(sap) {}

    string sapore() const override
    {
        return sapore_mela;
    }
};

class Arancia : public Frutto
{
private:
    string sapore_arancia;

public:
    Arancia(string n, string c, string s, string sap) : Frutto(n, c, s), sapore_arancia(sap) {}

    string sapore() const override
    {
        return sapore_arancia;
    }
};

template <typename T>
class Coda
{
private:
    struct Nodo
    {
        T valore;
        Nodo *successivo;

        Nodo(T v) : valore(v), successivo(nullptr) {}
    };

    Nodo *testa;
    Nodo *coda;
    int dimensione;

public:
    Coda()
    {
        testa = nullptr;
        coda = nullptr;
        dimensione = 0;
    }

    void enqueue(T elemento)
    {
        Nodo *nuovo = new Nodo(elemento);

        if (isEmpty())
        {
            testa = nuovo;
            coda = nuovo;
        }
        else
        {
            coda->successivo = nuovo;
            coda = nuovo;
        }
        dimensione++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw runtime_error("Errore: impossibile eseguire dequeue su una lista vuota.");
        }
        Nodo *tmp = testa;
        T val = testa->valore;

        testa = testa->successivo;
        if (testa == nullptr)
        {
            coda = nullptr;
        }

        delete tmp;

        dimensione--;
        return val;
    }

    bool isEmpty() const{ return dimensione == 0; }

    T front() const{
        if(!isEmpty()){
            return testa->valore;
        } else {
            throw runtime_error("Errore: impossibile chiamare front su una lista vuota.");
        }
    }

    void stampa(){
        Nodo* temp = testa;
        while(temp != nullptr) {
            temp->valore->stampa();

            temp = temp->successivo;
        }
    }

    ~Coda()
    {
        while (!isEmpty())
            dequeue();
    }
};

int rimuoviFrutti(Coda<Frutto*>& c, string tipo){
    if(c.isEmpty()){
        return 0;
    }

    Frutto* f = c.dequeue();

    int rimossi = rimuoviFrutti(c, tipo);

    bool daRimuovere = false;

    if(tipo == "Mela"){
        Mela *m = dynamic_cast<Mela*>(f);
        if(m != nullptr){
            daRimuovere = true;
        }
    } else if (tipo == "Arancia"){
        Arancia *a = dynamic_cast<Arancia*>(f);
        if(a != nullptr){
            daRimuovere = true;
        }
    }

    if(daRimuovere){
        delete f;
        return rimossi + 1;
    } else {
        c.enqueue(f);
        return rimossi;
    }
}

void flipQueue(Coda<Frutto*>& c){
    if(c.isEmpty()){
        return;
    }

    Frutto* f = c.dequeue();

    flipQueue(c);

    c.enqueue(f);
}

int main(){
    Coda<Frutto*> mia_coda;

    mia_coda.enqueue(new Mela("Granny Smith", "Verde", "Autunno", "Aspro"));
    mia_coda.enqueue(new Arancia("Tarocco", "Arancione", "Inverno", "Dolce"));
    mia_coda.enqueue(new Mela("Golden Delicious", "Giallo", "Autunno", "Dolce"));
    mia_coda.enqueue(new Arancia("Navel", "Arancione", "Inverno","Dolce-Acido"));
    mia_coda.enqueue(new Mela("Fuji", "Rosso", "Autunno", "Dolce"));
    mia_coda.enqueue(new Arancia("Valencia", "Arancione", "Estate", "Acido" ));

    string fruttiDaRimuovere;

    cout << "Inserisci il tipo di frutta da rimuovere: ";
    cin >> fruttiDaRimuovere;

    if(fruttiDaRimuovere != "Arancia" && fruttiDaRimuovere != "Mela") {
        throw runtime_error("Erorre: è possibile rimuovere solo \"Arancia\" o \"Mela\"");
    }

    int fruttiRimossi = rimuoviFrutti(mia_coda, fruttiDaRimuovere);
    flipQueue(mia_coda);

    cout << "Sono stati rimossi " << fruttiRimossi << " frutti dalla coda."<< endl;
    cout << "Frutti rimanenti nella coda:"<< endl;
    mia_coda.stampa();
}