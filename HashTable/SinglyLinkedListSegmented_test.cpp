#include "SinglyLinkedListSegmented.cpp"
#include <iostream>

using namespace std;

int main() {
    SinglyLinkedListSegmented<int, char> list;

    list.insertAtTail(1, '1');
    list.insertAtTail(2, '2');
    list.insertAtTail(3, '3');
    list.insertAtTail(4, '4');
    list.insertAtTail(5, '5');
    list.insertAtTail(6, '6');
    list.insertAtTail(7, '7');
    list.insertAtTail(8, '8');
    list.insertAtTail(9, '9');

    cout << list.search(1)->value << endl;
    cout << list.search(2)->value << endl;
    cout << list.search(3)->value << endl;

    list.remove(3);
    list.printSegments();
    list.remove(6);
    list.printSegments();
    list.remove(9);
    list.printSegments();
}