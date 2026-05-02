#pragma once
#include "priNode.h"
#include <iostream>

using namespace std;

template <typename T>
class priQueue {
protected:
    priNode<T>* head;
    int count; // Added to track number of elements

public:
    priQueue() : head(nullptr), count(0) {} // Initialize count

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    // Inside priQueue class in priQueue.h
    void printIDs() const {
        priNode<T>* curr = head;
        if (!curr) {
            cout << "None";
            return;
        }
        while (curr) {
            int p;
            T item = curr->getItem(p); // item is Order*
            if (item) cout << item->id << " ";
            curr = curr->getNext();
        }
    }

    void enqueue(const T& data, int priority) 
    {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) 
            {
                newNode->setNext(head);
                head = newNode;
            }
            else 
                {
                    priNode<T>* current = head;
                    while (current->getNext() && priority <= current->getNext()->getPri()) {
                        current = current->getNext();
                    }
                    newNode->setNext(current->getNext());
                    current->setNext(newNode);
                }
        count++; // Increment count
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--; // Decrement count
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // Added for simulation compatibility
    int GetCount() const {
        return count;
    }

    // Added for debugging/simulation output
    void print() const {
        priNode<T>* curr = head;
        if (!curr) {
            cout << "Empty";
            return;
        }
        while (curr) {
            int p;
            cout << curr->getItem(p) << " ";
            curr = curr->getNext();
        }
        cout << endl;
    }
};