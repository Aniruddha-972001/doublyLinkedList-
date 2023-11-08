#ifndef MYLL_H
#define MYLL_H

#include <iostream>
#include <string>

template <typename T>
class MyLL {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* iteratorPtr;
    Node* head;
    Node* tail;
    size_t size;

public:
    MyLL();
    ~MyLL();

    bool isEmpty() const;
    bool clear();

    bool add_to_front(const T& value);
    bool add_to_back(const T& value);

    bool merge(MyLL& other);
    // MyLL& operator+=(const MyLL& other);
    MyLL& operator+=(const MyLL& other); // Add this declaration
    MyLL& operator-=(const MyLL& other); // Add this declaration

    void print();
    int remove(char c);
    bool shift_forward(char c);

    void reset();
    bool finished();
    bool getNext(T& str);

};

#endif // MYLL_H
