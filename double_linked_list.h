//
// Created by iansg on 1/10/2024.
//

#ifndef SINGLE_LINKED_LIST_DOUBLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_DOUBLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class double_linked_list {
    class Node {
        T value {};
        Node* prev {};
        Node* next {};
        friend double_linked_list;
    public:
        Node() = default;
        Node(T val) : value(val) {}
    };

    Node* head {};
    Node* tail {};
    int sz {};
public:
    double_linked_list() = default;
    T front() { return head->value; }
    T back() { return tail->value; }
    void push_front(T val) {
        ++sz;

        if (head == nullptr) {
            head = new Node (val);
            tail = head;
            return;
        }

        Node* node = new Node (val);
        node->next = head;
        head->prev = node;
        head = node;
    }
    void push_back(T val) {
        ++sz;

        if (head == nullptr) {
            head = new Node (val);
            tail = head;
            return;
        }

        Node* node = new Node (val);
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    T pop_front() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");

        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        else head->prev = nullptr;

        --sz;

        T el = temp->value;
        delete temp;
        return el;
    }
    T pop_back() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");

        Node* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;
        else tail->next = nullptr;

        --sz;

        T el = temp->value;
        delete temp;
        return el;
    }
    void insert(T val, int pos) {    // position is 0-indexed
        if (pos > sz || pos < 0)
            throw invalid_argument("Invalid position.");

        if (pos == sz) {
            push_back(val);
            return;
        }
        if (pos == 0) {
            push_front(val);
            return;
        }

        Node* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;

        Node* node = new Node (val);
        temp->prev->next = node;
        node->prev = temp->prev;
        temp->prev = node;
        node->next = temp;

        ++sz;
    }
    void remove(int pos) {          // position is 0-indexed
        if (pos >= sz || pos < 0)
            throw invalid_argument("Invalid position.");

        if (pos == 0) {
            pop_front();
            return;
        }
        if (pos == sz - 1) {
            pop_back();
            return;
        }

        Node* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        --sz;
    }
    T operator[](int pos) {
        if (pos >= sz)
            throw invalid_argument("Invalid position.");

        Node* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;

        return temp->value;
    }
    bool empty() {
        return head == nullptr;
    }
    int size() {
        return sz;
    }
    void clear() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;

        sz = 0;
    }
    void reverse() {
        if (sz <= 1) return;

        Node* temp = head;
        head = tail;
        tail = temp;
        while (temp) {
            Node* prev = temp->prev;
            temp->prev = temp->next;
            temp->next = prev;
            temp = temp->prev;
        }
    }
    friend ostream& operator<<(ostream& out, double_linked_list dll) {
        Node* temp = dll.head;
        if (temp != nullptr) {
            out << temp->value;
            while (temp->next != nullptr) {
                temp = temp->next;
                out << ' ' << temp->value;
            }
        }
        out << '\n';
        return out;
    }
};

#endif //SINGLE_LINKED_LIST_DOUBLE_LINKED_LIST_H
