
#include<unordered_map>
using namespace std;

template <typename K, typename V> struct Node {
    K key;
    V value;
    Node<K, V>* next;
    Node<K, V>* previous;

    Node<K, V>() {
        key = -1;
        value = -1;
        next = nullptr;
        previous = nullptr;
    }

    Node(K k, V v) {
        key = k;
        value = v;
        next = nullptr;
        previous = nullptr;
    }
};

template <typename K, typename V> class LRUQueue {
public:
    Node<K, V>* head;
    Node<K, V>* tail;

    LRUQueue() {
        head = new Node<K, V>();
        tail = new Node<K, V>();
        head->next = tail;
        tail->previous = head;
    }

    void addLast(Node<K, V>* node) {
        node->next = tail;
        node->previous = tail->previous;

        tail->previous->next = node;
        tail->previous = node;
    }

    void removeFirst() {
        Node<K, V>* temp = head->next->next;
        delete head->next;
        head->next = temp;
        head->next->previous = head;
        temp = nullptr;
        delete temp;
    }

    void removeNode(Node<K, V>* node) {
        node->next->previous = node->previous;
        node->previous->next = node->next;
        node = nullptr;
        delete node;
    }
};

class LRUCache {
public:
    unordered_map<int, Node<int, int>*> quickAccess_nodeByKey;
    LRUQueue<int, int> lruQueue;
    int max_capacity;

    LRUCache(int capacity) {
        max_capacity = capacity;
    }

    int get(int key) {
        if (quickAccess_nodeByKey.find(key) != quickAccess_nodeByKey.end()) {
            lruQueue.removeNode(quickAccess_nodeByKey[key]);
            lruQueue.addLast(quickAccess_nodeByKey[key]);
            return (quickAccess_nodeByKey[key])->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (quickAccess_nodeByKey.find(key) != quickAccess_nodeByKey.end()) {
            lruQueue.removeNode(quickAccess_nodeByKey[key]);
            quickAccess_nodeByKey[key]->value = value;
            lruQueue.addLast(quickAccess_nodeByKey[key]);
            return;
        }

        if (quickAccess_nodeByKey.size() == max_capacity) {
            quickAccess_nodeByKey.erase(lruQueue.head->next->key);
            lruQueue.removeFirst();
        }

        quickAccess_nodeByKey[key] = new Node(key, value);
        lruQueue.addLast(quickAccess_nodeByKey[key]);
    }
};
