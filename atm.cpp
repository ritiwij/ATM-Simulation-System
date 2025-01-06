#include <bits/stdc++.h>
#include <conio.h>
#include <ctime>
#include <iomanip>
using namespace std;

class atm
{
private:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    int failed_attempts;
    bool locked;
    vector<string> transaction_history;

public:
    // Constructor
    atm() : failed_attempts(0), locked(false) {}

    // Setters for initializing user data
    void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_No_a)
    {
        account_No = account_No_a;
        name = name_a;
        PIN = PIN_a;
        balance = balance_a;
        mobile_No = mobile_No_a;
    }

    // Getter methods
    long int getAccountNo() { return account_No; }
    string getName() { return name; }
    double getBalance() { return balance; }
    string getMobileNo() { return mobile_No; }

    // Update mobile number
    void setMobile(string mob_prev, string mob_new)
    {
        if (mob_prev == mobile_No)
        {
            mobile_No = mob_new;
            transaction_history.push_back("Mobile number updated");
            cout << endl
                 << "Successfully Updated Mobile No.";
        }
        else
        {
            cout << endl
                 << "Incorrect Old Mobile No.";
        }
        _getch();
    }

    // Withdraw cash with basic validation
    void cashWithDraw(int amount_a)
    {
        try
        {
            if (amount_a <= 0 || amount_a > balance)
            {
                throw invalid_argument("Invalid Input or Insufficient Balance");
            }
            balance -= amount_a;
            transaction_history.push_back("Cash Withdrawn: " + to_string(amount_a));
            cout << endl
                 << "Please Collect Your Cash";
            cout << endl
                 << "Available Balance: " << balance;
        }
        catch (const exception &e)
        {
            cout << endl
                 << e.what();
        }
        _getch();
    }

    // Deposit cash
    void depositCash(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            transaction_history.push_back("Deposited: " + to_string(amount));
            cout << endl
                 << "Deposit Successful!";
            cout << endl
                 << "Available Balance: " << balance;
        }
        else
        {
            cout << endl
                 << "Invalid Deposit Amount";
        }
        _getch();
    }

    // Display transaction history
    void showTransactionHistory()
    {
        cout << endl
             << "*** Transaction History ***";
        for (const string &entry : transaction_history)
        {
            cout << endl
                 << entry;
        }
        _getch();
    }

    // Change the PIN
    void changePIN(int oldPIN, int newPIN)
    {
        if (oldPIN == PIN)
        {
            PIN = newPIN;
            transaction_history.push_back("PIN Changed");
            cout << endl
                 << "PIN Changed Successfully!";
        }
        else
        {
            cout << endl
                 << "Incorrect Old PIN!";
        }
        _getch();
    }

    // Account lock mechanism
    bool isAccountLocked() { return locked; }

    // Authenticate user by PIN with lockout after 3 failed attempts
    bool authenticate(int pin)
    {
        if (isAccountLocked())
        {
            cout << endl
                 << "Account is locked due to too many failed attempts.";
            return false;
        }

        if (PIN == pin)
        {
            failed_attempts = 0; // reset after successful login
            return true;
        }
        else
        {
            failed_attempts++;
            if (failed_attempts >= 3)
            {
                locked = true;
                cout << endl
                     << "Account Locked due to 3 failed attempts!";
            }
            else
            {
                cout << endl
                     << "Incorrect PIN!";
            }
            _getch();
            return false;
        }
    }

    // Apply quarterly interest (example of additional feature)
    void applyInterest(double rate)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int month = ltm->tm_mon + 1; // Get current month

        if (month % 3 == 0) // Apply interest every 3rd month (quarterly)
        {
            balance += balance * rate;
            transaction_history.push_back("Interest Applied: " + to_string(balance * rate));
        }
    }
};

// Function to display ATM menu
void displayMenu()
{
    cout << endl
         << "**** Welcome to ATM *****";
    cout << endl
         << "1. Check Balance";
    cout << endl
         << "2. Cash Withdraw";
    cout << endl
         << "3. Deposit Cash";
    cout << endl
         << "4. Show User Details";
    cout << endl
         << "5. Update Mobile No.";
    cout << endl
         << "6. Show Transaction History";
    cout << endl
         << "7. Change PIN";
    cout << endl
         << "8. Exit" << endl;
}

// Main function to drive the ATM system
int main()
{
    vector<atm> users;
    users.push_back(atm());
    users[0].setData(1234567, "Vaibhav", 1111, 45000.90, "9087654321");

    users.push_back(atm());
    users[1].setData(9876543, "Sourabh", 2222, 25000.50, "9876543210");

    int choice = 0, enterPIN;
    long int enterAccountNo;

    do
    {
        system("cls");
        cout << endl
             << "**** Welcome to ATM *****" << endl;
        cout << endl
             << "Enter Your Account No: ";
        cin >> enterAccountNo;

        cout << endl
             << "Enter PIN: ";
        cin >> enterPIN;

        bool userFound = false;
        atm *currentUser = nullptr;

        for (atm &user : users)
        {
            if (user.getAccountNo() == enterAccountNo)
            {
                userFound = true;
                currentUser = &user;
                break;
            }
        }

        if (!userFound)
        {
            cout << endl
                 << "Account Not Found!";
            _getch();
            continue;
        }

        if (currentUser->authenticate(enterPIN))
        {
            do
            {
                system("cls");
                displayMenu();
                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << endl
                         << "Your Bank balance is: " << fixed << setprecision(2) << currentUser->getBalance();
                    _getch();
                    break;

                case 2:
                {
                    int amount = 0;
                    cout << endl
                         << "Enter the amount: ";
                    cin >> amount;
                    currentUser->cashWithDraw(amount);
                    break;
                }

                case 3:
                {
                    double amount;
                    cout << endl
                         << "Enter the amount to deposit: ";
                    cin >> amount;
                    currentUser->depositCash(amount);
                    break;
                }

                case 4:
                    cout << endl
                         << "*** User Details ***";
                    cout << endl
                         << "Account No.: " << currentUser->getAccountNo();
                    cout << endl
                         << "Name: " << currentUser->getName();
                    cout << endl
                         << "Balance: " << currentUser->getBalance();
                    cout << endl
                         << "Mobile No.: " << currentUser->getMobileNo();
                    _getch();
                    break;

                case 5:
                {
                    string oldMobileNo, newMobileNo;
                    cout << endl
                         << "Enter Old Mobile No.: ";
                    cin >> oldMobileNo;
                    cout << endl
                         << "Enter New Mobile No.: ";
                    cin >> newMobileNo;
                    currentUser->setMobile(oldMobileNo, newMobileNo);
                    break;
                }

                case 6:
                    currentUser->showTransactionHistory();
                    break;

                case 7:
                {
                    int oldPIN, newPIN;
                    cout << endl
                         << "Enter Old PIN: ";
                    cin >> oldPIN;
                    cout << endl
                         << "Enter New PIN: ";
                    cin >> newPIN;
                    currentUser->changePIN(oldPIN, newPIN);
                    break;
                }

                case 8:
                    exit(0);

                default:
                    cout << endl
                         << "Enter Valid Option!";
                }

            } while (true);
        }
        else
        {
            cout << endl
                 << "Authentication Failed!";
        }

    } while (true);

    return 0;
}