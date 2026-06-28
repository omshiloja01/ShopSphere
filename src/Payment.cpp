#include <iostream>
using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() {}
};

class CashPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Cash Payment of Rs." << amount << " successful!" << endl;
    }
};

class CardPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Card Payment of Rs." << amount << " successful!" << endl;
    }
};