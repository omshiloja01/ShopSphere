#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include "InputUtils.h"
using namespace std;

// =====================
// Base User
// =====================
class User {
protected:
    int    id;
    string name;
    string email;
    string password;
    string phone;
    string address;
    bool   isBlocked;

public:
    User() : id(0), isBlocked(false) {}
    User(int id, string name, string email, string password,
         string phone = "", string address = "")
        : id(id), name(name), email(email), password(password),
          phone(phone), address(address), isBlocked(false) {}

    int    getId()          { return id; }
    string getName()        { return name; }
    string getEmail()       { return email; }
    string getPassword()    { return password; }
    string getPhone()       { return phone; }
    string getAddress()     { return address; }
    bool   getIsBlocked()   { return isBlocked; }

    void setAddress(string a)   { address = a; }
    void setPhone(string p)     { phone = p; }
    void setBlocked(bool b)     { isBlocked = b; }

    virtual void showRole() = 0;
    virtual string getRole() = 0;
    virtual ~User() {}
};

// =====================
// Customer
// =====================
class Customer : public User {
public:
    Customer() {}
    Customer(int id, string name, string email, string password,
             string phone = "", string address = "")
        : User(id, name, email, password, phone, address) {}

    void showRole() override {
        cout << "[Customer] " << name << " | " << email << endl;
    }
    string getRole() override { return "customer"; }
};

// =====================
// Seller / Owner
// =====================
class Seller : public User {
private:
    string shopName;
    bool   isApproved;

public:
    Seller() : isApproved(false) {}
    Seller(int id, string name, string email, string password,
           string shopName, string phone = "")
        : User(id, name, email, password, phone), shopName(shopName), isApproved(false) {}

    string getShopName()    { return shopName; }
    bool   getIsApproved()  { return isApproved; }
    void   setApproved(bool a) { isApproved = a; }

    void showRole() override {
        cout << "[Seller] " << name << " | Shop: " << shopName
             << " | Status: " << (isApproved ? "Approved" : "Pending") << endl;
    }
    string getRole() override { return "seller"; }
};

// =====================
// Super Admin (Hardcoded)
// =====================
class SuperAdmin : public User {
public:
    SuperAdmin() : User(0, "Super Admin", "superadmin@shopsphere.com", "super@123") {}

    void showRole() override {
        cout << "[Super Admin] " << name << endl;
    }
    string getRole() override { return "superadmin"; }
};

// =====================
// Auth Manager
// =====================
class AuthManager {
private:
    vector<Customer> customers;
    vector<Seller>   sellers;
    SuperAdmin       superAdmin;
    int nextCustomerId = 1;
    int nextSellerId   = 1;

public:
    // Register Customer
    Customer* registerCustomer() {
        string name, email, password, phone, address;
        cout << "\n======= Customer Register =======" << endl;
        cout << "Full Name : "; cin.ignore(); getline(cin, name);
        cout << "Email     : "; getline(cin, email);
        cout << "Phone     : "; phone = readPhone();
        cout << "Address   : "; getline(cin, address);
        cout << "Password  : "; getline(cin, password);

        for (auto& c : customers)
            if (c.getEmail() == email) {
                cout << "Email already registered!" << endl;
                return nullptr;
            }

        customers.push_back(Customer(nextCustomerId++, name, email, password, phone, address));
        cout << "Registration successful! Welcome, " << name << "!" << endl;
        return &customers.back();
    }

    // Register Seller
    Seller* registerSeller() {
        string name, email, password, phone, shopName;
        cout << "\n======= Seller Register =======" << endl;
        cout << "Full Name  : "; cin.ignore(); getline(cin, name);
        cout << "Shop Name  : "; getline(cin, shopName);
        cout << "Email      : "; getline(cin, email);
        cout << "Phone      : "; phone = readPhone();
        cout << "Password   : "; getline(cin, password);

        for (auto& s : sellers)
            if (s.getEmail() == email) {
                cout << "Email already registered!" << endl;
                return nullptr;
            }

        sellers.push_back(Seller(nextSellerId++, name, email, password, shopName, phone));
        cout << "Registration successful! Your account is pending admin approval." << endl;
        return &sellers.back();
    }

    // Customer Login
    Customer* loginCustomer() {
        string email, password;
        cout << "\n======= Customer Login =======" << endl;
        cout << "Email    : "; cin.ignore(); getline(cin, email);
        cout << "Password : "; getline(cin, password);

        for (auto& c : customers) {
            if (c.getEmail() == email && c.getPassword() == password) {
                if (c.getIsBlocked()) { cout << "Your account is blocked!" << endl; return nullptr; }
                cout << "Welcome back, " << c.getName() << "!" << endl;
                return &c;
            }
        }
        cout << "Invalid email or password!" << endl;
        return nullptr;
    }

    // Seller Login
    Seller* loginSeller() {
        string email, password;
        cout << "\n======= Seller Login =======" << endl;
        cout << "Email    : "; cin.ignore(); getline(cin, email);
        cout << "Password : "; getline(cin, password);

        for (auto& s : sellers) {
            if (s.getEmail() == email && s.getPassword() == password) {
                if (s.getIsBlocked()) { cout << "Your account is blocked!" << endl; return nullptr; }
                if (!s.getIsApproved()) { cout << "Your seller account is pending approval." << endl; return nullptr; }
                cout << "Welcome back, " << s.getName() << "!" << endl;
                return &s;
            }
        }
        cout << "Invalid email or password!" << endl;
        return nullptr;
    }

    // Admin Login
    User* loginAdmin() {
        string email, password;
        cout << "\n======= Admin Login =======" << endl;
        cout << "Email    : "; cin.ignore(); getline(cin, email);
        cout << "Password : "; getline(cin, password);

        if (email == superAdmin.getEmail() && password == superAdmin.getPassword()) {
            cout << "Welcome back, Super Admin!" << endl;
            return &superAdmin;
        }
        
        cout << "Invalid email or password!" << endl;
        return nullptr;
    }

    // For Admin use
    vector<Customer>& getCustomers() { return customers; }
    vector<Seller>&   getSellers()   { return sellers; }
};

#endif
