#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h> 
#include <iomanip>
#include <limits>
#include <tuple>
#include "1functions.h"
using namespace std;



int main()
{
    insertCsvFileToUserList(rhead, rtail, "1userlist.csv");
    insertCsvFileToList(uhead,utail,"2023_QS_World_University_Rankings.csv");
    insertCsvFileToFBList(fbhead,fbtail,"1feedback.csv");
    insertCsvFileToFVList(fvhead,fvtail,"1favourites.csv");
    int choice,fvc;
    do {
        cout << "-----------------------------------\n";
        cout << "              WELCOME              \n";
        cout << "-----------------------------------\n";
        cout << "1. LOGIN as ADMIN\n";
        cout << "2. LOGIN as CUSTOMER\n";
        cout << "3. REGISTER as CUSTOMER\n";
        cout << "4. BROWSE UNIVERSITY\n";
        cout << "5. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                customerLogin();
                break;
            case 3:
                registerCustomer();
                break;
            case 4:
                browseUniversity();
                break;
            case 5:
                cout << "Exiting...\n";
                writeuserintocsv("1userlist.csv");
                writefvintocsv();
                writefeedbackintocsv();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;
    } while (choice != 5);

    return 0;
}