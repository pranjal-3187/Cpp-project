#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ElectricityBill {
private:
    string customer_id;
    string customer_name;
    string customer_type;
    long long contact_no;
    float total_units;
    float rate_per_unit;
    float fixed_charge;
    float total_bill;

public:
    // Function to take input
    void inputData() {
        cout << "\nEnter Customer ID: ";
        cin >> customer_id;

        cin.ignore();
        cout << "Enter Customer Name: ";
        getline(cin, customer_name);

        // Contact number validation
        while (true) {
            cout << "Enter Contact Number (10 digits): ";
            cin >> contact_no;
            if (contact_no >= 1000000000LL && contact_no <= 9999999999LL)
                break;
            else
                cout << "Invalid contact number!\n";
        }

        cout << "Enter Customer Type (Residential/Commercial): ";
        cin >> customer_type;

        if (customer_type == "Residential") {
            rate_per_unit = 5.0;
            fixed_charge = 100.0;
        } else if (customer_type == "Commercial") {
            rate_per_unit = 7.0;
            fixed_charge = 150.0;
        } else {
            cout << "Invalid customer type!\n";
            rate_per_unit = fixed_charge = 0;
        }

        while (true) {
            cout << "Enter Units Consumed: ";
            cin >> total_units;
            if (total_units >= 0)
                break;
            else
                cout << "Units cannot be negative!\n";
        }

        calculateBill();
    }

    // Function to calculate bill
    void calculateBill() {
        total_bill = (total_units * rate_per_unit) + fixed_charge;
    }

    // Display bill
    void displayBill() {
        cout << "\n----- Electricity Bill -----\n";
        cout << "Customer ID      : " << customer_id << endl;
        cout << "Customer Name    : " << customer_name << endl;
        cout << "Contact Number   : " << contact_no << endl;
        cout << "Customer Type    : " << customer_type << endl;
        cout << "Units Consumed   : " << total_units << endl;
        cout << "Total Bill (Rs.) : " << total_bill << endl;
        cout << "----------------------------\n";
    }

    // Save record to file
    void saveToFile() {
        ofstream file("billing_data.txt", ios::app);
        file << customer_id << " | "
             << customer_name << " | "
             << contact_no << " | "
             << customer_type << " | "
             << total_units << " | "
             << total_bill << endl;
        file.close();
    }

    // View all records
    static void viewRecords() {
        ifstream file("billing_data.txt");
        string line;

        cout << "\n----- Stored Billing Records -----\n";
        if (!file) {
            cout << "No records found.\n";
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "---------------------------------\n";

        file.close();
    }
};

// Menu-driven main function
int main() {
    ElectricityBill bill;
    int choice;

    do {
        cout << "\n===== Electricity Billing System =====\n";
        cout << "1. Generate New Bill\n";
        cout << "2. View All Bills\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bill.inputData();
            bill.displayBill();
            bill.saveToFile();
            cout << "Bill saved successfully!\n";
            break;

        case 2:
            ElectricityBill::viewRecords();
            break;

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
