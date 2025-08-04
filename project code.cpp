#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

int getValidatedInt(const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && !(ss >> input) && value >= minVal && value <= maxVal) {
            return value;
        }
        cout << "Invalid input. Please enter a valid number";
        if (minVal != INT_MIN || maxVal != INT_MAX)
            cout << " (" << minVal << " to " << maxVal << ")";
        cout << ".\n";
    }
}

string getValidatedString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "Input cannot be empty. Please try again.\n";
    }
}



// Product class to store product details
class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product(int i, string n, double p, int q) : id(i), name(n), price(p), quantity(q) {}
};

// CartItem class to store items in the cart
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int q) : product(p), quantity(q) {}
};

// User class to store user details
class User {
public:
    string username;
    string password;

    User(string u, string p) : username(u), password(p) {}
};

// ShoppingSystem class to manage the shopping center
class ShoppingSystem {
private:
    vector<Product> products;
    vector<User> users;
    vector<CartItem> cart;
    User* currentUser;
    const string USER_FILE = "users.txt";
    const string CART_FILE_PREFIX = "_cart.txt";

public:
    ShoppingSystem() : currentUser(nullptr) {
        // Initialize some sample products
        products.push_back(Product(1, "Laptop", 51000, 10));
        products.push_back(Product(2, "Smartphone", 15000, 20));
        products.push_back(Product(3, "Headphones", 1600, 50));
        products.push_back(Product(4, "Charging Cable", 1200, 65));
        products.push_back(Product(5, "Rice (5kg)", 650, 50));
        products.push_back(Product(6, "Oil (1L)", 200, 60));
        products.push_back(Product(7, "Milk (1L)", 120, 100));
        products.push_back(Product(8, "Sugar (1kg)", 120, 80));
        products.push_back(Product(9, "T-shirt", 500, 30));
        products.push_back(Product(10,"Jeans", 1300, 25));
        products.push_back(Product(11,"Jacket", 2500, 15));
        products.push_back(Product(12,"Sneakers", 2000, 20));
        products.push_back(Product(13,"Burger", 200, 40));
        products.push_back(Product(14,"Pizza", 500, 30));
        products.push_back(Product(15,"Fries", 130, 50));
        loadUsers();
    }

    void clearCart() {
    if (!currentUser) {
        cout << "Please login to clear the cart!\n";
        return;
    }

    // Restore stock for all items in cart
    for (const auto& item : cart) {
        for (auto& prod : products) {
            if (prod.id == item.product.id) {
                prod.quantity += item.quantity;
                break;
            }
        }
    }

    cart.clear();
    saveCart();
    cout << "Cart cleared successfully.\n";
    }


    void editCartQuantity(int productId, int newQty) {
    if (!currentUser) {
        cout << "Please login to edit cart!\n";
        return;
    }
    if (newQty <= 0) {
        cout << "Quantity must be greater than zero!\n";
        return;
    }

    for (auto& item : cart) {
        if (item.product.id == productId) {
            for (auto& prod : products) {
                if (prod.id == productId) {
                    int diff = newQty - item.quantity;

                    if (prod.quantity >= diff) {
                        prod.quantity -= diff;
                        item.quantity = newQty;
                        saveCart();
                        cout << "Quantity updated successfully.\n";
                    } else {
                        cout << "Not enough stock to increase quantity.\n";
                    }
                    return;
                }
            }
        }
    }

    cout << "Product not found in cart.\n";
    }


    void removeFromCart(int productId) {
    if (!currentUser) {
        cout << "Please login to remove items from cart!\n";
        return;
    }

    bool found = false;
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->product.id == productId) {
            // Restore product quantity to stock
            for (auto& prod : products) {
                if (prod.id == productId) {
                    prod.quantity += it->quantity;
                    break;
                }
            }
            cart.erase(it);
            saveCart();
            cout << "Product removed from cart.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found in cart.\n";
    }
    }


    // Load users from file
    void loadUsers() {
        ifstream file(USER_FILE);
        if (!file.is_open()) {
            cout << "No existing user file found. Starting fresh.\n";
            return;
        }

        string username, password;
        while (file >> username >> password) {
            users.push_back(User(username, password));
        }
        file.close();
    }

    // Save users to file
    void saveUsers() {
        ofstream file(USER_FILE);
        if (!file.is_open()) {
            cout << "Error saving user data!\n";
            return;
        }
        for (const auto& user : users) {
            file << user.username << " " << user.password << endl;
        }
        file.close();
    }

    // Load cart for the current user
    void loadCart() {
        if (!currentUser) return;
        cart.clear();
        string cartFile = currentUser->username + CART_FILE_PREFIX;
        ifstream file(cartFile);
        if (!file.is_open()) {
            cout << "No existing cart found for " << currentUser->username << ".\n";
            return;
        }

        int productId, quantity;
        while (file >> productId >> quantity) {
            for (auto& product : products) {
                if (product.id == productId) {
                    cart.push_back(CartItem(product, quantity));
                    break;
                }
            }
        }
        file.close();
    }

    // Save cart for the current user
    void saveCart() {
        if (!currentUser) return;
        string cartFile = currentUser->username + CART_FILE_PREFIX;
        ofstream file(cartFile);
        if (!file.is_open()) {
            cout << "Error saving cart data!\n";
            return;
        }
        for (const auto& item : cart) {
            file << item.product.id << " " << item.quantity << endl;
        }
        file.close();
    }

    // Register a new user
    bool registerUser(string username, string password) {
        for (const auto& user : users) {
            if (user.username == username) {
                cout << "Username already exists!\n";
                return false;
            }
        }
        users.push_back(User(username, password));
        saveUsers();
        cout << "Registration successful!\n";
        return true;
    }

    // Login user
    bool login(string username, string password) {
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = new User(username, password);
                loadCart();
                cout << "Login successful! Welcome, " << username << "!\n";
                return true;
            }
        }
        cout << "Invalid username or password!\n";
        return false;
    }

    // Logout user
    void logout() {
        if (currentUser) {
            saveCart();
            delete currentUser;
            currentUser = nullptr;
            cart.clear();
            cout << "Logged out successfully!\n";
        } else {
            cout << "No user is logged in!\n";
        }
    }

    // Display all products
    void displayProducts() {
        cout << "\nAvailable Products:\n";
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        cout << string(45, '-') << endl;
        for (const auto& product : products) {
            cout << setw(5) << product.id << setw(20) << product.name 
                 << setw(10) << fixed << setprecision(2) << product.price 
                 << setw(10) << product.quantity << endl;
        }
    }

    // Add product to cart
    void addToCart(int productId, int quantity) {
        if (!currentUser) {
            cout << "Please login to add items to cart!\n";
            return;
        }
        if (quantity <= 0) {
            cout << "Quantity must be greater than zero!\n";
            return;
        }


        for (auto& product : products) {
            if (product.id == productId) {
                if (product.quantity >= quantity) {
                    for (auto& item : cart) {
                        if (item.product.id == productId) {
                            item.quantity += quantity;
                            product.quantity -= quantity;
                            saveCart();
                            cout << quantity << " more x " << product.name << " added to cart!\n";
                            return;
                        }
                    }
                    cart.push_back(CartItem(product, quantity));
                    product.quantity -= quantity;
                    saveCart();
                    cout << quantity << " x " << product.name << " added to cart!\n";
                    return;
                } else {
                    cout << "Insufficient stock for " << product.name << "!\n";
                    return;
                }
            }
        }
        cout << "Product ID not found!\n";
    }

    // View cart
    void viewCart() {
        if (!currentUser) {
            cout << "Please login to view cart!\n";
            return;
        }
        if (cart.empty()) {
            cout << "Your cart is empty!\n";
            return;
        }

        cout << "\nYour Cart:\n";
        cout << setw(10) << "ID" << setw(20) << "Product" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Total" << endl;
        cout << string(65, '-') << endl;
        double total = 0.0;
        for (const auto& item : cart) {
            double itemTotal = item.product.price * item.quantity;
            total += itemTotal;
            cout << setw(10) << item.product.id
             << setw(20) << item.product.name 
             << setw(10) << item.quantity 
             << setw(10) << fixed << setprecision(2) << item.product.price 
             << setw(15) << itemTotal << endl;
        }
        cout << string(65, '-') << endl;
        cout << "Total: Rs. " << fixed << setprecision(2) << total << endl;
    }

    // Checkout
    void checkout() {
        if (!currentUser) {
            cout << "Please login to checkout!\n";
            return;
        }
        if (cart.empty()) {
            cout << "Your cart is empty!\n";
            return;
        }

        viewCart();
        cout << "Processing payment...\n";
        cout << "Order placed successfully! Thank you for shopping!\n";
        cart.clear();
        saveCart();
    }

    // Check if user is logged in
    bool isLoggedIn() {
        return currentUser != nullptr;
    }

    // Destructor to clean up
    ~ShoppingSystem() {
        if (currentUser) {
            saveCart();
            delete currentUser;
        }
    }
};

// Main menu function
void displayMenu() {
    cout << "\nOnline Shopping Center\n";
    cout << "----------------------\n";
   
    cout << "1. View Products\n";
    cout << "2. Add to Cart\n";
    cout << "3. Edit Cart Quantity\n";
    cout << "4. Remove from Cart\n";
    cout << "5. Clear Cart\n";
    cout << "6. View Cart\n";
    cout << "7. Checkout\n";
    cout << "8. Logout\n";
    cout << "9. Exit\n";
}

int main() {
    ShoppingSystem system;
    string username, password;
    int choice;
    int productId, quantity;

    while (true) {
        cout << "\nOnline Shopping Center\n";
        cout << "----------------------\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        
        choice = getValidatedInt("Enter your choice: ", 1, 3);

        if (choice == 1) {
            username = getValidatedString("Enter username: ");
            password = getValidatedString("Enter password: ");

            if (system.login(username, password)) {
                // Logged in, show menu
                while (system.isLoggedIn()) {
                    displayMenu();

                    choice = getValidatedInt("Enter your choice: ", 1, 9);

                    switch (choice) {
                        case 1:
                            system.displayProducts();
                            break;

                        case 2:
                            system.displayProducts();
                            productId = getValidatedInt("Enter product ID: ",1 ,15);
                            quantity = getValidatedInt("Enter quantity: ", 1);
                            system.addToCart(productId, quantity);
                            break;

                        case 3:
                            system.viewCart();
                            productId = getValidatedInt("Enter product ID to edit: ",1 ,15);
                            quantity = getValidatedInt("Enter new quantity: ", 1);
                            system.editCartQuantity(productId, quantity);
                            break;

                        case 4:
                            system.viewCart();
                            productId = getValidatedInt("Enter product ID to remove: ",1 ,15);
                            system.removeFromCart(productId);
                            break;

                        case 5:
                            system.clearCart();
                            break;

                        case 6:
                            system.viewCart();
                            break;

                        case 7:
                            system.checkout();
                            break;

                        case 8:
                            system.logout();
                            break;

                        case 9:
                            cout << "Thank you for using Online Shopping Center!\n";
                            return 0;
                    }
                }
            } else {
                cout << "Login failed. Try again or register.\n";
            }
        } else if (choice == 2) {
            username = getValidatedString("Enter username: ");
            password = getValidatedString("Enter password: ");
            system.registerUser(username, password);
        } else if (choice == 3) {
            cout << "Thank you for using Online Shopping Center!\n";
            break;
        }
    }
    return 0;
}
