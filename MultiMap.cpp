#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	//TODO - Implementation
    this->capacity=10; //Kapazitat des Arrays von KeyValues
    this->size_map=0; //das Size von dem Arrays, also values
    this->elements= new KeyValue[capacity]; //elements ist mein Array von KeyValues
    for (int i = 0; i < capacity; i++) {
        elements[i].key = NULL_TVALUE;
        elements[i].values = nullptr;
        elements[i].size = 0;
        elements[i].cap = 0;
    }
}

int MultiMap::hashFunction(TKey key) const {
    return abs(key % capacity); //die erste HashFunktion
}

int MultiMap::hashFunction2(TKey key) const {
    return abs(key % capacity)+1; //die zweite Hashfunktion fur Doppelte Hashing
}

//das brauche ich fur rehash um die nachste Primzahl zu finden
bool MultiMap::isPrime(int number) const {
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    for (int i = 3; (i * i) <= number; i += 2) {
        if (number % i == 0)
            return false;
    }
    return true;
}

//das wird benutzt wenn ich rehash mache, die neue Kapazitat wird number sein
int MultiMap::getNextPrime(int number) const {
    while (!isPrime(number))
        number++;
    return number;
}

//das brauche ich um unsere Hashtabelle zu vergrossern wenn ich kein mehreres Platz habe
void MultiMap::rehash() {
    int newCapacity = getNextPrime(capacity * 2); //die neue Kapazitat
    auto* newElements = new KeyValue[newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newElements[i].key = NULL_TVALUE;
    }

    for (int i = 0; i < capacity; i++) {  //hier kopiere ich die Elemente die ich eingefugt habe
        if (elements[i].key != NULL_TVALUE) {
            int hash = hashFunction(elements[i].key);
            int step = hashFunction2(elements[i].key);
            int k = 0;
            while (newElements[hash].key != NULL_TVALUE) {
                k++;
                hash = (hash + k * step) % newCapacity;
            }
            newElements[hash] = elements[i];
        }
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

///Komplexitat: average case:theta(1) und worst case:theta(n) wobei n die Anzahl von Elementen ist
void MultiMap::add(TKey c, TValue v) {
    if (size_map >= capacity) {
        rehash();
    }

    int hash = hashFunction(c);
    int step = hashFunction2(c);
    int k = 0; // Counter fur doppelte hashing
    while (elements[hash].key != NULL_TVALUE && elements[hash].key != c) {
        k++;
        hash = (hash + k * step) % capacity;
        if (k >= capacity) {
            // es gibt kein freier Platz um ein neues Element einzufugen
            rehash();
           //wir vergrossern die Hashtabelle
            hash = hashFunction(c);
            step = hashFunction2(c);
            k = 0;
            break;
        }
    }

    if (elements[hash].key == NULL_TVALUE) {
        elements[hash].key = c;
        elements[hash].values = new TValue[1];
        elements[hash].size = 1;
        elements[hash].cap = 1;
        elements[hash].values[0] = v;
        size_map++;
    } else {
        // Das Schlussel existiert, ich fuge die neue Wert ein
        if (elements[hash].size >= elements[hash].cap) {
            // Resize the values array
            int newCapacity = elements[hash].cap * 2;
            auto* newValues = new TValue[newCapacity];
            for (int i = 0; i < elements[hash].size; i++) {
                newValues[i] = elements[hash].values[i];
            }
            //delete[] elements[hash].values;
            elements[hash].values = newValues;
            elements[hash].cap = newCapacity;
        }
        elements[hash].values[elements[hash].size] = v;
        elements[hash].size++;
        size_map++;
    }
}

///Komplexitat: average case:theta(1) und worst case:theta(n) wobei n die Anzahl von Elementen ist
bool MultiMap::remove(TKey c, TValue v) {

    for (int i = 0; i < capacity; i++) {
        if (elements[i].key == c) {
            for (int j = 0; j < elements[i].size; j++) {
                if (elements[i].values[j] == v) {
                    for (int k = j + 1; k < elements[i].size; k++) {
                        elements[i].values[k - 1] = elements[i].values[k];
                    }
                    elements[i].size--;
                    size_map--;
                    return true;
                }
            }
            break;
        }
    }
    return false;
}


///Komplexitat: average case:theta(1) und worst case:theta(n) wobei n die Anzahl von Elementen ist
vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
    vector<TValue> result;
    for (int i = 0; i < capacity; i++) {
        if (elements[i].key == c) {
           //ich habe das Schlussel gefunden wurde
            for (int j = 0; j < elements[i].size; j++) {
                result.push_back(elements[i].values[j]); //das Array(values)
            }
            break;
        }
    }
    return result;
	//return vector<TValue>();
}


int MultiMap::size() const {
	//TODO - Implementation
	return size_map;
}


bool MultiMap::isEmpty() const {
	//TODO - Implementation
	return size_map==0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    for (int i = 0; i < capacity; i++) {
            delete[] elements[i].values;
    }
    delete[] elements;


}

//concatenarea a doua multimaps
MultiMap MultiMap::unionMultiMaps(const MultiMap& map1, const MultiMap& map2) {
    MultiMap result;

    // Addiert ELementen von map1
    for (int i = 0; i < map1.capacity; i++) {
        if (map1.elements[i].key != NULL_TVALUE) {
            for (int j = 0; j < map1.elements[i].size; j++) {
                result.add(map1.elements[i].key, map1.elements[i].values[j]);
            }
        }
    }

    // Addiert Elementen von map2
    for (int i = 0; i < map2.capacity; i++) {
        if (map2.elements[i].key != NULL_TVALUE) {
            for (int j = 0; j < map2.elements[i].size; j++) {
                result.add(map2.elements[i].key, map2.elements[i].values[j]);
            }
        }
    }

    return result;
}

//Kopiekonstruktor
MultiMap::MultiMap(const MultiMap& other) {
    this->capacity = other.capacity;
    this->size_map = other.size_map;
    this->elements = new KeyValue[capacity];

    for (int i = 0; i < capacity; i++) {
        elements[i].key = other.elements[i].key;
        elements[i].size = other.elements[i].size;
        elements[i].cap = other.elements[i].cap;
        if (elements[i].size > 0) {
            elements[i].values = new TValue[elements[i].cap];
            for (int j = 0; j < elements[i].size; j++) {
                elements[i].values[j] = other.elements[i].values[j];
            }
        } else {
            elements[i].values = nullptr;
        }
    }
}
