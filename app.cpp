// create separate choice validation function for choices
#include<iostream>
#include<string>
#include<fstream>
#include <cstdlib>
#include<iomanip>
using namespace std;

// data validation for sign up process;
bool name_validation(string name);
bool cnic_validation(string cnic);
bool phone_number_validation(string phone_number);
bool bar_license_number_validation(string bar_license_number);
bool username_validation(string user_name);
bool password_validation(string password);
// other data validations
//bool choice_validation(string choice); // validation for choice at starting 
bool lawyer_admin_choice_validation(string lawyer_admin_choice); // validation for admin choice
// validation for admin entered password and user name
bool choices_atStart_Validation(string choice);


// user defined functions
void print_menu(); // print starting menus
void admin_menus(); // print admin menus
void lawyer_menus(); // print lawyer menus
void client_menus(); // print client menus
void logout();

// options when program is executed first
 //1
bool adminSignin(string enteredUser, string enteredPass, string u_names[], string u_passwords[], string u_roles[], int u_count);
    void add_new_lawyer(string l_names[], string l_cnics[], string l_phones[], string l_bar_ids[], int &l_count, int maximum); //1.1
    void remove_lawyer(string l_names[], string l_cnics[], string l_phones[], string l_bar_ids[], int &l_count); //1.2
    void view_master_case_list(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count); //1.3
    void calculate_totalRevenue_firmTax(double c_total_bills[], int c_count); //1.4
    void purge_close_case(string c_ids[], string c_clients[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int &c_count); //1.5

bool lawyerSignin(string enteredCNIC, string enteredBar, string l_cnics[], string l_bar_ids[], int l_count, int &foundIndex);
    void add_new_case(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int &c_count, string currentLawyerBarID); //2.1
        void saveCases(string[], string[], string[], double[], double[], string[], string[], int);
    void update_case_status(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count); //2.2
    void manage_schedule(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count); //2.3
    void invoicing(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count); //2.4
    void personal_dashboard_lawyer(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count, string currentLawyerBarID); //2.5

bool clientSignin(string enteredName, string enteredLawyerID, string c_names[], string c_lids[], int c_count, int &foundIndex);
    void view_client_status(string[], int);
    void view_client_balance(double[], double[], int);
    void view_client_lawyer_info(string[], string[], string[], string[], int, int);
    void view_client_hearing(string[], int);
    void view_client_profile(string[], string[], string[], string[], int);


string getField(string record, int field) {
    int commaCount = 1;
    string item = "";
    for (int x = 0; x < record.length(); x++) {
        if (record[x] == ',') {
            commaCount++;
        } else if (commaCount == field) {
            item = item + record[x];
        }
    }
    return item;
}

void loadUsers(string u_real_names[], string u_usernames[], string u_passwords[], string u_roles[], int &u_count) {
    string record;
    fstream data;
    u_count = 0;
    data.open("users.csv", ios::in);
    if (!data.is_open()) return; // Safety check

    while (getline(data, record) && u_count < 200) {
        if (record == "" || record == " ") continue;
        u_real_names[u_count] = getField(record, 1); // e.g., Luqman Admin
        u_usernames[u_count]  = getField(record, 2); // e.g., adm_luq
        u_passwords[u_count]  = getField(record, 3); // e.g., 11223344
        u_roles[u_count]      = getField(record, 4); // e.g., Admin
        u_count++;
    }
    data.close();
}

void loadLawyers(string l_names[], string l_cnics[], string l_phones[], string l_bar_ids[], int &l_count) {
    string record;
    fstream data;
    l_count = 0;
    data.open("lawyers.csv", ios::in);
    while (getline(data, record) && l_count < 200) {
        if (record == "") continue;
        l_names[l_count]    = getField(record, 1);
        l_cnics[l_count]    = getField(record, 2);
        l_phones[l_count]   = getField(record, 3);
        l_bar_ids[l_count]  = getField(record, 4);
        l_count++;
    }
    data.close();
}

void loadCases(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int &c_count) {
    string record;
    fstream data;
    c_count = 0;
    data.open("cases.csv", ios::in);
    while (getline(data, record) && c_count < 200) {
        if (record == "") continue;
        c_ids[c_count]      = getField(record, 1);
        c_names[c_count]    = getField(record, 2);
        c_stats[c_count]    = getField(record, 3);
        c_bills[c_count]    = stod(getField(record, 4));
        c_paid[c_count]     = stod(getField(record, 5));
        c_lids[c_count]     = getField(record, 6);
        c_dates[c_count]    = getField(record, 7);
        c_count++;
    }
    data.close();
}


int main()
{
    // 1. Declare Arrays
    // 1. User related arrays (4 columns now)
string u_real_names[200], u_usernames[200], u_passwords[200], u_roles[200];

// 2. Lawyer related arrays (4 columns)
string l_names[200], l_cnics[200], l_phones[200], l_bar_ids[200];

// 3. Case related arrays (7 columns)
string c_ids[200], c_names[200], c_stats[200], c_lids[200], c_dates[200];
double c_bills[200], c_paid[200];

// 4. Counters
int u_count = 0, l_count = 0, c_count = 0;

    

    // 2. Declare counters for each file
    

    // 3. Sync RAM with Files (Pass the count variables you just declared)
    loadUsers(u_real_names, u_usernames, u_passwords, u_roles, u_count);
    loadLawyers(l_names, l_cnics, l_phones, l_bar_ids, l_count);
    loadCases(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);

// Note 1: i have to create separate functions for starting menus for 1,2,3,4,5 so that after signup, sign in function can be called
// Note 2: we have to create arrays to store data and we have to use while loop in main so that data can be stored in arrays efficiently

    string choice=" "; bool app_rn=true;
    while(app_rn==true)
    {
    print_menu();
    do{
        cout<<"Enter your choice: (only 1 to 6)";
        getline(cin>>ws,choice);
    }while(!choices_atStart_Validation(choice));
    cout<<"Successfully entered choice\n";

    // now using if for comparing what will happen to our program if user selects 1,2,3 or 4,5
    if(choice[0]=='1')// check if user enters 1 (sign in as admin)
    {
        // sign in as admin
        string admin_user_name=" ";
        string admin_password=" ";
        
        // require user name from admin
        do{
            cout<<"Enter your username (7 characters long): ";
            getline(cin >> ws, admin_user_name);
        }while(!username_validation(admin_user_name));
        cout<<"Successfully Entered Admin User Name\n";

        // require password from admin
        do{
            cout<<"Enter password for admin(8 digits long): ";
            getline(cin>>ws,admin_password);
        }while(!password_validation(admin_password));
        cout<<"Successfully Entered Admin Password\n";

        if(adminSignin(admin_user_name, admin_password, u_usernames, u_passwords, u_roles, u_count)) // in this function we will pass admin pass and user name so that it can be compared with file
        {
            bool adminLoggedIn = true;
            while (adminLoggedIn) {
        
        
        admin_menus();
        string admin_choice="";
        do{
            cout<<"Enter Choice(1 to 6 only): ";
            getline(cin>>ws,admin_choice);
        }while(!lawyer_admin_choice_validation(admin_choice));

        if(admin_choice[0]==49) // check for 1 (add new lawyer)
        {
            add_new_lawyer(l_names, l_cnics, l_phones, l_bar_ids, l_count, 100);
        }
        else if(admin_choice[0]==50) // check for 2 (remove lawyer) 
        {
            remove_lawyer(l_names, l_cnics, l_phones, l_bar_ids, l_count);
        }
        else if(admin_choice[0]==51) // check for 3 (view master case list)
        {
            view_master_case_list(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);
        }
        else if(admin_choice[0]==52) // check for 4 (calculate total revenue and firm tax)
        {
            calculate_totalRevenue_firmTax(c_bills, c_count);
        }
        else if(admin_choice[0]==53) // check for 5 (purge closed cases)
        {
            purge_close_case(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);
        }
        else if(admin_choice[0]==54)// check for 6 (log out)
        {
            logout();
            adminLoggedIn = false; // Exit the admin menu loop
            
        }
    }
    }
    }
    else if(choice[0]=='2')// check if user enters 4 (signin as a lawyer)
    {

        // should take username and password from lawyer and compare it to file in which lawyer data is stored
        string enteredCNIC, enteredBar;
    int lawyerIndex = -1; // To store the index of the logged-in lawyer

    cout << "\n--- LAWYER SIGN-IN ---\n";
    do{
    cout << "Enter your 13-digit CNIC: ";
    getline(cin>>ws, enteredCNIC);} while(!cnic_validation(enteredCNIC));
    do{
    cout << "Enter your 4-digit Bar License Number: ";
    getline(cin>>ws, enteredBar);} while(!bar_license_number_validation(enteredBar));
    if (lawyerSignin(enteredCNIC, enteredBar, l_cnics, l_bar_ids, l_count, lawyerIndex))
{
    
    bool lawyerLoggedIn = true;
        while (lawyerLoggedIn){
        lawyer_menus();
        string lawyer_choice=" ";
        do{
            cout<<"Enter Choice(1 to 6 only): ";
            getline(cin>>ws,lawyer_choice);
        }while(!lawyer_admin_choice_validation(lawyer_choice));

        if(lawyer_choice[0]==49) // check for 1 (add new client and assign new case id)
        {
            add_new_case(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count, enteredBar);
        }
        else if(lawyer_choice[0]==50) // check for 2 (update case status,Pending/In-Court/Won/Loss) 
        {
            update_case_status(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);
        }
        else if(lawyer_choice[0]==51) // check for 3 (Manage Schedule (Update Next Hearing))
        {
            manage_schedule(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);
        }
        else if(lawyer_choice[0]==52) // check for 4 (Invoicing (Receive Payment))
        {
            invoicing(c_ids, c_names, c_stats, c_bills, c_paid, 
              c_lids, c_dates, c_count);
        }
        else if(lawyer_choice[0]==53) // check for 5 (Personal Dashboard (View My Cases Only))
        {
            personal_dashboard_lawyer(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count, enteredBar);
        }
        else if(lawyer_choice[0]==54)// check for 6 (log out)
        {
            logout();
            lawyerLoggedIn = false; // Exit the lawyer menu loop
        }
    }
    }
    else {
        cout << "\n[!] Invalid Lawyer Credentials.\n"; }
    }
    else if(choice[0]=='3') // checks if user enter 3 for (signin as client)
    
    {
        string searchName, searchLawyerID;
    int caseIndex = -1;

    cout << "\n--- CLIENT CASE ACCESS ---\n";
    cout << "Enter your Full Name: ";
    getline(cin >> ws, searchName); // Clears buffer and takes name with spaces
    cout << "Enter your Lawyer's Bar ID: ";
    getline(cin >>ws, searchLawyerID);

    if (clientSignin(searchName, searchLawyerID, c_names, c_lids, c_count, caseIndex)) 
    {
        cout << "\n[✔] Case Found! Accessing your details...\n";
        system("pause");

        bool clientViewing = true;
        while (clientViewing) {
            client_menus(); // Show the client dashboard
            string client_choice;
            cout << "Enter choice: ";
            getline(cin>>ws,client_choice);

            if (client_choice[0] == '1') {
        view_client_status(c_stats, caseIndex);
    }
    else if (client_choice[0] == '2') {
        view_client_balance(c_bills, c_paid, caseIndex);
    }
    else if (client_choice[0] == '3') {
        view_client_lawyer_info(c_lids, l_names, l_phones, l_bar_ids, caseIndex, l_count);
    }
    else if (client_choice[0] == '4') {
        view_client_hearing(c_dates, caseIndex);
    }
    else if (client_choice[0] == '5') {
        view_client_profile(c_ids, c_names, c_lids, c_stats, caseIndex);
    }
    else if (client_choice[0] == '6') {
        logout();
        clientViewing = false;
        continue;
    }
    else {
        cout << "Invalid Option!\n";
    }
    system("pause");
        }


    }
    else {
        cout << "\n[!] Error: No case exists for " << searchName << " under Lawyer ID " << searchLawyerID << ".\n";
        system("pause");
    }
}
    else if(choice[0]=='4')
    {
        cout<<"Exiting the program! ";
        app_rn=false;
    }

    } 
}// close main


bool password_validation(string password){

    if (password.length()==0) return false;
    else if (password.length()!=8) return false;

    for(int i=0; i<password.length(); i++)
    {
        if(password[i] < 48 || password[i] > 57)
        {
            return false;
        }
    }
    return true;
}

bool cnic_validation(string cnic) {
    if(cnic.length() != 13) return false;

    for(int i = 0; i < cnic.length(); i++) {
        // Using '0' and '9' is easier to read than 48 and 57
        if(cnic[i] < '0' || cnic[i] > '9') {
            return false;
        }
    }
    return true;
}

bool phone_number_validation(string phone_number)
{
    
    if(phone_number.length()!=11) return false;
    for(int i=0; i<phone_number.length(); i++)
    {
        if(!(phone_number[i]>=48 && phone_number[i]<=57)) // other than digit? return false
        {
            return false;
        }
    }
    return true;
}

bool name_validation(string name)
{
    // 1. Length Check
    if (name.length() == 0 || name.length() > 16) {
        return false;
    }

    // 2. Character Check
    for(int i = 0; i < name.length(); i++)
    {
        // If we find a DIGIT, the name is INVALID
        if(name[i] >= '0' && name[i] <= '9') 
        {
            return false; 
        }
        
        // If we find a special character (like !@#$%^&*), it's INVALID
        // You can use isalnum or just check for letters and spaces
        if(!( (name[i] >= 'a' && name[i] <= 'z') || 
              (name[i] >= 'A' && name[i] <= 'Z') || 
               name[i] == ' ') ) 
        {
            return false;
        }
    }

    // If the loop finishes without returning false, the name is clean!
    return true; 
}

bool bar_license_number_validation(string bar_license_number){
    if(bar_license_number.length()!=4) return false;
    for(int i=0; i<bar_license_number.length(); i++)
    {
        if(!(bar_license_number[i]>=48 && bar_license_number[i]<=57)) // other than digit? return false 
        {
            return false;
        }
    }
    return true;

}

void print_menu()
{
    cout << "\n--- MAIN MENU ---\n";
    cout << "1) Sign in as Admin\n";
    cout << "2) Sign in as Lawyer\n";
    cout << "3) Sign in as Client\n";
    cout << "4) Exit Program\n";
}
/*
bool choice_validation(string choice)
{
    if (choice.length()!=1) return false;
    int choice_number = choice[0]-'0';
    if(choice_number<1||choice_number>5)
    return false;

    return true;
}
    */

void admin_menus()
{
    cout << "1. Add New Lawyer" << endl;
    cout << "2. Remove Lawyer (Shift Arrays)" << endl;
    cout << "3. View Master Case List" << endl;
    cout << "4. Calculate Total Revenue & Firm Tax" << endl;
    cout << "5. Purge Closed Cases" << endl;
    cout << "6. Logout" << endl;
}

bool lawyer_admin_choice_validation(string choice)
{
    // Check if empty or more than 1 char
    if (choice.length() != 1) return false;

    // Check if it's actually a digit (ASCII 48-57)
    if (choice[0] < '0' || choice[0] > '9') return false;

    int num = choice[0] - '0';
    
    // Now check the range 1-6
    if (num < 1 || num > 6) return false;

    return true;
}
bool choices_atStart_Validation(string choice)
{
// Check if empty or more than 1 char
    if (choice.length() != 1) return false;

    // Check if it's actually a digit (ASCII 48-57)
    if (choice[0] < '0' || choice[0] > '9') return false;

    int num = choice[0] - '0';
    
    // Now check the range 1-6
    if (num < 1 || num > 4) return false;

    return true;
}

void lawyer_menus()
{
    cout << "1. Add New Client & Assign Case ID" << endl;
    cout << "2. Update Case Status (Pending/In-Court/Won/Loss)" << endl;
    cout << "3. Manage Schedule (Update Next Hearing)" << endl;
    cout << "4. Invoicing (Receive Payment)" << endl;
    cout << "5. Personal Dashboard (View My Cases Only)" << endl;
    cout << "6. Logout" << endl;
}


void client_menus()
{
    cout << "\n--- CLIENT DASHBOARD ---\n";
    cout << "1. View Case Progress (Status)\n";
    cout << "2. Check Balance (Total vs Paid)\n";
    cout << "3. Lawyer Information\n";
    cout << "4. View Next Hearing Date\n";
    cout << "5. Personal Profile\n";
    cout << "6. Logout\n";
}
void add_new_lawyer(string l_names[], string l_cnics[], string l_phones[], string l_bar_ids[], int &l_count, int maximum) {
    // 1. Capacity Check
    if (l_count >= maximum) {
        cout << "\n!! ERROR: System Full. Cannot add more lawyers (Max 100) !!\n";
        return;
    }

    string name, cnic, phone, bar;

    cout << "\n--- ADD NEW LAWYER ---\n";

    // 2. Input and Validation
    do {
    // Updated prompt to match your code's logic
    cout << "Enter Name (1-16 chars, letters & spaces only): ";
    
    // getline with ws ensures we catch the full name (like "John Doe")
    // and clears any leftover newline characters from previous 'cin >>'
    getline(cin >> ws, name); 

    if (!name_validation(name)) {
        cout << "[!] Invalid Name. Please use only letters (max 16 chars) and no digits.\n";
    }
} while (!name_validation(name));

cout << "Successfully Entered Name: " << name << endl;

    
do {
    // Be very specific in the prompt to avoid validation failure
    cout << "Enter 13-digit CNIC (Numbers only, NO dashes): ";
    
    // Using cin >> cnic is fine here since CNICs don't have spaces
    cin >> cnic;

    if (!cnic_validation(cnic)) {
        cout << "[!] Invalid CNIC. Must be exactly 13 digits and contain no letters or dashes.\n";
    }
} while (!cnic_validation(cnic));

// After valid input, clear the buffer for any following getlines
cin.ignore(100, '\n');

    do {
        cout << "Enter Phone Number (11 digits): ";
        getline(cin>>ws, phone);
    } while (!phone_number_validation(phone));

    do {
        cout << "Enter Bar License Number (4 digits): ";
        getline(cin>>ws, bar);
    } while (!bar_license_number_validation(bar));

    // 3. Update Parallel Arrays
    l_names[l_count] = name;
    l_cnics[l_count] = cnic;
    l_phones[l_count] = phone;
    l_bar_ids[l_count] = bar;

    // 4. Update CSV File (Append Mode)
    fstream data;
    data.open("lawyers.csv", ios::app); // Open in append mode
    if (data.is_open()) {
        data << name << "," << cnic << "," << phone << "," << bar << endl;
        data.close();
        
        l_count++; // Increment count only after successful file write
        cout << "\nLawyer added successfully to System and File!\n";
    } else {
        cout << "\nError: Could not open file to save data.\n";
    }
}
void remove_lawyer(string l_names[], string l_cnics[], string l_phones[], string l_bar_ids[], int &l_count) {
    if (l_count == 0) {
        cout << "\n!! ERROR: No lawyers found in the system to remove. !!\n";
        return;
    }

    string targetBarID;
    bool found = false;
    int indexToRemove = -1;

    cout << "\n--- REMOVE LAWYER ---\n";
    cout << "Enter the Bar License Number of the lawyer to remove: ";
    getline(cin, targetBarID);

    // 1. Search for the lawyer
    for (int i = 0; i < l_count; i++) {
        if (l_bar_ids[i] == targetBarID) {
            found = true;
            indexToRemove = i;
            break;
        }
    }

    if (found) {
        // 2. Perform Array Shifting
        for (int i = indexToRemove; i < l_count - 1; i++) {
            l_names[i] = l_names[i + 1];
            l_cnics[i] = l_cnics[i + 1];
            l_phones[i] = l_phones[i + 1];
            l_bar_ids[i] = l_bar_ids[i + 1];
        }

        // 3. Decrease the count
        l_count--;

        // 4. Overwrite the file to sync with new array state
        fstream data;
        data.open("lawyers.csv", ios::out); // 'ios::out' wipes the file and starts fresh
        if (data.is_open()) {
            for (int i = 0; i < l_count; i++) {
                data << l_names[i] << "," << l_cnics[i] << "," 
                     << l_phones[i] << "," << l_bar_ids[i] << endl;
            }
            data.close();
            cout << "\nLawyer removed successfully and file updated.\n";
        }
    } else {
        cout << "\nLawyer with Bar ID " << targetBarID << " not found.\n";
    }
}

void view_master_case_list(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count) {
    if (c_count == 0) {
        cout << "\n!! No cases found in the system. !!\n";
        return;
    }

    // Left align everything and set fixed widths for columns
    cout << left << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << setw(10) << "ID" 
         << setw(18) << "Client" 
         << setw(12) << "Status" 
         << setw(10) << "Total" 
         << setw(10) << "Paid" 
         << setw(10) << "Lawyer" 
         << setw(15) << "Hearing Date" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < c_count; i++) {
        cout << setw(10) << c_ids[i]
             << setw(18) << c_names[i]
             << setw(12) << c_stats[i]
             << setw(10) << c_bills[i]
             << setw(10) << c_paid[i]
             << setw(10) << c_lids[i]
             << setw(15) << c_dates[i] << endl;
    }
    cout << "--------------------------------------------------------------------------------------------" << endl;
    
    // To keep the list on screen until the user is done reading
    cout << "Press Enter to return to menu...";
    cin.ignore(); 
    string dummy;
    getline(cin, dummy); 
}

void calculate_totalRevenue_firmTax(double c_bills[], int c_count) {
    if (c_count == 0) {
        cout << "\n!! ERROR: No case data available to calculate revenue. !!\n";
        return;
    }

    double totalRevenue = 0.0;
    double taxRate = 0.20; // Assuming 20% Firm Tax

    // 1. Sum up the total bills from the array
    for (int i = 0; i < c_count; i++) {
        totalRevenue += c_bills[i];
    }

    // 2. Calculate the tax/firm's share
    double firmTaxAmount = totalRevenue * taxRate;

    // 3. Display the financial report
    cout << "\n========================================" << endl;
    cout << "        FIRM FINANCIAL REPORT           " << endl;
    cout << "========================================" << endl;
    cout << "Total Number of Cases: " << c_count << endl;
    cout << "Gross Revenue:         " << totalRevenue << " PKR" << endl;
    cout << "Firm Tax (20%):        " << firmTaxAmount << " PKR" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Net Profit for Firm:   " << firmTaxAmount << " PKR" << endl;
    cout << "========================================" << endl;

    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

void purge_close_case(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int &c_count) {
    if (c_count == 0) {
        cout << "\n!! ERROR: No cases found to purge. !!\n";
        return;
    }

    int initialCount = c_count;
    int purgedCount = 0;

    // We use a simple loop. If we delete a record, we do NOT increment 'i' 
    // because the next record has shifted into the current index 'i'.
    int i = 0;
    while (i < c_count) {
        if (c_stats[i] == "Won" || c_stats[i] == "Loss") {
            // Shift all elements after 'i' one position to the left
            for (int j = i; j < c_count - 1; j++) {
                c_ids[j] = c_ids[j + 1];
                c_names[j] = c_names[j + 1];
                c_stats[j] = c_stats[j + 1];
                c_bills[j] = c_bills[j + 1];
                c_paid[j] = c_paid[j + 1];
                c_lids[j] = c_lids[j + 1];
                c_dates[j] = c_dates[j + 1];
            }
            c_count--;      // Decrease total count
            purgedCount++;  // Track how many were removed
            // Do NOT increment i here, so we check the new record at this index
        } else {
            i++; // Move to next record only if no deletion happened
        }
    }

    if (purgedCount > 0) {
        // Overwrite cases.txt to reflect the purged list
        fstream data;
        data.open("cases.csv", ios::out); 
        if (data.is_open()) {
            for (int k = 0; k < c_count; k++) {
                data << c_ids[k] << "," << c_names[k] << "," << c_stats[k] << ","
                     << c_bills[k] << "," << c_paid[k] << "," << c_lids[k] << "," 
                     << c_dates[k] << endl;
            }
            data.close();
            cout << "\nSUCCESS: " << purgedCount << " closed cases (Won/Loss) have been purged.\n";
        }
    } else {
        cout << "\nNo closed cases found. Nothing was removed.\n";
    }
    
    cout << "Press Enter to return...";
    cin.ignore();
    cin.get();
}

void logout() {
    cout << "\nLogging out..." << endl;
    // Clears the console screen for the next user
    // "cls" works on Windows. For Linux/Mac, use system("clear")
    system("cls"); 
    
    cout << "========================================" << endl;
    cout << "   LOGGED OUT SUCCESSFULLY!             " << endl;
    cout << "========================================" << endl;
}

bool adminSignin(string enteredUser, string enteredPass, string u_names[], string u_passwords[], string u_roles[], int u_count) {
    for (int i = 0; i < u_count; i++) {
        // Check if username and password match AND if the role is actually "Admin"
        if (u_names[i] == enteredUser && u_passwords[i] == enteredPass && u_roles[i] == "Admin") {
            cout << "\nAccess Granted. Welcome, " << enteredUser << "!\n";
            system("pause");
            return true; // Match found
        }
    }

    // If the loop finishes without returning, no match was found
    cout << "\n[!] Invalid Admin Credentials or Unauthorized Role.\n";
    system("pause");
    return false; 
}

bool lawyerSignin(string enteredCNIC, string enteredBar, string l_cnics[], string l_bar_ids[], int l_count, int &foundIndex){
for (int i = 0; i < l_count; i++) {
        // Compare the inputs with the data in RAM
        if (l_cnics[i] == enteredCNIC && l_bar_ids[i] == enteredBar) {
            foundIndex = i; // Save the position of this lawyer
            return true;    // Login successful
        }
    }
    return false; // Loop finished with no match

}
void saveCases(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count) {
    fstream file;
    file.open("cases.csv", ios::out); // Overwrite mode

    if (file.is_open()) {
        for (int i = 0; i < c_count; i++) {
            file << c_ids[i] << "," 
                 << c_names[i] << "," 
                 << c_stats[i] << "," 
                 << c_bills[i] << "," 
                 << c_paid[i] << "," 
                 << c_lids[i] << "," 
                 << c_dates[i] << endl;
        }
        file.close();
    } else {
        cout << "[!] Error: File could not be opened for saving.\n";
    }
}
void add_new_case(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int &c_count, string currentLawyerBarID) {
    
    // 1. Capacity Check
    if (c_count >= 200) {
        cout << "\n[!] Error: System capacity reached. Cannot add more cases.\n";
        return;
    }

    string client_name;
    cout << "\n--- OPEN NEW CASE ---\n";

    // 2. Get Client Name (Handles spaces)
    // We use ws to clear any leading newlines from the buffer
    do {
        cout << "Enter Client Real Name: ";
        getline(cin >> ws, client_name); 
    } while (!name_validation(client_name));

    // 3. Automatic Data Assignment
    // ID is generated based on current count (e.g., case_21)
    c_ids[c_count] = "case_" + to_string(c_count + 1);
    c_names[c_count] = client_name;
    c_stats[c_count] = "Pending";
    c_bills[c_count] = 0.0;
    c_paid[c_count] = 0.0;
    
    // Automatically link to the logged-in lawyer
    c_lids[c_count] = currentLawyerBarID; 
    c_dates[c_count] = "Not Assigned";

    // 4. Increment the count
    c_count++;

    // 5. Save to File
    // We declare the save function prototype here or at the top of the file
    
    saveCases(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);

    cout << "\nSUCCESS: Case " << c_ids[c_count-1] << " created for " << client_name << ".\n";
    cout << "This case is linked to your Bar License: " << currentLawyerBarID << endl;
    system("pause");
}

void update_case_status(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count) {
    string searchID;
    bool found = false;

    cout << "\n--- UPDATE CASE STATUS ---\n";
    cout << "Enter Case ID to update (e.g., case_1): ";
    cin >> searchID;

    // 1. Search for the Case
    for (int i = 0; i < c_count; i++) {
        if (c_ids[i] == searchID) {
            found = true;
            cout << "\nCase Found for Client: " << c_names[i] << endl;
            cout << "Current Status: " << c_stats[i] << endl;

            // 2. Select New Status
            string statusChoice;
            cout << "\nSelect New Status:\n";
            cout << "1. In-Court\n";
            cout << "2. Won\n";
            cout << "3. Loss\n";
            cout << "4. Pending\n";
            cout << "Enter choice (1-4): ";
            cin >> statusChoice;

            if (statusChoice == "1") c_stats[i] = "In-Court";
            else if (statusChoice == "2") c_stats[i] = "Won";
            else if (statusChoice == "3") c_stats[i] = "Loss";
            else if (statusChoice == "4") c_stats[i] = "Pending";
            else {
                cout << "[!] Invalid choice. No changes made.\n";
                system("pause");
                return;
            }

            // 3. Save updated arrays back to CSV
            saveCases(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);

            cout << "\nSUCCESS: Case status updated to " << c_stats[i] << "!\n";
            break;
        }
    }

    if (!found) {
        cout << "[!] Error: Case ID " << searchID << " not found.\n";
    }
    system("pause");
}
void manage_schedule(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count) {
    string searchID, newDate;
    bool found = false;

    cout << "\n--- MANAGE SCHEDULE (UPDATE HEARING DATE) ---\n";
    cout << "Enter Case ID to schedule (e.g., case_1): ";
    cin >> searchID;

    // 1. Search for the Case
    for (int i = 0; i < c_count; i++) {
        if (c_ids[i] == searchID) {
            found = true;
            cout << "\nCase Found for Client: " << c_names[i] << endl;
            cout << "Current Hearing Date: " << c_dates[i] << endl;

            // 2. Input New Date
            cout << "Enter New Hearing Date (YYYY-MM-DD) or 'TBA': ";
            cin.ignore(); // Clear buffer
            getline(cin, newDate); // Getline used in case there are spaces

            c_dates[i] = newDate;

            // 3. Sync with CSV
            saveCases(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);

            cout << "\nSUCCESS: Hearing date for " << c_ids[i] << " updated to " << c_dates[i] << "!\n";
            break;
        }
    }

    if (!found) {
        cout << "[!] Error: Case ID " << searchID << " not found in the system.\n";
    }
    system("pause");
}

void invoicing(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count) {
    string searchID;
    double paymentAmount;
    bool found = false;

    cout << "\n--- INVOICING & PAYMENT MANAGEMENT ---\n";
    cout << "Enter Case ID for Payment (e.g., case_1): ";
    cin >> searchID;

    // 1. Search for the Case
    for (int i = 0; i < c_count; i++) {
        if (c_ids[i] == searchID) {
            found = true;
            double balance = c_bills[i] - c_paid[i];

            cout << "\nClient: " << c_names[i] << endl;
            cout << "Total Fee:     " << c_bills[i] << " PKR" << endl;
            cout << "Already Paid:  " << c_paid[i] << " PKR" << endl;
            cout << "Remaining:     " << balance << " PKR" << endl;

            // 2. Process New Payment
            cout << "\nEnter amount received today: ";
            cin >> paymentAmount;

            if (paymentAmount < 0) {
                cout << "[!] Error: Payment cannot be negative.\n";
            } else {
                // Update the array by adding to the existing paid amount
                c_paid[i] = c_paid[i] + paymentAmount;

                // 3. Save updated financial data back to CSV
                saveCases(c_ids, c_names, c_stats, c_bills, c_paid, c_lids, c_dates, c_count);

                cout << "\nSUCCESS: Payment recorded! New Total Paid: " << c_paid[i] << " PKR\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "[!] Error: Case ID " << searchID << " not found.\n";
    }
    system("pause");
}
void personal_dashboard_lawyer(string c_ids[], string c_names[], string c_stats[], double c_bills[], double c_paid[], string c_lids[], string c_dates[], int c_count, string currentLawyerBarID) {
    bool foundAny = false;

    cout << "\n=========================================================================================\n";
    cout << "                    MY PERSONAL CASE DASHBOARD (ID: " << currentLawyerBarID << ")\n";
    cout << "=========================================================================================\n";
    
    // Header with fixed widths
    cout << left 
         << setw(12) << "ID" 
         << setw(20) << "Client Name" 
         << setw(15) << "Status" 
         << setw(20) << "Remaining Bill" 
         << setw(15) << "Next Hearing" << endl;
    cout << "-----------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < c_count; i++) {
        // Only show cases that match the current lawyer's Bar License
        if (c_lids[i] == currentLawyerBarID) {
            double remaining = c_bills[i] - c_paid[i];
            
            // cout << c_ids[i] << "\t\t";
            // cout << c_names[i] << "\t\t";
            // cout << c_stats[i] << "\t\t";
            // cout << remaining << " PKR\t\t";
            // cout << c_dates[i] << endl;
            cout << left 
                 << setw(12) << c_ids[i]
                 << setw(20) << c_names[i]
                 << setw(15) << c_stats[i];
            cout << setw(20) << remaining<<"PKR" 
            << setw(15) << c_dates[i] << endl;

            
            foundAny = true;
        }
    }

    if (!foundAny) {
        cout << "\n[!] You currently have no cases assigned to your Bar ID.\n";
    }
    
    cout << "=========================================================================================\n";
    system("pause");
}

bool clientSignin(string enteredName, string enteredLawyerID, string c_names[], string c_lids[], int c_count, int &foundIndex) {
    for (int i = 0; i < c_count; i++) {
        // Double verification: Name must match the Lawyer assigned to them
        if (c_names[i] == enteredName && c_lids[i] == enteredLawyerID) {
            foundIndex = i; // Store the index to display their data later
            return true;
        }
    }
    return false;
}

// 1. View Case Progress (Choice 1)
void view_client_status(string c_stats[], int caseIndex) {
    cout << "\n--- CASE PROGRESS ---\n";
    cout << "Current Status: " << c_stats[caseIndex] << endl;
}

// 2. Check Balance (Choice 2)
void view_client_balance(double c_bills[], double c_paid[], int caseIndex) {
    double remaining = c_bills[caseIndex] - c_paid[caseIndex];
    cout << "\n--- FINANCIAL BALANCE ---\n";
    cout << "Total Fee:     " << c_bills[caseIndex] << " PKR" << endl;
    cout << "Amount Paid:   " << c_paid[caseIndex] << " PKR" << endl;
    cout << "Remaining:     " << remaining << " PKR" << endl;
}

// 3. Lawyer Information (Choice 3)
void view_client_lawyer_info(string c_lids[], string l_names[], string l_phones[], string l_bar_ids[], int caseIndex, int l_count) {
    string lawyerID = c_lids[caseIndex];
    bool found = false;
    cout << "\n--- LAWYER DETAILS ---\n";
    for (int i = 0; i < l_count; i++) {
        if (l_bar_ids[i] == lawyerID) {
            cout << "Lawyer Name:  " << l_names[i] << endl;
            cout << "Contact No:   " << l_phones[i] << endl;
            cout << "Bar License:  " << l_bar_ids[i] << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Lawyer information not found.\n";
}

// 4. View Next Hearing Date (Choice 4)
void view_client_hearing(string c_dates[], int caseIndex) {
    cout << "\n--- SCHEDULE ---\n";
    cout << "Next Hearing Date: " << c_dates[caseIndex] << endl;
}

// 5. Personal Profile (Choice 5)
void view_client_profile(string c_ids[], string c_names[], string c_lids[], string c_stats[], int caseIndex) {
    cout << "\n--- YOUR PROFILE ---\n";
    cout << "Name:            " << c_names[caseIndex] << endl;
    cout << "Case ID:         " << c_ids[caseIndex] << endl;
    cout << "Assigned Lawyer: " << c_lids[caseIndex] << endl;
    cout << "Current Status:  " << c_stats[caseIndex] << endl;
}
bool username_validation(string user_name) {
    // 1. Length Check (Exactly 7 characters)
    if (user_name.length() != 7) {
        return false;
    }

    // 2. Content Check (Letters, Numbers, and Underscore only)
    for (int i = 0; i < user_name.length(); i++) {
        char c = user_name[i];
        if (!((c >= 'a' && c <= 'z') || 
              (c >= 'A' && c <= 'Z') || 
              (c >= '0' && c <= '9') || 
               c == '_')) {
            return false; // Found an invalid character (like space, @, !, etc.)
        }
    }

    return true; 
}
