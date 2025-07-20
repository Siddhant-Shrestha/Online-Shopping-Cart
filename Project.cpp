#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for setw

using namespace std;

// Structure to store item details
struct Item {
    string category;
    string name;
    float price;
    int quantity;
};

// Shopping Cart Class
class ShoppingCart {
private:
    vector<Item> cart;

public:
    // Add item to cart
    void addItem(string category, string name, float price, int quantity) {
        for (int i = 0; i < cart.size(); i++) {
            if (cart[i].name == name) {
                cart[i].quantity += quantity;
                cout << "Updated quantity for " << name << ".\n";
                return;
            }
        }
        Item newItem;
        newItem.category = category;
        newItem.name = name;
        newItem.price = price;
        newItem.quantity = quantity;
        cart.push_back(newItem);
        cout << "Item added.\n";
    }

    // Remove item from cart
    void removeItem(string name) {
        for (int i = 0; i < cart.size(); i++) {
            if (cart[i].name == name) {
                cart.erase(cart.begin() + i);
                cout << "Item removed.\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    // Update item quantity
    void updateQuantity(string name, int quantity) {
        for (int i = 0; i < cart.size(); i++) {
            if (cart[i].name == name) {
                cart[i].quantity = quantity;
                cout << "Quantity updated.\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    // Display cart contents
    void displayCart() {
        float total = 0.0;
        cout << "\n========== Shopping Cart ==========\n";
        cout << left << setw(15) << "Category"
             << setw(15) << "Item"
             << setw(10) << "Price"
             << setw(10) << "Qty"
             << "Total\n";

        for (int i = 0; i < cart.size(); i++) {
            float itemTotal = cart[i].price * cart[i].quantity;
            total += itemTotal;

            cout << left << setw(15) << cart[i].category
                 << setw(15) << cart[i].name
                 << setw(10) << cart[i].price
                 << setw(10) << cart[i].quantity
                 << itemTotal << "\n";
        }

        cout << "------------------------------------\n";
        cout << "Total Price: Rs " << total << endl;
    }
};

// Show predefined items
void showItems() {
    cout << "\nAvailable Items:\n";
    cout << "Groceries: Rice (Rs 50), Oil (Rs 120)\n";
    cout << "Electronics: Charger (Rs 300), Headphones (Rs 1500)\n";
    cout << "Clothes: TShirt (Rs 500), Jeans (Rs 1200)\n";
    cout << "Fast Food: Burger (Rs 150), Pizza (Rs 400)\n";
}

// Main function
int main() {
    ShoppingCart cart;
    int choice;
    string category, name;
    float price;
    int quantity;

    do {
        cout << "\n========== Shopping Menu ==========\n";
        cout << "1. Show Items\n";
        cout << "2. Add Item to Cart\n";
        cout << "3. Remove Item from Cart\n";
        cout << "4. Update Item Quantity\n";
        cout << "5. Display Cart\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showItems();
            break;

        case 2:
            cout << "Enter Category: ";
            cin >> category;
            cout << "Enter Item Name: ";
            cin >> name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;
            cart.addItem(category, name, price, quantity);
            break;

        case 3:
            cout << "Enter Item Name to Remove: ";
            cin >> name;
            cart.removeItem(name);
            break;

        case 4:
            cout << "Enter Item Name to Update Quantity: ";
            cin >> name;
            cout << "Enter New Quantity: ";
            cin >> quantity;
            cart.updateQuantity(name, quantity);
            break;

        case 5:
            cart.displayCart();
            break;

        case 6:
            cout << "Exiting...!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}