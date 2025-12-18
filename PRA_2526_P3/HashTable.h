#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h" 
using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        // ...
	int n;
	int max;
	ListLinked<TableEntry<V> >* table;
	int h(string key){
		int res = 0;
		for(int i = 0; i < key.length(); i++){	
			res += key[i] - '0';
		}
		return res % max;
	}
	// table[i] es la cubeta es on hi han nodos amb informacio de clave->valor

    public:
        // ...
	void insert(string key, V value) override{
		int i = h(key);
		int pos = table[i].search(key);
		if(pos != -1){
			throw runtime_error("Ya existe en el diccionario");
		}

		TableEntry<V> aux = TableEntry<V>(key, value);
		table[i].append(aux); // tinc que recorrer tots els nodos de la posició i despres afegir 
		n++;
	}
	V search(string key)override{
		int i = h(key);      
		int pos = table[i].search(key); // en la posicio i se suposa que esta key, si no esta fem un throw
		if(pos == -1){
			throw runtime_error("No se encuentra en el diccionario");
		}
		
		TableEntry<V> aux = table[i].get(pos);
		return aux.value;
	}
    V remove(string key)override{
		int i = h(key);
		int pos = table[i].search(key);
        if(pos == -1){
            throw runtime_error("No se encuentra en el diccionario");
        }

		TableEntry<V> aux = table[i].get(pos);
		table[i].remove(pos);
		n--;
		return aux.value;
		
	}
    int entries() override{
		return n;
	}
	
	HashTable(int size){
		table = new ListLinked<TableEntry<V> >[size];
		n = 0;
		max = size;
	}

	~HashTable(){
		delete[] table;		
	}

	int capacity(){	
		return max;
	}
	
	friend ostream& operator<<(std::ostream &out, HashTable<V> &th){
		
		out << "HashTable [entries: " << th.entries() << ", capacity: " << th.capacity() << "]" << endl;
		out << "==============" << endl << endl;

    	for (int i = 0; i < th.max; i++) { 
			out << "== Cubeta " << i << " ==" << endl << endl;
			out << th.table[i] << endl << endl; // utilitza el operator de TableEntry i ListLinked
    	}

		out << "==============" << endl;

    	return out;
	}
	
	V operator[](string key){
		return search(key);
	}
};

#endif
