#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int stock;

public:
    Product(int id, string name, string category, double price, int stock) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->stock = stock;
    }

    int getId() { return id; }
    string getName() { return name; }
    string getCategory() { return category; }
    double getPrice() { return price; }
    int getStock() { return stock; }

    void setPrice(double p) { this->price = p; }
    void setStock(int s) { this->stock = s; }

    void display() {
        cout << "-----------------------------" << endl;
        cout << "ID       : " << id << endl;
        cout << "Name     : " << name << endl;
        cout << "Category : " << category << endl;
        cout << "Price    : Rs." << price << endl;
        cout << "Stock    : " << stock << endl;
        cout << "-----------------------------" << endl;
    }
};