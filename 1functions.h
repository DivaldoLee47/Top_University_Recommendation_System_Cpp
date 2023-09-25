

#include <iostream>
#include <fstream>
#include <string> 
#include <tuple>
#include <array>
#include <ctime>
#include "1doublelinked.h"

using namespace std;

ofstream outputFile;
ofstream fs;

bool login(string loginid, string loginpw){
            reguser* temp = rhead;
            reguser* previous = nullptr;
                
                while (temp != nullptr) {
                    if(temp->id == loginid && temp->password == loginpw){
                        cout<<"Admin Login Successful";
                        cout << "Login successfully." << endl;
                        return true;
                        break;
                    }
                temp = temp->rnext;
            }
}



void registeruser(){
    
    string inpuser;
    string inpattribute;
    string inpn;
    // univ* uhead = NULL;
    int choice;
    bool exit = false;
    bool test = false;
    // insertCsvFileToUserList(rhead,rtail,"Registered_user.csv");
    while (exit == false){
        choice = 0;
        cout << "Sorted list: ";
        // displayDoubleList();
        // mergeSort(&uhead);
        // displayDoubleList();
        // displayDoubleList();
        displayUserDoubleList(rhead);
        cout<< "\n\n Enter A Function: \n\n 1. Modify a user's detail\n 2. Delete user accounts \n 3. Exit\n\n";
        cin >>choice;
        switch(choice){
            case 1:
                cout<<" Please Enter a User Id you would like to modify: ";
                cin>>inpuser;
                cout<<"\n";
                selectuser(inpuser);
                cout<<"\n type the name of the attribute to change: \n\n 1. Password\n 2. Name \n 3. Email\n\n";
                cin>>inpattribute;
                searchandupdateuser(inpattribute,inpuser);
                break;
            case 2:
                cout<< "\n The Users have been sorted based on inactivity: \n";
                insertionUserSort(rhead);
                displayUserDoubleList(rhead);
                cout<<"\nEnter The User ID you want to delete: ";
                cin>>inpn;
                cout<<"\n";
                
                deleteendofuserlist(inpn);
                break;
            case 3:
                cout<< "-- Program will now Exit --";
                exit = true;
        }
    }
}

void feedback(){
    string inpuser2;
    int choice1,choice2,inpn;;;
    bool exit = false;
    bool test = false;

    
    while (exit == false){
        choice1 = 0;
        choice2 = 0;
        displayfeedbackDoubleList();
        cout<< "\n Enter A Function: \n\n 1. Reply to a feedback\n 2. Exit \n\n";
        cin >>choice2;
        switch(choice2){
            case 1:
                cout<<" Please Enter the Feedback Id of the Feedback you would like to reply to: \n";
                cin>>inpuser2;
                cout<<"\n";
                replyfb(inpuser2);
                
                break;
            case 2:
                cout<< "-- Program will now Exit --";
                exit = true;
                break;
        }
    }
}

void favourite(string id){
    bool exit2 = false;
    string inpuser;
    int choice = 0;
    string uniname;
    while(exit2==false){
        // displayDoubleList();
        cout<< "\n Enter A Function: \n\n 1. Save a university to your Favourites \n 2. Exit \n\n";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "\n Please enter the University Ranking of the University you want to save";
                cin >> inpuser;
                uniname = selectuni(inpuser);
                insert_favourite_end(id,inpuser,uniname);
                cout<<"\nUniversity has been Favourited";
                // displayfavouriteDoubleList();
                break;
            case 2:
                cout<< "-- Program will now Exit --";
                exit2 = true;
                break;
        }
    }
}



void adminLogin()
{
    HashMap* hashmap;
    HashMap* head;
    string adminid,inputid, pword, tempid;
    int choice,fvcounter;
    bool adminlogin = false;
    bool logout = true;
    bool exit = false;

    while (exit == false){
        if(logout == true){
            while(adminlogin == false){
                cout << "enter name: " << endl;
                cin >> inputid;
                cout << "enter password: " << endl;
                cin >> pword;
                adminlogin = login(inputid,pword);
            } 
            tempid = inputid;  
            logout = false;
        }


    cout<<"\n\n  Admin Main Menu  \n\n";


        cout<< " Enter A Function: \n\n 1. Display all Register User's Details\n 2. Display all Feedbacks of Users\n 3. Report Generation\n 4. Logout\n 5. Exit\n\n";
        cin >>choice;
        switch(choice){
            case 1:
                registeruser();
                break;
            case 2:
                feedback();
                break;
            case 3:
                cout << "== Top 10 universities most preferred by parents in Malaysia ==" << endl << endl;
				hashmap = calculateTopUniversities();
				hashmap->display();
                break;
            case 4:
                logout = true;
                adminlogin = false;
                break;
            case 5:
                cout<< "-- Program will now Exit --";
                // writeuserintocsv("1userlist.csv");
                // writefeedbackintocsv();
                // writefvintocsv(fvcounter);
                exit = true;
                break;
            case 6:
                favourite(tempid);
                break;
                
        }
    }
}


void customermenu(string id){
    int choice = -1;
    int fvcounter;
    string tempid;
    string cusid, inputid, pword;
    bool cusLogin = false;
    bool logout = true;
    bool exit = false;

    while (choice != 0)
    {
        cout << "Please select the option below:\n "
             << "1. Display University Information\n"
             << "2. Search University Details\n"
             << "3. Send Feedback to MoHE\n"
             << "4. Read Reply from MoHE\n"
             << "5. Logout\n"
             << "6. Save Favourite\n"
             << "0. Exit\n"
             << "Enter your choice: " << endl;
        cin >> choice;

        if (choice == 1)
        {
            displayUniInfo();
        }
        else if (choice == 2)
        {
            search();
        }
        else if (choice == 3)
        {
            sendFeedback(id);
        }
        else if (choice == 4)
        {
            insertionFBSort(fbhead);
            readFeedback(id);
        }
        else if (choice == 5)
        {
            logout = true;
            break;
        }
        else if (choice == 6)
        {
            favourite(id);
        }
        else if (choice == 0)
        {
            cout << "Exited from Program" << endl;
            exit = true;
            break;
        }
        else
        {
            cout << "Choice entered is not available" << endl;
        }
        cout << endl;
    }
}        
void customerLogin()
{
    string id, password,tid,tpw,name,email,logtime;
    time_t now = time(0);
    tm *local_time = localtime(&now);
    int year = (local_time->tm_year)+1900;;
    int month = (local_time->tm_mon)+1;
    int day = local_time->tm_mday;
    logtime = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    reguser* current = rhead;
    reguser* previous = nullptr;

    // Find the node with the selected ID
    while (current != nullptr) {
        if(current->id == id && current->password == password){
            cout<<"User Login Successful";
            current->logtime = logtime;
            customermenu(id);
        }
        current = current->rnext;
    }
    cout<<"Unsuccesful";
}
void registerCustomer()
{
    time_t now = time(0);
    string name, password, email,logtime;
    // string id = "CUS002";
    string id = autoid();
    tm *local_time = localtime(&now);
    int year = (local_time->tm_year)+1900;;
    int month = (local_time->tm_mon)+1;
    int day = local_time->tm_mday;
    logtime = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << "Generated User ID: " << id << endl;

    cin.ignore(); // Clear the newline character from the input buffer

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    getline(cin, password);
    cout << "Enter Email: ";
    getline(cin, email);

    // Create a new user node with the entered data
    insert_user_end(id, password, name, email,logtime);

    cout << "\n>>> Registration SUCCESS! <<<\n" << endl;
}




