

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHTABLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHTABLE_H
#include<functional>
#include <set>
using namespace std;
template<typename K, typename V>
class HashTable{
private:
    struct HashNode{
        K key;
        set<V> values;
        HashNode* next;

        HashNode(const K& k, const V& v): key(k), next(nullptr){
            values.insert(v);
        }
    };
    int size;
    HashNode** arr;
    int uniqueSize;

public:
    // create new table
    HashTable(): size(100003), uniqueSize(0){
        arr = new HashNode* [size];
    }
    void insert(const K& key, const V& val){
        // hash the key
        size_t hashValue = hash<K>{}(key);
        int loc = hashValue % size;

        // get the bucket
        HashNode* bucket = arr[loc];
        HashNode* prev = nullptr;

        // get to the bucket that has the same key
        while(bucket!=nullptr && bucket->key!=key){
            prev = bucket;
            bucket = bucket->next;
        }

        // if key not found
        if(bucket==nullptr){
            bucket = new HashNode(key, val);
            // start list
            if(prev == nullptr)
                arr[loc] = bucket;
                // or add to list
            else
                prev->next = bucket;
            uniqueSize++;
        }
        else
            bucket->values.insert(val);

    }
    set<V>* get(const K& key){
        // hash key
        size_t hashValue = hash<K>{}(key);
        int loc = hashValue % size;

        // get the bucket
        HashNode* bucket = arr[loc];

        while(bucket!=nullptr){
            if(bucket->key==key){
                return &bucket->values;
            }
            bucket = bucket->next;
        }
        return nullptr;
    }
    int getUniqueSize(){return uniqueSize;};
    ~HashTable() {
        // destroy all buckets one by one
        for (int i=0; i < size; i++) {
            HashNode* curr = arr[i];
            while (curr != nullptr) {
                HashNode* prev = curr;
                curr = curr->next;
                delete prev;
            }
            arr[i] = nullptr;
        }
        // destroy the hash table
        delete[]arr;
    }
};
#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHTABLE_H
