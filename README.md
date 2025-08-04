# 🛒 Online Shopping Center (Console-Based C++ Application)

A simple yet functional console-based shopping system built using C++. This application allows users to register, log in, browse products, manage a shopping cart, and complete a checkout process. The system persists user and cart data using file I/O.

---

## 📌 Features

- 👤 User Registration and Login (with persistent storage)
- 🛍️ Product Catalog Browsing
- 🛒 Add, Remove, Edit Items in Cart
- 🧼 Clear Cart Option
- 💾 Cart Data Saved Per User
- 💸 Checkout Process
- 📁 File-based persistence (`users.txt` and `[username]_cart.txt`)
- ✅ Input validation using `getline` and `stringstream`

---

## 🧱 Classes Used

- `Product` – Represents a product with ID, name, price, and stock quantity.
- `CartItem` – Represents a product added to the cart with quantity.
- `User` – Represents a registered user with username and password.
- `ShoppingSystem` – Core system managing products, users, cart, and operations.

---

## 📂 File Structure

- `main.cpp` – The main application code.
- `users.txt` – Stores registered user credentials.
- `<username>_cart.txt` – Stores individual user’s cart data.

---

## 🧪 Sample Products (Preloaded)

- Laptop, Smartphone, Headphones, Rice, Oil, Milk, T-shirt, etc.

---

## 🖥️ How to Run

1. **Clone this repository:**
   ```bash
   git clone https://github.com/yourusername/online-shopping-center.git
   cd online-shopping-center

