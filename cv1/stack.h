#ifndef CV1_STACK_H
#define CV1_STACK_H

// pouzil jsem jmenny prostor, aby mi nevznikl konflikt s std::stackem
namespace ll {
    // teto prazdne deklaraci, kde rikam pouze to, ze nekde dal bude nasledovat trida stack
    // se rika dopredna deklarace
    template <typename T> class stack;
}

// Zasobnik implementovany pres jednosmerne zretezeny seznam
template <typename T> // trida bude sablonova, cely radek lze nahradit prikazem // using T = int;
class ll::stack{
private:
    // struktura node predstavujici prvek zasobniku je private, protoze nechci, aby uzivatel mohl vytvaret instance dane struktury
    struct node{
       T data;
       node * next;
    };
public:
    stack() {
        head = nullptr;
        length = 0;
    }

    // destruktor ma za ukol smazat veskerou dynamicky alokovanou pamet
    ~stack() {
        while(!empty()) {
            pop();
        }
    }

    // metoda push vlozi prvek na konec zasobniku - v nasem pripade na zacatek seznamu
    void push(T value) {
        length++;
        node * pom = new node{value, head};
        head = pom;
    }

    // metoda pop odstrani prvek z konce zasobniku - v nasem pripade ze zacatku seznamu
    void pop() {
        length--;
        node * pom = head;
        head = head->next;
        delete pom;
    }

    // metoda top vrati referenci na hodnotu posledniho prvku zasobniku - v nasem pripade hodnotu prvniho prvku seznamu
    T& top() {
        return head->data;
    }

    // metoda, ktera vrati pocet prvku zasobniku
    unsigned int size() {
        return length;
    }

    // metoda ktera vrati informaci, zda-li je zasobnik prazdny
    bool empty() {
        return length == 0;
    }

private:
    node * head;
    unsigned int length;
};

//_______________________________________________________________________________________

// jmenny prostor zasobniku implementovanyho pres automaticky se zvetsujici dynamicke pole (vektor)
namespace vec {
    template <typename T> class stack;
}

// Zasobnik implementovany pres vektor
template <typename T>
class vec::stack {
public:
    // konstruktor
    stack() {
        data = new T[8];
        length = 0;
        capacity = 8;
    }

    // destruktor dealokuje dynamicky alokovanou pamet
    ~stack() {
        delete[] data;
    }

    // metoda push vlozi prvek na konec zasobniku - v nasem pripade na "konec" (za posledni prvek v poli) dynamickeho pole
    void push(T value) {
        if(length == capacity) {
            grow();
        }
        data[length] = value;
        length++;
    }

    // metoda pop "smaze" posledni prvek ze zasobniku - staci snizit delku pole
    void pop() {
        length--;
    }

    // metoda top vraci hodnotu posledniho prvku - tedy prvku na indexu length - 1
    T& top() {
        return data[length-1];
    }

    // metoda size vrati pocet prvku zasobniku
    unsigned int size() {
        return length;
    }

    // metoda empty vraci informaci, zda-li je zasobnik prazdny
    bool empty() {
        return length == 0;
    }
private:
    T * data; // dynamicke pole
    unsigned int length; // pocet prvku zasobniku
    unsigned int capacity; // velikost alokovaneho pole

    // Metoda, ktera je volana v pripade zaplneni dynamicky alokovaneho pole
    // metoda vytvori nove pole o 2nasobne velikosti
    // prekopiruje prvky ze stareho pole do noveho
    // smaze stare pole a nove nastavi jako aktualni pole
    void grow() {
        capacity *= 2;
        T * new_data = new T[capacity];
        for(unsigned int i = 0; i < length; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
};

#endif //CV1_STACK_H
