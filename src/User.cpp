#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    int id;
    string name;
    string email;
    string password;

public:
    User(int id, string name, string email, string password) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->password = password;
    }

    string getName() { return name; }
    string getEmail() { return email; }

    virtual void showRole() = 0;
    virtual ~User() {}
};

class Customer : public User {
public:
    Customer(int id, string name, string email, string password)
        : User(id, name, email, password) {}

    void showRole() override {
        cout << "Role: Customer | Name: " << name << endl;
    }
};

class Admin : public User {
public:
    Admin(int id, string name, string email, string password)
        : User(id, name, email, password) {}

    void showRole() override {
        cout << "Role: Admin | Name: " << name << endl;
    }
};