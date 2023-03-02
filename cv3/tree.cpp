#include "tree.h"
#include <iostream>
#include <iomanip> // kvuli std::setw, std::right
#include <queue>   // pouzito v metodach height() a wide_print()
#include <stack>   // pouzito v metode print_with_stack()
// Konstruktor
// Nastavi ukazatel na koren na nullptr
tree::tree()
{
    root = nullptr;
}

// Destruktor
// Zavola rekurzivni metodu pro odstraneni vrcholu ze stromu
tree::~tree()
{
    clear(root);
}

// Rekurzivni metoda na vymazani prvku z podstromu
// POSTUP:
// 1) Je-li podstrom prazdny -> ukonci rekurzi
// 2) Vymaz prvky z leveho podstromu (aktualniho podstromu)
// 3) Vymaz prvky z praveho podstromu (aktualniho podstromu)
// 4) Odstran koren aktualniho podstromu
void tree::clear(vertex * branch)
{
    if(branch == nullptr)
        return;

    clear(branch->left);
    clear(branch->right);
    delete branch;
}

// strom je prazdny, pokud koren je nullptr
bool tree::empty()
{
    return root == nullptr;
}

// Vlozeni vrcholu do stromu
// metoda jednoduse najde spravne misto kam prvek patri
// existuje-li dany prvek jiz ve strome ==> prvek nelze do stromu vlozit
// neexistuje-li pak metoda na dane misto vlozi novy prvek
// Metoda vraci false, pokud se prvek nepovede do stromu vlozit, jinak vraci true
bool tree::insert(T key)
{
    if (empty())    // je-li seznam prazdny ==> prvek je novym korenem stromu
    {
        root = new vertex(key, nullptr);
        return true;
    }

    vertex * curr = root; // aktualne prochazeny vrchol
    while(true) // Opakuj
    {
        if(key == curr->key) return false; // existuje-li vrchol s danym klicem ve strome
        else if(key < curr->key) // je-li vkladany klic mensi nez klic aktualniho prvku
        {
            if(curr->left == nullptr) { // nema-li aktualni vrchol leveho syna
                curr->left = new vertex(key, curr);
                return true;
            }
            curr = curr->left; // jinak prejdi (navstiv) do leveho podstromu
        }
        else // je-li vkladany klic vetsi nez klic aktualniho prvku
        {
            if(curr->right == nullptr) { // nema-li aktualni vrchol praveho syna
                curr->right = new vertex(key, curr);
                return true;
            }
            curr = curr->right; // jinak prejdi (navstiv) do praveho podstromu
        }
    }
    //return insert_recursively(root, key);  // 2)
}

// REKURZIVNI VLOZENI VRCHOLU DO PODSTROMU
// POSTUP:
// 1A) Je-li hodnota korene podstromu rovna hodnote vkladaneho prvku -> prvek se jiz ve strome nachazi
//          ->return false (vrchol neni mozne do stromu vlozit)         (1. PODMINKA UKONCENI REKURZE)
// 1B) Je-li hodnota korene podstromu vetsi nez hodnota vkladaneho prvku
//       1Ba) Ma-li koren podstormu levy podstrom -> vloz prvek do leveho podstromu (REKURZE)
//       1Bb) Jinak je-li levy podstrom prazdny -> vytvor novy prvek a nastav jej jako leveho syna korene podstromu a vrat true (KONEC REKURZE)
// 1C) Je-li hodnota korene podstromu mensi nez hodnota vkladaneho prvku
//       1Ca) Ma-li koren podstromu praveho podstrom -> vloz prvek do praveho podstromu (REKURZE)
//       1Cb) Jinak je-li pravy podstrom prazdny -> vytvor novy prvek a nastav jej jako praveho syna korene podstromu a vrat true (KONEC REKURZE)
bool tree::insert_recursively(vertex *branch, T key)
{
    if(branch->key == key) // 1A)
    {
        return false;
    }
    else if(branch->key > key) // 1B)
    {
        if(branch->left != nullptr) // 1Ba)
            return insert_recursively(branch->left, key);

        branch->left = new vertex(key, branch); // 1Bb)
    }
    else
    {
        if(branch->right != nullptr) // 1Ca)
            return insert_recursively(branch->right, key);

        branch->right = new vertex(key, branch); // 1Cb)
    }
    return true;
}

// Iterativni metoda pro nalezeni vrcholu s klicem key
tree::vertex * tree::find(T key)
{
    //return find_recursively(root, key); // rekurzivní volání

    vertex * curr = root; // aktualne navstiveny vrchol

    while(curr != nullptr) // dokud neni aktualne navstiveny vrchol nullptr
    {
        if(key == curr->key) break; // je-li aktualne prochazeny vrchol hledanym vrcholem ==> konec
        else if(key < curr->key) curr = curr->left; // ma-li hledany vrchol vyssi klicovou hodnotu ==> prejdi do leveho podstromu
        else curr = curr->right; // ma-li hledany vrchol mensi klicovou hodnotu ==> prejdi do praveho podstromu
    }
    return curr; // vrat posledne naavstiveny vrchol
}

// Rekurzivni metoda find ma za ukol v podstrome branch najit vrchol s klicem key
// Postup:
// 1) Je-li podstrom prazdny -> ve strome se vrchol s hodnotou key nenachazi ->return nullptr a KONEC (1. podminka ukonceni rekurze)
// 2a) Je-li koren podstromu hledany prvek -> vrat koren podstromu                                    (2. podminka ukonceni rekurze)
// 2b) Je-li klic korene podstromu vetsi nez klic hledaneho vrcholu -> najdi prvek v levem podstrome (REKURZE)
// 2c) Je-li klice korene podstromu mensi nez klic hledaneho vrcholu -> najdi prvek v pravem podstrome (REKURZE)
tree::vertex * tree::find_recursively(vertex * branch, T key)
{
    if(branch == nullptr) return nullptr;   // 1)

    if(branch->key == key) // 2a)
    {
        return branch;
    }
    else if(branch->key > key) // 2b)
    {
        return find_recursively(branch->left, key);
    }
    else    // 2c)
    {
        return find_recursively(branch->right, key);
    }
}

// Funkce na smazani prvku ze stromu
// Postup:
// 1) najdi prvek s klicem key a uloz jej do promenne pom
// 2) nenachazi-li se vrchol ve strome -> return false a KONEC
// 3a) Ma-li mazany vrchol dva potomky -> zavolej metodu remove_with_two(pom)
// 3b) Ma-li mazany vrchol pouze jednoho potomka -> zavolej metodu remove_with_one(pom)
// 3c) Je-li mazany vrchol listem -> zavolej metodu remove_leaf(pom)
// 4) return true (vrchol byl uspesne smazan)
bool tree::remove(T key)
{
    vertex * pom = find(key); // 1)
    if(pom == nullptr)         // 2)
        return false;

    if(pom->left != nullptr && pom->right != nullptr) // 3a)
    {
        remove_with_two(pom);
    }
    else if(pom->left != nullptr || pom->right != nullptr) // 3b)
    {
        remove_with_one(pom);
    }
    else    // 3c)
    {
        remove_leaf(pom);
    }
    return true; // 4)
}

// Odstraneni listu ze stromu
// POSTUP:
// 1A) Je-li mazany list - korenem bude strom prazdny -> nastav ukazatel na koren na nullptr
// 1B) Jinak:
//      1Ba) byl-li mazany prvek levym synem rodice, bude nove levy syn rodice nullptr
//      1Bb) symetricky pro praveho syna
// 2) smaz list
void tree::remove_leaf(vertex *leaf)
{
    if(leaf->parent == nullptr)
        root = nullptr;
    else
    {
        vertex* father = leaf->parent;
        if(leaf == father->left)
            father->left = nullptr;
        else
            father->right = nullptr;
    }

    delete leaf;
}

// Vylepsena metoda rekurzivniho smazani prvku s jednim potomkem
// POSTUP:
// 1) do promenne father uloz rodice mazaneho vrcholu
// 2)  do promenne child uloz (toho) jednoho potomka mazaneho vrcholu
// 3A) Je-li mazany prvek korenem (otec je nullptr) pak child je novym korenem stromu
// 3B) Jinak:
//      3Ba) Je-li mazany vrchol (pom) levym synem otce pak dite bude novym levym synem otce
//      3bb) Jinak je-li mazany vrchol pravym synem otce tak dite bude novym pravym synem otce
// 4) rodic ditete bude nove otec mazaneho prvku
// 5) smaz mazany prvek
void tree::remove_with_one(vertex *pom)
{
    vertex * father = pom->parent; // 1)
    vertex * child = (pom->left == nullptr) ? pom->right : pom->left; // 2)

    if(father == nullptr)  // 3A)
    {
        root = child;
    }
    else    // 3B)
    {
        if(father->left == pom) // 3Ba)
        {
            father->left = child;
        }
        else // 3Bb)
        {
            father->right = child;
        }
    }

    child->parent = father; //  4)
    delete pom; // 5)
}

// metoda, ktera smaze prvek pom, ktery je argumentem metody
// prvek pom ma dva potomky
// Prvek mazeme nasledujicim zpusobem:
// 1) swap_vertex := nejvetsi_prvek_v_levem_podstrome(pom)
// 2) prohodime hodnoty swap_vertex a pom
// 3a) Pokud ma prvek leveho potomka -> smaz_prvek_s_jednim_potomkem(pom)
// 3b) Jinak ->smaz_list(pom)
void tree::remove_with_two(vertex *pom)
{
    vertex * swap_vertex = max(pom->left); // 1)
    pom->key = swap_vertex->key; // 2)

    if(swap_vertex->left != nullptr) // 3a)
        remove_with_one(swap_vertex);
    else    // 3b)
        remove_leaf(swap_vertex);
}

// metoda vrati prvek s nejvetsi hodnotou v danem podstrome
// nejvetsi prvek se z logiky binarnich vyhledavacich podstromu nachazi v "nejpravejsim" prvku stromu
// princip vyhledani nejpravejsiho prvku podstromu je snadny:
// 1) Ulozim si koren podstromu do pomocne promenne
// 2) Dokud ma pomocna promenna praveho syna -> posun pomocny prvek doprava: pom = pom->pravy_syn
// 3) V pomocnem prvku se nachazi nejpravejsi vrchol stromu
tree::vertex * tree::max(vertex * branch)
{
    vertex * pom = branch; // 1)

    // 2)
    while(pom->right != nullptr)
        pom = pom->right;

    return pom; // 3)
}

// metoda pro nalezeni nejmensiho vrcholu podstromu branch
// jedna se o symetricky algoritmus metody tree::max
// metoda vrati nejlevejsi prvek v danem podstromu
tree::vertex * tree::min(vertex * branch)
{
    vertex * pom = branch;

    while(pom->left != nullptr)
        pom = pom->left;

    return pom;
}

// metoda volajici rekurzivni vypis stromu
void tree::print()
{
    print_recursively(root);
    std::cout << std::endl;
}

// rekurzivni jednoradkovy inorder vypis stromu
void tree::print_recursively(vertex * branch)
{
    if(branch == nullptr) // podminka ukonceni rekurze
        return;

    print_recursively(branch->left); // vypis levy podstrom
    std::cout << branch->key << ", ";      // pak vypis aktualni vrchol
    print_recursively(branch->right);// a nakonec vypis pravy podstrom
}

// jednoradkovy vypis stromu pouzivajici zasobnik na misto rekurze
void tree::print_with_stack()
{
    std::stack<vertex *> s; // zasobnik rodicovskych vrcholu
    vertex * curr = root;   // pomocna promenna pro aktualne prochazeny prvek

    while(curr != nullptr || !s.empty()) // Opakuj dokud aktualni prvek neni nullptr a zasobnik neni prazdny
    {
        // pujdeme co nejhloubeji do leve vetve a vrcholy po ceste si budeme postupne ukladat do zasobniku
        // po vypisu nejlevejsich prvku se zase budeme postupne vracet zpet k ulozenym prvkum vetve a budeme vypisovat jejich
        // prave podstromy
        while (curr != nullptr) // Dokud aktualni prvek neni nullptr
        {
            s.push(curr); // uloz vsechny vrcholy na ceste k nejlevejsimu vrcholu do zasobniku
            curr = curr->left;
        }
        // neexistuje-li jiz zadny "levejsi" vrchol
        curr = s.top(); s.pop(); // vezmi posledni vlozeny vrchol do zasobniku
        std::cout << curr->key << ", "; // a vypis jej
        curr = curr->right; // a navstiv jeho pravy podstrom
    }
    std::cout << std::endl;
}

// Iterativni zpusob vypisu stromu
// Zpusob bez pouziti rekurze a zasobniku ==> prostorova slozitost algoritmu je T(1)
void tree::print_iteratively()
{
    if(empty())
        return;

    // zacneme od nejmensiho vrcholu stromu
    vertex* curr = min(root);

    // dokud aktualne prochazeny prvek neni nullptr
    while(curr)
    {
        std::cout << curr->key << ", "; // vypis aktualni prvek
        if(curr->right) { // ma-li aktualni prvek pravy podstrom pak:
            curr = min(curr->right); // prejdi do nejmensiho prvku praveho podstromu
        } else { // nema-li aktualni vrchol pravy podstrom pak:
            // pak prejdi k prvnimu rodicovskemu prvku, u nehoz jsme jeste nevypsali pravy podstrom
            vertex * father = curr->parent;
            while(father != nullptr && curr == father->right)
            {
                curr = father;
                father = curr->parent;
            }
            curr = father;
        }
    }
    std::cout << std::endl;
}


/*
    Metoda na vypocteni vysko binarniho stromu
    Metoda vraci vysku. (usnigned int)
    Vyska stromu je delka nejdelsi cesty z korene k listu.
    Metoda pouziva metodu prohledavani do sirky (BFS)
*/
unsigned int tree::height()
{
    if(empty()) return 0; // vyska prazdneho stromu je 0

    // pomocne promenne:
    vertex * curr = root;  // ukazatel na aktualne navstiveny prvek
    std::queue<vertex *> q;// fronta, v ktere je ulozen i-te patro (uroven) stromu
    unsigned int h = 0;    // aktualne navstivene patro

    q.push(root);

    while(!q.empty())   // Opakuj dokud neni fronta prazdna
    {
        int level_size = q.size(); // pocet prvku na h-te urovni
        for(int i = 0; i < level_size; i++) // pro kazdy prvek na h-te urovni udelej:
        {
            // prvek vyjmi z fronty
            curr = q.front();
            q.pop();
            // a jeho syny vloz do fronty
            if(curr->left)
                q.push(curr->left);
            if(curr->right)
                q.push(curr->right);
        }
        h++; // prejdi na novou uroven (zvys h o 1)
    }
    return h; // vrat pocet navstivenych urovni (pocet navstivenych urovni == vyska stromu)
}


void tree::wide_print()
{
    unsigned int h = height(); // Vypocti vysku stromu
    unsigned int space = (1 << (h - 1)); // mezera pred a za kazdym prvkem je 2^(h-1)
    std::queue<vertex *> q; // Fronta na uchovavani jednotlivych urovni stromu
    q.push(root);        // vloz 1. uroven do stromu
    vertex * curr;          // pomocna promenna ukazujici na aktualni vypisovany prvek

    for(unsigned int i = 1; i <= h; i++) // Projdi vsech h pater
    {
        unsigned int level_size = q.size(); // velikost i-te urovne - (slo by i jinak protoze delame siroky vypis, ale lookup na q.size() je O(1) takze neni potreba rucne pocitat)
        for(unsigned int j = 0; j < level_size; j++) // Projdi vsech k prvku na patre
        {
            // postupne vyjmi kazdy prvek z i-teho patra
            curr = q.front();
            q.pop();
            //
            std::cout << std::setw(space * 2) << std::right; // cislo kterym nasobime space je maximalni pocet cislic klice
            if(curr) { // existuje-li aktualni prvek
                // vloz jeho syny do frontu (do dalsiho patra)
                 q.push(curr->left);
                 q.push(curr->right);
                 // a vypis jeho klic
                 std::cout << curr->key;
            } else { // neexistuje-li aktualni prvek (prvek je nullptr)
                // vloz do fronty jako jeho syny zase nullptr
                 q.push(nullptr);
                 q.push(nullptr);
                 // Vypis mezeru misto jeho hodnoty
                 std::cout << "  "; // lze prepsat na "xx" a bude na miste chybejiciho vrcholu psat "xx"
            }
            // vynech zase mezeru za prvkem
            std::cout << std::setw(space * 2) << " "; // cislo kterym nasobime space je maximalni pocet cislic klice
        }
        space /= 2; // zmensi mezeru na dalsi urovni na polovinu
        std::cout << std::endl; // prejdi na novy radek
    }
    std::cout << std::endl;
}