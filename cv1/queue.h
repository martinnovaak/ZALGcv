#ifndef CV1_QUEUE_H
#define CV1_QUEUE_H

namespace ll {
    // dopredna deklarace sablonove tridy queue
    template <typename T> class queue;
}

template <typename T>
class ll::queue{
private:
    // deklarace struktury node - prvek
    // nachazi se v private casti tridy, protoze nechceme aby o deklaraci vedeli jini uzivatele
    struct node{
        T data;
        node * next;
    };
public:
    // konstruktor tridy, pri vytvoreni instance chceme aby headpointer i tailpointer ukazovali na nullptr
    queue()
    {
        head = tail = nullptr;
        length = 0;
    }

    // alternativne muzeme napsat to same nasledovne:
    // queue() : head(nullptr), tail(nullptr), length(0) {}

    // destruktor, pri zaniku instance chceme uvolnit vsechnu dynamicky alokovanou pamet
    ~queue()
    {
        while(!empty())  // Dokud neni spojovy seznam (fronty),
        {
            pop();       // mazeme prvky.
        }
    }

    // metoda pro vlozeni prvku do fronty
    // prvek vlozime na konec spojoveho seznamu (fronty)
    void push(T value)
    {
        // vytvorime novy prvek s hodnotou value, ukazatel na dalsi prvek bude ukazovat na nullptr, protoze prvek bude na konci seznamu
        node * pom = new node{value, nullptr};
        if(length != 0) // neni-li seznam prazdny -> je novy prvek nasledujici prvek ocasu
        {
            tail->next = pom;
        }
        else  // je-li delka seznamu 0, vkladame prvek na zacatek seznamu - tedy novy prvek == hlava
        {
            head = pom;
        }
        tail = pom; // novy prvek bude nove ocasem
        length++;
    }

    // pop smaze prvni prvek ze seznamu (fronty)
    void pop()
    {
        if(empty()) // pokud je fronta prazdna nic nemaz
            return;
        length--;
        node * pom = head;
        head = head->next; // posun headpointer
        delete pom;        // smaz mazany prvek
    }

    // funkce vrati hodnotu v "prvnim" prvku
    T& top()
    {
        return head->data;
    }

    // metoda, ktera vrati pocet prvku seznamu (fronty)
    unsigned int size()
    {
        return length;
    }

    // metodu vracejici booleovskou promennou, jestli je seznam (fronta) prazdna
    bool empty()
    {
        return length == 0;
    }

private:
    node * head; // ukazatel na prvni prvek
    node * tail; // ukazatel na posledni prvek
    unsigned int length; // pocet prvku
};


#endif //CV1_QUEUE_H
