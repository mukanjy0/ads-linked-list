//
// Created by iansg on 1/9/2024.
//

#ifndef SINGLE_LINKED_LIST_SINGLY_LINKED_LIST_H
#define SINGLE_LINKED_LIST_SINGLY_LINKED_LIST_H

#include <stdexcept>
using namespace std;

template<typename T>
class singly_linked_list {
    class Node {
        T value {};
        Node* next {};
        friend singly_linked_list;
    public:
        Node() = default;
        explicit Node(T val) : value(val) {}
    };

    Node* head {};
    int sz {};

    void _reverse(Node* prev, Node* cur) {
        prev->next = nullptr;

        if (cur->next == nullptr) {
            cur->next = prev;
            head = cur;
        }
        else {
            _reverse(cur, cur->next);
            cur->next = prev;
        }
    }

    void _insertion_sort(Node* cur, int c) {
        if (c == 0) return;
        _insertion_sort(cur->next, --c);
        if (cur->value > cur->next->value)
            swap(cur->value, cur->next->value);
    }

public:
    singly_linked_list() = default;
    T front() { return head->value; }
    T back() {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->value;
    }
    void push_front(T val) {
        ++sz;

        Node* node = new Node(val);
        node->next = head;
        head = node;
    }
    void push_back(T val) {
        ++sz;

        if (head == nullptr) {
            head = new Node(val);
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        Node* node = new Node(val);
        temp->next = node;
    }
    T pop_front() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");
        Node* temp = head;
        head = temp->next;

        --sz;

        T el = temp->value;
        delete temp;
        return el;
    }
    T pop_back() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");

        --sz;

        if (head->next == nullptr) {
            T el = head->value;
            delete head;
            head = nullptr;
            return el;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        T el = temp->next->value;
        delete temp->next;
        temp->next = nullptr;
        return el;
    }
    T operator[](int k) {
        if (k >= sz)
            throw invalid_argument("Not a valid index.");
        Node* temp = head;
        for (int i = 0; i < k; ++i)
            temp = temp->next;
        return temp->value;
    }
    bool empty() { return head == nullptr; }
    int size() { return sz; }
    void clear() {
        if (head == nullptr) return;

        Node* temp = head;
        while (head->next != nullptr) {
            temp = head;
            head = temp->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }
    // insertion sort
    void sort() {
        for (int i = 0; i < sz; ++i)
            _insertion_sort(head, i);
    }
    void reverse() {
        if (head && head->next)
            _reverse(head, head->next);
    }
    singly_linked_list<T> merge(const singly_linked_list<T>& other) {
        int i {}, j {};
        Node* n1 = head;
        Node* n2 = other.head;
        singly_linked_list<T> result;
        while (i < sz && j < other.sz) {
            if (n1->value > n2->value) {
                result.push_back(n2->value);
                n2 = n2->next;
                ++j;
            }
            else  {
                result.push_back(n1->value);
                n1 = n1->next;
                ++i;
            }
        }
        while (i < sz) {
            result.push_back(n1->value);
            n1 = n1->next;
            ++i;
        }
        while (j < other.sz) {
            result.push_back(n2->value);
            n2 = n2->next;
            ++j;
        }
        return result;
    }
    singly_linked_list<T> intersect(const singly_linked_list& other) {
        int i {}, j {};
        Node* n1 = head;
        Node* n2 = other.head;
        singly_linked_list<T> result;
        while (i < sz && j < other.sz) {
            if (n1->value == n2->value) {
                result.push_back(n1->value);
                n1 = n1->next, n2 = n2->next;
                ++i, ++j;
            }
            else  if (n1->value < n2->value) {
                n1 = n1->next;
                ++i;
            }
            else {
                n2 = n2->next;
                ++j;
            }
        }
        return result;
    }
    friend ostream& operator<<(ostream& out, singly_linked_list sll) {
        Node* temp = sll.head;
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

#endif //SINGLE_LINKED_LIST_SINGLY_LINKED_LIST_H
