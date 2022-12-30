#ifndef LONGNUM_LONGNUM_H
#define LONGNUM_LONGNUM_H

#include <vector>
#include <string>
#include <ostream>


class Longnum {
public:

    Longnum();

    Longnum(long long int number);

    Longnum(std::string &number);

    Longnum(const Longnum &number) = default;

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Longnum &longnum);

    Longnum operator+(const Longnum &second_number) const;

    Longnum operator+(long int second_number) const;

    Longnum operator-() const;

    bool operator<(const Longnum &second_number) const;

    bool operator>(const Longnum &second_number) const;

    bool operator==(const Longnum &second_number) const;

    bool operator!=(const Longnum &second_number) const;

    bool operator<=(const Longnum &second_number) const;

    bool operator>=(const Longnum &second_number) const;

private:
    std::vector<unsigned char> number;
    bool isNegativ;
};

Longnum abs(const Longnum& num);

#endif //LONGNUM_LONGNUM_H
