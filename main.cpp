#include <iostream>
#include <vector>

#include "Longnum.h"

#include "test.cpp"

using namespace std;

int main() {
    test();
   /* short int a = -14794,b = -22571;
    Longnum res(-22571), kek(-14794), r;
    r = res + (-14794);
    cout << r << ' ' << to_string(a+b);*/

    short int number1 = 26369,number2 = -26470;
    Longnum num1(number1), num2(number2), res(number1 + number2), tmp;
    tmp = num1 + num2;
    cout << tmp << endl;
    cout << res;
    assert(res == num1 + num2);
    assert(tmp.toString() == std::to_string(number1 + number2));
    assert(res == num1 + number2);
    return 0;
}