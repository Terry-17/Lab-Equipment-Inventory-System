#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

/* =========================
   CLASS: Equipment
   ========================= */
class Equipment {
public:
    int id;
    string name;
    string condition;
    string location;
    bool available;

    Equipment(int i, string n, string c, string l, bool a = true) {
        id = i;
        name = n;
        condition = c;
        location = l;
        available = a;
    }
};

/* =========================
   CLASS: Checkout
   ========================= */
class Checkout {
public:
    int equipmentId;
    int studentId;
    string checkoutDate;
    string dueDate;

    Checkout(int eId, int sId, string cDate, string dDate) {
        equipmentId = eId;
        studentId = sId;
        checkoutDate = cDate;
        dueDate = dDate;
    }
};

/* =========================
   CLASS: InventorySystem
   ========================= */
class InventorySystem {
private:
    vector<Equipment> equipmentList;
    vector<Checkout> checkoutList;
    vector<string> transactionLog;

public:
    InventorySystem();  // Constructor (hard-coded equipment)
    void menu();
    void viewEquipment();
    void checkoutEquipment();
    void checkinEquipment();
    void viewBorrowed();
    void viewTransactions();
};

/* =========================1
   CONSTRUCTOR
   Hard-coded equipment here
   ========================= */
InventorySystem::InventorySystem() {

    equipmentList.push_back(Equipment(101, "Oscilloscope", "Good", "Lab A"));
    equipmentList.push_back(Equipment(102, "Multimeter", "Good", "Lab A"));
    equipmentList.push_back(Equipment(103, "Signal Generator", "Fair", "Lab B"));
    equipmentList.push_back(Equipment(104, "Power Supply", "Good", "Lab B"));
    equipmentList.push_back(Equipment(105, "Function Generator", "Excellent", "Store Room"));
}

// Helper: format a time_t as D/M/YYYY
static string getFormattedDate(time_t rawTime) {
    tm *timeInfo = localtime(&rawTime);
    stringstream ss;

    ss << (timeInfo->tm_mday) << "/"
       << (timeInfo->tm_mon + 1) << "/"
       << (timeInfo->tm_year + 1900);

    return ss.str();
}

/* =========================
   VIEW EQUIPMENT
   ========================= */
void InventorySystem::viewEquipment() {
    cout << "\nID   Name               Condition   Location      Status\n";
    cout << "---------------------------------------------------------------\n";

    for (auto &e : equipmentList) {
        cout << e.id << "   "
             << e.name << "   "
             << e.condition << "   "
             << e.location << "   "
             << (e.available ? "Available" : "Checked Out") << endl;
    }
}

/* =========================
   CHECKOUT EQUIPMENT
   ========================= */
void InventorySystem::checkoutEquipment() {
    int eqId, studentId;
    bool found = false;

    cout << "Enter Equipment ID: ";
    cin >> eqId;

    cout << "Enter Student ID: ";
    cin >> studentId;

    

    // Get current time
    time_t now = time(0);

    // Checkout date = today
    string checkoutDate = getFormattedDate(now);

    // Due date = 7 days from today
    time_t dueTime = now + (7 * 24 * 60 * 60);
    string dueDate = getFormattedDate(dueTime);

    for (auto &e : equipmentList) {
        if (e.id == eqId && e.available) {
            e.available = false;
            found = true;

            checkoutList.push_back(
                Checkout(eqId, studentId, checkoutDate, dueDate)
            );

            transactionLog.push_back(
                "CHECKOUT | Equipment ID: " + to_string(eqId) +
                " | Student ID: " + to_string(studentId) +
                " | Due: " + dueDate
            );

            break;
        }
    }

    if (found) {
        cout << "Equipment checked out successfully.\n";
        cout << "Checkout Date: " << checkoutDate << endl;
        cout << "Due Date: " << dueDate << endl;
    }
    else {
        cout << "Equipment not available or does not exist.\n";
    }
}
/* =========================
   CHECKIN EQUIPMENT
   ========================= */
void InventorySystem::checkinEquipment() {
    int eqId, studentId;
    bool found = false;

    cout << "Enter Equipment ID: ";
    cin >> eqId;

    cout << "Enter Student ID: ";
    cin >> studentId;

    for (auto &e : equipmentList) {
        if (e.id == eqId) {
            e.available = true;
            found = true;

            transactionLog.push_back(
                "CHECKIN | Equipment ID: " + to_string(eqId) +
                " | Student ID: " + to_string(studentId)
            );
            break;
        }
    }

    if (found)
        cout << "Equipment checked in successfully.\n";
    else
        cout << "Equipment not found.\n";
}

/* =========================
   VIEW BORROWED EQUIPMENT
   ========================= */
void InventorySystem::viewBorrowed() {
    cout << "\nBorrowed Equipment\n";
    cout << "EqID   StudentID   CheckoutDate   DueDate\n";
    cout << "---------------------------------------------\n";

    for (auto &c : checkoutList) {
        cout << c.equipmentId << "     "
             << c.studentId << "     "
             << c.checkoutDate << "     "
             << c.dueDate << endl;
    }
}

/* =========================
   VIEW TRANSACTIONS
   ========================= */
void InventorySystem::viewTransactions() {
    cout << "\nTransaction Log\n";
    cout << "-----------------\n";

    for (auto &t : transactionLog) {
        cout << t << endl;
    }
}

/* =========================
   MENU
   ========================= */
void InventorySystem::menu() {
    int choice;

    do {
        cout << "\n===== LAB EQUIPMENT INVENTORY SYSTEM =====\n";
        cout << "1. View Equipment\n";
        cout << "2. Check Out Equipment\n";
        cout << "3. Check In Equipment\n";
        cout << "4. View Borrowed Equipment\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewEquipment(); break;
            case 2: checkoutEquipment(); break;
            case 3: checkinEquipment(); break;
            case 4: viewBorrowed(); break;
            case 5: viewTransactions(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);
}

/* =========================
   MAIN
   ========================= */
int main() {
    InventorySystem system;
    system.menu();
    return 0;
}