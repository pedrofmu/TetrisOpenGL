#ifndef HASH_MAP 
#define HASH_MAP 

#include <stdlib.h>
#include <iostream>

using namespace std;

template<typename K,typename D>
struct node{
    K key;
    D data;
    node *nextNode;
};

// New node creation
template<typename K,typename D>
class HashMap{
public:
    HashMap(): firstNode(nullptr){}

    HashMap(std::initializer_list<std::pair<K, D>> list) : firstNode(nullptr) {
        for (const auto& pair : list) {
            AddNode(pair.first, pair.second);
        }
    }

    void AddNode(K key, D data){
        if (firstNode == nullptr){
            firstNode = NewNode(key, data);
            return;
        }

        node<K, D>* currentNode = firstNode;
        while (currentNode->nextNode != nullptr){
           currentNode = currentNode->nextNode; 
        }

        currentNode->nextNode = NewNode(key, data);
    };

    bool HasKey(K key){
        node<K, D>* currentNode = firstNode;
        while (currentNode->nextNode != nullptr){
            if (currentNode->key == key){
                return true;
            }
            currentNode = currentNode->nextNode; 
        }

        return false;
    };

    D& operator[](const K& key) {
        node<K, D>* currentNode = firstNode;
        while (currentNode != nullptr) {
            if (currentNode->key == key) {
                return currentNode->data;
            }
            currentNode = currentNode->nextNode;
        }

        throw std::out_of_range("La key no existe");
    }

private:
    node<K, D>* firstNode;

    node<K, D>* NewNode(K key, D data){
        node<K, D>* node = new ::node<K, D>();

        node->key = key;
        node->data = data;

        node->nextNode = nullptr;

        return node;
    }
};

#endif 
