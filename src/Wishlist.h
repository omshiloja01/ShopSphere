#ifndef WISHLIST_H
#define WISHLIST_H

#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

class Wishlist {
private:
    vector<Product> items;

public:
    void add(Product p) {
        for (auto& w : items)
            if (w.getId() == p.getId()) { cout << p.getName() << " already in wishlist!" << endl; return; }
        items.push_back(p);
        cout << p.getName() << " added to wishlist!" << endl;
    }

    void remove(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == id) { cout << it->getName() << " removed." << endl; items.erase(it); return; }
        }
        cout << "Not found in wishlist." << endl;
    }

    void display() {
        if (items.empty()) { cout << "Wishlist is empty!" << endl; return; }
        cout << "\n===== Wishlist =====" << endl;
        for (auto& p : items) p.display();
    }

    bool isEmpty() { return items.empty(); }
};

#endif
