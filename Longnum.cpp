#include "Longnum.h"

std::string sum_numbers(const std::string &first_number, const std::string &second_number) {
    for (unsigned long int i = 0; i < first_number.size(); ++i) {
        if (first_number[i] < '0' || first_number[i] > '9' || (i == 0 && first_number[i] == '-'))
            throw std::invalid_argument("first_number not in integer form");
    }
    for (unsigned long int i = 0; i < second_number.size(); ++i) {
        if (second_number[i] < '0' || second_number[i] > '9' || (i == 0 && second_number[i] == '-'))
            throw std::invalid_argument("second_number not in integer form");
    }
    std::string res, big_number, low_number;
    if (first_number.size() < second_number.size()) {
        big_number = second_number;
        low_number = first_number;
    } else {
        big_number = first_number;
        low_number = second_number;
    }
    unsigned long int i = 0;
    int carry = 0;
    for (; i < low_number.size(); ++i) {
        int first_digit, second_digit;
        first_digit = low_number[i] - 48;
        second_digit = big_number[i] - 48;
        res.push_back((char) ((first_digit + second_digit + carry) % 10 + 48));
        carry = (first_digit + second_digit + carry) / 10;
    }
    for (; i < big_number.size(); ++i) {
        int digit;
        digit = big_number[i] - 48;
        res.push_back((char) ((digit + carry) % 10 + 48));
        carry = (digit + carry) / 10;
    }
    if (carry != 0)
        res.push_back((char) (carry + 48));

    return res;
}

std::string pow_of_2(unsigned long int n) {
    if (n == 0)
        return "1";
    std::string base = "2";

    for (int i = 1; i < n; ++i) {
        base = sum_numbers(base, base);
    }
    return base;
}

Longnum::Longnum() {
    number.resize(1);
    isNegativ = false;
    number[0] = 0;
}

Longnum::Longnum(long long int number) {
    // Create empty number
    this->number.resize(1);
    isNegativ = number < 0;
    number = abs(number);

    int cur_bit = 0;
    while (number != 0) {
        // If we fill chuck - go to next
        if (cur_bit == 8) {
            this->number.resize(this->number.size() + 1);
            cur_bit = 0;
        }

        // last significant bit
        int reminder = number % 2;
        number /= 2;

        this->number[this->number.size() - 1] |= (reminder << cur_bit);

        // go to next bit in current chunk
        cur_bit++;
    }
    if (isNegativ) {
        isNegativ = !isNegativ;
        *this = -*this;
    }
}

Longnum::Longnum(std::string number) {

}

std::string Longnum::toString() const {
    std::string res = "0";
    Longnum tmp = *this;
    if (tmp.isNegativ)
        tmp = -tmp;
    for (int i = 0; i < tmp.number.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tmp.number[i] & (1 << j))
                res = sum_numbers(res, pow_of_2(8 * i + j));
        }

    }
    if (this->isNegativ)
        res.push_back('-');
    std::reverse(res.begin(), res.end());
    return res;
}


std::ostream &operator<<(std::ostream &os, const Longnum &longnum) {
    os << longnum.toString();
    return os;
}


Longnum Longnum::operator+(const Longnum &second_number) const {
    Longnum res, big_number, low_number;
    if (abs(*this) < abs(second_number)) {
        big_number = second_number;
        low_number = *this;
    } else {
        big_number = *this;
        low_number = second_number;
    }

    res.isNegativ = !(abs(*this) == abs(second_number)) && big_number.isNegativ;
    big_number.number.resize(big_number.number.size() + 1);
    low_number.number.resize(big_number.number.size());

    big_number.number[big_number.number.size() - 1] = big_number.isNegativ ? 255 : 0;

    for (int i = std::min(this->number.size(), second_number.number.size()); i < big_number.number.size(); ++i) {
        low_number.number[i] = low_number.isNegativ ? 255 : 0;
    }

    unsigned short int carry = 0;
    unsigned long int i = 0;
    for (; i < low_number.number.size(); ++i) {
        unsigned short int first_block, second_block, sum_of_blocks;
        first_block = big_number.number[i];
        second_block = low_number.number[i];
        sum_of_blocks = first_block + second_block + carry;
        if (i == 0)
            res.number[0] = ((unsigned char) sum_of_blocks);
        else
            res.number.push_back((unsigned char) sum_of_blocks);
        carry = sum_of_blocks >> 8;
    }

    while (res.number[res.number.size() - 1] == 255 && res.isNegativ && res.number.size() != 1)
        res.number.erase(res.number.begin() + res.number.size() - 1, res.number.end());
    while (res.number[res.number.size() - 1] == 0 && !res.isNegativ && res.number.size() != 1)
        res.number.erase(res.number.begin() + res.number.size() - 1, res.number.end());

    return res;
}

Longnum Longnum::operator+(const long int second_number) const {
    Longnum sec_number(second_number);
    return *this + sec_number;
}

Longnum Longnum::operator-(const Longnum &second_number) const {
    Longnum tmp = -second_number;
    return *this + tmp;
}

Longnum Longnum::operator-(const long int second_number) const {
    Longnum sec_number(second_number);
    return *this - sec_number;
}

Longnum Longnum::operator*(const Longnum &second_number) const {
    Longnum res;
    for (int i = 0; abs(second_number) > i; ++i) {
        res = res + *this;
        std::cout << res << std::endl;
    }
    if (second_number.isNegativ)
        res = -res;
    return res;
}

Longnum Longnum::operator*(const long int second_number) const {
    Longnum sec_number(second_number);
    return *this * sec_number;
}

Longnum Longnum::operator-() const {
    Longnum res;
    res.number.resize(this->number.size());
    for (int i = 0; i < this->number.size(); ++i) {
        res.number[i] = ~this->number[i];
    }
    res = res + 1;
    res.isNegativ = !isNegativ;
    return res;
}

Longnum Longnum::operator++() {
    *this = *this + 1;
    return *this;
}

Longnum Longnum::operator--() {
    *this = *this - 1;
    return *this;
}

Longnum Longnum::operator++(int) {
    Longnum res(*this);
    *this = *this + 1;
    return res;
}

Longnum Longnum::operator--(int) {
    Longnum res(*this);
    *this = *this - 1;
    return res;
}

bool Longnum::operator<(const Longnum &second_number) const {
    if (this->isNegativ && !second_number.isNegativ)
        return true;
    if (!this->isNegativ && second_number.isNegativ)
        return false;
    if (this->isNegativ && second_number.isNegativ) {
        Longnum num1 = *this, num2 = second_number;
        num1 = -num1;
        num2 = -num2;
        return num1 > num2;
    }
    if (second_number.number.size() > this->number.size())
        return true;
    if (second_number.number.size() < this->number.size())
        return false;
    // If length of them are equal
    for (unsigned long int i = second_number.number.size(); i > 0; --i) {
        if (second_number.number[i - 1] > this->number[i - 1])
            return true;
        if (second_number.number[i - 1] < this->number[i - 1])
            return false;
    }
    return false;
}

bool Longnum::operator<(long int second_number) const {
    return *this < (Longnum) second_number;
}

bool Longnum::operator>(const Longnum &second_number) const {
    return !(*this < second_number) && *this != second_number;
}

bool Longnum::operator>(long int second_number) const {
    return *this > (Longnum) second_number;
}

bool Longnum::operator==(const Longnum &second_number) const {
    return !(*this < second_number) && !(second_number < *this);
}

bool Longnum::operator==(long int second_number) const {
    return *this == (Longnum) second_number;
}

bool Longnum::operator!=(const Longnum &second_number) const {
    return !(*this == second_number);
}

bool Longnum::operator!=(long int second_number) const {
    return *this != (Longnum) second_number;
}

bool Longnum::operator<=(const Longnum &second_number) const {
    return *this < second_number || *this == second_number;
}

bool Longnum::operator<=(long int second_number) const {
    return *this <= (Longnum) second_number;
}

bool Longnum::operator>=(const Longnum &second_number) const {
    return *this > second_number || *this == second_number;
}

bool Longnum::operator>=(long int second_number) const {
    return *this >= (Longnum) second_number;
}


Longnum abs(const Longnum &num) {
    Longnum res, tmp(0);
    res = num;
    if (num < tmp)
        return -res;
    return res;
}
