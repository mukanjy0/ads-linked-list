#include <iostream>
#include "single_linked_list.h"

using namespace std;

void test_sll() {
    single_linked_list<int> sll;
    for (int i = 15; i > 0; --i)
        sll.push_back(i);
    cout << sll;

    sll.insertion_sort();
    cout << sll;
    sll.pop_back();
    sll.push_front(0);
    cout << sll.size() << ' ' <<  sll.front() << ' ' << sll.back() << '\n';

    for (int i = 0; i < sll.size(); ++i)
        cout << sll[i] << " \n"[i == sll.size() - 1];
    sll.reverse();
    cout << sll;
}

int main() {
    test_sll();
    return 0;
}
