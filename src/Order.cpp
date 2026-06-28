#include <iostream>
#include <string>
#include "Cart.cpp"
using namespace std;

class Order {
private:
    int orderId;
    string customerName;
    Cart cart;
    string status;

public:
    Order(int orderId, string customerName, Cart cart) {
        this->orderId = orderId;
        this->customerName = customerName;
        this->cart = cart;
        this->status = "Placed";
    }

    void displayOrder() {
        cout << "\n===== Order Details =====" << endl;
        cout << "Order ID : " << orderId << endl;
        cout << "Customer : " << customerName << endl;
        cout << "Status   : " << status << endl;
        cart.displayCart();
    }

    void setStatus(string s) { this->status = s; }
    string getStatus() { return status; }
};