
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* frontPtr;
    Node* rearPtr;
    int count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontPtr = newNode;
            rearPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) return T();
        Node* temp = frontPtr;
        T value = frontPtr->data;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }
        delete temp;
        count--;
        return value;
    }

    T peekFront() {
        if (isEmpty()) return T();
        return frontPtr->data;
    }

    bool isEmpty() {
        return frontPtr == nullptr;
    }

    int getCount() {
        return count;
    }

    void print() {
        Node* current = frontPtr;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printIDs() {
        Node* current = frontPtr;
        while (current != nullptr) {
            if (current->data != nullptr) {
                cout << current->data->id << " ";
            }
            current = current->next;
        }
        cout << endl;
    }
};

