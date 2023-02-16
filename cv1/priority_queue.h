#ifndef CV1_PRIORITY_QUEUE_H
#define CV1_PRIORITY_QUEUE_H

using T = int; // hodnota vkladana do prioritni fronty
using P = int; // priorita

class priority_queue
{
private:
    struct node{
        T data;
        node * next;
    };
public:
    // konstruktor tridy, pri vytvoreni instance chceme aby headpointer i tailpointer ukazovali na nullptr
    priority_queue()
    {
        head = tail = nullptr;
        length = 0;
    }

    // destruktor, pri zaniku instance chceme uvolnit vsechnu dynamicky alokovanou pamet
    ~priority_queue()
    {
        while(!empty())  // Dokud neni spojovy seznam (prioritni fronta) prazdny,
        {
            pop();       // mazeme prvky.
        }
    }

    // metoda pro vlozeni prvku do prioritni fronty
    // prvek vlozime do seznamu (prioritni fronty) na "spravne misto"
    // to znamena, ze nejvetsi prvky (prvky s nejvetsi prioritou) davame na zacatek seznamu (fronty)
    // a na konec fronty naopak vkladame prvky s nejmensi hodnotou
    void push(T value, P priority)
    {
        /*
         TODO
         */
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

#endif //CV1_PRIORITY_QUEUE_H
