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
## Future Improvemnents

- Add password hashing for better security.
- Integrate GUI using Qt or a web front-end.
- Implement product filtering and search.
- Add admin features for product management.

---


## 📝 License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for full details.
