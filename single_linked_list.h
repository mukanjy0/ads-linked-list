//
// Created by iansg on 1/9/2024.
//

#ifndef SINGLE_LINKED_LIST_SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_SINGLE_LINKED_LIST_H

#include <stdexcept>
using namespace std;

template<typename T>
class single_linked_list {
    class Node {
        T value {};
        Node* next {};
        friend single_linked_list;
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
    single_linked_list() = default;
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
    void pop_front() {
        if (head == nullptr) return;
        Node* temp = head;
        head = temp->next;
        delete temp;

        --sz;
    }
    void pop_back() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;

        --sz;
    }
    T operator[](int k) {
        if (k >= sz)
            throw invalid_argument("Not a valid index.");
        Node* temp = head;
        for (int i = 0; i < k; ++i)
            temp = temp->next;
        return temp->value;
    }
    bool empty() { return sz == 0; }
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
    void reverse() {
        if (head && head->next)
            _reverse(head, head->next);
    }
    single_linked_list<T> merge(const single_linked_list<T>& other) {
        int i {}, j {};
        Node* n1 = head;
        Node* n2 = other.head;
        single_linked_list<T> result;
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
    single_linked_list<T> intersect(const single_linked_list& other) {
        int i {}, j {};
        Node* n1 = head;
        Node* n2 = other.head;
        single_linked_list<T> result;
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
    void insertion_sort() {
         for (int i = 0; i < sz; ++i)
             _insertion_sort(head, i);
    }
    friend ostream& operator<<(ostream& out, single_linked_list sll) {
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

#endif //SINGLE_LINKED_LIST_SINGLE_LINKED_LIST_H
