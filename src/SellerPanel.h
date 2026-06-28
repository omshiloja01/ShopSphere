#ifndef SELLERPANEL_H
#define SELLERPANEL_H

#include <iostream>
#include <vector>
#include "Product.h"
#include "User.h"
#include "Order.h"
using namespace std;

class SellerPanel {
private:
    Seller*          seller;
    vector<Product>& catalog;
    OrderManager&    orderManager;
    int              nextProductId;

    // Only seller's products
    vector<Product*> getMyProducts() {
        vector<Product*> mine;
        for (auto& p : catalog)
            if (p.getSellerId() == seller->getId()) mine.push_back(&p);
        return mine;
    }

    void listMyProducts() {
        auto mine = getMyProducts();
        if (mine.empty()) { cout << "You have no products yet." << endl; return; }
        cout << "\n===== Your Products =====" << endl;
        for (auto p : mine) p->display();
    }

    Product* findMyProduct(int id) {
        for (auto& p : catalog)
            if (p.getId() == id && p.getSellerId() == seller->getId()) return &p;
        return nullptr;
    }

public:
    SellerPanel(Seller* s, vector<Product>& cat, OrderManager& om)
        : seller(s), catalog(cat), orderManager(om) {
        nextProductId = 500 + seller->getId() * 100;
        for (auto& p : catalog)
            if (p.getSellerId() == seller->getId() && p.getId() >= nextProductId)
                nextProductId = p.getId() + 1;
    }

    void addProduct() {
        string name, category;
        double price; int stock;
        cout << "\n===== Add Product =====" << endl;
        cout << "Name     : "; cin.ignore(); getline(cin, name);
        cout << "Category : "; getline(cin, category);
        cout << "Price    : Rs."; cin >> price;
        cout << "Stock    : "; cin >> stock;

        catalog.push_back(Product(nextProductId++, name, category, price, stock,
                                  seller->getId(), seller->getName(), 0.0, "pending"));
        cout << "Product submitted for admin approval!" << endl;
    }

    void editProduct() {
        listMyProducts();
        cout << "Enter Product ID to edit: ";
        int id; cin >> id;
        Product* p = findMyProduct(id);
        if (!p) { cout << "Product not found!" << endl; return; }

        cout << "1. Name\n2. Category\n3. Price\n4. Stock\nChoice: ";
        int c; cin >> c;
        if (c == 1) { string n; cout << "New Name: "; cin.ignore(); getline(cin, n); p->setName(n); }
        else if (c == 2) { string cat; cout << "New Category: "; cin.ignore(); getline(cin, cat); p->setCategory(cat); }
        else if (c == 3) { double pr; cout << "New Price: Rs."; cin >> pr; p->setPrice(pr); }
        else if (c == 4) { int st; cout << "New Stock: "; cin >> st; p->setStock(st); }
        cout << "Updated! (Changes need re-approval)" << endl;
        p->setStatus("pending");
    }

    void deleteProduct() {
        listMyProducts();
        cout << "Enter Product ID to delete: ";
        int id; cin >> id;
        for (auto it = catalog.begin(); it != catalog.end(); ++it) {
            if (it->getId() == id && it->getSellerId() == seller->getId()) {
                cout << it->getName() << " deleted." << endl;
                catalog.erase(it);
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    void salesReport() {
        auto mine = getMyProducts();
        cout << "\n===== Sales Report - " << seller->getName() << " =====" << endl;
        cout << "Shop: " << seller->getShopName() << endl;
        cout << "Total Products Listed: " << mine.size() << endl;
        int approved = 0, pending = 0;
        for (auto p : mine) {
            if (p->getStatus() == "approved") approved++;
            else if (p->getStatus() == "pending") pending++;
        }
        cout << "Approved Products : " << approved << endl;
        cout << "Pending Approval  : " << pending << endl;
    }

    void showMenu() {
        int choice = 0;
        while (choice != 6) {
            cout << "\n==============================" << endl;
            cout << " SELLER PANEL - " << seller->getShopName() << endl;
            cout << "==============================" << endl;
            cout << "1. View My Products" << endl;
            cout << "2. Add New Product" << endl;
            cout << "3. Edit Product" << endl;
            cout << "4. Delete Product" << endl;
            cout << "5. Sales Report" << endl;
            cout << "6. Logout" << endl;
            cout << "Choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }

            if      (choice == 1) listMyProducts();
            else if (choice == 2) addProduct();
            else if (choice == 3) editProduct();
            else if (choice == 4) deleteProduct();
            else if (choice == 5) salesReport();
            else if (choice == 6) cout << "Seller logged out." << endl;
            else cout << "Invalid choice!" << endl;
        }
    }
};

#endif
