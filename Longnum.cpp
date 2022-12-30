#include "Longnum.h"

std::string sum_numbers(const std::string &first_number, const std::string &second_number) {
    for (const auto &i: first_number) {
        if (i < '0' || i > '9')
            throw std::invalid_argument("first_number not in integer form");
    }
    for (const auto &i: second_number) {
        if (i < '0' || i > '9')
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
    isNegativ = false;

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
}

Longnum::Longnum(std::string &number) {

}

Longnum::Longnum(const Longnum &number) {
    this->number = number.number;
    this->isNegativ = number.isNegativ;
}

std::string Longnum::toString() const {
    std::string res = "0";
    for (int i = 0; i < this->number.size(); ++i) {

        for (int j = 0; j < 8; ++j) {
            if (this->number[i] & (1 << j))
                res = sum_numbers(res, pow_of_2(8 * i + j));
        }

    }
    std::reverse(res.begin(), res.end());
    return res;
}


std::ostream &operator<<(std::ostream &os, const Longnum &longnum) {
    os << longnum.toString();
    return os;
}


Longnum Longnum::operator+(const Longnum &second_number) const {
    Longnum res, big_number, low_number;
    if (*this < second_number) {
        big_number = second_number;
        low_number = *this;
    } else {
        big_number = *this;
        low_number = second_number;
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
    for (; i < big_number.number.size(); ++i) {
        unsigned short int sum_of_blocks;
        sum_of_blocks = big_number.number[i] + carry;
        if (i == 0)
            res.number[0] = ((unsigned char) sum_of_blocks);
        else
            res.number.push_back(((unsigned char) sum_of_blocks));
        carry = sum_of_blocks >> 8;
    }
    if (carry != 0)
        res.number.push_back((unsigned char) carry);

    return res;
}

bool Longnum::operator<(const Longnum &second_number) const {
    if (second_number.number.size() > this->number.size())
        return true;
    if (second_number.number.size() < this->number.size())
        return false;
    // If length of them are equal
    for (unsigned long int i = second_number.number.size() - 1; i > 0; --i) {
        if (second_number.number[i] > this->number[i])
            return true;
        if (second_number.number[i] < this->number[i])
            return false;
    }
    return false;
}

bool Longnum::operator>(const Longnum &second_number) const {
    return !(*this < second_number) && *this != second_number;
}

bool Longnum::operator==(const Longnum &second_number) const {
    return !(*this < second_number) && !(second_number < *this);
}

bool Longnum::operator!=(const Longnum &second_number) const {
    return !(*this == second_number);
}

bool Longnum::operator<=(const Longnum &second_number) const {
    return *this < second_number || *this == second_number;
}

bool Longnum::operator>=(const Longnum &second_number) const {
    return *this > second_number || *this == second_number;
}