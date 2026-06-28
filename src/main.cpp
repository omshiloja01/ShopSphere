#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Product.h"
#include "User.h"
#include "Cart.h"
#include "Order.h"
#include "Payment.h"
#include "Wishlist.h"
#include "SellerPanel.h"
#include "SuperAdminPanel.h"
using namespace std;

// =====================
// Sample Products (pre-loaded by platform)
// =====================
vector<Product> initCatalog() {
    return {
        Product(101, "Laptop",        "Electronics", 55000, 10, 0, "ShopSphere",  4.5, "approved"),
        Product(102, "T-Shirt",       "Clothing",      499, 50, 0, "ShopSphere",  4.2, "approved"),
        Product(103, "Headphones",    "Electronics",  1999, 20, 0, "ShopSphere",  4.7, "approved"),
        Product(104, "Running Shoes", "Footwear",     2499, 30, 0, "ShopSphere",  4.3, "approved"),
        Product(105, "Novel Book",    "Books",          299,100, 0, "ShopSphere", 4.8, "approved"),
        Product(106, "Smartwatch",    "Electronics", 12999, 15, 0, "ShopSphere",  4.6, "approved"),
        Product(107, "Backpack",      "Accessories",  1499, 25, 0, "ShopSphere",  4.4, "approved"),
        Product(108, "Water Bottle",  "Accessories",   399, 60, 0, "ShopSphere",  4.1, "approved"),
    };
}

// =====================
// Browse products by category filter or all
// =====================
void browseProducts(vector<Product>& catalog) {
    cout << "\n===== Browse =====" << endl;
    cout << "1. All Products" << endl;
    cout << "2. Filter by Category" << endl;
    cout << "3. Search by Name" << endl;
    cout << "Choice: ";
    int c; cin >> c;

    if (c == 1) {
        for (auto& p : catalog)
            if (p.isAvailable()) p.display();

    } else if (c == 2) {
        // Collect unique categories
        vector<string> cats;
        for (auto& p : catalog) {
            bool found = false;
            for (auto& cat : cats) if (cat == p.getCategory()) { found = true; break; }
            if (!found) cats.push_back(p.getCategory());
        }
        cout << "\nCategories:" << endl;
        for (int i = 0; i < (int)cats.size(); i++)
            cout << i+1 << ". " << cats[i] << endl;
        cout << "Choose category number: ";
        int n; cin >> n;
        if (n < 1 || n > (int)cats.size()) { cout << "Invalid!" << endl; return; }
        string chosen = cats[n-1];
        bool found = false;
        for (auto& p : catalog)
            if (p.getCategory() == chosen && p.isAvailable()) { p.display(); found = true; }
        if (!found) cout << "No products in this category!" << endl;

    } else if (c == 3) {
        string keyword;
        cout << "Search: "; cin.ignore(); getline(cin, keyword);
        bool found = false;
        for (auto& p : catalog)
            if (p.isAvailable() &&
               (p.getName().find(keyword) != string::npos ||
                p.getCategory().find(keyword) != string::npos)) {
                p.display(); found = true;
            }
        if (!found) cout << "No products found!" << endl;
    }
}

// =====================
// Customer Menu
// =====================
void customerMenu(Customer* user, vector<Product>& catalog, OrderManager& orderManager) {
    Cart     cart;
    Wishlist wishlist;
    int choice = 0;

    while (choice != 9) {
        cout << "\n==============================" << endl;
        cout << " Hello, " << user->getName() << "! (Customer)" << endl;
        cout << "==============================" << endl;
        cout << "1. Browse / Search Products" << endl;
        cout << "2. Add to Cart" << endl;
        cout << "3. View Cart" << endl;
        cout << "4. Remove from Cart" << endl;
        cout << "5. Wishlist" << endl;
        cout << "6. Place Order" << endl;
        cout << "7. My Orders & Tracking" << endl;
        cout << "8. Write Review" << endl;
        cout << "9. Logout" << endl;
        cout << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }

        if (choice == 1) {
            browseProducts(catalog);

        } else if (choice == 2) {
            browseProducts(catalog);
            cout << "Enter Product ID to add to cart: ";
            int pid; cin >> pid;
            bool found = false;
            for (auto& p : catalog)
                if (p.getId() == pid) { cart.addProduct(p); found = true; break; }
            if (!found) cout << "Invalid Product ID!" << endl;

        } else if (choice == 3) {
            cart.displayCart();

        } else if (choice == 4) {
            cart.displayCart();
            if (!cart.isEmpty()) {
                cout << "Enter Product ID to remove: ";
                int pid; cin >> pid;
                cart.removeProduct(pid);
            }

        } else if (choice == 5) {
            int wc;
            cout << "\n1. Add to Wishlist\n2. View Wishlist\n3. Remove\nChoice: ";
            cin >> wc;
            if (wc == 1) {
                browseProducts(catalog);
                cout << "Enter Product ID: ";
                int pid; cin >> pid;
                for (auto& p : catalog)
                    if (p.getId() == pid) { wishlist.add(p); break; }
            } else if (wc == 2) {
                wishlist.display();
            } else if (wc == 3) {
                wishlist.display();
                if (!wishlist.isEmpty()) {
                    cout << "Enter Product ID to remove: ";
                    int pid; cin >> pid;
                    wishlist.remove(pid);
                }
            }

        } else if (choice == 6) {
            cart.displayCart();
            if (cart.isEmpty()) { cout << "Cart is empty!" << endl; continue; }

            string address = user->getAddress();
            if (address.empty()) {
                cout << "Enter delivery address: "; cin.ignore(); getline(cin, address);
            } else {
                cout << "Deliver to [" << address << "]? (1=Yes / 2=New): ";
                int ac; cin >> ac;
                if (ac == 2) { cout << "New address: "; cin.ignore(); getline(cin, address); }
            }

            cout << "\nPayment:\n1. Cash on Delivery\n2. Card\n3. UPI\nChoice: ";
            int pc; cin >> pc;
            Payment* pay = nullptr;
            if      (pc == 1) pay = new CashPayment();
            else if (pc == 2) pay = new CardPayment();
            else if (pc == 3) pay = new UPIPayment();
            else { cout << "Invalid!" << endl; continue; }

            pay->pay(cart.getTotal());
            orderManager.placeOrder(user->getName(), address, cart, pay->getMethod());
            delete pay;
            cart.clearCart();

        } else if (choice == 7) {
            int oc;
            cout << "1. View All My Orders\n2. Track Order\n3. Cancel Order\nChoice: ";
            cin >> oc;
            if (oc == 1) orderManager.showCustomerHistory(user->getName());
            else if (oc == 2) orderManager.trackOrder(user->getName());
            else if (oc == 3) orderManager.cancelOrder(user->getName());

        } else if (choice == 8) {
            cout << "Enter Product ID to review: ";
            int pid; cin >> pid;
            for (auto& p : catalog) {
                if (p.getId() == pid) {
                    int r; string comment;
                    cout << "Rating (1-5): "; cin >> r;
                    cout << "Comment: "; cin.ignore(); getline(cin, comment);
                    p.addReview(user->getName(), r, comment);
                    p.displayReviews();
                    cout << "Review added!" << endl;
                    break;
                }
            }

        } else if (choice == 9) {
            cout << "Logged out. Thank you for shopping!" << endl;
        }
    }
}

// =====================
// Main
// =====================
int main() {
    vector<Product> catalog = initCatalog();
    AuthManager     auth;
    OrderManager    orderManager;

    cout << "==============================" << endl;
    cout << "   Welcome to ShopSphere!     " << endl;
    cout << "==============================" << endl;

    int mainChoice = 0;
    while (mainChoice != 6) {
        cout << "\n1. Customer Register" << endl;
        cout << "2. Seller Register" << endl;
        cout << "3. Customer Login" << endl;
        cout << "4. Seller Login" << endl;
        cout << "5. Admin Login" << endl;
        cout << "6. Exit" << endl;
        cout << "Choice: ";
        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (mainChoice == 1) {
            Customer* c = auth.registerCustomer();
            if (c) customerMenu(c, catalog, orderManager);

        } else if (mainChoice == 2) {
            Seller* s = auth.registerSeller();
            if (s) cout << "Please login after admin approves your account." << endl;

        } else if (mainChoice == 3) {
            Customer* c = auth.loginCustomer();
            if (c) customerMenu(c, catalog, orderManager);

        } else if (mainChoice == 4) {
            Seller* s = auth.loginSeller();
            if (s) {
                SellerPanel panel(s, catalog, orderManager);
                panel.showMenu();
            }

        } else if (mainChoice == 5) {
            User* u = auth.loginAdmin();
            if (u) {
                SuperAdminPanel panel(catalog, auth, orderManager);
                panel.showMenu();
            }

        } else if (mainChoice == 6) {
            cout << "Thank you for visiting ShopSphere! Goodbye!" << endl;
        }
    }

    return 0;
}
