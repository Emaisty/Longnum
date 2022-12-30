#ifndef UNIT_TESTS

#include <sstream>
#include "random"

#include "Longnum.h"


void constructor() {
    // with integer
    for (int i = 0; i < 1000; ++i) {
        std::ostringstream oss;
        int number = rand();
        Longnum num(number);
        assert(num.toString() == std::to_string(number));
        oss << num;
        assert(oss.str() == std::to_string(number));
    }
}

void operators() {
    // lower
    for (int i = 0; i < 1000; ++i) {
        long long int number1 = rand(), number2 = rand();
        Longnum num1(number1), num2(number2);
        assert((num1 < num2) == (number1 < number2));
    }

    //plus
    for (int i = 0; i < 1000; ++i) {
        long long int number1 = rand(), number2 = rand();
        Longnum num1(number1), num2(number2), res(number1 + number2), tmp;
        tmp = num1 + num2;
        assert(res == num1 + num2 && tmp.toString() == std::to_string(number1 + number2));
    }
}


void test() {
    constructor();
    operators();
}

#endif