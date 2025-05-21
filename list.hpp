// list.hpp
#pragma once

#include <stdexcept>  // for std::runtime_error

// -----------------------------------------------------------------------------
// templated node
// -----------------------------------------------------------------------------
template<typename T>
struct node {
    T       info;
    node* next;
};

// -----------------------------------------------------------------------------
// List<T>
// -----------------------------------------------------------------------------
template<typename T>
class List {
public:
    List() : head(nullptr) {}

    // no copy for simplicity (you could add copy/move if you need it)
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    ~List() {
        // delete all nodes
        while (head) {
            node<T>* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    // push new element onto front
    void push_front(const T& value) {
        node<T>* n = new node<T>{ value, head };
        head = n;
    }

    // push new element onto back
    void push_back(const T& value) {
        // allocate new node (next defaults to nullptr)
        node<T>* n = new node<T>{ value, nullptr };

        if (!head) {
            // empty list: head becomes the new node
            head = n;
        }
        else {
            // otherwise find current tail...
            node<T>* cur = head;
            while (cur->next) {
                cur = cur->next;
            }
            // ...and link the new node there
            cur->next = n;
        }
    }

    // pop element from front and return its value
    T pop_front() {
        if (!head) {
            throw std::runtime_error("List::pop(): empty list");
        }

        T val = head->info;
        node<T>* tmp = head->next;
        delete head;
        head = tmp;
        return val;
    }

    // pop element from back and return its value
    T pop_back() {
        if (!head) {
            throw std::runtime_error("List::pop_back(): empty list");
        }

        // 1) single element?
        if (head->next == nullptr) {
            T val = head->info;
            delete head;
            head = nullptr;
            return val;
        }

        // 2) at least two nodes: walk to the end, tracking the one before
        node<T>* prev = nullptr;
        node<T>* cur = head;
        while (cur->next != nullptr) {
            prev = cur;
            cur = cur->next;
        }

        // cur is last node, prev is second-to-last
        T val = cur->info;
        prev->next = nullptr;  // unlink
        delete cur;            // free last node
        return val;
    }


    // peek at front element without removing
    const T& front() const {
        if (!head) {
            throw std::runtime_error("List::front(): empty list");
        }
        return head->info;
    }

    bool empty() const { 
        return head == nullptr; 
    }

private:
    node<T>* head;
};
