#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Groceries{
    public:
    string name;
    float rate;
};
class Clothes{
    public:
    string name;
    float rate;
};
class Electronics{
    public:
    string name;
    float rate;
};
void showItems(){

    cout << "\n\n======================================================================="; 
    cout << endl << left << setw(30) << "GROCERIES" <<  setw(30) << "CLOTHES"  << "ELECTRONICS" << endl;
    cout << left << setw(10) << "1. Rice" << setw(25) << "Rs. 80/kg" << setw(10) << "1. T-shirt" << setw(25) << "Rs. 370" << endl;
    cout << left << setw(10) << "2. Oil" << setw(25) << "Rs. 200/litre" << setw(10) << "2. Pant" << setw(25) << "Rs. 700" << endl;
    cout << left << setw(10) << "3. Mango" << setw(25) << "Rs. 100/kg" << setw(10) << "3. Shirt" << setw(25) << "Rs. 500" << endl;
    cout << left << setw(10) << "4. Potato" << setw(25) << "Rs. 60/kg" << setw(10) << "4. Jacket" << setw(25) << "Rs. 1500" << endl;
    cout << left << setw(10) << "5. Milk" << setw(25) << "Rs. 120/litre" << setw(10) << "5. Hoodie" << setw(25) << "Rs. 1200" << endl;
}
int main(){
    int choice;
    do {
        
        cout << "\n========== Shopping Menu ==========\n";
        cout << "1. Show Available Items\n";
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
           /* cin >> category;
            cout << "Enter Item Name: ";
            cin >> name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;
            cart.addItem(category, name, price, quantity);
            */
            break;

        case 3:
            cout << "Enter Item Name to Remove: ";
           /* cin >> name;
            cart.removeItem(name); */
            break;

        case 4:
            cout << "Enter Item Name to Update Quantity: ";
            /*cin >> name;
            cout << "Enter New Quantity: ";
            cin >> quantity;
            cart.updateQuantity(name, quantity); */
            break;

        case 5:
          //  cart.displayCart();
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