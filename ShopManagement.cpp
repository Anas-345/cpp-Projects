#include <iostream>
using namespace std;

// Main Menu
int menu();

// Add Item
int addItem(int, int[], int[], string[]);

// View Items
void viewItems(int, int[], int[], string[]);

// Sell Items
int sellItems(int, int[], int[], string[], int &);

int main()
{
    int totalSales = 0;
    int choice;
    int itemCount = 0;
    int itemPrice[100];
    int itemStock[100];
    string itemName[100];
    bool isContinue = true;

    cout << "============================" << endl;
    cout << "      Welcome to the Shop    " << endl;
    cout << "============================" << endl;

    while (isContinue)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            itemCount = addItem(itemCount, itemPrice, itemStock, itemName);
            break;
        case 2:
            viewItems(itemCount, itemPrice, itemStock, itemName);
            break;
        case 3:
            itemCount = sellItems(itemCount, itemPrice, itemStock, itemName, totalSales);
            break;
        case 4:
            cout << "Exiting Program. Thank you for using the Shop Management System." << endl;
            isContinue = false;
            cout << "Total Sales Today: " << totalSales << endl;
            break;
        default:
            cout << "Invalid choice entered. Please enter a number between 1 and 4." << endl;
            break;
        }
    }

    return 0;
}

// Main Menu
int menu()
{
    cout << "===== Main Menu =====" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - View Items" << endl;
    cout << "3 - Sell Item" << endl;
    cout << "4 - Exit" << endl;

    int choice;
    cout << "Please enter your choice: ";
    cin >> choice;

    return choice;
}

// Add Item
int addItem(int itemCount, int itemPrice[], int itemStock[], string itemName[])
{
    int price, stock;
    string name;

    cout << "===== Add a New Item =====" << endl;
    cout << "Enter the name of the item: ";
    cin >> name;
    do
    {
        cout << "Enter the price of the item: ";
        cin >> price;
    } while (price <= 0);

    do
    {
        cout << "Enter the quantity of the item: ";
        cin >> stock;
    } while (stock <= 0);
    

    for (int i = 0; i < itemCount; i++)
    {
        if (itemName[i] == name)
        {
            itemStock[i] += stock;
            itemPrice[i] = price;
            cout << "Notice: Stock of '" << name << "' updated successfully. New quantity: " << itemStock[i] << endl;
            return itemCount;
        }
    }

    itemName[itemCount] = name;
    itemPrice[itemCount] = price;
    itemStock[itemCount] = stock;
    itemCount++;

    cout << "Item '" << name << "' has been successfully added to the shop." << endl;

    return itemCount;
}

// View Item
void viewItems(int itemCount, int itemPrice[], int itemStock[], string itemName[])
{
    cout << "===== Current Shop Items =====" << endl;

    if (itemCount == 0)
    {
        cout << "There are currently no items in the shop." << endl;
        return;
    }

    cout << "No.   Item Name           Price   Stock" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < itemCount; i++)
    {
        cout << i << "     " << itemName[i] << "     " << itemPrice[i] << "     " << itemStock[i] << endl;
    }
}

// Sell Item
int sellItems(int itemCount, int itemPrice[], int itemStock[], string itemName[], int &totalSales)
{
    int quantity, itemNumber;
    cout << "===== Sell Item =====" << endl;
    viewItems(itemCount, itemPrice, itemStock, itemName);

    cout << "Enter the number of the item you want to buy: ";
    cin >> itemNumber;

    if (itemNumber >= 0 && itemNumber < itemCount)
    {
        cout << "Enter the quantity you want to buy: ";
        cin >> quantity;

        if (itemStock[itemNumber] < quantity)
        {
            cout << "Notice: Only " << itemStock[itemNumber] << " unit(s) of '" << itemName[itemNumber] << "' are available." << endl;
            return itemCount;
        }

        itemStock[itemNumber] -= quantity;
        cout << "Success: You purchased " << quantity << " unit(s) of '" << itemName[itemNumber] << "' in Rs." << (itemPrice[itemNumber] * quantity) << "." << endl;
        totalSales += (itemPrice[itemNumber] * quantity);

            if (!itemStock[itemNumber])
        {
            string removedItem = itemName[itemNumber];
            for (int i = itemNumber; i < itemCount - 1; i++)
            {
                itemName[i] = itemName[i + 1];
                itemPrice[i] = itemPrice[i + 1];
                itemStock[i] = itemStock[i + 1];
            }
            itemCount--;
            cout << "Notice: '" << removedItem << "' is now out of stock and removed from the shop." << endl;
            return itemCount;
        }

        return itemCount;
    }

    cout << "Invalid item number entered. Please try again." << endl;
    return itemCount;
}
