
import java.util.HashMap;
import java.util.Map;

public class LRUCache {

    Map<Integer, Node<Integer, Integer>> quickAccess_nodeByKey;
    LRUQueue<Integer, Integer> lruQueue;
    int capacity;

    public LRUCache(int capacity) {
        quickAccess_nodeByKey = new HashMap<>();
        lruQueue = new LRUQueue<>();
        this.capacity = capacity;
    }

    public int get(int key) {
        if (quickAccess_nodeByKey.containsKey(key)) {
            lruQueue.removeNode(quickAccess_nodeByKey.get(key));
            lruQueue.addLast(quickAccess_nodeByKey.get(key));
            return quickAccess_nodeByKey.get(key).value;
        }
        return -1;
    }

    public void put(int key, int value) {

        if (quickAccess_nodeByKey.containsKey(key)) {
            lruQueue.removeNode(quickAccess_nodeByKey.get(key));
            lruQueue.addLast(quickAccess_nodeByKey.get(key));
            quickAccess_nodeByKey.get(key).value = value;
            return;
        }

        if (quickAccess_nodeByKey.size() == this.capacity) {
            quickAccess_nodeByKey.remove(lruQueue.head.next.key);
            lruQueue.removeFirst();
        }

        quickAccess_nodeByKey.put(key, new Node(key, value));
        lruQueue.addLast(quickAccess_nodeByKey.get(key));
    }
}

class LRUQueue<K, V> {

    Node<K, V> head;
    Node<K, V> tail;

    public LRUQueue() {
        this.head = new Node<>();
        this.tail = new Node<>();
        this.head.next = this.tail;
        this.tail.previous = this.head;
    }

    public void addLast(Node node) {
        node.next = this.tail;
        node.previous = this.tail.previous;

        this.tail.previous.next = node;
        this.tail.previous = node;
    }

    public void removeFirst() {
        this.head.next = this.head.next.next;
        this.head.next.previous = this.head;
    }

    public void removeNode(Node node) {
        node.next.previous = node.previous;
        node.previous.next = node.next;
    }
}

class Node<K, V> {

    K key;
    V value;
    Node<K, V> next;
    Node<K, V> previous;

    public Node() {
    }

    public Node(K key, V value) {
        this.key = key;
        this.value = value;
    }
}
