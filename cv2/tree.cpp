#include "tree.h"

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
// 1) Je-li strom prazdny -> vytvor novy prvek a nastav jej jako koren
// 2) Jinak vloz vrchol rekurzivne do stromu root
bool tree::insert(T data)
{
    if (empty())    // 1)
    {
        root = new vertex(data, nullptr);
        return true;
    }

    return insert_recursively(root, data);  // 2)
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
    if(branch->data == key) // 1A)
    {
        return false;
    }
    else if(branch->data > key) // 1B)
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

// Metoda find zavola rekurzivni metodu find_recursively
tree::vertex * tree::find(T data)
{
    return find_recursively(root, data);
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

    if(branch->data == key) // 2a)
    {
        return branch;
    }
    else if(branch->data > key) // 2b)
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
// 1) najdi prvek s klicem data a uloz jej do promenne pom
// 2) nenachazi-li se vrchol ve strome -> return false a KONEC
// 3a) Ma-li mazany vrchol dva potomky -> zavolej metodu remove_with_two(pom)
// 3b) Ma-li mazany vrchol pouze jednoho potomka -> zavolej metodu remove_with_one(pom)
// 3c) Je-li mazany vrchol listem -> zavolej metodu remove_leaf(pom)
// 4) return true (vrchol byl uspesne smazan)
bool tree::remove(T data)
{
    vertex * pom = find(data); // 1)
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

// METODA NAPSANA NA CVICENI
// Metoda na mazani prvku pom s jednim potomkem
// Pouzivame nasledujici postup:
// 1a) Je-li vrchol pom koren (root) pak:
//      A) Ma-li pom leveho potomka -> levy potomek je novy koren && rodic (predek) leveho potomka je nove nullptr
//      B) Ma-li pom praveho potomka -> stejne akorat pro praveho
// 1b) Neni-li pom korenem pak:
//      2a) Je-li mazany vrchol levym synem rodice (otce)
//          levy potomek rodice je nove potomek mazaneho prvku && potomek mazaneho prvku ma jako rodice rodice mazaneho prvku
//      2b) Je-li mazany vrchol pravym synem rodice(otce)
//          symetricky
/*
void tree::remove_with_one(vertex *pom)
{
    vertex * father = pom->parent;
    if(father == nullptr) // 1a)
    {
        if(pom->left != nullptr) {
            root = pom->left;
            pom->left->parent = nullptr; // pom->left je novy koren -> jeho otec je, tudiz nullptr
        } else {
            root = pom->right;
            pom->right->parent = nullptr;// pom->right je novy koren -> jeho otec je, tudiz nullptr
        }
    }
    else
    {
        if(father->left == pom)
        {
            if(pom->left != nullptr) {
                father->left = pom->left; // pom->left->parent = father;
                pom->left->parent = father;
            } else {
                father->left = pom->right;
                pom->right->parent = father;
            }
        }
        else
        {
            if(pom->left != nullptr) {
                father->right = pom->left;
                pom->left->parent = father;
            } else {
                father->right = pom->right;
                pom->right->parent = father;
            }
        }
    }

    delete pom;
}
 */

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
    pom->data = swap_vertex->data; // 2)

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