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

    Longnum(const Longnum &number);

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Longnum &longnum);

    Longnum operator+(const Longnum &second_number) const;

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

#endif //LONGNUM_LONGNUM_H
