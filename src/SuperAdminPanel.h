#ifndef SUPERADMINPANEL_H
#define SUPERADMINPANEL_H

#include <iostream>
#include <vector>
#include "Product.h"
#include "User.h"
#include "Order.h"
using namespace std;

class SuperAdminPanel {
private:
    vector<Product>& catalog;
    AuthManager&     auth;
    OrderManager&    orderManager;

    void approvePendingProducts() {
        bool found = false;
        cout << "\n===== Pending Products =====" << endl;
        for (auto& p : catalog) {
            if (p.getStatus() == "pending") {
                p.display();
                found = true;
                cout << "1. Approve  2. Reject  3. Skip: ";
                int c; cin >> c;
                if      (c == 1) { p.setStatus("approved"); cout << "Approved!" << endl; }
                else if (c == 2) { p.setStatus("rejected"); cout << "Rejected!" << endl; }
            }
        }
        if (!found) cout << "No pending products!" << endl;
    }

    void viewAllProducts() {
        if (catalog.empty()) { cout << "No products!" << endl; return; }
        cout << "\n===== All Products =====" << endl;
        for (auto& p : catalog) p.display();
    }

    void manageCustomers() {
        auto& customers = auth.getCustomers();
        if (customers.empty()) { cout << "No customers registered!" << endl; return; }
        cout << "\n===== Customers =====" << endl;
        int i = 1;
        for (auto& c : customers) {
            cout << i++ << ". "; c.showRole();
            cout << "   Status: " << (c.getIsBlocked() ? "BLOCKED" : "Active") << endl;
        }
        cout << "\nEnter customer number to block/unblock (0 to skip): ";
        int n; cin >> n;
        if (n > 0 && n <= (int)customers.size()) {
            customers[n-1].setBlocked(!customers[n-1].getIsBlocked());
            cout << (customers[n-1].getIsBlocked() ? "Customer blocked!" : "Customer unblocked!") << endl;
        }
    }

    void manageSellers() {
        auto& sellers = auth.getSellers();
        if (sellers.empty()) { cout << "No sellers registered!" << endl; return; }
        cout << "\n===== Sellers =====" << endl;
        int i = 1;
        for (auto& s : sellers) {
            cout << i++ << ". "; s.showRole();
            cout << "   Blocked: " << (s.getIsBlocked() ? "YES" : "No") << endl;
        }
        cout << "\n1. Approve Seller\n2. Block/Unblock Seller\n3. Back\nChoice: ";
        int c; cin >> c;

        if (c == 1) {
            cout << "Enter seller number to approve: ";
            int n; cin >> n;
            if (n > 0 && n <= (int)sellers.size()) {
                sellers[n-1].setApproved(true);
                cout << sellers[n-1].getName() << " approved as seller!" << endl;
            }
        } else if (c == 2) {
            cout << "Enter seller number to block/unblock: ";
            int n; cin >> n;
            if (n > 0 && n <= (int)sellers.size()) {
                sellers[n-1].setBlocked(!sellers[n-1].getIsBlocked());
                cout << (sellers[n-1].getIsBlocked() ? "Seller blocked!" : "Seller unblocked!") << endl;
            }
        }
    }

    void platformStats() {
        cout << "\n===== Platform Statistics =====" << endl;
        cout << "Total Customers  : " << auth.getCustomers().size() << endl;
        cout << "Total Sellers    : " << auth.getSellers().size() << endl;
        cout << "Total Products   : " << catalog.size() << endl;
        cout << "Total Orders     : " << orderManager.getTotalOrders() << endl;
        cout << "Total Revenue    : Rs." << orderManager.getTotalRevenue() << endl;

        int approved = 0, pending = 0;
        for (auto& p : catalog) {
            if (p.getStatus() == "approved") approved++;
            else if (p.getStatus() == "pending") pending++;
        }
        cout << "Approved Products: " << approved << endl;
        cout << "Pending Approval : " << pending << endl;
    }

public:
    SuperAdminPanel(vector<Product>& cat, AuthManager& a, OrderManager& om)
        : catalog(cat), auth(a), orderManager(om) {}

    void showMenu() {
        int choice = 0;
        while (choice != 8) {
            cout << "\n==============================" << endl;
            cout << "     SUPER ADMIN PANEL        " << endl;
            cout << "==============================" << endl;
            cout << "1. Platform Statistics" << endl;
            cout << "2. Approve Pending Products" << endl;
            cout << "3. View All Products" << endl;
            cout << "4. Manage Customers" << endl;
            cout << "5. Manage Sellers" << endl;
            cout << "6. View All Orders" << endl;
            cout << "7. Update Order Tracking" << endl;
            cout << "8. Logout" << endl;
            cout << "Choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }

            if      (choice == 1) platformStats();
            else if (choice == 2) approvePendingProducts();
            else if (choice == 3) viewAllProducts();
            else if (choice == 4) manageCustomers();
            else if (choice == 5) manageSellers();
            else if (choice == 6) orderManager.showAllOrders();
            else if (choice == 7) orderManager.updateTracking();
            else if (choice == 8) cout << "Super Admin logged out." << endl;
            else cout << "Invalid choice!" << endl;
        }
    }
};

#endif
