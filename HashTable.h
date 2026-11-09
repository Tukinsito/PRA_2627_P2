#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            sum += static_cast<int>(key[i]);
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    int entries() override {
        return n;
    }

    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entry(key, value);
        int pos = table[idx].search(entry);
        if (pos != -1) {
            throw std::runtime_error("Key '" + key + "' already exists!");
        }
        table[idx].insert(0, entry);
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Key '" + key + "' not found!");
        }
        return table[idx].get(pos).value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Key '" + key + "' not found!");
        }
        V val = table[idx].get(pos).value;
        table[idx].remove(pos);
        n--;
        return val;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        out << "==============\n\n";
        for (int i = 0; i < th.max; ++i) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => [";
            if (th.table[i].size() > 0) {
                out << "\n";
                for (int j = 0; j < th.table[i].size(); ++j) {
                    out << "  " << th.table[i].get(j) << "\n";
                }
            }
            out << "]\n\n";
        }
        out << "==============\n";
        return out;
    }
};

#endif
