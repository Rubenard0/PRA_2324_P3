#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <vector>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}

    ~BSTreeDict() {
        delete tree;
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }

        V operator[](std::string key) const {
        return this->search(key); // Delegamos en el método search
    }


    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        if (tree->exists(entry)) {
            throw std::runtime_error("Key already exists");
        }
        tree->insert(entry);
    }

        V search(std::string key) const override {
        TableEntry<V> query(key); // Creamos un TableEntry con solo la clave
        TableEntry<V> result = tree->search(query); // Usamos el ABB para buscar
        return result.getValue(); // Devolvemos el valor asociado a la clave
    }


    V remove(std::string key) override {
        TableEntry<V> query(key);
        if (!tree->exists(query)) {
            throw std::runtime_error("Key not found");
        }
        return tree->remove(query).getValue();
    }

    int entries() override {
        return tree->size();
    }
};

#endif // BSTREEDICT_H
