#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================
// Review
// =====================
struct Review {
    string customerName;
    int rating;       // 1-5
    string comment;

    Review(string n, int r, string c) : customerName(n), rating(r), comment(c) {}
};

// =====================
// Product
// =====================
class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int stock;
    double rating;
    bool available;
    int sellerId;
    string sellerName;
    string status;   // "pending", "approved", "rejected"
    vector<Review> reviews;

public:
    Product() : id(0), name(""), category(""), price(0), stock(0),
                rating(0), available(true), sellerId(0), sellerName(""), status("approved") {}

    Product(int id, string name, string category, double price,
            int stock, int sellerId, string sellerName,
            double rating = 0.0, string status = "approved") {
        this->id         = id;
        this->name       = name;
        this->category   = category;
        this->price      = price;
        this->stock      = stock;
        this->sellerId   = sellerId;
        this->sellerName = sellerName;
        this->rating     = rating;
        this->status     = status;
        this->available  = (stock > 0);
    }

    // Getters
    int    getId()          { return id; }
    string getName()        { return name; }
    string getCategory()    { return category; }
    double getPrice()       { return price; }
    int    getStock()       { return stock; }
    double getRating()      { return rating; }
    int    getSellerId()    { return sellerId; }
    string getSellerName()  { return sellerName; }
    string getStatus()      { return status; }
    bool   isAvailable()    { return available && stock > 0 && status == "approved"; }
    vector<Review>& getReviews() { return reviews; }

    // Setters
    void setPrice(double p)    { price = p; }
    void setStock(int s)       { stock = s; available = (s > 0); }
    void setName(string n)     { name = n; }
    void setCategory(string c) { category = c; }
    void setStatus(string s)   { status = s; }
    void setRating(double r)   { rating = r; }

    void addReview(string customerName, int r, string comment) {
        reviews.push_back(Review(customerName, r, comment));
        // Recalculate avg rating
        double total = 0;
        for (auto& rv : reviews) total += rv.rating;
        rating = total / reviews.size();
    }

    void displayReviews() {
        if (reviews.empty()) { cout << "No reviews yet." << endl; return; }
        cout << "\n--- Reviews for " << name << " ---" << endl;
        for (auto& r : reviews) {
            cout << r.customerName << " [" << r.rating << "/5]: " << r.comment << endl;
        }
    }

    void display() {
        cout << "-----------------------------" << endl;
        cout << "ID       : " << id << endl;
        cout << "Name     : " << name << endl;
        cout << "Category : " << category << endl;
        cout << "Price    : Rs." << price << endl;
        cout << "Stock    : " << stock << endl;
        cout << "Rating   : " << rating << "/5 (" << reviews.size() << " reviews)" << endl;
        cout << "Seller   : " << sellerName << endl;
        cout << "Status   : " << (isAvailable() ? "In Stock" : "Out of Stock");
        if (status == "pending")  cout << " [PENDING APPROVAL]";
        if (status == "rejected") cout << " [REJECTED]";
        cout << endl;
        cout << "-----------------------------" << endl;
    }
};

#endif
