#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdlib.h>

// Nodo genérico para la lista enlazada
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(NULL), prev(NULL) {}
};

// Clase Lista Doblemente Enlazada genérica
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(NULL), tail(NULL), size(0) {}

    // Destructor: limpia todos los nodos
    ~LinkedList() {
        clear();
    }

    // Agrega un elemento al final de la lista
    void add(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Agrega un elemento al inicio de la lista
    void addFront(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Elimina un elemento específico de la lista
    bool remove(T val) {
        Node<T>* curr = head;
        while (curr) {
            if (curr->data == val) {
                if (curr->prev) curr->prev->next = curr->next;
                if (curr->next) curr->next->prev = curr->prev;
                if (curr == head) head = curr->next;
                if (curr == tail) tail = curr->prev;
                delete curr;
                size--;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // Obtiene el dato en un índice específico
    T get(int index) {
        Node<T>* curr = head;
        for (int i = 0; i < index && curr; i++) {
            curr = curr->next;
        }
        return curr ? curr->data : (T)0;
    }

    Node<T>* getHead() const { return head; }
    int count() const { return size; }

    // Limpia la lista eliminando todos los nodos
    void clear() {
        Node<T>* curr = head;
        while (curr) {
            Node<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = NULL;
        size = 0;
    }
};

#endif
