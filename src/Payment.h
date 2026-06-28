#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0;
    virtual string getMethod() = 0;
    virtual ~Payment() {}
};

class CashPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Cash on Delivery of Rs." << amount << " confirmed!" << endl;
    }
    string getMethod() override { return "Cash on Delivery"; }
};

class CardPayment : public Payment {
public:
    void pay(double amount) override {
        string last4;
        cout << "Enter last 4 digits of card: "; cin >> last4;
        cout << "Card Payment of Rs." << amount << " successful! (****" << last4 << ")" << endl;
    }
    string getMethod() override { return "Card Payment"; }
};

class UPIPayment : public Payment {
public:
    void pay(double amount) override {
        string upiId;
        cout << "Enter UPI ID: "; cin >> upiId;
        cout << "UPI Payment of Rs." << amount << " to " << upiId << " successful!" << endl;
    }
    string getMethod() override { return "UPI Payment"; }
};

#endif
