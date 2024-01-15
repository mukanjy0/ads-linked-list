//
// Created by iansg on 1/15/2024.
//

#ifndef SINGLE_LINKED_LIST_CIRCULAR_DOUBLY_LINKED_LIST_H
#define SINGLE_LINKED_LIST_CIRCULAR_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class circular_doubly_linked_list {
    class Node {
        T value {};
        Node* next {};
        Node* prev {};
        friend circular_doubly_linked_list;
    public:
        Node() = default;
        explicit Node(T val) : value(val) {
            next = this;
            prev = this;
        };
    };

    Node* head {};
    int sz {};

public:
    circular_doubly_linked_list() = default;
    T front() { return head->value; }
    T back() { return head->prev->value; }
    void push_front(T val) {
        push_back(val);
        head = head->prev;
    }
    void push_back(T val) {
        ++sz;

        if (head == nullptr) {
            head = new Node (val);
            return;
        }

        Node* node = new Node(val);
        head->prev->next = node;
        node->prev = head->prev;
        node->next = head;
        head->prev = node;
    }
    T pop_front() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");
        --sz;
        if (sz == 1) {
            T el = head->value;
            head = head->next = head->prev = nullptr;
            return el;
        }
        head->next->prev = head->prev;
        head->prev->next = head->next;
        Node* temp = head;
        head = head->next;
        T el = temp->value;
        delete temp;
        return el;
    }
    T pop_back() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");
        --sz;
        if (sz == 1) {
            T el = head->value;
            head = head->next = head->prev = nullptr;
            return el;
        }
        head->prev->prev->next = head;
        Node* temp = head->prev;
        head->prev = head->prev->prev;
        T el = temp->value;
        delete temp;
        return el;
    }
    void insert(T val, int pos) {
        if (pos > sz || pos < 0)
            throw invalid_argument("Invalid position.");

        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == sz) {
            push_back(val);
            return;
        }

        ++sz;
        Node* temp = head;
        for (int i = 1; i < pos; ++i)
            temp = temp->next;
        Node* node = new Node (val);
        node->prev = temp;
        node->next = temp->next;
        temp->next = node;
        temp->next->prev = node;
    }
    void remove(int pos) {
        if (pos >= sz  || pos < 0)
            throw invalid_argument("Invalid position.");

        if (pos == 0) {
            pop_front();
            return;
        }
        if (pos == sz - 1) {
            pop_back();
            return;
        }

        --sz;
        Node* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
    T operator[](int pos) {
        if (pos >= sz || pos < 0)
            throw invalid_argument("Not a valid index.");
        Node* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;
        return temp->value;
    }
    bool empty() { return sz == 0; }
    int size() { return sz; }
    void clear() {
        if (head == nullptr) return;
        while (sz) pop_front();
    }
    void reverse() {
        Node* sentinel = head;
        Node* temp = sentinel->next;
        sentinel->next = sentinel->prev;
        sentinel->prev = temp;
        sentinel = sentinel->prev;
        while (sentinel != head) {
            temp = sentinel->next;
            sentinel->next = sentinel->prev;
            sentinel->prev = temp;
            sentinel = sentinel->prev;
        }
        head = head->next;
    }
    friend ostream& operator<<(ostream& out, circular_doubly_linked_list cdll) {
        if (cdll.head == nullptr) return out;

        Node* temp = cdll.head;
        out << temp->value;
        temp = temp->next;
        for (int i = 1; i < cdll.sz; ++i) {
            out << ' ' << temp->value;
            temp = temp->next;
        }
        out << '\n';
        return out;
    }
};

#endif //SINGLE_LINKED_LIST_CIRCULAR_DOUBLY_LINKED_LIST_H
