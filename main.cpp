#include <iostream>
#include <vector>

using namespace std;

class Longnum {
private:
    //Number. Saved as vector, where 1 cell = 1 digit
    vector<int> number;

    //check number for non-digit symbols
    //return true, if number correct
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


    Longnum operator+(Longnum another_number) {
        vector<int> smaller_num, bigger_num;
        if (this->number.size() > another_number.number.size()) {
            bigger_num = this->number;
            smaller_num = another_number.number;
        } else {
            smaller_num = this->number;
            bigger_num = another_number.number;
        }
        int extra = 0, extra_new = 0;
        for (int i = 0; i < bigger_num.size(); ++i) {
            extra_new = (bigger_num[i] + smaller_num[i] + extra) / 10;
            bigger_num[i] = (bigger_num[i] + smaller_num[i] + extra) % 10;
            extra = extra_new;
        }
        if (extra != 0)
            bigger_num.push_back(extra);
        return Longnum(bigger_num);
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
    c = a + b;
    cout << c;
    return EXIT_SUCCESS;
}
