// Assignment 2

#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

// create node to represent a transaction
struct node
{
    string date;
    int transactionNumber;
    string description;
    double amount;
    struct node * next;
};

node *head = NULL;

// returning the pointer to the element
// whose transaction id no. is less than or equal
// to input transaction id number
struct node *searchNode(int n)
{
    if(head == NULL) return head;
    node *cur = head;
    node *prev = head;
    while(cur)
    {
        if(cur->transactionNumber == n) return cur;
        if(cur->transactionNumber > n) return prev;
        prev = cur;
        cur = cur->next;
    }
}

// returning the pointer to the element
// whose transaction id no. is equal
// to input transaction id number
struct node *searchNode2(int n)
{
    if(head == NULL) return head;
    node *cur = head;
    node *prev = head;
    while(cur)
    {
        if(cur->transactionNumber == n) return cur;
        prev = cur;
        cur = cur->next;
    }
    return cur;
}

// auto generate dates
string getDate()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%y  %X", &tstruct);
    return buf;
}

// demonstrate the addition of a new node/transaction
void addNode(string d, int t, double a)
{
    node *newNode = new node;
    newNode->date = getDate();
    newNode->transactionNumber = t;
    newNode->description = d;
    newNode->amount = a;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
        return;
    }
    node *cur = head;
    while(cur)
    {
        if(cur->next == NULL)
        {
            cur->next = newNode;
            return;
        }
        cur = cur->next;
    }
}

// demonstrate the insertion of a node(by transaction id no.)
void insertNode(string d, int t, double a)
{
    node *ptr = searchNode(t);
    node *newNode = new node;
    newNode->date = getDate();
    newNode->transactionNumber = t;
    newNode->description = d;
    newNode->amount = a;
    node *cur = head;
    // if there's no node: insert at start.
    // increment(by 2) normal transaction id number so future
    // addNodes will be in sequence
    if(head == NULL)
    {
        head = newNode;
        return;
    }
    // insert the node
    while(cur)
    {
        if(cur == ptr )
        {
            newNode->next = cur->next;
            cur->next = newNode;
            return;
        }
        // if transaction id no. is bigger than any in
        // list add the node to the end and increment
        // normal Transaction id no. also so future
        // addNode id nos. are in sequence
        else if(cur->next == NULL)
        {
            cur->next = newNode;
            return;
        }
        cur = cur->next;
    }
}

// demonstrate deletion of a node(by transaction id no.)
void deleteNode(int n)
{
    node *ptr = searchNode(n);
    if(ptr == NULL)
        cout << "No transaction with number = " << n << endl;
    if(ptr == head)
    {
        head = ptr->next;
        return;
    }
    node *cur = head;
    node *prev = head;

    while(cur)
    {
        if(cur == ptr)
        {
            prev->next = cur->next;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

// update balance after deleting node
double updateBalance(double b, int n)
{
    b -= searchNode2(n)->amount;
    return b;
}

// show last node/transaction
void displayLastTransaction()
{
    cout << endl;
    cout << setw(22) << left << "Date/Time" << setw(13) << left << "Trans-No." <<
            setw(14) << left << "Details" << setw(8) << left << "Transaction" << endl;
    cout << "------------------------------------------------------------" << endl;

    node *cur = head;
    if(cur)
    {
        while(cur->next != NULL)
        {
            cur = cur->next;
        }

        cout << setw(22) << left << cur->date << setw(13) << left << cur->transactionNumber <<
                setw(14) << left << cur->description << setw(11) << right << cur->amount << endl;
    }

    cout << endl;
}

// demonstrate traversing nodes to show all transactions
void displayAllTransactions()
{
    cout << endl;
    cout << setw(22) << left << "Date/Time" << setw(13) << left << "Trans-No." <<
            setw(14) << left << "Details" << setw(8) << left << "Transaction" << endl;
    cout << "------------------------------------------------------------" << endl;

    node *list = head;
    while(list)
    {
        cout << setw(22) << left << list->date << setw(13) << left << list->transactionNumber <<
                setw(14) << left << list->description << setw(11) << right << list->amount << endl;
        list = list->next;
    }
    cout << endl;
}

// traverses nodes and returns transactions from a month chosen by user
void showMonthlyTransactions(string year, string month)
{
    cout << endl;
    cout << setw(22) << left << "Date/Time" << setw(13) << left << "Trans-No." <<
            setw(14) << left << "Details" << setw(11) << left << "Transaction" << endl;
    cout << "------------------------------------------------------------" << endl;

    node *cur = head;
    string checkDate = month + "-" + year;
    while(cur)
    {
        if(cur->date.substr(3,5) == checkDate)
        {
            cout << setw(22) << left << cur->date << setw(13) << left << cur->transactionNumber <<
                    setw(14) << left << cur->description << setw(11) << right << cur->amount << endl;
        }
        cur = cur->next;
    }
    cout << endl;
}

int main()
{
    // initial balance of account
    double balance = 0;
    int selection;
    string description;
    double amount;
    string year;
    string month;
    int deleteNumber;
    // use transaction id nos. to demonstrate insert/delete node
    // will be incremented by 2 for insertion purposes
    // creates unique identifier, easier than date to work with
    int transactionNumber = 9000;
    int insertTransaction = 9001;

    do
    {
        cout << "Please make a selection:\n" << endl;
        cout << "1.) Deposit" << endl;
        cout << "2.) Withdraw" << endl;
        cout << "3.) Show Balance" << endl;
        cout << "4.) Show Last Transaction" << endl;
        cout << "5.) Show All Transactions" << endl;
        cout << "6.) Monthly Statement" << endl;
        cout << "7.) Delete Transaction" << endl;
        cout << "8.) Insert Transaction" << endl;
        cout << "9.) Quit" << endl;
        cout << endl;
        cin >> selection;
        cin.ignore();

        if(selection == 1)
        {
            cout << endl << "Please enter description:\n" << endl;
            getline(cin, description);
            cout << endl << "Please enter the amount to be deposited:\n" << endl;
            cin >> amount;
            cout << endl;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "Error: Expected a number!\n\n";
            }
            else
            {
                balance += amount;
                addNode(description, transactionNumber, amount);
                transactionNumber += 2;
            }
        }

        else if(selection == 2)
        {
            cout << endl << "Please enter description:\n" << endl;
            getline(cin, description);
            cout << endl << "Please enter the amount to be withdrawn:\n" << endl;
            cin >> amount;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nError: Expected a number!\n";
            }
            else
            {
                if(balance - amount >= 0)
                {
                    balance -= amount;
                    addNode(description, transactionNumber, -amount);
                    transactionNumber += 2;
                }
                else
                    cout << "\nInsuffiencient Funds!" << endl;
            }
            cout << endl;
        }

        else if(selection == 3)
            cout << "\nYour Balance is: " << balance << endl<<endl;

        else if(selection == 4)
            displayLastTransaction();

        else if(selection == 5)
            displayAllTransactions();

        else if(selection == 6)
        {
            cout << endl << "Please enter year(YY):\n" << endl;
            getline(cin, year);
            cout << endl << "Please enter month(MM):\n" << endl;
            getline(cin, month);
            showMonthlyTransactions(year, month);
        }

        else if(selection == 7)
        {
            cout << endl << "Please enter Transaction Number for deletion:\n" << endl;
            cin >> deleteNumber;
            if(searchNode2(deleteNumber))
            {
                balance = updateBalance(balance, deleteNumber);
                deleteNode(deleteNumber);
            }
            else
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nTransaction Number not found.\n";
            }
            cout << endl;
        }

        else if(selection == 8)
        {
            cout << endl << "Please enter reason for insertion:\n" << endl;
            getline(cin, description);
            cout << endl << "Please enter +/- amount:\n" << endl;
            cin >> amount;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "\nError: Expected a number!\n";
            }
            else
            {
                balance += amount;
                insertNode(description, insertTransaction, amount);
                insertTransaction += 2;
                transactionNumber += 2;
            }
            cout << endl;
        }

        else if(cin.fail())
        {
          cin.clear();
          cin.ignore(20, '\n');
          cout << endl << "Incorrect entry: Choose a number.\n\n";
        }
    }
    while(selection != 9);

    return 0;
}
