#ifndef UTILITIES_H
#define UTILITIES_H

#include <unordered_map>

template<typename K, typename V>
bool isInMap(const std::unordered_map<K, V>& myMap, const K& key) {
    return myMap.find(key) != myMap.end();
}

#endif