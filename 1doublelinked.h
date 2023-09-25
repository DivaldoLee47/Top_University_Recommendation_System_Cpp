#include<bits/stdc++.h>
#define maxreply 300
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h> 
#include "1hashmap.h"
using namespace std;

class univ {
   public:
    string Rank;
    string Institution;
    string LocationCode;
    string Location;
    string ArScore;
    string ArRank;
    string ErScore;
    string ErRank;
    string FsrScore;
    string FsrRank;
    string CpfScore;
    string CpfRank;
    string IfrScore;
    string IfrRank;
    string IsrScore;
    string IsrRank;
    string IrnScore;
    string IrnRank;
    string GerScore;
    string GerRank;
    string ScoreScaled;
    struct univ* next;
    struct univ* prev;
}*uhead,*utail;

class reguser{
    public:
    string id;
    string password;
    string name;
    string email;
    string logtime;
    struct reguser* rnext;
    struct reguser* rprev;
}*rhead, *rtail;

class fv{
    public:
    string id;
    string rank;
    string institution;
    struct fv* fvnext;
    struct fv* fvprev;
}*fvhead, *fvtail;

class fb{
    public:
    string fbid;
    string id;
    string uniname;
    string feedback;
    string reply;
    string fbtime;
    struct fb* fbnext;
    struct fb* fbprev;
}*fbhead, *fbtail;


//MERGESORT
univ *merge(univ *first, univ *second)    
{    
     if (!first)
        return second;
    if (!second)
        return first;

    univ* result = NULL;
    if (first->Institution <= second->Institution) {
        result = first;
        result->next = merge(first->next, second);
        if (result->next)
            result->next->prev = result;
    } else {
        result = second;
        result->next = merge(first, second->next);
        if (result->next)
            result->next->prev = result;
    }

    result->prev = NULL;
    return result;
}    
univ *split(univ *head){
     univ* fast = head;
    univ* slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    univ* second = slow->next;
    slow->next = NULL;
    if (second)
        second->prev = NULL;
    return second;  
};  
    
univ *mergeSort(univ** headref)    
{    
    univ* head = *headref;
    if (!head || !head->next)
        return head;
    univ* second = split(head);
    mergeSort(&head);
    mergeSort(&second);
    *headref = merge(head, second); 
}  

void insertSorted(univ*& head, univ* newNode) {
    if (head == nullptr) {
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return;
    }

    if (newNode->Institution > head->Institution) {
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    univ* current = head;
    while (current->next != nullptr && newNode->Institution.compare(current->next->Institution) >= 0) {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

void insertionSort(univ*& head) {
    univ* sorted = nullptr;
    univ* current = head;
    while (current != nullptr) {
        univ* nextNode = current->next;
        insertSorted(sorted, current);
        current = nextNode;
    }
    head = sorted;
}



void insertUserSorted(reguser*& rhead, reguser* newNode) {
    if (rhead == nullptr) {
        rhead = newNode;
        newNode->rprev = nullptr;
        newNode->rnext = nullptr;
        return;
    }

    std::stringstream newNodeStream(newNode->logtime);
    std::stringstream currentStream(rhead->logtime);

    int newDay, newMonth, newYear;
    int currentDay, currentMonth, currentYear;

    char delimiter;
    newNodeStream >> newDay >> delimiter >> newMonth >> delimiter >> newYear;
    currentStream >> currentDay >> delimiter >> currentMonth >> delimiter >> currentYear;

    std::tm newDate = {0};
    newDate.tm_mday = newDay;
    newDate.tm_mon = newMonth - 1; // Months are zero-based
    newDate.tm_year = newYear - 1900; // Years are relative to 1900

    std::tm currentDate = {0};
    currentDate.tm_mday = currentDay;
    currentDate.tm_mon = currentMonth - 1;
    currentDate.tm_year = currentYear - 1900;

    if (std::mktime(&newDate) < std::mktime(&currentDate)) {
        newNode->rprev = nullptr;
        newNode->rnext = rhead;
        rhead->rprev = newNode;
        rhead = newNode;
        return;
    }

    reguser* current = rhead;
    while (current->rnext != nullptr) {
        std::stringstream nextStream(current->rnext->logtime);
        int nextDay, nextMonth, nextYear;
        nextStream >> nextDay >> delimiter >> nextMonth >> delimiter >> nextYear;

        std::tm nextDate = {0};
        nextDate.tm_mday = nextDay;
        nextDate.tm_mon = nextMonth - 1;
        nextDate.tm_year = nextYear - 1900;

        if (std::mktime(&newDate) < std::mktime(&nextDate)) {
            break;
        }

        current = current->rnext;
    }

    newNode->rprev = current;
    newNode->rnext = current->rnext;
    if (current->rnext != nullptr) {
        current->rnext->rprev = newNode;
    }
    current->rnext = newNode;
}

void insertFBSorted(fb*& fbhead, fb* newNode) {
    if (fbhead == nullptr) {
        fbhead = newNode;
        newNode->fbprev = nullptr;
        newNode->fbnext = nullptr;
        return;
    }

    std::stringstream newNodeStream(newNode->fbtime);
    std::stringstream currentStream(fbhead->fbtime);

    int newDay, newMonth, newYear;
    int currentDay, currentMonth, currentYear;

    char delimiter;
    newNodeStream >> newDay >> delimiter >> newMonth >> delimiter >> newYear;
    currentStream >> currentDay >> delimiter >> currentMonth >> delimiter >> currentYear;

    std::tm newDate = {0};
    newDate.tm_mday = newDay;
    newDate.tm_mon = newMonth - 1; // Months are zero-based
    newDate.tm_year = newYear - 1900; // Years are relative to 1900

    std::tm currentDate = {0};
    currentDate.tm_mday = currentDay;
    currentDate.tm_mon = currentMonth - 1;
    currentDate.tm_year = currentYear - 1900;

    if (std::mktime(&newDate) < std::mktime(&currentDate)) {
        newNode->fbprev = nullptr;
        newNode->fbnext = fbhead;
        fbhead->fbprev = newNode;
        fbhead = newNode;
        return;
    }

    fb* current = fbhead;
    while (current->fbnext != nullptr) {
        std::stringstream nextStream(current->fbnext->fbtime);
        int nextDay, nextMonth, nextYear;
        nextStream >> nextDay >> delimiter >> nextMonth >> delimiter >> nextYear;

        std::tm nextDate = {0};
        nextDate.tm_mday = nextDay;
        nextDate.tm_mon = nextMonth - 1;
        nextDate.tm_year = nextYear - 1900;

        if (std::mktime(&newDate) < std::mktime(&nextDate)) {
            break;
        }

        current = current->fbnext;
    }

    newNode->fbprev = current;
    newNode->fbnext = current->fbnext;
    if (current->fbnext != nullptr) {
        current->fbnext->fbprev = newNode;
    }
    current->fbnext = newNode;
}

void insertionUserSort(reguser*& rhead) {
    reguser* sorted = nullptr;
    reguser* current = rhead;
    while (current != nullptr) {
        reguser* nextNode = current->rnext;
        insertUserSorted(sorted, current);
        current = nextNode;
    }
    rhead = sorted;
}

void displayFBSorted(fb* fbhead) {
    fb* current = fbhead;
    while (current != nullptr) {
        // Display the node, assuming the `fbtime` field is a string
        std::cout << current->fbtime << std::endl;

        current = current->fbnext;
    }
}
void insertionFBSort(fb*& fbhead) {
    fb* sorted = nullptr;
    fb* current = fbhead;
    while (current != nullptr) {
        fb* nextNode = current->fbnext;
        insertFBSorted(sorted, current);
        current = nextNode;
    }
    displayFBSorted(sorted); // Display the sorted nodes
}
void insertSortedFacultyRatioScore(univ *&head, univ *newNode)
{
    if (head == nullptr)
    {
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return;
    }

    if (newNode->FsrScore > head->FsrScore)
    {
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    univ *current = head;
    while (current->next != nullptr && newNode->FsrScore < current->next->FsrScore)
    {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != nullptr)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
}
void insertionSortFacultyRatioScore(univ *&head)
{
    univ *sorted = nullptr;
    univ *current = head;
    while (current != nullptr)
    {
        univ *nextNode = current->next;
        current->prev = nullptr;
        current->next = nullptr;
        insertSortedFacultyRatioScore(sorted, current);
        current = nextNode;
    }
    head = sorted;
}

void insertSortedAcaRepuScore(univ *&head, univ *newNode)
{
    if (head == nullptr)
    {
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return;
    }

    if (newNode->ArScore > head->ArScore)
    {
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    univ *current = head;
    while (current->next != nullptr && newNode->ArScore < current->next->ArScore)
    {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != nullptr)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

void insertSortedEmployRepuScore(univ *&head, univ *newNode)
{
    if (head == nullptr)
    {
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return;
    }

    if (newNode->ErScore > head->ErScore)
    {
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    univ *current = head;
    while (current->next != nullptr && newNode->ErScore < current->next->ErScore)
    {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != nullptr)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

void insertionSortAcademyReputationScore(univ *&head)
{
    univ *sorted = nullptr;
    univ *current = head;
    while (current != nullptr)
    {
        univ *nextNode = current->next;
        current->prev = nullptr;
        current->next = nullptr;
        insertSortedAcaRepuScore(sorted, current);
        current = nextNode;
    }
    head = sorted;
}

void insertionSortEmployerReputationScore(univ *&head)
{
    univ *sorted = nullptr;
    univ *current = head;
    while (current != nullptr)
    {
        univ *nextNode = current->next;
        current->prev = nullptr;
        current->next = nullptr;
        insertSortedEmployRepuScore(sorted, current);
        current = nextNode;
    }
    head = sorted;
}

univ* linearSearchByInstitution(univ* head, const string& targetInstitution) {
    univ* current = head;
    
    while (current != nullptr) {
        if (current->Institution == targetInstitution) {
            return current; // Found the node with the target institution
        }
        current = current->next;
    }
    
    return nullptr; // Target institution not found in the list
}

fv* linearSearchByFavourite(fv* head, const string& targetInstitution) {
    fv* current = fvhead;
    
    while (current != nullptr) {
        if (current->institution == targetInstitution) {
            return current; // Found the node with the target institution
        }
        current = current->fvnext;
    }
    
    return nullptr; // Target institution not found in the list
}
HashMap* calculateTopUniversities() {
    HashMapNode* head = nullptr;
    HashMap* uniToCount = new HashMap();
    fv* current = fvhead;

    while (current != nullptr) {
        if (uniToCount->hasKey(current->institution)) {
            uniToCount->setValue(current->institution, uniToCount->getValue(current->institution) + 1);
        } else {
            uniToCount->setValue(current->institution, 1);
        }
        current = current->fvnext;
    }
    return uniToCount;
}
void linearSearch(univ* head) {
    cin.ignore(); // Ignore any remaining newline character

    cout << "Enter the institution to search for: ";
    string targetInstitution;
    getline(cin, targetInstitution);

    univ* result = linearSearchByInstitution(head, targetInstitution);
    if (result != nullptr) {
        cout << "Found the node with institution " << targetInstitution << endl;
        cout << "Rank: " << result->Rank << endl;
        cout << "Institution: " << result->Institution << endl;
        cout << "Location Code: " << result->LocationCode << endl;
        cout << "Location: " << result->Location << endl;
        cout << "Ar Score: " << result->ArScore << endl;
        cout << "Ar Rank: " << result->ArRank << endl;
        cout << "Er Score: " << result->ErScore << endl;
        cout << "Er Rank: " << result->ErRank << endl;
        cout << "Fsr Score: " << result->FsrScore << endl;
        cout << "Fsr Rank: " << result->FsrRank << endl;
        cout << "Cpf Score: " << result->CpfScore << endl;
        cout << "Cpf Rank: " << result->CpfRank << endl;
        cout << "Ifr Score: " << result->IfrScore << endl;
        cout << "Ifr Rank: " << result->IfrRank << endl;
        cout << "Isr Score: " << result->IsrScore << endl;
        cout << "Isr Rank: " << result->IsrRank << endl;
        cout << "Irn Score: " << result->IrnScore << endl;
        cout << "Irn Rank: " << result->IrnRank << endl;
        cout << "Ger Score: " << result->GerScore << endl;
        cout << "Ger Rank: " << result->GerRank << endl;
        cout << "Score Scaled: " << result->ScoreScaled << endl;
    }
    else {
        cout << "Node with institution " << targetInstitution << " not found" << endl;
    }
}
void linearSearchCustomer(univ *head)
{
    cin.ignore();

    cout << "Enter any rank, institution, location, or location code:  ";
    string targetDecision;
    getline(cin, targetDecision);

    univ *result = head;
    bool found = false;

    cout << "Matching...\n"
         << endl;
    cout << "--------------\n"
         << endl;
    while (result != nullptr)
    {
        if (result->LocationCode == targetDecision ||
            result->Rank == targetDecision ||
            result->Institution == targetDecision ||
            result->Location == targetDecision
           
        )
        {
            found = true;
            cout << "===========================================================================" << endl;
            cout << "Location Code: " << result->LocationCode << endl;
            cout << "Rank: " << result->Rank << endl;
            cout << "Institution: " << result->Institution << endl;
            cout << "Location: " << result->Location << endl;
            cout << "Academic Reputation Score: " << result->ArScore << endl;
            cout << "Academic Reputation Rank: " << result->ArRank << endl;
            cout << "Employer Reputation Score: " << result->ErScore << endl;
            cout << "Employer Reputation Rank: " << result->ErRank << endl;
            cout << "Faculty/Student Ratio Score: " << result->FsrScore << endl;
            cout << "Faculty/Student Ratio Rank: " << result->FsrRank << endl;
            cout << "Citations per Faculty Score: " << result->CpfScore << endl;
            cout << "Citations per Faculty Rank: " << result->CpfRank << endl;
            cout << "International Faculty Ratio Score: " << result->IfrScore << endl;
            cout << "International Faculty Ratio Rank: " << result->IfrRank << endl;
            cout << "International Student Ratio Score: " << result->IsrScore << endl;
            cout << "International Student Ratio Rank: " << result->IsrRank << endl;
            cout << "International Research Network Score: " << result->IrnScore << endl;
            cout << "International Research Network Rank: " << result->IrnRank << endl;
            cout << "Employment Outcome Score: " << result->GerScore << endl;
            cout << "Employment Outcome Rank: " << result->GerRank << endl;
            cout << "===========================================================================" << endl;
            cout << endl;
        }
        result = result->next;
    }

    if (!found)
    {
        cout << "No information found!" << endl;
    }
}
univ* createLinkedListFromCSV(univ*& head, string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return nullptr;
    }
    string line;
    getline(file, line); // skip header row

    univ* tail = nullptr;
    while (getline(file, line)) {
        stringstream ss(line);
        string Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank,
            CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;
        getline(ss, Rank, ',');
        getline(ss, Institution, ',');
        getline(ss, LocationCode, ',');
        getline(ss, Location, ',');
        getline(ss, ArScore, ',');
        getline(ss, ArRank, ',');
        getline(ss, ErScore, ',');
        getline(ss, ErRank, ',');
        getline(ss, FsrScore, ',');
        getline(ss, FsrRank, ',');
        getline(ss, CpfScore, ',');
        getline(ss, CpfRank, ',');
        getline(ss, IfrScore, ',');
        getline(ss, IfrRank, ',');
        getline(ss, IsrScore, ',');
        getline(ss, IsrRank, ',');
        getline(ss, IrnScore, ',');
        getline(ss, IrnRank, ',');
        getline(ss, GerScore, ',');
        getline(ss, GerRank, ',');
        getline(ss, ScoreScaled);

        univ* node = new univ();
        node->Rank = Rank;
        node->Institution = Institution;
        node->LocationCode = LocationCode;
        node->Location = Location;
        node->ArScore = ArScore;
        node->ArRank = ArRank;
        node->ErScore = ErScore;
        node->ErRank = ErRank;
        node->FsrScore = FsrScore;
        node->FsrRank = FsrRank;
        node->CpfScore = CpfScore;
        node->CpfRank = CpfRank;
        node->IfrScore = IfrScore;
        node->IfrRank = IfrRank;
        node->IsrScore = IsrScore;
        node->IsrRank = IsrRank;
        node->IrnScore = IrnScore;
        node->IrnRank = IrnRank;
        node->GerScore = GerScore;
        node->GerRank = GerRank;
        node->ScoreScaled = ScoreScaled;

        node->prev = tail; // Set the previous node as the current tail

        if (tail == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node; // Set the next node of the current tail as the new node
            tail = node; // Update the tail to the new node
        }
    }
    return head;
}

void search()
{
    univ *head = nullptr;
    string filepath = "2023_QS_World_University_Rankings.csv";
    string tempid;
    head = createLinkedListFromCSV(head, filepath);

    int page = 1;
    int count = 0;
    univ *current = head;

    int maxRankLength = 0;
    int maxLocationLength = 0;
    int maxInstitutionLength = 0;
    while (current != nullptr)
    {
        // Calculate the maximum length of each attribute
        maxRankLength = max(maxRankLength, static_cast<int>(current->Rank.length()));
        maxLocationLength = max(maxLocationLength, static_cast<int>(current->Location.length()));
        maxInstitutionLength = max(maxInstitutionLength, static_cast<int>(current->Institution.length()));
        current = current->next;
    }

    current = head;

    while (current != nullptr)
    {
        if (count % 30 == 0)
        {
            if (count > 0)
            {
                cout << "-----------------------------------------------------------" << endl;
                cout << endl;
                int searchChoice;

                cout << "1. Navigate to Next Page\n";
                cout << "2. Search by Linear Search\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> searchChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (searchChoice == 2)
                {
                    linearSearchCustomer(head);
                    break;
                }
                else if (searchChoice == 3)
                {
                    return;
                }
                else
                {
                    cout << "Invalid Choice\n"
                         << endl;
                }
            }
            cout << "Page " << page << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << left << setw(maxRankLength + 2) << "Rank";
            cout << left << setw(maxLocationLength + 2) << "Location";
            cout << left << "Institution" << endl;
            cout << "-----------------------------------------------------------" << endl;
            page++;
        }

        cout << left << setw(maxRankLength + 2) << current->Rank;
        cout << left << setw(maxLocationLength + 2) << current->Location;
        cout << left << current->Institution << endl;
        count++;

        current = current->next;
    }

    if (count % 30 != 0)
    {
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;
    }
}
univ* binarySearchByInstitution(univ* head, const std::string& targetInstitution) {
    univ* start = head;
    univ* end = nullptr;

    while (start != end) {
        univ* mid = start;
        int count = 0;
        
        // Move mid to the middle node
        while (mid != end && mid->next != end) {
            mid = mid->next;
            count++;
        }
        
        if (mid == nullptr) {
            // Empty list or invalid state, exit the loop
            break;
        }
        
        // Move mid back to the actual middle node
        for (int i = 0; i < count / 2; i++) {
            mid = mid->prev;
        }
        
        if (mid->Institution == targetInstitution) {
            return mid; // Found the node with the target institution
        }
        else if (mid->Institution < targetInstitution) {
            start = mid->next; // Update the start to search the right half
        }
        else {
            end = mid; // Update the end to search the left half
        }
    }

    return nullptr; // Target institution not found in the list
}

void binarySearch(univ* head) {
    cin.ignore(); // Ignore any remaining newline character

    cout << "Enter the institution to search for: ";
    string targetInstitution;
    getline(cin, targetInstitution);

    univ* result = binarySearchByInstitution(head, targetInstitution);
    if (result != nullptr) {
        cout << "Found the node with institution " << targetInstitution << endl;
        cout << "Rank: " << result->Rank << endl;
        cout << "Institution: " << result->Institution << endl;
        cout << "Location Code: " << result->LocationCode << endl;
        cout << "Location: " << result->Location << endl;
        cout << "Ar Score: " << result->ArScore << endl;
        cout << "Ar Rank: " << result->ArRank << endl;
        cout << "Er Score: " << result->ErScore << endl;
        cout << "Er Rank: " << result->ErRank << endl;
        cout << "Fsr Score: " << result->FsrScore << endl;
        cout << "Fsr Rank: " << result->FsrRank << endl;
        cout << "Cpf Score: " << result->CpfScore << endl;
        cout << "Cpf Rank: " << result->CpfRank << endl;
        cout << "Ifr Score: " << result->IfrScore << endl;
        cout << "Ifr Rank: " << result->IfrRank << endl;
        cout << "Isr Score: " << result->IsrScore << endl;
        cout << "Isr Rank: " << result->IsrRank << endl;
        cout << "Irn Score: " << result->IrnScore << endl;
        cout << "Irn Rank: " << result->IrnRank << endl;
        cout << "Ger Score: " << result->GerScore << endl;
        cout << "Ger Rank: " << result->GerRank << endl;
        cout << "Score Scaled: " << result->ScoreScaled << endl;
    }
    else {
        cout << "Node with institution " << targetInstitution << " not found" << endl;
    }
}
void displayList(univ* head) {
    int page = 1;
    int count = 0;
    univ* current = head;
    bool shouldContinue = true; // Flag variable to control the loop

    // Calculate the maximum length of each attribute
    int maxRankLength = 0;
    int maxLocationLength = 0;
    int maxInstitutionLength = 0;
    while (current != nullptr) {
        maxRankLength = max(maxRankLength, static_cast<int>(current->Rank.length()));
        maxInstitutionLength = max(maxInstitutionLength, static_cast<int>(current->Institution.length()));
        maxLocationLength = max(maxLocationLength, static_cast<int>(current->Location.length()));
        current = current->next;
    }

    current = head;
    while (current != nullptr && shouldContinue) {
        // Print the table header for each page
        if (count % 30 == 0) {
            if (count > 0) {
                cout << "-----------------------------------------------------------" << endl;
                cout << endl;

                // Prompt the user for their choice
                cout << "1. Navigate to the next page" << endl;
                cout << "2. Search University by Linear Search" << endl;
                cout << "3. Search University by Binary Search" << endl;
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;
                cout << endl;

                // Process the user's choice
                if (choice == 2) {
                    // Call the linearSearch method
                    linearSearch(head);
                    shouldContinue = false; // Break out of the loop when linear search is requested
                } else if (choice == 3){
                    binarySearch(head);
                    shouldContinue = false; 
                }
            }
            if (shouldContinue) {
                cout << "Page " << page << endl;
                cout << "-----------------------------------------------------------" << endl;
                cout << left << setw(maxRankLength + 2) << "Rank";
                cout << left << setw(maxInstitutionLength + 2) << "Institution";
                cout << left << "Location" << endl;
                cout << "-----------------------------------------------------------" << endl;
                page++;
            }
        }

        if (shouldContinue) {
            // Print the data row with appropriate spacing
            cout << left << setw(maxRankLength + 2) << current->Rank;
            cout << left << setw(maxInstitutionLength + 2) << current->Institution;
            cout << left << current->Location << endl;
            count++;

            current = current->next;
        }
    }

    // Print the final page if there are remaining rows
    if (count % 30 != 0) {
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;
    }
}
void display(univ *head)
{
    int page = 1;
    int count = 0;
    univ *current = head;
    bool shouldContinue = true; // Flag variable to control the loop

    // Calculate the maximum length of each attribute
    int maxRankLength = 0;
    int maxLocationLength = 0;
    int maxInstitutionLength = 0;
    int maxAcedemicReputationLength = 0;
    int maxEmployerReputationLength = 0;

    while (current != nullptr)
    {
        maxRankLength = max(maxRankLength, static_cast<int>(current->Rank.length()));
        maxInstitutionLength = max(maxInstitutionLength, static_cast<int>(current->Institution.length()));
        maxLocationLength = max(maxLocationLength, static_cast<int>(current->Location.length()));
        maxAcedemicReputationLength = max(maxAcedemicReputationLength, static_cast<int>(current->ArScore.length()));
        maxEmployerReputationLength = max(maxEmployerReputationLength, static_cast<int>(current->ErScore.length()));
        current = current->next;
    }

    current = head;
    while (current != nullptr && shouldContinue)
    {
        // Print the table header for each page
        if (count % 30 == 0)
        {
            if (count > 0)
            {
                cout << "-----------------------------------------------------------" << endl;
                cout << endl;
            }
            if (shouldContinue)
            {
                cout << "Page " << page << endl;
                cout << "-----------------------------------------------------------" << endl;
                cout << left << setw(maxRankLength + 2) << "Rank";
                cout << left << setw(maxInstitutionLength + 2) << "Institution";
                cout << left << setw(maxLocationLength + 2) << "Location";
                cout << left << setw(maxLocationLength + 2) << "Academic Reputation";
                cout << left << setw(maxLocationLength + 2) << "Faculty Ratio";
                cout << left << "Employer Reputation" << endl;
                cout << "-----------------------------------------------------------" << endl;
                page++;
            }
        }

        if (shouldContinue)
        {
            // Print the data row with appropriate spacing
            cout << left << setw(maxRankLength + 2) << current->Rank;
            cout << left << setw(maxInstitutionLength + 2) << current->Institution;
            cout << left << setw(maxLocationLength + 2) << current->Location;
            cout << left << setw(maxLocationLength + 2) << current->ArScore;
            cout << left << setw(maxLocationLength + 2) << current->FsrScore;
            cout << left << current->ErScore << endl;
            count++;

            current = current->next;
        }
    }

    // Print the final page if there are remaining rows
    if (count % 30 != 0)
    {
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;
    }
}


string autoid(){
    reguser* current = rhead;
	int counter = 0;
    int usercount = 0;
    string newid;
    int numLines = 0;
    ifstream in("1userlist.csv");
    std::string unused;
    while ( std::getline(in, unused) )
        ++numLines;
    while(counter != numLines){
        counter = counter + 1;
		if (current->id.substr(0, 4) == "USER")
		{
            usercount = usercount + 1;
        }
        current = current->rnext;
	}
    newid = "USER"+to_string(usercount+1);
    return newid;
}
string autofbid() {
    fb* current = fbhead;
    int fbcount = 0;
    string newfbid;

    // Count the number of feedback entries with IDs starting with "FB"
    while (current != nullptr) {
        if (current->fbid.substr(0, 2) == "FB") {
            fbcount++;
        }
        else{
            fbcount = 0;
        }
        current = current->fbnext;
    }

    // Generate the new feedback ID
    newfbid = "FB" + to_string(fbcount + 1);
    return newfbid;
}


univ* createNewNode(string rank, string institution, string LocationCode, string location, string arScore, string arRank, string erScore, string erRank, string fsrScore, string fsrRank, string cpfScore, string cpfRank, string ifrScore, string ifrRank, string isrScore, string isrRank, string irnScore, string irnRank, string gerScore, string gerRank, string scoreScaled){
    univ* newNode = new univ;
    newNode->Rank = rank;
   newNode->Institution = institution;
   newNode->LocationCode = LocationCode;
   newNode->Location = location;
   newNode->ArScore = arScore;
   newNode->ArRank = arRank;
   newNode->ErScore = erScore;
   newNode->ErRank = erRank;
   newNode->FsrScore = fsrScore;
   newNode->FsrRank = fsrRank;
   newNode->CpfScore = cpfScore;
   newNode->CpfRank = cpfRank;
   newNode->IfrScore = ifrScore;
   newNode->IfrRank = ifrRank;
   newNode->IsrScore = isrScore;
   newNode->IsrRank = isrRank;
   newNode->IrnScore = irnScore;
    return newNode;
}

void saveListToCSV(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    reguser* current = rhead;
    while (current != nullptr) {
        file << current->id << "," << current->password << "," << current->name << "," << current->email << "," << current->logtime << endl;
        current = current->rnext;
    }

    file.close();

    cout << "Data saved to CSV file: " << filename << endl;
}

reguser* createNewUserNode(string id, string password, string name, string email, string logtime){
    
    reguser* newNode = new reguser;
    newNode->id = id;
    newNode->password = password;
    newNode->name = name;
    newNode->email = email;
    newNode->logtime = logtime;
   
    return newNode;
}


fv* createNewFavouriteNode(string id, string rank,string institution){
    fv* newNode = new fv;
    newNode->id = id;
    newNode->rank = rank;
    newNode->institution = institution;
    return newNode;
}

fb* createNewFeedbackNode(string fbid,string id, string uni, string feedback, string reply, string fbtime){
    fb* newNode = new fb;
    newNode->fbid = fbid;
    newNode->id = id;
    newNode->uniname = uni;
    newNode->feedback = feedback;
    newNode->reply = reply;
    newNode->fbtime = fbtime;
    return newNode;
}



// UNIVERSITY
// Insert node at the front doubly


//DOUBLY
void insertNode(univ*& uhead, univ*& utail, univ* newNode) {
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (uhead == NULL) {
        uhead = utail = newNode;
    }
    else {
        utail->next = newNode;
        newNode->prev = utail;
        utail = newNode;
    }
}

void insertRNode(reguser*& rhead, reguser*& rtail, reguser* newNode) {
    newNode->rnext = nullptr;
    newNode->rprev = nullptr;
    if (rhead == NULL) {
        rhead = rtail = newNode;
    }
    else {
        newNode->rprev = rtail;
        rtail->rnext = newNode;
        rtail = newNode;
    }
}

void insertCsvFileToList(univ*& uhead, univ*& utail, string filename) {
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each line of the CSV file
    string line;
    getline(file,line);
    while (getline(file, line)) {
        // Create a new node for each line
        univ* newNode = new univ;

        // Use a stringstream to split the line into comma-separated values
        stringstream ss(line);
        string value;

        // Read each value from the stringstream and store it in the new node
        getline(ss, value, ',');
        newNode->Rank = value;

        getline(ss, value, ',');
        newNode->Institution = value;

        getline(ss, value, ',');
        newNode->LocationCode = value;

        getline(ss, value, ',');
        newNode->Location = value;

        getline(ss, value, ',');
        newNode->ArScore = value;

        getline(ss, value, ',');
        newNode->ArRank = value;

        getline(ss, value, ',');
        newNode->ErScore = value;

        getline(ss, value, ',');
        newNode->ErRank = value;

        getline(ss, value, ',');
        newNode->FsrScore = value;

        getline(ss, value, ',');
        newNode->FsrRank = value;

         getline(ss, value, ',');
        newNode->CpfScore = value;

        getline(ss, value, ',');
        newNode->CpfRank = value;

        getline(ss, value, ',');
        newNode->IfrScore = value;

        getline(ss, value, ',');
        newNode->IfrRank = value;

        getline(ss, value, ',');
        newNode->IsrScore = value;

        getline(ss, value, ',');
        newNode->IsrRank = value;

        getline(ss, value, ',');
        newNode->IrnScore = value;

        getline(ss, value, ',');
        newNode->IrnRank = value;

        getline(ss, value, ',');
        newNode->GerScore = value;

        getline(ss, value, ',');
        newNode->GerRank = value;

        getline(ss, value, ',');
        newNode->ScoreScaled = value;

        // Add the new node to the linked list
        insertNode(uhead, utail, newNode);
        
    }
   file.close();
}


void displayDoubleList() {
    univ* current = uhead;
    while(current!=NULL){
        cout << "Rank: " << current->Rank << endl;
        cout << "Institution: " << current->Institution << endl;
        cout << "Location Code: " << current->LocationCode << endl;
        cout << "Location: " << current->Location << endl;
        cout << "ArScore: " << current->ArScore << endl;
        cout << "ArRank: " << current->ArRank << endl;
        cout << "ErScore: " << current->ErScore << endl;
        cout << "ErRank: " << current->ErRank << endl;
        cout << "FsrScore: " << current->FsrScore << endl;
        cout << "FsrRank: " << current->FsrRank << endl;
        cout << "CpfScore: " << current->CpfScore << endl;
        cout << "CpfRank: " << current->CpfRank << endl;
        cout << "IfrScore: " << current->IfrScore << endl;
        cout << "IfrRank: " << current->IfrRank << endl;
        cout << "IsrScore: " << current->IsrScore << endl;
        cout << "IsrRank: " << current->IsrRank << endl;
        cout << "IrnScore: " << current->IrnScore << endl;
        cout << "IrnRank: " << current->IrnRank << endl;
        cout << "GerScore: " << current->GerScore << endl;
        cout << "GerRank: " << current->GerRank << endl;
        cout << "ScoreScaled: " << current->ScoreScaled << endl;
        cout << endl;

        current = current->next;
    }
}



// REGISTERED USERS


void insertCsvFileToUserList(reguser*& rhead, reguser*& rtail, string filename) {
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each line of the CSV file
    string line;
    while (getline(file, line)) {
        // Create a new node for each line
        reguser* newNode = new reguser;

        // Use a stringstream to split the line into comma-separated values
        stringstream ss(line);
        string value;

        // Read each value from the stringstream and store it in the new node
        getline(ss, value, ',');
        newNode->id = value;

        getline(ss, value, ',');
        newNode->password = value;

        getline(ss, value, ',');
        newNode->name = value;

        getline(ss, value,',');
        newNode->email = value;

        getline(ss, value,',');
        newNode->logtime = value;

        // Add the new node to the linked list
        insertRNode(rhead, rtail, newNode);
    }

    // Remove the extra node if rtail is not equal to rhead

    file.close();
}


// insert end doubly
void insert_user_end( string id, string password, string name, string email, string logtime)
{

   struct reguser* newNode = createNewUserNode(id, password, name, email,logtime);
    newNode->rnext = nullptr;
    newNode->rprev = nullptr;
    if (rhead == NULL)
	{
		rhead = rtail =newNode;
	}
	else
	{
	    rtail -> rnext = newNode;
        newNode->rprev = rtail;
		rtail = newNode;
	}

}

void selectuser(string id)
{
	if (rhead == nullptr)
	{
		cout<< "ID NOT FOUND!";
	}
	reguser* current = rhead;
	
    while ( current != nullptr )
		if (current->id == id && current->id.substr(0, 4) == "USER")
		{
            cout << "User ID:  " << current->id << endl;
            cout << "Password: " << current->password << endl;
            cout << "Name:     " << current->name << endl;
            cout << "Email:    " << current->email << endl;
            cout << "Time :    " << current->logtime << endl;
            cout << endl; 
            break;
        }
        current = current->rnext;
	}


void searchandupdateuser(string attribute, string id)
{
	reguser* current = rhead;
    string name;
    ifstream in("1userlist.csv");
    while(current!=nullptr){
		if (current->id == id && current->id.substr(0, 4) == "USER")
		{
            if(attribute == "password" || attribute == "Password" ){
			    cout << "Please retype password: ";
			    cin >> current->password;
                break;
                break;
            }
            if (attribute == "name" || attribute == "Name" ){
                cout << "Please retype name: ";
                fflush(stdin);
                getline(cin,name);
                current->name = name;
                break;
                
            }
            if (attribute == "email" || attribute == "Email" ){
                cout << "Please retype email: ";
                cin >> current->email;
                break;
                break;
            }
            if (attribute != "email" || attribute != "Email" || attribute != "name" || attribute != "Name" || attribute != "password" || attribute != "Password" ){
                cout<< "Enter the option correctly!\n";
                break;
            }
		
        }
		current = current->rnext;
    }
    cout<<"\n Changes have been made!";
}

void deleteendofuserlist(string selectedid)
{
    struct reguser* currentNode = rhead;

    // Traverse the doubly linked list to find the node with matching ID
    while (currentNode != NULL) {
        if (currentNode->id == selectedid) {
            // Node to be deleted is found

            // Update the previous node's next pointer
            if (currentNode->rprev != NULL)
                currentNode->rprev->rnext = currentNode->rnext;
            else
                rhead = currentNode->rnext;

            // Update the next node's previous pointer
            if (currentNode->rnext != NULL)
                currentNode->rnext->rprev = currentNode->rprev;
            else
                rtail = currentNode->rprev;

            // Free the memory occupied by the node
            delete currentNode;

            return;
        }
        currentNode = currentNode->rnext;
    }

    // Node with the given ID was not found
    cout << "Node with ID " << selectedid << " not found." << endl;
}

void writeuserintocsv(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    reguser* current = rhead;
    while (current != nullptr) {
        file << current->id << "," << current->password << "," << current->name << "," << current->email << "," << current->logtime << endl;
        current = current->rnext;
    }

    file.close();

    cout << "Data saved to CSV file: " << filename << endl;
}

void displayUserDoubleList(reguser* rhead) {
    if (rhead == nullptr) {
        cout << "User list is empty." << endl;
        return;
    }

    cout << "User List:" << endl;
    reguser* currentNode = rhead;
    while (currentNode != nullptr) {
        if(currentNode->id.substr(0, 4) == "USER"){
        cout << "ID: " << currentNode->id << endl;
        cout << "Password: " << currentNode->password << endl;
        cout << "Name: " << currentNode->name << endl;
        cout << "Email: " << currentNode->email << endl;
        cout << "Time: " << currentNode->logtime << endl;
        cout << "---------------------" << endl;
    }
        currentNode = currentNode->rnext;
    }
}


// FEEDBACK
void insertfbNode(fb*& fbhead, fb*& fbtail, fb* newNode) {
    newNode->fbnext = nullptr;
    newNode->fbprev = nullptr;
    if (fbhead == NULL) {
        fbhead = fbtail = newNode;
    }
    else {
        fbtail->fbnext = newNode;
        newNode->fbprev = fbtail;
        fbtail = newNode;
    }
}

void insert_fb_end(string fbid, string id, string uni, string feedback, string reply, string fbtime)
{
    struct fb* newNode = createNewFeedbackNode(fbid, id, uni, feedback, reply, fbtime);
    newNode->fbnext = nullptr;
    newNode->fbprev = nullptr;
    if (fbhead == NULL)
    {
        fbhead = fbtail = newNode;
    }
    else
    {
        fbtail->fbnext = newNode;
        newNode->fbprev = fbtail;
        fbtail = newNode;
    }
}
void insertCsvFileToFBList(fb*& fbhead, fb*& fbtail, string filename) {
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each line of the CSV file
    string line;
    while (getline(file, line)) {
        // Create a new node for each line
        fb* newNode = new fb;

        // Use a stringstream to split the line into comma-separated values
        stringstream ss(line);
        string value;

        // Read each value from the stringstream and store it in the new node
        getline(ss, value, ',');
        newNode->fbid = value;

        getline(ss, value, ',');
        newNode->id = value;

        getline(ss, value, ',');
        newNode->uniname = value;

        getline(ss, value, ',');
        newNode->feedback = value;

        getline(ss, value, ',');
        newNode->reply = value;

        getline(ss, value, ',');
        newNode->fbtime = value;

        // Add the new node to the linked list
        insertfbNode(fbhead, fbtail, newNode);
        
    }
   file.close();
}

void displayfeedbackDoubleList() {
    fb* current = fbhead;
    while(current!= nullptr){
        if(current == NULL){
            break;
        }
        cout << "\nFeedback ID:   " << current->fbid << endl;
        cout << "User ID:         " << current->id << endl;
        cout << "University Name: " << current->uniname << endl;
        cout << "Feedback:   \n " << current->feedback << endl;
        cout << "Reply:      \n " << current->reply << endl;
        cout << "Time:            " << current->fbtime << endl;
        cout << endl;  
        current = current->fbnext;
    }
}



void sendFeedback(string id)
{
    string uniname, feedback;
    string reply;
    string fbid = autofbid();
    string fbtime;

    cout << "Feedback ID: " << fbid << endl;
    cout << "User ID: "<< id <<endl;
    cout << "Enter university name: "<< endl;
    cin.ignore();
    getline(cin, uniname);
    cout << "Enter feedback: "<< endl;
    getline(cin, feedback);
    insert_fb_end(fbid, id, uniname, feedback, reply,fbtime);
    cout << "\n>>> Feedback Sent <<<\n" << endl;

}

void readFeedback(string id)
{
    fb* current = fbhead;
    while(current != nullptr){
        if(current == NULL){
            break;
        }
        if(current->id == id){
        cout << "\nFeedback ID:   " << current->fbid << endl;
        cout << "User ID:         " << current->id << endl;
        cout << "University Name: " << current->uniname << endl;
        cout << "Feedback:   \n " << current->feedback << endl;
        cout << "Reply:      \n " << current->reply << endl;
        cout << "Time:       \n " << current->fbtime << endl;
        cout << endl; 
        } 
        current = current->fbnext;

    }
}


void replyfb(string fbid)
{
	fb* current = fbhead;
    string reply,fbtime;
    while(current!= nullptr){
        if(current == NULL){
            break;
        }
		if (current->fbid == fbid)
		{
            cout << "\nFeedback ID:   " << current->fbid << endl;
            cout << "User ID:         " << current->id << endl;
            cout << "University Name: " << current->uniname << endl;
            cout << "Feedback:        " << current->feedback << endl;
            cout << "Reply:           " << current->reply << endl;
            cout << "Time:         \n " << current->fbtime << endl;
            cout << endl; 
            cout << "\nWrite a Reply below : \n";
            fflush(stdin);
            getline(cin,reply);
            current->reply = reply;
            time_t now = time(0);
            tm *local_time = localtime(&now);
            int year = (local_time->tm_year)+1900;;
            int month = (local_time->tm_mon)+1;
            int day = local_time->tm_mday;
            fbtime = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            current->fbtime = fbtime;
            break;
        }
		current = current->fbnext;
        
    }
    cout<<"\n Reply to the feedback has been made!";
}
void browseUniversityMenu(univ* head)
{
    int browseChoice;

    do {
        cout << "1. SORT by Insertion Sort\n";
        cout << "2. SORT by Merge Sort\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> browseChoice;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters until newline
        }

        switch (browseChoice) {
            case 1:
                insertionSort(head);
                displayList(head);
                break;
            case 2:
                mergeSort(&uhead);
                displayList(uhead);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (browseChoice != 3);
}
void browseUniversity()
{
    univ* head = nullptr;
    string filepath = "2023_QS_World_University_Rankings.csv";
    head = createLinkedListFromCSV(head, filepath);

    cout << "---------------------------------------------------------\n";
    cout << "                2023 QS University Rankings              \n";
    cout << "---------------------------------------------------------\n";

    int page = 1;
    int count = 0;
    univ* current = head;

    // Calculate the maximum length of each attribute
    int maxRankLength = 0;
    int maxInstitutionLength = 0;
    int maxLocationCodeLength = 0;
    int maxLocationLength = 0;
    int maxArScoreLength = 0;
    int maxArRankLength = 0;
    int maxErScoreLength = 0;
    int maxErRankLength = 0;
    int maxFsrScoreLength = 0;
    int maxFsrRankLength = 0;
    int maxCpfScoreLength = 0;
    int maxCpfRankLength = 0;
    int maxIfrScoreLength = 0;
    int maxIfrRankLength = 0;
    int maxIsrScoreLength = 0;
    int maxIsrRankLength = 0;
    int maxIrnScoreLength = 0;
    int maxIrnRankLength = 0;
    int maxGerScoreLength = 0;
    int maxGerRankLength = 0;
    int maxScoreScaledLength = 0;

    while (current != nullptr) {
        maxRankLength = max(maxRankLength, static_cast<int>(current->Rank.length()));
        maxInstitutionLength = max(maxInstitutionLength, static_cast<int>(current->Institution.length()));
        maxLocationCodeLength = max(maxLocationCodeLength, static_cast<int>(current->LocationCode.length()));
        maxLocationLength = max(maxLocationLength, static_cast<int>(current->Location.length()));
        maxArScoreLength = max(maxArScoreLength, static_cast<int>(current->ArScore.length()));
        maxArRankLength = max(maxArRankLength, static_cast<int>(current->ArRank.length()));
        maxErScoreLength = max(maxErScoreLength, static_cast<int>(current->ErScore.length()));
        maxErRankLength = max(maxErRankLength, static_cast<int>(current->ErRank.length()));
        maxFsrScoreLength = max(maxFsrScoreLength, static_cast<int>(current->FsrScore.length()));
        maxFsrRankLength = max(maxFsrRankLength, static_cast<int>(current->FsrRank.length()));
        maxCpfScoreLength = max(maxCpfScoreLength, static_cast<int>(current->CpfScore.length()));
        maxCpfRankLength = max(maxCpfRankLength, static_cast<int>(current->CpfRank.length()));
        maxIfrScoreLength = max(maxIfrScoreLength, static_cast<int>(current->IfrScore.length()));
        maxIfrRankLength = max(maxIfrRankLength, static_cast<int>(current->IfrRank.length()));
        maxIsrScoreLength = max(maxIsrScoreLength, static_cast<int>(current->IsrScore.length()));
        maxIsrRankLength = max(maxIsrRankLength, static_cast<int>(current->IsrRank.length()));
        maxIrnScoreLength = max(maxIrnScoreLength, static_cast<int>(current->IrnScore.length()));
        maxIrnRankLength = max(maxIrnRankLength, static_cast<int>(current->IrnRank.length()));
        maxGerScoreLength = max(maxGerScoreLength, static_cast<int>(current->GerScore.length()));
        maxGerRankLength = max(maxGerRankLength, static_cast<int>(current->GerRank.length()));
        maxScoreScaledLength = max(maxScoreScaledLength, static_cast<int>(current->ScoreScaled.length()));
        current = current->next;
    }

    current = head;
    while (current != nullptr) {
        // Print the table header for each page
        if (count % 30 == 0) {
            if (count > 0) {
                cout << "-----------------------------------------------------------" << endl;
                cout << endl;

                // Prompt the user for their choice
                cout << "1. Navigate to the next page" << endl;
                cout << "2. Sort Universities" << endl;
                cout << "3. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;
                cout << endl;

                // Process the user's choice
                if (choice == 2) {
                    // Call the browseUniversity method to display the menu options
                    browseUniversityMenu(head);
                } else if (choice == 3) {
                    return;
                }
            }
            cout << "Page " << page << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << left << setw(maxRankLength + 2) << "Rank";
            cout << left << setw(maxLocationCodeLength + 2) << "Location Code";
            cout << left << setw(maxLocationLength + 2) << "Location";
            cout << left << setw(maxInstitutionLength + 2) << "Institution";
            cout << left << setw(maxArScoreLength + 2) << "Ar Score";
            cout << left << setw(maxArRankLength + 2) << "Ar Rank";
            cout << left << setw(maxErScoreLength + 2) << "Er Score";
            cout << left << setw(maxErRankLength + 2) << "Er Rank";
            cout << left << setw(maxFsrScoreLength + 2) << "Fsr Score";
            cout << left << setw(maxFsrRankLength + 2) << "Fsr Rank";
            cout << left << setw(maxCpfScoreLength + 2) << "Cpf Score";
            cout << left << setw(maxCpfRankLength + 2) << "Cpf Rank";
            cout << left << setw(maxIfrScoreLength + 2) << "Ifr Score";
            cout << left << setw(maxIfrRankLength + 2) << "Ifr Rank";
            cout << left << setw(maxIsrScoreLength + 2) << "Isr Score";
            cout << left << setw(maxIsrRankLength + 2) << "Isr Rank";
            cout << left << setw(maxIrnScoreLength + 2) << "Irn Score";
            cout << left << setw(maxIrnRankLength + 2) << "Irn Rank";
            cout << left << setw(maxGerScoreLength + 2) << "Ger Score";
            cout << left << setw(maxGerRankLength + 2) << "Ger Rank";
            cout << left << "Score Scaled" << endl;
            cout << "-----------------------------------------------------------" << endl;
            page++;
        }

        // Print the data row with appropriate spacing
        cout << left << setw(maxRankLength + 2) << current->Rank;
        cout << left << setw(maxLocationCodeLength + 2) << current->LocationCode;
        cout << left << setw(maxLocationLength + 2) << current->Location;
        cout << left << setw(maxInstitutionLength + 2) << current->Institution;
        cout << left << setw(maxArScoreLength + 2) << current->ArScore;
        cout << left << setw(maxArRankLength + 2) << current->ArRank;
        cout << left << setw(maxErScoreLength + 2) << current->ErScore;
        cout << left << setw(maxErRankLength + 2) << current->ErRank;
        cout << left << setw(maxFsrScoreLength + 2) << current->FsrScore;
        cout << left << setw(maxFsrRankLength + 2) << current->FsrRank;
        cout << left << setw(maxCpfScoreLength + 2) << current->CpfScore;
        cout << left << setw(maxCpfRankLength + 2) << current->CpfRank;
        cout << left << setw(maxIfrScoreLength + 2) << current->IfrScore;
        cout << left << setw(maxIfrRankLength + 2) << current->IfrRank;
        cout << left << setw(maxIsrScoreLength + 2) << current->IsrScore;
        cout << left << setw(maxIsrRankLength + 2) << current->IsrRank;
        cout << left << setw(maxIrnScoreLength + 2) << current->IrnScore;
        cout << left << setw(maxIrnRankLength + 2) << current->IrnRank;
        cout << left << setw(maxGerScoreLength + 2) << current->GerScore;
        cout << left << setw(maxGerRankLength + 2) << current->GerRank;
        cout << left << current->ScoreScaled << endl;
        count++;

        current = current->next;
    }

    // Print the final page if there are remaining rows
    if (count % 30 != 0) {
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;
    }
}
void displayUniInfo()
{
    int displayChoice;
    univ *head = nullptr;
    string filepath = "2023_QS_World_University_Rankings.csv";
    head = createLinkedListFromCSV(head, filepath);
    while (displayChoice != 4)
    {
        cout << "Please select the option below\n"
             << "1. Sort on academic reputation score\n"
             << "2. Sort on faculty/student ratio score\n"
             << "3. Sort on employer reputation score\n"
             << "4. Return to Main Menu\n"
             << "Enter your choice: " << endl;
        cin >> displayChoice;
        if (displayChoice == 1)
        {
            insertionSortAcademyReputationScore(head);
            display(head);
            break;
        }
        else if (displayChoice == 2)
        {
            insertionSortFacultyRatioScore(head);
            display(head);
            break;
        }
        else if (displayChoice == 3)
        {
            insertionSortEmployerReputationScore(head);
            display(head);
            break;
        }
        else if (displayChoice == 4)
        {
            break;
        }
        else
        {
            cout << "Choice entered is not available" << endl;
        }
        cout << endl;
    }
}
// FAVOURITES

void insertfvNode(fv*& fvhead, fv*& fvtail, fv* newNode) {
    newNode->fvnext = nullptr;
    newNode->fvprev = nullptr;
    if (fvhead == NULL) {
        fvhead = fvtail = newNode;
    }
    else {
        fvtail->fvnext = newNode;
        newNode->fvprev = fvtail;
        fvtail = newNode;
    }
}

void insert_favourite_end( string id, string rank, string uniname)
{
  
   struct fv* newNode = createNewFavouriteNode(id, rank, uniname);
    newNode->fvnext = nullptr;
    newNode->fvprev = nullptr;
    if (fvhead == NULL)
	{
		fvhead = fvtail =newNode;
	}
	else
	{
	    fvtail -> fvnext = newNode;
        newNode->fvprev = fvtail;
		fvtail = newNode;
	}

}

void insertCsvFileToFVList(fv*& fvhead, fv*& fvtail, string filename) {
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each line of the CSV file
    string line;
    while (getline(file, line)) {
        // Create a new node for each line
        fv* newNode = new fv;

        // Use a stringstream to split the line into comma-separated values
        stringstream ss(line);
        string value;

        // Read each value from the stringstream and store it in the new node

        getline(ss, value, ';');
        newNode->id = value;
        getline(ss, value, ';');
        newNode->rank = value;
        getline(ss, value, ';');
        newNode->institution = value;

        // Add the new node to the linked list
        insertfvNode(fvhead, fvtail, newNode);
    }
   file.close();
}


int getCount(fv* fvhead)
{
    // Base Case
    if (fvhead == NULL) {
        return 0;
    }
    // Count this node plus the rest of the list
    else {
        return 1 + getCount(fvhead->fvnext);
    }
}

void writefvintocsv() {
    fstream fout;
    fv* current = fvhead;
    ofstream outfile("1favourites.csv", ios::trunc);
    while(current!= nullptr){
        if(current == NULL){
            break;
        }
         outfile<< current->id<< ";"
            << current->rank<< ";"
            << current->institution<< "\n";
        current = current->fvnext;
    }
    fout.close();
}

void writefeedbackintocsv() {
    fstream fout;
    fb* current = fbhead;
    ofstream file("1feedback.csv", ios::trunc);
    while (current != nullptr) {
        file << current->fbid << ","<<current->id << "," << current->uniname << "," << current->feedback << "," << current->reply<< "," << current->fbtime << endl;
        current = current->fbnext;
    }

    fout.close();

}

string selectuni(string rank)
{
	if (uhead == NULL)
	{
		cout<< "ID NOT FOUND!";
	}
	univ* current = uhead;
	int counter = 0;
    int numLines = 0;
    ifstream in("2023_QS_World_University_Rankings.csv");
    std::string unused;
    while ( std::getline(in, unused) )
        ++numLines;
    while(current!=NULL){
        counter = counter + 1;
		if (current->Rank == rank)
		{
        cout << "Rank: " << current->Rank << endl;
        cout << "Institution: " << current->Institution << endl;
        cout << "Location Code: " << current->LocationCode << endl;
        cout << "Location: " << current->Location << endl;
        cout << "ArScore: " << current->ArScore << endl;
        cout << "ArRank: " << current->ArRank << endl;
        cout << "ErScore: " << current->ErScore << endl;
        cout << "ErRank: " << current->ErRank << endl;
        cout << "FsrScore: " << current->FsrScore << endl;
        cout << "FsrRank: " << current->FsrRank << endl;
        cout << "CpfScore: " << current->CpfScore << endl;
        cout << "CpfRank: " << current->CpfRank << endl;
        cout << "IfrScore: " << current->IfrScore << endl;
        cout << "IfrRank: " << current->IfrRank << endl;
        cout << "IsrScore: " << current->IsrScore << endl;
        cout << "IsrRank: " << current->IsrRank << endl;
        cout << "IrnScore: " << current->IrnScore << endl;
        cout << "IrnRank: " << current->IrnRank << endl;
        cout << "GerScore: " << current->GerScore << endl;
        cout << "GerRank: " << current->GerRank << endl;
        cout << "ScoreScaled: " << current->ScoreScaled << endl;
        cout << endl; 
        return current->Institution;
        break;
        }
        current = current->next;
	}
}






