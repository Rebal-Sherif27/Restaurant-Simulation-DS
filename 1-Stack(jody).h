#pragma once
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topPtr;
    int count;

public:
    Stack() : topPtr(nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = topPtr;
        topPtr = newNode;
        count++;
    }

    T pop() {
        if (isEmpty()) return T();
        Node* temp = topPtr;
        T value = topPtr->data;
        topPtr = topPtr->next;
        delete temp;
        count--;
        return value;
    }

    T peek() {
        if (isEmpty()) return T();
        return topPtr->data;
    }

    bool isEmpty() {
        return topPtr == nullptr;
    }

    int getCount() {
        return count;
    }

    void print() {
        Node* current = topPtr;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};
