#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

class Cart {
private:
    vector<Product> items;

public:
    void addProduct(Product p) {
        if (!p.isAvailable()) {
            cout << "Sorry! " << p.getName() << " is out of stock or not available." << endl;
            return;
        }
        items.push_back(p);
        cout << p.getName() << " added to cart!" << endl;
    }

    void removeProduct(int productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == productId) {
                cout << it->getName() << " removed from cart." << endl;
                items.erase(it);
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void displayCart() {
        if (items.empty()) { cout << "Cart is empty!" << endl; return; }
        cout << "\n===== Your Cart =====" << endl;
        for (auto& p : items) p.display();
        cout << "------------------------------" << endl;
        cout << "Total: Rs." << getTotal() << endl;
    }

    double getTotal() {
        double total = 0;
        for (auto& p : items) total += p.getPrice();
        return total;
    }

    vector<Product> getItems() { return items; }
    bool isEmpty()  { return items.empty(); }
    void clearCart(){ items.clear(); }
};

#endif
