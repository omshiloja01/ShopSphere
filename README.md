# 🛒 ShopSphere – E-Commerce Management System – OOPS Project
This project is a comprehensive, console-based E-Commerce Management System built using C++. It features a well-structured object-oriented design with role-based access control, allowing interactions between customers, sellers, and administrators within a unified platform.

## 🛠️ Project Overview
The project simulates how an e-commerce marketplace operates, utilizing C++ classes, inheritance, and polymorphism to manage users, product inventories, shopping carts, and order fulfillment processes. 

## ✅ Key Features
**Object-Oriented Architecture for managing:**
- Customers, Sellers, and Super Admins
- Product Catalog, Categories, and Stock
- Shopping Carts and Wishlists
- Order Placement and Tracking
- Polymorphic Payment Processing (Cash, Card, UPI)

**Additional Highlights:**
- Distinct, interactive console panels for different roles
- Admin approval workflow for new seller accounts and products
- Sales reporting tools for sellers to track approved vs. pending products
- **Implements C++ concepts like:**
  - Inheritance and Polymorphism
  - Encapsulation
  - Standard Template Library (STL) Vectors
  - Input validation

## 📂 Project Structure
| File | Description |
|------|-------------|
| `main.cpp` | Entry point of the application handling main menu routing and execution |
| `User.h` / `User.cpp` | Base class and derived classes for Customers, Sellers, and SuperAdmin |
| `Product.h` / `Product.cpp` | Manages product attributes, reviews, and availability status |
| `Cart.h` / `Cart.cpp` | Handles adding, removing, and calculating totals for customer carts |
| `Wishlist.h` | Allows customers to save products for later without purchasing |
| `Order.h` / `Order.cpp` | Manages order creation, tracking states, and history |
| `Payment.h` / `Payment.cpp` | Abstract base class and concrete implementations for Cash, Card, and UPI |
| `InputUtils.h` | Helper utilities for reading formatted inputs and preventing crashes |
| `AdminPanel.h` | Sub-panel logic for general product and catalog management |
| `SellerPanel.h` | Interface for sellers to add, edit, and track their specific merchandise |
| `SuperAdminPanel.h` | Master interface for approving users/products and viewing platform statistics |
