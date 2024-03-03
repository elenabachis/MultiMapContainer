#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c), current(0), current_value(0) {
    first();
}

void MultiMapIterator::first() {
    current = 0;

    while (current < col.capacity && col.elements[current].key == NULL_TVALUE) {
        current++;
    }

    if (current < col.capacity) {
        current_value = 0;
    } else {
        current_value = -1;
    }
}

TElem MultiMapIterator::getCurrent() const {
    if (!valid())
        throw std::runtime_error("Invalid");
    TKey key = col.elements[current].key;
    TValue* value = &(col.elements[current].values[current_value]);
    return TElem(key, *value);
}

bool MultiMapIterator::valid() const {
    return (current < col.capacity && col.elements[current].key != NULL_TVALUE && current_value < col.elements[current].size);
}

void MultiMapIterator::next() {
    if (!valid())
        throw std::runtime_error("Invalid");

    current_value++;
    if (current_value >= col.elements[current].size) {
        current++;
        current_value = 0;

        while (current < col.capacity && col.elements[current].key == NULL_TVALUE) {
            current++;
        }
    }
}
