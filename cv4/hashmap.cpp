#include <stdexcept>
#include <functional>
#include <iostream>
#include "hashmap.h"

// metoda pro zahesovani klice
unsigned int hashmap::hash_index(const Key & key) const
{
    std::hash<Key> hash_fun; // hesovaci fce
    return hash_fun(key) % number_of_buckets; // zahesuj klic a preved ho na index (pomoci modula)
}

// konstruktor
hashmap::hashmap(unsigned int nob)
{
    // parametr nob obsahuje pocet kybliku, kolik jich chceme alokovat
    this->number_of_buckets = nob;
    number_of_elements = 0;
    table.resize(number_of_buckets); // alokuj n kybliku
}

// metoda na vlozeni dvojice key-value do tabulky
void hashmap::insert(const Key &key, const Value &value)
{
    // zjisti, do ktereho kybliku patri klic
    unsigned int index = hash_index(key);
    auto & bucket = table[index]; // std::list<std::pair<Key, Value>>

    // zjisti, jestli se jiz klic v kybliku nenachazi
    for(auto & [k, v] : bucket)
    {
        if(k == key) { // pokud se v kybliku jiz klic nachazi
            v = value; // prepis jeho hodnotu (value) a skonci
            return;
        }
    }

    // pokud se nenachazi, vloz novou dvojici na konec kybliku
    number_of_elements ++;
    bucket.emplace_back(key, value); //std::make_pair(key, value);
}

//metoda, ktera vrati informaci, zda-li se v tabulce nachazi prvek s klicem key
bool hashmap::contains(const Key &key) const
{
    // zjisti, do ktereho kybliku patri klic
    unsigned int index = hash_index(key);
    auto & bucket = table[index]; // std::list<std::pair<Key, Value>>

    // zjisti, jestli se klic v kybliku nachazi
    for(auto & [k, v] : bucket)
    {
        if(k == key) {
            return true; // pokud ano ==> vrat true
        }
    }
    // pokud se nenachazi v kybliku ==> vrat false
    return false;
}

// Metoda na odstraneni prvku s klicem key z tabulky
// vraci true pokud se odstraneni povede, jinak false
bool hashmap::remove(const Key &key)
{
    // zjisti, do ktereho kybliku patri klic
    unsigned int index = hash_index(key);
    auto & bucket = table[index]; // std::list<std::pair<Key, Value>>

    // std::list pro mazani prvku vyzaduje iterator (ukazatel na dany prvek)
    for(auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if(it->first == key)  // pokud se hledany klic v kybliku nachazi
        {
            bucket.erase(it); // tak jej smaz (pomoci metody erase)
            number_of_elements--;
            return true;
        }
    }
    // pokud se klic v tabulce nenachazi
    return false;
}

// Metoda, ktera vrati pocet prvku v tabulce
unsigned int hashmap::size() const
{
    return number_of_elements;
}

// nekonstantni operator indexovani pro pristup ke klici key (L-hodnota)
Value &hashmap::operator[](const Key &key)
{
    // zjisti, do ktereho kybliku patri klic
    unsigned int index = hash_index(key);
    auto & bucket = table[index]; // std::list<std::pair<Key, Value>>

    // zjisti, do ktereho kybliku patri klic
    for(auto & [k, v] : bucket)
    {
        if(k == key) { // pokud se nachazi
            return v;  // tak vrat hodnotu, ktera se pod klicem nachazi
        }
    }
    // Pokud se klic nenachazi, alokuj novy prvek na konci kybliku s klicem key
    bucket.emplace_back(key, Value());
    number_of_elements++;
    return bucket.back().second; // a vrat l-hodnotu jeho hodnoty pod danym klicem
}

// konstantni operator indexovani pro pristup ke klici key (R-hodnota)
const Value &hashmap::operator[](const Key &key) const
{
    // zjisti, do ktereho kybliku patri klic
    unsigned int index = hash_index(key);
    auto & bucket = table[index]; // std::list<std::pair<Key, Value>>

    // projdi kyblik a zjisti,jestli se v nem nenachazi hledany klic
    for(auto & [k, v] : bucket)
    {
        if(k == key) { // pokud se nachazi
            return v;  // tak vrat hodnotu, ktera se pod klicem nachazi
        }
    }
    // jinak vyhod vyjimku
    throw std::out_of_range("Key not found in hash table.");
}

// Funkce, ktera vypise obsazenost jednotlivych kybliku
void hashmap::print_sizes() const
{
    for(unsigned int i = 0; i < number_of_buckets; i++)
        std::cout << "bucket number: " << i << "  " << table[i].size() <<std::endl;
}
