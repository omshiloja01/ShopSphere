#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Cart.h"
using namespace std;

class Order {
private:
    int    orderId;
    string customerName;
    string address;
    Cart   cart;
    string paymentMethod;
    string trackingStatus; // Placed -> Shipped -> Out for Delivery -> Delivered

public:
    Order() {}
    Order(int orderId, string customerName, string address, Cart cart, string paymentMethod) {
        this->orderId        = orderId;
        this->customerName   = customerName;
        this->address        = address;
        this->cart           = cart;
        this->paymentMethod  = paymentMethod;
        this->trackingStatus = "Placed";
    }

    void displayOrder() {
        cout << "\n===== Order Details =====" << endl;
        cout << "Order ID   : " << orderId << endl;
        cout << "Customer   : " << customerName << endl;
        cout << "Deliver To : " << address << endl;
        cout << "Payment    : " << paymentMethod << endl;
        cout << "Status     : " << trackingStatus << endl;
        cart.displayCart();
        cout << "=========================" << endl;
    }

    void displayTracking() {
        cout << "\n--- Order #" << orderId << " Tracking ---" << endl;
        cout << "[" << (trackingStatus == "Placed"            ? ">>>" : "   ") << "] Placed" << endl;
        cout << "[" << (trackingStatus == "Shipped"           ? ">>>" : "   ") << "] Shipped" << endl;
        cout << "[" << (trackingStatus == "Out for Delivery"  ? ">>>" : "   ") << "] Out for Delivery" << endl;
        cout << "[" << (trackingStatus == "Delivered"         ? ">>>" : "   ") << "] Delivered" << endl;
    }

    void setTrackingStatus(string s)  { trackingStatus = s; }
    string getTrackingStatus()        { return trackingStatus; }
    int    getOrderId()               { return orderId; }
    string getCustomerName()          { return customerName; }
    double getTotal()                 { return cart.getTotal(); }
    Cart&  getCart()                  { return cart; }
};

// =====================
// Order Manager
// =====================
class OrderManager {
private:
    vector<Order> orders;
    int nextOrderId = 1001;

public:
    void placeOrder(string customerName, string address, Cart& cart, string paymentMethod) {
        Order o(nextOrderId++, customerName, address, cart, paymentMethod);
        orders.push_back(o);
        orders.back().displayOrder();
        cout << "Order placed! Order ID: " << nextOrderId - 1 << endl;
    }

    void showCustomerHistory(string customerName) {
        bool found = false;
        cout << "\n===== Your Orders =====" << endl;
        for (auto& o : orders) {
            if (o.getCustomerName() == customerName) {
                o.displayOrder();
                found = true;
            }
        }
        if (!found) cout << "No orders found!" << endl;
    }

    void trackOrder(string customerName) {
        cout << "Enter Order ID: ";
        int id; cin >> id;
        for (auto& o : orders) {
            if (o.getOrderId() == id && o.getCustomerName() == customerName) {
                o.displayTracking();
                return;
            }
        }
        cout << "Order not found!" << endl;
    }

    void cancelOrder(string customerName) {
        cout << "Enter Order ID to cancel: ";
        int id; cin >> id;
        for (auto& o : orders) {
            if (o.getOrderId() == id && o.getCustomerName() == customerName) {
                if (o.getTrackingStatus() == "Placed") {
                    o.setTrackingStatus("Cancelled");
                    cout << "Order #" << id << " has been successfully cancelled." << endl;
                } else if (o.getTrackingStatus() == "Cancelled") {
                    cout << "Order is already cancelled." << endl;
                } else {
                    cout << "Order cannot be cancelled because it is already " << o.getTrackingStatus() << "." << endl;
                }
                return;
            }
        }
        cout << "Order not found!" << endl;
    }

    void showAllOrders() {
        if (orders.empty()) { cout << "No orders yet!" << endl; return; }
        cout << "\n===== All Orders =====" << endl;
        for (auto& o : orders) o.displayOrder();
    }

    // Admin: update tracking
    void updateTracking() {
        cout << "Enter Order ID: ";
        int id; cin >> id;
        for (auto& o : orders) {
            if (o.getOrderId() == id) {
                cout << "Current Status: " << o.getTrackingStatus() << endl;
                cout << "1. Placed\n2. Shipped\n3. Out for Delivery\n4. Delivered\nChoice: ";
                int c; cin >> c;
                if      (c == 1) o.setTrackingStatus("Placed");
                else if (c == 2) o.setTrackingStatus("Shipped");
                else if (c == 3) o.setTrackingStatus("Out for Delivery");
                else if (c == 4) o.setTrackingStatus("Delivered");
                cout << "Tracking updated!" << endl;
                return;
            }
        }
        cout << "Order not found!" << endl;
    }

    // Platform stats
    int getTotalOrders()       { return orders.size(); }
    double getTotalRevenue() {
        double total = 0;
        for (auto& o : orders) total += o.getTotal();
        return total;
    }
};

#endif
