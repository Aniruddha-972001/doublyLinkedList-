#include "MyLL.h"

template <typename T>
MyLL<T>::MyLL() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
MyLL<T>::~MyLL() {
    clear();
}

template <typename T>
bool MyLL<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool MyLL<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
    return true;
}

template <typename T>
bool MyLL<T>::add_to_front(const T& value) {
    Node* newNode = new Node(value);
    if (newNode == nullptr) {
        return false;
    }
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
    return true;
}

template <typename T>
bool MyLL<T>::add_to_back(const T& value) {
    Node* newNode = new Node(value);
    if (newNode == nullptr) {
        return false;
    }
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
    return true;
}

template <typename T>
bool MyLL<T>::merge(MyLL& other) {
    if (this == &other) {
        return true; // If merging into itself, do nothing and return true
    }

    if (!other.isEmpty()) {
        if (tail) {
            tail->next = other.head;
            if (other.tail) {
                tail = other.tail;
            }
        } else {
            head = other.head;
            tail = other.tail;
        }

        size += other.size;

        // Clear the 'other' list (without freeing the memory of nodes)
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;

        return true;
    }

    return false;
}
template <typename T>
MyLL<T>& MyLL<T>::operator+=(const MyLL& other) {
    if (this == &other) {
        return *this;
    }

    Node* otherCurrent = other.head;

    while (otherCurrent != nullptr) {
        T dataCopy = otherCurrent->data;
        Node* newNode = new Node(dataCopy);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        otherCurrent = otherCurrent->next;
    }

    return *this;
}
template <typename T>
MyLL<T>& MyLL<T>::operator-=(const MyLL& other) {
    if (this == &other) {
        return *this;
    }

    Node* current = head;

    while (current != nullptr) {
        Node* otherCurrent = other.head;
        bool found = false;

        while (otherCurrent != nullptr) {
            if (current->data == otherCurrent->data) {
                found = true;
                break;
            }
            otherCurrent = otherCurrent->next;
        }

        // remove the current node.
        if (found) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            Node* temp = current;
            current = current->next;
            delete temp;
        } else {
            current = current->next;
        }
    }

    return *this;
}

// template <typename T>
// MyLL<T>& MyLL<T>::operator+=(const MyLL& other) {
//     if (this == &other) {
//         return *this; // Return the current object unchanged
//     }

//     Node* current = other.head;
//     while (current != nullptr) {
//         add_to_back(current->data);
//         current = current->next;
//     }

//     return *this;
// }

template <typename T>
void MyLL<T>::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
int MyLL<T>::remove(char c) {
    int count = 0;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        if (current->data[0] == c) {
            if (current == head) {
                head = current->next;
            }
            if (current == tail) {
                tail = current->prev;
            }
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            delete current;
            size--;
            count++;
        }
        current = next;
    }

    return count;
}

template <typename T>
bool MyLL<T>::shift_forward(char c) {
    Node* current = head;
    Node* matchingHead = nullptr;
    Node* matchingTail = nullptr;
    Node* nonMatchingHead = nullptr;
    Node* nonMatchingTail = nullptr;

    while (current != nullptr) {
        Node* next = current->next;

        if (current->data[0] == c) {
            if (matchingHead == nullptr) {
                matchingHead = matchingTail = current;
                matchingHead->prev = nullptr;
                matchingTail->next = nullptr;
            } else {
                matchingTail->next = current;
                current->prev = matchingTail;
                matchingTail = current;
                matchingTail->next = nullptr;
            }
        } else {
            if (nonMatchingHead == nullptr) {
                nonMatchingHead = nonMatchingTail = current;
                nonMatchingHead->prev = nullptr;
                nonMatchingTail->next = nullptr;
            } else {
                nonMatchingTail->next = current;
                current->prev = nonMatchingTail;
                nonMatchingTail = current;
                nonMatchingTail->next = nullptr;
            }
        }

        current = next;
    }

    if (matchingHead != nullptr) {
        matchingTail->next = nonMatchingHead;
        if (nonMatchingHead != nullptr) {
            nonMatchingHead->prev = matchingTail;
        }
        head = matchingHead;
    } else {
        head = nonMatchingHead;
    }

    return true;
}

template <typename T>
void MyLL<T>::reset() {
    iteratorPtr = head;
}

template <typename T>
bool MyLL<T>::finished() {
    return iteratorPtr == nullptr;
}

template <typename T>
bool MyLL<T>::getNext(T& str) {
    if (iteratorPtr == nullptr) {
        return false;
    }

    str = iteratorPtr->data;
    iteratorPtr = iteratorPtr->next;
    return true;
}

// Explicit instantiation for the types we need
template class MyLL<std::string>;
