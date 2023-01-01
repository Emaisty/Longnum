#include <iostream>
#include <vector>

#include "Longnum.h"

#include "test.cpp"

using namespace std;

int main() {
    test();
    Longnum kek, lol;
    kek = 12;
    lol = 13;
    kek = kek*lol;
    cout << kek * -2;

    return 0;
}