#include <iostream>
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "circular_doubly_linked_list.h"

using namespace std;

void test_sll() {
    cout << "singly linked list tests\n";
    singly_linked_list<int> sll;
    for (int i = 15; i > 0; --i)
        sll.push_back(i);
    cout << sll;

    sll.sort();
    cout << sll;
    cout << sll.pop_front() <<'\n';
    cout << sll.pop_back() <<'\n';
    sll.push_front(0);
    cout << sll.size() << ' ' <<  sll.front() << ' ' << sll.back() << '\n';

    for (int i = 0; i < sll.size(); ++i)
        cout << sll[i] << " \n"[i == sll.size() - 1];
    sll.reverse();
    cout << sll;
}

void test_dll() {
    cout << "doubly linked list tests\n";
    // testing push
    cout << "\nTesting push\n";
    doubly_linked_list<int> dll;
    for (int i = 15; i > 0; --i)
        if (i&1)
            dll.push_back(i);
        else
            dll.push_front(i);
    cout << dll;
    cout << dll.front() << ' ' << dll.back() << '\n';

    // testing pop
    cout << "\nTesting pop\n";
    cout << dll.pop_back() << '\n';
    cout << dll.pop_front() << '\n';
    cout << dll.front() << ' ' << dll.back() << '\n';
    // testing printing with indexing
    for (int i = 0; i < dll.size(); ++i)
        cout << dll[i] << " \n"[i == dll.size() - 1];

    // testing reverse
    cout << "\nPrior to reverse: " << dll;
    dll.reverse();
    cout << "After reverse: " << dll;

    // testing insert + remove
    cout << "\nTesting insert + remove\n";
    dll.insert(0, dll.size());
    dll.insert(1, 0);
    dll.insert(2, dll.size() - 1);
    dll.remove(7);
    cout << dll;

    // testing empty + clear
    cout << "\nTesting empty & clear\n";
    cout << dll;
    cout << boolalpha << dll.empty() << '\n';
    dll.clear();
    cout << dll;
    cout << boolalpha << dll.empty() << '\n';
}

void test_dll_is_palindrome() {
    cout << "\nTesting is_palindrome\n";
    doubly_linked_list<int> dll;
    for (int i = 0; i < 10; ++i)
        dll.push_back(i);
    for (int i = 0; i < 10; ++i)
        dll.push_front(i);
    cout << dll;
    cout << boolalpha << dll.is_palindrome() << '\n';
    cout << dll.pop_front() << '\n';
    cout << boolalpha << dll.is_palindrome() << '\n';
}

void test_dll_sorted_insert() {
    cout << "\nTesting sorted_insert\n";
    doubly_linked_list<int> dll;
    for (int i = 15; i > 0; --i)
        if (i&1)
            dll.sorted_insert(16 - i);
        else
            dll.sorted_insert(i);
    dll.sorted_insert(0);
    dll.sorted_insert(100);
    cout << dll;
}

void test_dll_remove_duplicates() {
    cout << "\nTesting remove_duplicates\n";
    doubly_linked_list<int> dll;
    for (int i = 10; i > 0; --i) {
        for (int j = 11 - i; j > 0; --j)
            dll.push_back(i);
    }

    cout << dll;
    dll.remove_duplicates();
    cout << dll;
}

void test_cdll() {
    cout << "singly linked list tests\n";
    circular_doubly_linked_list<int> cdll;
    cout << boolalpha << cdll.empty() << '\n';
    for (int i = 0 ; i < 10; ++i)
        cdll.push_front(i);
    cout << boolalpha << cdll.empty() << ' ' << cdll.size() << '\n';
    cdll.reverse();
    cout << cdll;
    for (int i = 10 ; i < 20; ++i)
        cdll.push_back(i);
    cout << cdll;
    cout << cdll.pop_front() << ' ' << cdll.pop_back() << '\n';
    cdll.insert(14, 15);
    cout << cdll;
    cout << cdll.size() << '\n';
    cdll.remove(15);
    cout << cdll;
}

// forward list ~= singly linked list
int main() {
//    test_sll();
//    cout << '\n';
//    test_dll_is_palindrome();
//    cout << '\n';
//    test_dll_sorted_insert();
//    cout << '\n';
//    test_dll_remove_duplicates();
    test_cdll();
    return 0;
}
