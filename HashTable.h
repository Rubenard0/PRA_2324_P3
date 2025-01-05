#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;  // Número de elementos almacenados
    int max;  // Tamaño de la tabla hash (número de cubetas)
    ListLinked<TableEntry<V>>* table;  // Array de punteros a listas enlazadas (cubetas)

    // Función hash: suma los valores ASCII de los caracteres de la clave y calcula el módulo con el tamaño de la tabla
    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    // Constructor: reserva memoria dinámica para la tabla e inicializa atributos
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor: libera la memoria dinámica
    ~HashTable() {
        delete[] table;
    }

    // Inserta un par clave->valor en el diccionario
    void insert(std::string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key, value);

        if (table[index].search(entry) != -1) {
            throw std::runtime_error("Key '" + key + "'");
            }

        table[index].append(entry);
        n++;
    }

    // Busca un valor asociado a una clave
    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);

        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Key '" + key +"'");
            }

        return table[index].get(pos).value;
    }

    // Elimina un par clave->valor
    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);

        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Key '" + key + "'");
            }

        V removedValue = table[index].get(pos).value;
        table[index].remove(pos);
        n--;

        return removedValue;
    }

    // Devuelve el número de elementos en el diccionario
    int entries() override {
        return n;
    }

    // Devuelve la capacidad total de la tabla
    int capacity() {
        return max;
    }

    // Sobrecarga del operador [] para buscar valores asociados a claves
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga del operador << para imprimir la tabla hash
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        out << "HashTable (" << ht.n << "/" << ht.max << "):\n";
        for (int i = 0; i < ht.max; i++) {
            out << "Cubeta " << i << ": " << ht.table[i] << "\n";
        }
        return out;
    }
};

#endif // HASHTABLE_H
