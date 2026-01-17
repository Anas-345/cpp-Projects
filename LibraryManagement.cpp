#include <iostream>
using namespace std;

// Main Menu
int menu();

// Add Book
int addBook(int, string[], bool[]);

// View Book
void viewBook(int, string[], bool[]);

// Issue Book
void issueBook(int, string[], bool[]);

// Return Book
void returnBook(int, string[], bool[]);

int main()
{
    int choice;
    int bookCount = 0;
    bool isContinue = true;
    string totalBooks[100];
    bool isIssued[100];
    cout << "============================" << endl;
    cout << "   Welcome to the Library   " << endl;
    cout << "============================" << endl;

    while (isContinue)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            bookCount = addBook(bookCount, totalBooks, isIssued);
            break;
        case 2:
            viewBook(bookCount, totalBooks, isIssued);
            break;
        case 3:
            issueBook(bookCount, totalBooks, isIssued);
            break;
        case 4:
            returnBook(bookCount, totalBooks, isIssued);
            break;
        case 5:
            cout << "Exiting Program. Thank you for using the Library Management System." << endl;
            isContinue = false;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }
    }

    return 0;
}

// Main Menu
int menu()
{
    cout << "===== Main Menu =====" << endl;
    cout << "1 - Add Book" << endl;
    cout << "2 - View Books" << endl;
    cout << "3 - Issue Book" << endl;
    cout << "4 - Return Book" << endl;
    cout << "5 - Exit" << endl;

    int choice;
    cout << "Please enter your choice: ";
    cin >> choice;

    return choice;
}

// Add Book
int addBook(int bookCount, string totalBooks[], bool isIssued[])
{
    cout << "===== Add a New Book =====" << endl;
    string newBook;
    cout << "Enter the name of the book: ";
    cin >> newBook;

    for (int i = 0; i < bookCount; i++)
    {
        if (newBook == totalBooks[i])
        {
            cout << "This book is already in the library database." << endl;
            return bookCount;
        }
    }

    totalBooks[bookCount] = newBook;
    isIssued[bookCount] = false;
    bookCount++;

    cout << "Book \"" << newBook << "\" has been successfully added to the library." << endl;

    return bookCount;
}

// View Book
void viewBook(int bookCount, string totalBooks[], bool isIssued[])
{
    cout << "===== Library Books =====" << endl;

    if (bookCount == 0)
    {
        cout << "There are currently no books in the library." << endl;
        return;
    }

    cout << "No.   Book Name                 Status" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < bookCount; i++)
    {
        cout << i << "     " << totalBooks[i] << "     ";
        cout << (isIssued[i] ? "Not Available" : "Available") << endl;
    }
}

// Issue Book
void issueBook(int bookCount, string totalBooks[], bool isIssued[])
{
    int bookNumber;
    cout << "===== Issue a Book =====" << endl;

    viewBook(bookCount, totalBooks, isIssued);

    cout << "Enter the number of the book you want to issue: ";
    cin >> bookNumber;

    if (bookNumber >= 0 && bookNumber < bookCount)
    {
        if (isIssued[bookNumber])
        {
            cout << "Sorry, \"" << totalBooks[bookNumber] << "\" is currently not available." << endl;
        }
        else
        {
            isIssued[bookNumber] = true;
            cout << "You have successfully issued \"" << totalBooks[bookNumber] << "\"." << endl;
            cout << "Please return it on time." << endl;
        }
    }
    else
    {
        cout << "Invalid book number entered. Please try again." << endl;
    }
}

// Returning Book
void returnBook(int bookCount, string totalBooks[], bool isIssued[])
{
    int bookNumber;
    cout << "===== Return a Book =====" << endl;

    viewBook(bookCount, totalBooks, isIssued);
    cout << "Enter the number of the book you want to return: ";
    cin >> bookNumber;

    if (bookNumber >= 0 && bookNumber < bookCount)
    {
        if (isIssued[bookNumber])
        {
            isIssued[bookNumber] = false;
            cout << "Thank you for returning \"" << totalBooks[bookNumber] << "\"." << endl;
            cout << "The book has been successfully returned to the library." << endl;
        }
        else
        {
            cout << "Notice: \"" << totalBooks[bookNumber] << "\" was not issued to you." << endl;
            cout << "No action was required." << endl;
        }
    }
    else
    {
        cout << "Invalid book number entered. Please try again." << endl;
    }
}
