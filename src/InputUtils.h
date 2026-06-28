#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

inline int readInt() {
    int value;
    while (true) {
        if (cin >> value) {
            return value;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number: ";
        }
    }
}

inline double readDouble() {
    double value;
    while (true) {
        if (cin >> value) {
            return value;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number: ";
        }
    }
}

inline string readPhone() {
    string value;
    while (true) {
        getline(cin, value);
        bool valid = true;
        if (value.length() != 10) valid = false;
        for (char c : value) {
            if (!isdigit(c)) valid = false;
        }
        if (valid) return value;
        cout << "Invalid phone number. It must be exactly 10 digits. Try again: ";
    }
}

#endif
