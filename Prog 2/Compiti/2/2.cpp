#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Dipendente {
    private:
    string codiceFiscale;
    string dataNascita;

    public:
    Dipendente(const string &CF, const string &d): codiceFiscale(CF), dataNascita(d){}

    string get_codiceFiscale() const {
        return codiceFiscale;
    }

    string get_dataNascita() const{
        return dataNascita;
    }

    void set_codiceFiscale(const string &codice){
        codiceFiscale = codice;
    }

    void set_dataNascita(const string &data){
        dataNascita = data;
    }

    friend ostream& operator<<(ostream &os, const Dipendente &d){
        os << "Dipendente[CF: " << d.codiceFiscale << ", Nato il: " << d.dataNascita << "]";
        return os;
    }

    ~Dipendente() = default;
};

class DipendenteOccasionale: public Dipendente{
    private:
    int trimestri;
    int pagaExtra;

    public:
    DipendenteOccasionale(const string &CF, const string &d, int t, int px): Dipendente::Dipendente(CF, d), pagaExtra(px), trimestri(t){}

    int get_trimestri() const {
        return trimestri;
    }

    int get_pagaExtra() const{
        return pagaExtra;
    }

    void set_trimestri(int t){
        trimestri = t;
    }

    void set_pagaExtra(int px){
        pagaExtra = px;
    }

    friend ostream& operator<<(ostream& os, DipendenteOccasionale &d){
        os << static_cast<const Dipendente &>(d);
        os << "[Trimestri: " << d.trimestri << ", paga extra: " << d.pagaExtra << "]";
        return os;
    }

};

class Azienda{
    private:
    string pIva;
    string nome;

    Dipendente** dipendenti;
    int maxDipendenti;
    int numeroDipendenti;

    public:
    Azienda(const string& pI, const string& n): pIva(pI), nome(n) {
        maxDipendenti = 100;
        dipendenti = new Dipendente*[maxDipendenti];
        numeroDipendenti = 0;
    }

    friend ostream& operator<<(ostream& os, const Azienda& a) {
        os << "Azienda: " << a.nome << "\nP. Iva: " << a.pIva;
        for(int i = 0; i < a.numeroDipendenti; i++){
            os << a.dipendenti[i] << endl;
        } 
    }

    void aggiungiDipendente(Dipendente* nuovo){
        if(numeroDipendenti > maxDipendenti){
            throw runtime_error("Errore: numero massimo di dipendenti raggiunto");
        }
        dipendenti[numeroDipendenti] = nuovo;
        numeroDipendenti++;
    }
};