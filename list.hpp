// list.hpp
#pragma once

#include <cstddef>      // for std::size_t
#include <stdexcept>    // for std::runtime_error, std::out_of_range
#include <iterator>     // for std::forward_iterator_tag

template<typename T>
struct node {
    T       info;
    node* next = nullptr;

    node(const T& v, node* n = nullptr)
        : info(v), next(n) {
    }
};

template<typename T>
class List {
public:
    List() = default;
    ~List() { clear(); }

    // no copy/move for now
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // capacity
    bool        empty() const noexcept { return sz == 0; }
    std::size_t size()  const noexcept { return sz; }

    // element access
    T& front() {
        ensure_not_empty("List::front");
        return head->info;
    }
    const T& front() const {
        ensure_not_empty("List::front");
        return head->info;
    }

    T& back() {
        ensure_not_empty("List::back");
        return tail->info;
    }
    const T& back() const {
        ensure_not_empty("List::back");
        return tail->info;
    }

    // at() with bounds check
    T& at(std::size_t index) {
        return const_cast<T&>(std::as_const(*this).at(index));
    }
    const T& at(std::size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("List::at(): index " + std::to_string(index)
                + " >= size " + std::to_string(sz));
        }
        node<T>* cur = head;
        for (std::size_t i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->info;
    }

    // operator[] as alias to at() (no performance difference)
    T& operator[](std::size_t idx) { return at(idx); }
    const T& operator[](std::size_t idx) const { return at(idx); }

    // modifiers
    void push_front(const T& value) {
        head = new node<T>(value, head);
        if (!tail) tail = head;
        ++sz;
    }

    void push_back(const T& value) {
        node<T>* n = new node<T>(value);
        if (!head) {
            head = tail = n;
        }
        else {
            tail->next = n;
            tail = n;
        }
        ++sz;
    }

    T pop_front() {
        ensure_not_empty("List::pop_front");
        node<T>* old = head;
        T val = head->info;
        head = head->next;
        delete old;
        if (!head) tail = nullptr;
        --sz;
        return val;
    }

    T pop_back() {
        ensure_not_empty("List::pop_back");
        // single element
        if (head == tail) {
            T val = tail->info;
            delete head;
            head = tail = nullptr;
            sz = 0;
            return val;
        }
        // find penultimate
        node<T>* cur = head;
        while (cur->next != tail) {
            cur = cur->next;
        }
        T val = tail->info;
        delete tail;
        tail = cur;
        tail->next = nullptr;
        --sz;
        return val;
    }

    void clear() noexcept {
        while (head) {
            auto tmp = head->next;
            delete head;
            head = tmp;
        }
        tail = nullptr;
        sz = 0;
    }

    // simple forward iterator
    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        node<T>* ptr = nullptr;
        explicit iterator(node<T>* p) : ptr(p) {}

        reference operator*() const { return ptr->info; }
        pointer   operator->() { return &ptr->info; }

        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        bool operator==(const iterator& o) const { return ptr == o.ptr; }
        bool operator!=(const iterator& o) const { return ptr != o.ptr; }
    };

    iterator begin()       noexcept { return iterator(head); }
    iterator end()         noexcept { return iterator(nullptr); }
    // const_iterators omitted for brevity...

private:
    node<T>* head = nullptr;
    node<T>* tail = nullptr;
    std::size_t sz = 0;

    void ensure_not_empty(const char* fn) const {
        if (!head) {
            throw std::runtime_error(std::string(fn) + ": empty list");
        }
    }
};
