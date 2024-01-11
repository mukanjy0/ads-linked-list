#include <iostream>
#include "single_linked_list.h"
#include "double_linked_list.h"

using namespace std;

void test_sll() {
    cout << "Single linked list tests\n";
    single_linked_list<int> sll;
    for (int i = 15; i > 0; --i)
        sll.push_back(i);
    cout << sll;

    sll.sort();
    cout << sll;
    sll.pop_back();
    sll.push_front(0);
    cout << sll.size() << ' ' <<  sll.front() << ' ' << sll.back() << '\n';

    for (int i = 0; i < sll.size(); ++i)
        cout << sll[i] << " \n"[i == sll.size() - 1];
    sll.reverse();
    cout << sll;
}

void test_dll() {
    cout << "Double linked list tests\n";
    // testing push
    cout << "\nTesting push\n";
    double_linked_list<int> dll;
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

    // testing empty + clear
    cout << "\nTesting empty & clear\n";
    cout << dll;
    cout << boolalpha << dll.empty() << '\n';
    dll.clear();
    cout << dll;
    cout << boolalpha << dll.empty() << '\n';
}

int main() {
    test_dll();
    return 0;
}
