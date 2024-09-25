#include <iostream>
#include <stdlib.h>
using namespace std;

#include "Deque.hpp"

int main() {

    Deque_int *a1 = Deque_int_new();
    a1->at(a1, 0) = 1234;
    printf("%d\n", a1->at(a1, 0));
    // a1->at(10) = 1234; // Will assert.
    a1->delet(a1);

    Deque_MyClass *a2 = Deque_MyClass_new();
    strcpy(a2->at(a2, 0).str, "John");
    printf("%s\n", a2->at(a2, 0).str);
    a2->delet(a2);
}