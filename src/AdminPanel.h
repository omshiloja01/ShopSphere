#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <iostream>
#include <vector>
#include <string>
#include "Product.h"
#include "Order.h"
using namespace std;

class AdminPanel {
private:
    vector<Product>& catalog;
    OrderManager& orderManager;
    int nextProductId;

    void listProducts() {
        if (catalog.empty()) { cout << "No products in catalog!" << endl; return; }
        cout << "\n===== Product Catalog =====" << endl;
        for (auto& p : catalog) p.display();
    }

    Product* findProduct(int id) {
        for (auto& p : catalog) {
            if (p.getId() == id) return &p;
        }
        return nullptr;
    }

public:
    AdminPanel(vector<Product>& catalog, OrderManager& om) : catalog(catalog), orderManager(om) {
        nextProductId = 200;
        for (auto& p : catalog)
            if (p.getId() >= nextProductId) nextProductId = p.getId() + 1;
    }

    // 1. Add new product
    void addProduct() {
        string name, category;
        double price, rating;
        int stock;

        cout << "\n===== Add New Product =====" << endl;
        cout << "Product Name   : "; cin.ignore(); getline(cin, name);
        cout << "Category       : "; getline(cin, category);
        cout << "Price (Rs.)    : "; cin >> price;
        cout << "Stock Quantity : "; cin >> stock;
        cout << "Rating (0-5)   : "; cin >> rating;

        catalog.push_back(Product(nextProductId++, name, category, price, stock, rating));
        cout << "\nProduct '" << name << "' added successfully! ID: " << nextProductId - 1 << endl;
    }

    // 2. Update price
    void updatePrice() {
        listProducts();
        cout << "\nEnter Product ID to update price: ";
        int id; cin >> id;
        Product* p = findProduct(id);
        if (!p) { cout << "Product not found!" << endl; return; }

        cout << "Current Price: Rs." << p->getPrice() << endl;
        cout << "New Price     : Rs."; 
        double newPrice; cin >> newPrice;
        p->setPrice(newPrice);
        cout << "Price updated successfully!" << endl;
    }

    // 3. Update stock
    void updateStock() {
        listProducts();
        cout << "\nEnter Product ID to update stock: ";
        int id; cin >> id;
        Product* p = findProduct(id);
        if (!p) { cout << "Product not found!" << endl; return; }

        cout << "Current Stock: " << p->getStock() << endl;
        cout << "New Stock     : ";
        int newStock; cin >> newStock;
        p->setStock(newStock);
        cout << "Stock updated successfully!" << endl;
    }

    // 4. Delete product
    void deleteProduct() {
        listProducts();
        cout << "\nEnter Product ID to delete: ";
        int id; cin >> id;

        for (auto it = catalog.begin(); it != catalog.end(); ++it) {
            if (it->getId() == id) {
                cout << "Product '" << it->getName() << "' deleted successfully!" << endl;
                catalog.erase(it);
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    // 5. View all products
    void viewAllProducts() {
        listProducts();
    }

    // 6. View all orders
    void viewAllOrders() {
        orderManager.showAllOrders();
    }

    // 7. Update product details
    void updateProductDetails() {
        listProducts();
        cout << "\nEnter Product ID to edit: ";
        int id; cin >> id;
        Product* p = findProduct(id);
        if (!p) { cout << "Product not found!" << endl; return; }

        p->display();
        cout << "\nWhat to update?" << endl;
        cout << "1. Name\n2. Category\n3. Price\n4. Stock\n5. Rating\nChoice: ";
        int c; cin >> c;

        if (c == 1) {
            string n; cout << "New Name: "; cin.ignore(); getline(cin, n);
            p->setName(n); cout << "Name updated!" << endl;
        } else if (c == 2) {
            string cat; cout << "New Category: "; cin.ignore(); getline(cin, cat);
            p->setCategory(cat); cout << "Category updated!" << endl;
        } else if (c == 3) {
            double pr; cout << "New Price: Rs."; cin >> pr;
            p->setPrice(pr); cout << "Price updated!" << endl;
        } else if (c == 4) {
            int st; cout << "New Stock: "; cin >> st;
            p->setStock(st); cout << "Stock updated!" << endl;
        } else if (c == 5) {
            double r; cout << "New Rating (0-5): "; cin >> r;
            p->setRating(r); cout << "Rating updated!" << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    // Admin Menu
    void showMenu() {
        int choice = 0;
        while (choice != 8) {
            cout << "\n==============================" << endl;
            cout << "      ADMIN PANEL             " << endl;
            cout << "==============================" << endl;
            cout << "1. View All Products" << endl;
            cout << "2. Add New Product" << endl;
            cout << "3. Edit Product Details" << endl;
            cout << "4. Update Price" << endl;
            cout << "5. Update Stock/Quantity" << endl;
            cout << "6. Delete Product" << endl;
            cout << "7. View All Orders" << endl;
            cout << "8. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;

            if      (choice == 1) viewAllProducts();
            else if (choice == 2) addProduct();
            else if (choice == 3) updateProductDetails();
            else if (choice == 4) updatePrice();
            else if (choice == 5) updateStock();
            else if (choice == 6) deleteProduct();
            else if (choice == 7) viewAllOrders();
            else if (choice == 8) cout << "Admin logged out." << endl;
            else cout << "Invalid choice!" << endl;
        }
    }
};

#endif
