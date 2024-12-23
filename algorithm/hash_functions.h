#pragma once

#include <cmath>
#include <string>

using namespace std;

template <typename K>
size_t base_hash_function(K key) {
    size_t a = 2654435761;
    size_t w = sizeof(int) * 8;
    size_t result = (key * a) >> (w - 1);
    return result;
}

template <typename K>
size_t murmur_hash(K key) {
    size_t seed = 0;
    size_t m = 0x5bd1e995;
    size_t r = 24;
    size_t h = seed ^ (sizeof(K) * m);

    while (key) {
        size_t k = key % 256;
        key /= 256;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;
    }
    return h;
}

template <typename K>
size_t fnv1a_hash(K key) {
    size_t hash = 14695981039346656037u;
    while (key) {
        hash ^= (key % 256);
        hash *= 1099511628211u;
        key /= 256;
    }
    return hash;
}


size_t sdbm_hash(string key) {
    size_t hash = 0;
    for (char c : key) {
        hash = ((hash << 6) + (hash << 16) - hash) + c;
    }
    return hash;
}

size_t djb2_hash(string key) {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}

size_t city_hash(string key) {
    size_t hash = 0;
    size_t prime = 37; 
    for (char c : key) {
        hash = hash * prime + c;
    }
    return hash;
}
