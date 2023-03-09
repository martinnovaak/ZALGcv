#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <vector>
#include <list>
#include <tuple>
#include <string>


using Key = std::string;
using Value = std::string;

class hashmap
{
public:
    hashmap(unsigned int number_of_buckets = 100);
    ~hashmap() = default;
    void insert(const Key & key, const Value & value);
    bool contains(const Key & key) const;
    bool remove(const Key & key);
    unsigned int size() const;

    Value & operator[](const Key & key);
    const Value & operator[](const Key & key) const;

    void print_sizes() const;
private:
    unsigned int number_of_buckets;
    unsigned int number_of_elements;
    std::vector<std::list<std::pair<Key, Value>>> table;

    unsigned int hash_index(const Key & key) const;
};


#endif //HASHMAP_HASHMAP_H
