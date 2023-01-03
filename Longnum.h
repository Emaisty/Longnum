#ifndef LONGNUM_LONGNUM_H
#define LONGNUM_LONGNUM_H

#include <vector>
#include <string>
#include <ostream>
#include <cmath>


class Longnum {
public:

    Longnum();

    Longnum(long long int number);

    Longnum(std::string number);

    Longnum(const Longnum &number) = default;

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Longnum &longnum);

    Longnum operator+(const Longnum &second_number) const;

    Longnum operator+(long int second_number) const;

    Longnum operator-(const Longnum &second_number) const;

    Longnum operator-(long int second_number) const;

    Longnum operator*(const Longnum &second_number) const;

    Longnum operator*(long int second_number) const;

    Longnum operator/(const Longnum &second_number) const;

    Longnum operator/(long int second_number) const;

    Longnum operator%(const Longnum &second_number) const;

    Longnum operator%(long int second_number) const;

    Longnum operator<<(const Longnum &second_number) const;

    Longnum operator<<(long int second_number) const;

    Longnum operator>>(const Longnum &second_number) const;

    Longnum operator>>(long int second_number) const;

    Longnum operator-() const;

    Longnum operator++();

    Longnum operator--();

    Longnum operator++(int);

    Longnum operator--(int);

    bool operator<(const Longnum &second_number) const;

    bool operator<(long int second_number) const;

    bool operator>(const Longnum &second_number) const;

    bool operator>(long int second_number) const;

    bool operator==(const Longnum &second_number) const;

    bool operator==(long int second_number) const;

    bool operator!=(const Longnum &second_number) const;

    bool operator!=(long int second_number) const;

    bool operator<=(const Longnum &second_number) const;

    bool operator<=(long int second_number) const;

    bool operator>=(const Longnum &second_number) const;

    bool operator>=(long int second_number) const;

private:
    std::vector<unsigned char> number;
    bool isNegativ;
};

Longnum abs(const Longnum &num);

Longnum pow(const Longnum &first_number, const Longnum &second_number);

#endif //LONGNUM_LONGNUM_H
