#include <iostream>
using namespace std;

// Menu
int mainMenu();

// Transaction
void transactionMenu(int &, int[], string[], int &, int[], string[]);
void addTransaction(int &, int[], string[], int &, int[], string[]);
void viewTransaction(int, int[], string[], int, int[], string[], int);
void deleteTransaction(int &, int[], string[], int &, int[], string[]);
void displaySummary(int, int[], int, int[]); 

int main()
{
    int choice, incomeCount = 0, expenseCount = 0;
    int incomeAmount[100], expenseAmount[100];
    string incomeSource[100], expenseCategory[100];
    bool isContinue = true;

    cout << "==================== Personal Finance Tracker ====================" << endl;
    cout << "Welcome! Manage your income and expenses efficiently." << endl;

    while (isContinue)
    {
        choice = mainMenu();
        switch (choice)
        {
        case 1:
            transactionMenu(incomeCount, incomeAmount, incomeSource,
                            expenseCount, expenseAmount, expenseCategory);
            break;
        case 2:
            cout << endl;
            cout << "==================== Thank You ====================" << endl;
            cout << "Exiting the application. Thank you for using the Personal Finance Tracker." << endl;
            cout << "===================================================" << endl;
            isContinue = false;
            break;
        default:
            cout << endl;
            cout << "[ERROR] Invalid selection. Please choose a valid option from the menu." << endl;
            cout << endl;
        }
    }

    return 0;
}

// Menu
int mainMenu()
{
    int choice;
    cout << endl;
    cout << "--------------------------- Main Menu ----------------------------" << endl;
    cout << "1 - Manage Transactions" << endl;
    cout << "2 - Exit Program" << endl;
    cout << "Please select an option (1 - 2): ";
    cin >> choice;
    return choice;
}

// Transactions
void transactionMenu(int &incomeCount, int incomeAmount[], string incomeSource[],
                     int &expenseCount, int expenseAmount[], string expenseCategory[])
{
    int choice;
    bool isContinue = true;

    while (isContinue)
    {
        cout << endl;
        cout << "------------------------ Transaction Management ------------------" << endl;
        cout << "1 - Add a Transaction" << endl;
        cout << "2 - View Transactions" << endl;
        cout << "3 - Delete a Transaction" << endl;
        cout << "4 - View Financial Summary" << endl; // NEW OPTION
        cout << "5 - Return to Main Menu" << endl;
        cout << "Please select an option (1 - 5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTransaction(incomeCount, incomeAmount, incomeSource,
                           expenseCount, expenseAmount, expenseCategory);
            break;

        case 2:
        {
            int viewChoice;
            cout << endl;
            cout << "1 - View Income Records" << endl;
            cout << "2 - View Expense Records" << endl;
            cout << "Please select the type of transaction to view: ";
            cin >> viewChoice;

            viewTransaction(incomeCount, incomeAmount, incomeSource,
                            expenseCount, expenseAmount, expenseCategory, viewChoice);
        }
        break;

        case 3:
            deleteTransaction(incomeCount, incomeAmount, incomeSource,
                              expenseCount, expenseAmount, expenseCategory);
            break;

        case 4: 
            displaySummary(incomeCount, incomeAmount, expenseCount, expenseAmount);
            break;

        case 5:
            cout << endl;
            cout << "Returning to the Main Menu..." << endl;
            cout << endl;
            isContinue = false;
            break;

        default:
            cout << endl;
            cout << "[ERROR] Invalid selection. Please enter a valid option." << endl;
            cout << endl;
        }
    }
}

void addTransaction(int &incomeCount, int incomeAmount[], string incomeSource[], int &expenseCount, int expenseAmount[], string expenseCategory[])
{
    int choice, totalIncome = 0, totalExpense = 0;
    bool isContinue = true;

    for (int i = 0; i < incomeCount; i++)
        totalIncome += incomeAmount[i];

    for (int i = 0; i < expenseCount; i++)
        totalExpense += expenseAmount[i];

    cout << endl;
    cout << "--------------------------- Add Transaction ----------------------" << endl;
    cout << "Current Balance: " << (totalIncome - totalExpense) << endl; // NEW LINE

    if (totalIncome > totalExpense)
    {
        cout << "1 - Add Income" << endl;
        cout << "2 - Add Expense" << endl;
    }
    else
    {
        cout << endl;
        cout << "[NOTICE] Since total income is less than or equal to total expense," << endl;
        cout << "         you can only add income for now." << endl;
        cout << endl;
        choice = 1;
    }

    while (isContinue)
    {
        if (totalIncome > totalExpense)
        {
            cout << "Please select an option: ";
            cin >> choice;
        }
        else
        {
            choice = 1;
        }

        switch (choice)
        {
        case 1:
        {
            if (incomeCount == 100)
            {
                cout << endl;
                cout << "[ERROR] Income record storage is full!" << endl;
                cout << endl;
                return;
            }

            string incomeName;
            int earned;

            cout << endl;
            cout << "----------------------- Income Entry -----------------------------" << endl;

            do
            {
                cout << "Please enter the income amount (non-negative): ";
                cin >> earned;
                if (earned < 0)
                {
                    cout << "[ERROR] Income amount cannot be negative. Please try again." << endl;
                }
            } while (earned < 0);

            cout << "Please enter the source of income: ";
            cin >> incomeName;

            for (int i = 0; i < incomeCount; i++)
            {
                if (incomeSource[i] == incomeName)
                {
                    incomeAmount[i] += earned;
                    cout << endl;
                    cout << "[SUCCESS] Amount added to existing income source: " << incomeName << endl;
                    cout << "          New total for " << incomeName << ": " << incomeAmount[i] << endl;
                    return;
                }
            }

            incomeAmount[incomeCount] = earned;
            incomeSource[incomeCount] = incomeName;
            incomeCount++;
            cout << endl;
            cout << "[SUCCESS] Income record added successfully!" << endl;
            isContinue = false;
            break;
        }

        case 2:
        {
            if (expenseCount == 100)
            {
                cout << endl;
                cout << "[ERROR] Expense record storage is full!" << endl;
                cout << endl;
                return;
            }

            string expenseName;
            int expense;

            cout << endl;
            cout << "---------------------- Expense Entry -----------------------------" << endl;

            do
            {
                cout << "Please enter the expense amount (non-negative): ";
                cin >> expense;
                if (expense < 0)
                {
                    cout << "[ERROR] Expense amount cannot be negative. Please try again." << endl;
                }
            } while (expense < 0);

            cout << "Please enter the expense category: ";
            cin >> expenseName;

            for (int i = 0; i < expenseCount; i++)
            {
                if (expenseCategory[i] == expenseName)
                {
                    expenseAmount[i] += expense;
                    cout << endl;
                    cout << "[SUCCESS] Amount added to existing expense category: " << expenseName << endl;
                    cout << "          New total for " << expenseName << ": " << expenseAmount[i] << endl;
                    return;
                }
            }

            expenseAmount[expenseCount] = expense;
            expenseCategory[expenseCount] = expenseName;
            expenseCount++;
            cout << endl;
            cout << "[SUCCESS] Expense record added successfully!" << endl;
            isContinue = false;
            break;
        }

        default:
            cout << endl;
            cout << "[ERROR] Invalid selection. Please try again." << endl;
            cout << endl;
        }
    }
}

void viewTransaction(int incomeCount, int incomeAmount[], string incomeSource[], int expenseCount, int expenseAmount[], string expenseCategory[], int choice)
{
    cout << endl;
    cout << "---------------------- Transaction Records -----------------------" << endl;

    if (incomeCount == 0 && expenseCount == 0)
    {
        cout << endl;
        cout << "[NOTICE] No records available for income or expense." << endl;
        cout << endl;
        return;
    }

    switch (choice)
    {
    case 1:
        if (incomeCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No income records available." << endl;
            cout << endl;
            return;
        }

        cout << endl;
        cout << "Income Records:" << endl;
        cout << "No.   Income Source             Amount" << endl;
        cout << "------------------------------------------------------------------" << endl;
        for (int i = 0; i < incomeCount; i++)
        {
            cout << i << "     " << incomeSource[i]
                 << "                     " << incomeAmount[i] << endl;
        }
        cout << "------------------------------------------------------------------" << endl;
        break;

    case 2:
        if (expenseCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No expense records available." << endl;
            cout << endl;
            return;
        }

        cout << endl;
        cout << "Expense Records:" << endl;
        cout << "No.   Expense Category          Amount" << endl;
        cout << "------------------------------------------------------------------" << endl;
        for (int i = 0; i < expenseCount; i++)
        {
            cout << i << "     " << expenseCategory[i]
                 << "                     " << expenseAmount[i] << endl;
        }
        cout << "------------------------------------------------------------------" << endl;
        break;

    default:
        cout << endl;
        cout << "Viewing All Records" << endl;
        if (incomeCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No income records available." << endl;
        }
        else
        {
            cout << endl;
            cout << "Income Records:" << endl;
            cout << "No.   Income Source             Amount" << endl;
            cout << "------------------------------------------------------------------" << endl;
            for (int i = 0; i < incomeCount; i++)
            {
                cout << i << "     " << incomeSource[i]
                     << "                     " << incomeAmount[i] << endl;
            }
            cout << "------------------------------------------------------------------" << endl;
        }

        if (expenseCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No expense records available." << endl;
        }
        else
        {
            cout << endl;
            cout << "Expense Records:" << endl;
            cout << "No.   Expense Category          Amount" << endl;
            cout << "------------------------------------------------------------------" << endl;
            for (int i = 0; i < expenseCount; i++)
            {
                cout << i << "     " << expenseCategory[i]
                     << "                     " << expenseAmount[i] << endl;
            }
            cout << "------------------------------------------------------------------" << endl;
        }
        break;
    }
}

void deleteTransaction(int &incomeCount, int incomeAmount[], string incomeSource[], int &expenseCount, int expenseAmount[], string expenseCategory[])
{
    int choice;

    cout << endl;
    cout << "---------------------- Delete Transaction ------------------------" << endl;

    if (incomeCount == 0 && expenseCount == 0)
    {
        cout << endl;
        cout << "[NOTICE] No records available for deletion." << endl;
        cout << endl;
        return;
    }

    cout << "1 - Delete Income Record" << endl;
    cout << "2 - Delete Expense Record" << endl;
    cout << "Please select the type of record to delete: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        if (incomeCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No income records available." << endl;
            cout << endl;
            return;
        }

        int viewChoice = 1, delIncome;
        viewTransaction(incomeCount, incomeAmount, incomeSource,
                        expenseCount, expenseAmount, expenseCategory, viewChoice);

        cout << endl;
        cout << "Enter the record number to delete: ";
        cin >> delIncome;

        if (delIncome >= 0 && delIncome < incomeCount)
        {
            cout << endl;
            cout << "[DELETING] Income source: " << incomeSource[delIncome] 
                 << " | Amount: " << incomeAmount[delIncome] << endl;
            
            for (int i = delIncome; i < incomeCount; i++)
            {
                incomeAmount[i] = incomeAmount[i + 1];
                incomeSource[i] = incomeSource[i + 1];
            }
            incomeCount--;
            cout << "[SUCCESS] Income record deleted successfully." << endl;
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << "[ERROR] Invalid record number. Deletion failed." << endl;
            cout << endl;
        }
        break;
    }

    case 2:
    {
        if (expenseCount == 0)
        {
            cout << endl;
            cout << "[NOTICE] No expense records available." << endl;
            cout << endl;
            return;
        }

        int viewChoice = 2, delExpense;
        viewTransaction(incomeCount, incomeAmount, incomeSource,
                        expenseCount, expenseAmount, expenseCategory, viewChoice);

        cout << endl;
        cout << "Enter the record number to delete: ";
        cin >> delExpense;

        if (delExpense >= 0 && delExpense < expenseCount)
        {
            cout << endl;
            cout << "[DELETING] Expense category: " << expenseCategory[delExpense] 
                 << " | Amount: " << expenseAmount[delExpense] << endl;
            
            for (int i = delExpense; i < expenseCount; i++)
            {
                expenseAmount[i] = expenseAmount[i + 1];
                expenseCategory[i] = expenseCategory[i + 1];
            }
            expenseCount--;
            cout << "[SUCCESS] Expense record deleted successfully." << endl;
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << "[ERROR] Invalid record number. Deletion failed." << endl;
            cout << endl;
        }
        break;
    }

    default:
        cout << endl;
        cout << "[ERROR] Invalid selection. Please try again." << endl;
        cout << endl;
    }
}

void displaySummary(int incomeCount, int incomeAmount[], int expenseCount, int expenseAmount[])
{
    int totalIncome = 0, totalExpense = 0, balance = 0;
    
    cout << endl;
    cout << "===================== Financial Summary ======================" << endl;
    
    for(int i = 0; i < incomeCount; i++)
        totalIncome += incomeAmount[i];
    
    for(int i = 0; i < expenseCount; i++)
        totalExpense += expenseAmount[i];
    
    balance = totalIncome - totalExpense;
    
    cout << endl;
    cout << "Total Income Records:  " << incomeCount << endl;
    cout << "Total Expense Records: " << expenseCount << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Total Income:          " << totalIncome << endl;
    cout << "Total Expense:         " << totalExpense << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Current Balance:       " << balance << endl;
    
    if(balance > 0)
    {
        cout << endl;
        cout << "[STATUS] You have a positive balance! Keep up the good work." << endl;
    }
    else if(balance == 0)
    {
        cout << endl;
        cout << "[STATUS] Your income equals your expenses. Break even!" << endl;
    }
    else
    {
        cout << endl;
        cout << "[WARNING] You have a negative balance! Consider reducing expenses." << endl;
    }
    
    cout << "==============================================================" << endl;
}