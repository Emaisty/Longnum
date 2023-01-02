#include <iostream>
#include <vector>

#include "Longnum.h"

#include "test.cpp"

using namespace std;

int main() {
    test();
    Longnum num1(3), num2(-3), res(0);
    for (Longnum i = 0; i < num1; ++i) {
        cout << i << endl;
    }
    return 0;
}