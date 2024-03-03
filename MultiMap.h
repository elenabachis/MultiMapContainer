#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue > TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;
struct KeyValue {
    TKey key;
    TValue* values;
    int size;
    int cap;
};

class MultiMap
{
	friend class MultiMapIterator;

private:
	//TODO - Representation
    int capacity; // Kapazität der Hashtabelle
    int size_map; // Anzahl der gespeicherten Elemente
    KeyValue* elements;

    int hashFunction(TKey key) const; // Hashfunktion
    int hashFunction2(TKey key) const; // Zweite Hashfunktion
    bool isPrime(int number) const; // Hilfsfunktion zum Überprüfen, ob eine Zahl prim ist
    int getNextPrime(int number) const; // Hilfsfunktion zum Erhalten der nächsten Primzahl
    void rehash(); //es vergrossert unsere Hashtabelle

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

    MultiMap unionMultiMaps(const MultiMap& map1, const MultiMap& map2);

    MultiMap (const MultiMap& other);

	//descturctor
	~MultiMap();

};

