#include <iostream>
#include <vector>

using namespace std;

class Longnum {
private:
    vector<int> number;

    bool check() {
        for (int i = 0; i < this->number.size(); ++i) {
            if (this->number[i] > 9)
                return false;
        }
        return true;
    }

public:
    Longnum(vector<int> input = vector<int>(0)) {
        this->number = input;
        if (!check()) {
            this->number = vector<int>(0);
        }
    }


    Longnum &operator+(Longnum another_number) {
        vector<int> smaller_num, bigger_num;
        if (this->number.size() > another_number.number.size()) {
            bigger_num = this->number;
            smaller_num = another_number.number;
        } else {
            smaller_num = this->number;
            bigger_num = another_number.number;
        }

    }

    friend istream &operator>>(istream &is, Longnum &Num) {
        string str;
        cin >> str;
        for (int i = str.size() - 1; i >= 0; --i) {
            Num.number.push_back((int) str[i] - 48);
        }
        if (!Num.check()) {
            Num.number = vector<int>(0);
        }
        return is;
    }

    friend ostream &operator<<(ostream &os, Longnum &Num) {
        for (int i = Num.number.size() - 1; i >= 0; --i) {
            cout << Num.number[i];
        }
        cout << ' ';
        return os;
    }

};


int main() {
    Longnum a, b, c;
    cin >> a >> b;
    cout << a << b;
    return EXIT_SUCCESS;
}
