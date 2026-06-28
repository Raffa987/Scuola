#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
#define MAX_SIZE 64

// ==========================================
// CLASSE ITEM E DERIVATE
// ==========================================
class item {
    protected:
        inline static int nextID = 1;

        string title;
        string publicationDate;
        int ID;
        bool isBorrowed;

    public:        
        item(string title_, string publicationDate_) :
        title(title_), publicationDate(publicationDate_) {
            ID = nextID++;
            isBorrowed = false;
        }

        virtual ~item() = default;

        // Getters
        string getTitle() const { return title; }
        string getPublicationDate() const { return publicationDate; }
        int getID() const { return ID; }
        bool getIsBorrowed() const { return isBorrowed; }

        // Setters per stato prestito
        void borrowItemAction() { isBorrowed = true; }
        void returnItemAction() { isBorrowed = false; }

        virtual void print() const = 0;
};

class book : public item {
    private:
        string author;
    public:
        book(string title_, string publicationDate_, string author_) : 
        item(title_, publicationDate_), author(author_) {}

        ~book() = default;

        string getAuthor() const { return author; }

        void print() const override {
            cout << "Book - " << title << " - " << author << " - " << ID << "\n";
        }
};

class DVD : public item {
    private:
        string duration;
    public:
        DVD(string title_, string publicationDate_, string duration_) : 
        item(title_, publicationDate_), duration(duration_) {}

        ~DVD() = default;

        string getDuration() const { return duration; }

        void print() const override {
            cout << "DVD - " << title << " - " << duration << " - " << ID << "\n";
        }
};

// ==========================================
// CLASSI UTENTE
// ==========================================
class user {
    protected:
        string name;
        string surname;
        item **borrowed;
        int size;

    public: 
        user(string name_, string surname_, int s) : name(name_), surname(surname_), size(s) {
            borrowed = new item*[size];
            for(int i = 0; i < size; i++) {
                borrowed[i] = nullptr;
            }
        }

        virtual ~user() {
            delete[] borrowed;
        }

        string getName() const { return name; }
        string getSurname() const { return surname; }
        int getSize() const { return size; }

        // Aggiunge un item all'array se c'è spazio
        bool addItem(item* ptr) {
            for(int i = 0; i < size; i++) {
                if(borrowed[i] == nullptr) {
                    borrowed[i] = ptr;
                    return true; // Aggiunto con successo
                }
            }
            return false; // Limite raggiunto
        }

        // Rimuove un item dall'array
        bool removeItem(int itemID) {
            for(int i = 0; i < size; i++) {
                if(borrowed[i] != nullptr && borrowed[i]->getID() == itemID) {
                    borrowed[i] = nullptr;
                    return true;
                }
            }
            return false; // Item non trovato
        }

        void printitems() const {
            cout << "Prodotti in prestito a " << name << " " << surname << ":\n";
            bool hasItems = false;
            for(int i = 0; i < size; i++) {
                if(borrowed[i] != nullptr) {
                    borrowed[i]->print();
                    hasItems = true;
                }
            }
            if (!hasItems) cout << "Nessun prodotto in prestito.\n";
            cout << "-----------------------\n";
        }
};

class Student: public user {
    public:
        Student(string name_, string surname_) : user(name_, surname_, 5) {}
        ~Student() = default;
};

class Professor: public user {
    public:
        Professor(string name_, string surname_) : user(name_, surname_, 10) {}
        ~Professor() = default;
};

// ==========================================
// CLASSE LIBRARY
// ==========================================
class Library {
    private:
        string name;
        item *inventory[MAX_SIZE];
        user *registeredUsers[MAX_SIZE];
        int itemCount;
        int userCount;

    public:
        Library(string name_) : name(name_), itemCount(0), userCount(0) {
            for(int i=0; i<MAX_SIZE; i++) {
                inventory[i] = nullptr;
                registeredUsers[i] = nullptr;
            }
        }

        // Metodi helper per popolare la libreria nel main
        void addItemToInventory(item* i) {
            if(itemCount < MAX_SIZE) {
                inventory[itemCount++] = i;
            }
        }

        int registerUser(user* u) {
            if(userCount < MAX_SIZE) {
                registeredUsers[userCount] = u;
                return userCount++; // Ritorna l'indice dell'array come ID utente
            }
            return -1;
        }

        void borrowitem(int itemID, int userID) {
            if (userID < 0 || userID >= userCount || registeredUsers[userID] == nullptr) {
                cout << "[ERRORE] Utente non trovato all'indice " << userID << ".\n";
                return;
            }

            user* currentUser = registeredUsers[userID];
            item* targetItem = nullptr;

            // Cerca l'item nell'inventario
            for(int i = 0; i < itemCount; i++) {
                if(inventory[i] != nullptr && inventory[i]->getID() == itemID) {
                    targetItem = inventory[i];
                    break;
                }
            }

            if (targetItem == nullptr) {
                cout << "[ERRORE] Prodotto con ID " << itemID << " non trovato nella libreria.\n";
                return;
            }

            if (targetItem->getIsBorrowed()) {
                cout << "[ATTENZIONE] Il prodotto '" << targetItem->getTitle() << "' e' gia' in prestito.\n";
                return;
            }

            // Tenta di assegnare il prodotto all'utente
            if (currentUser->addItem(targetItem)) {
                targetItem->borrowItemAction();
                cout << "[SUCCESSO] Prodotto '" << targetItem->getTitle() << "' prestato a " << currentUser->getName() << ".\n";
            } else {
                cout << "[RIFIUTATO] Limite prestiti (" << currentUser->getSize() << ") raggiunto per " << currentUser->getName() << ".\n";
            }
        }

        void returnitem(int itemID, int userID) {
            if (userID < 0 || userID >= userCount || registeredUsers[userID] == nullptr) {
                cout << "[ERRORE] Utente non trovato all'indice " << userID << ".\n";
                return;
            }
            
            user* currentUser = registeredUsers[userID];
            item* targetItem = nullptr;

            for(int i = 0; i < itemCount; i++) {
                if(inventory[i] != nullptr && inventory[i]->getID() == itemID) {
                    targetItem = inventory[i];
                    break;
                }
            }

            if (targetItem != nullptr && currentUser->removeItem(itemID)) {
                targetItem->returnItemAction();
                cout << "[SUCCESSO] Prodotto '" << targetItem->getTitle() << "' restituito da " << currentUser->getName() << ".\n";
            } else {
                cout << "[ERRORE] Impossibile restituire. Il prodotto non risulta in prestito a questo utente.\n";
            }
        }
};

// ==========================================
// METODO MAIN
// ==========================================
int main() {
    Library uniLibrary("Biblioteca Universitaria Centrale");

    // Creazione Prodotti
    book b1("C++ Programming", "2020-01-01", "Bjarne Stroustrup");
    book b2("Design Patterns", "1994-10-21", "Gang of Four");
    book b3("Clean Code", "2008-08-01", "Robert C. Martin");
    book b4("Effective C++", "2005-05-12", "Scott Meyers");
    book b5("Refactoring", "1999-07-08", "Martin Fowler");
    book b6("Code Complete", "2004-06-09", "Steve McConnell");
    DVD d1("The Matrix", "1999-03-31", "136 min");
    
    uniLibrary.addItemToInventory(&b1);
    uniLibrary.addItemToInventory(&b2);
    uniLibrary.addItemToInventory(&b3);
    uniLibrary.addItemToInventory(&b4);
    uniLibrary.addItemToInventory(&b5);
    uniLibrary.addItemToInventory(&b6);
    uniLibrary.addItemToInventory(&d1);

    // Creazione Utenti
    Student s1("Mario", "Rossi");
    Professor p1("Alan", "Turing");

    int idS1 = uniLibrary.registerUser(&s1);
    int idP1 = uniLibrary.registerUser(&p1);

    cout << "\n--- TEST PRESTITI ---\n";
    uniLibrary.borrowitem(b1.getID(), idP1); // Docente prende b1
    uniLibrary.borrowitem(d1.getID(), idS1); // Studente prende d1
    uniLibrary.borrowitem(b2.getID(), idS1); // Studente prende b2
    uniLibrary.borrowitem(b3.getID(), idS1); // Studente prende b3
    uniLibrary.borrowitem(b4.getID(), idS1); // Studente prende b4
    uniLibrary.borrowitem(b5.getID(), idS1); // Studente prende b5

    cout << "\n--- TEST LIMITE PRESTITI ---\n";
    // Lo studente ha un limite di 5. Cerchiamo di prestargli il 6° prodotto.
    uniLibrary.borrowitem(b6.getID(), idS1); 

    cout << "\n--- TEST RESTITUZIONE ---\n";
    uniLibrary.returnitem(b2.getID(), idS1); // Studente restituisce b2

    // Ora che ha restituito un libro, lo studente può prenderne un altro
    cout << "\n--- NUOVO PRESTITO DOPO RESTITUZIONE ---\n";
    uniLibrary.borrowitem(b6.getID(), idS1); 

    cout << "\n--- STAMPA PRODOTTI ATTUALMENTE IN PRESTITO ---\n";
    s1.printitems();
    p1.printitems();

    return 0;
}