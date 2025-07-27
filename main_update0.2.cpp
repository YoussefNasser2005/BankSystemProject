#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
    bool DoTransaction = false;

};
struct sUser
{
    string Uname;
    string Pass;
    short Permissions = 0;
    bool MarkForDelete = false;
};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
sUser CurrentUser;

enum EnPermissions
{
    pcall    = -1,
    pcClientList    = 1,
    pcNew_Client    = 2, 
    pcDeleteAcc     = 4,
    pcUpdate_Client = 8,
    pcFind_Client   = 16,
    pcTrans_actions = 32,
    pcManage_Users  = 64, 
};
enum EnTransactionsMenuOptions
{
    Deposit = 1, Withdraw = 2, Total_Balance = 3, Main_Menu = 4
};
enum EnMainMenuOptions
{
    ClientList = 1,
    New_Client = 2,
    DeleteAcc = 3,
    Update_Client = 4,
    Find_Client = 5,
    Trans_actions = 6,
    Manage_Users = 7,
    Log_out = 8,
    Program_Ends = 9
};
enum EnManageUsersOptions
{
    LUsers = 1, AUsers = 2, DUsers = 3, UUsers = 4, FUsers = 5, MMinue = 6,
};

void SwitchOpenMainMenu();
void SwitchOpenTransactionsMenu();
short MainMenu()
{
    short num = 0;
    system("cls");
    cout << "***************************************************************\n";
    cout << "\t\t\t|================|                    *\n";
    cout << "\t\t\t|    Jo Bank     |                    *\n";
    cout << "\t\t\t|Main Menu Screen|                    *\n";
    cout << "\t\t\t|================|                    *\n";
    cout << "***************************************************************\n\n";
    cout << " [1] Show Client List.                                        *\n\n";
    cout << " [2] Add New Client.                                          *\n\n";
    cout << " [3] Delete Client.                                           *\n\n";
    cout << " [4] Update Client info.                                      *\n\n";
    cout << " [5] Find Client.                                             *\n\n";
    cout << " [6] Transactions.                                            *\n\n";
    cout << " [7] Manage Users                                             *\n\n";
    cout << " [8] Logout                                                   *\n\n";
    cout << " [9] Exit.                                                    *\n\n";
    cout << "***************************************************************\n\n";
    cout << " -Choose What DO You Want To Do? [1 -> 9] ";
    cin >> num;
    return num;

}
void PressKey_GoOut()
{
    cout << "\n\nPress Any Key To Close This Window....";
    system("pause>0");
}
void ShowAccessMessage()
{
    system("cls");
    cout << "\n\t\t\t********* You Don't Have Access Here! *********\n";
    PressKey_GoOut();
}
bool CheckAccessPermission(EnPermissions Permission)
{
    if (CurrentUser.Permissions == pcall)
        return true;
    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;
    else
        return false;
}

short TransactionMenuScreen()
{
    if (!CheckAccessPermission(pcTrans_actions))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    system("cls");
    short Num;
    cout << "=================================================\n";
    cout << "\t\t    Transaction Menu Screen     * \n";
    cout << "=================================================\n";
    cout << "\t[1]. Deposit                            * \n\n";
    cout << "\t[2]. Withdraw                           *\n\n";
    cout << "\t[3]. Total Balance                      *\n\n";
    cout << "\t[4]. Main Menu                          *\n";
    cout << "=================================================\n";
    cout << "Choose What Do You Want To Do [ 1 -> 4 ]? \n";
    cin >> Num;

    return Num;
}
short ManageUsersMinuScreen()
{
    if (!CheckAccessPermission(pcManage_Users))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    system("cls");
    short Num;
    cout << "=================================================\n";
    cout << "\t\tManage Users Screen              * \n";
    cout << "=================================================\n";
    cout << "\t[1]. List Users                         * \n\n";
    cout << "\t[2]. Add New User                       *\n\n";
    cout << "\t[3]. Delete User                        *\n\n";
    cout << "\t[4]. Update User                        *\n\n";
    cout << "\t[5]. Find User                          *\n\n";
    cout << "\t[6]. Main Menu                          *\n";
    cout << "=================================================\n";
    cout << "Choose What Do You Want To Do [ 1 -> 6 ]? ";
    cin >> Num;

    return Num;
}
void MessagesScreens(string Title)
{
    system("cls");
    cout << "_______________________________\n\n";
    cout << "      " << Title << "           \n";
    cout << "_______________________________\n\n";
}



vector<string> SplitString(string s1, string delim = " ")
{
    size_t pos = 0; string sword;
    vector<string> vString;
    while ((pos = s1.find(delim)) != std::string::npos)
    {
        sword = s1.substr(0, pos);
        if (!sword.empty())
            vString.push_back(sword);
        s1.erase(0, pos + delim.length());
    }
    if (!s1.empty())
        vString.push_back(s1);
    return vString;
}
sClient ConvertLineToRecord(string line)
{
    sClient Client;
    vector<string> vString = SplitString(line, "//");

    if (vString.size() >= 5)
    {
        Client.AccountNumber = vString[0];
        Client.Name = vString[1];
        Client.PinCode = vString[2];
        Client.Phone = vString[3];
        Client.AccountBalance = stod(vString[4]);
    }

    return Client;
}
vector<sClient> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    vector<sClient> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
        {
            vClients.push_back(ConvertLineToRecord(line));
        }
        MyFile.close();
    }
    return vClients;
}
void PrintClientRecord(sClient Client)
{
    cout << left << "| " << setw(15) << Client.AccountNumber;
    cout << left << "| " << setw(40) << Client.Name;
    cout << left << "| " << setw(10) << Client.PinCode;
    cout << left << "| " << setw(12) << Client.Phone;
    cout << left << "| " << setw(12) << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";     cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\n\t\t\t\t\t No Clients Available in the system! ";
    else

        for (sClient C : vClients)
        {
            PrintClientRecord(C);
            cout << endl;
        }

    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

void ShowClientList()
{
    if (!CheckAccessPermission(pcClientList))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    system("cls");
    PrintAllClientsData(vClients);
    PressKey_GoOut();
}


string ConvertRecordToLine(sClient Client, string delim = "//")
{
    string s1 = "";
    s1 += Client.AccountNumber + delim;
    s1 += Client.Name + delim;
    s1 += Client.PinCode + delim;
    s1 += Client.Phone + delim;
    s1 += to_string(Client.AccountBalance);
    return s1;
}
sClient ReadNewClient()
{
    sClient Client;
    bool IsExit = false;

    do
    {
        IsExit = false;
        cout << "Enter Account Number? ";
        getline(cin >> ws, Client.AccountNumber);

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == Client.AccountNumber)
            {
                IsExit = true;
                cout << "The Number (" << Client.AccountNumber << ") already There is\nTry Again\n";
                break;
            }
        }

    } while (IsExit);

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        cout << '\n';
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void Add_New_Client()
{
    if (!CheckAccessPermission(pcNew_Client))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    MessagesScreens("Add Client Screen");

    sClient NewClient = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(NewClient));
    vClients.push_back(NewClient);
    cout << "\nClient added successfully!\n";

    cin.ignore();
    char AddClient = 'Y';
    cout << "\nDo You Want To Add New Client Y/N? ";
    cin >> AddClient;

    while (tolower(AddClient) == 'y')
    {
        sClient NewClient = ReadNewClient();
        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(NewClient));
        vClients.push_back(NewClient);
        cout << "\nClient added successfully!\n";

        cout << "\nDo You Want To Add New Client Y/N? ";
        cin >> AddClient;
    }

    cout << "\nAll clients added successfully.\n\n";
    PressKey_GoOut();
}


void PrintClientCard(sClient Client)
{
    cout << "The Following Is The Client Details\n\n";
    cout << "________________________________________\n";
    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nName           : " << Client.Name;
    cout << "\nPinCode        : " << Client.PinCode;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n________________________________________\n";
}
vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (sClient& C : vClients)
        {
            if (!C.MarkForDelete)
            {
                string DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients
    , sClient& Client)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            Client = C;
            return true;
        }
    }
    return false;
}

bool DeleteAccount()
{
    if (!CheckAccessPermission(pcDeleteAcc))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    MessagesScreens("Delete Account Screen");
    string AccNum = "";
    sClient Client;
    cout << "Who Is The Account Number You Want To Delete: ";
    cin >> AccNum;

    if (!MarkClientForDeleteByAccountNumber(AccNum, vClients, Client))
    {
        cout << "The Account Number (" << AccNum << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }

    PrintClientCard(Client);
    cin.ignore();
    char Choose = 'Y';
    cout << "\nDo You Want Delete This Account Y/N: "; cin >> Choose;

    if (tolower(Choose) == 'y')
    {
        SaveClientsDataToFile(ClientsFileName, vClients);
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout << "Deleted Successfully!\n";
    }

    PressKey_GoOut();
    return true;
}


sClient UpdateClient(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Enter Name? ";
    getline(cin >> ws, Client.Name);
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    cin.ignore();

    return Client;
}
bool MarkClientForUpdateByAccountNumber(string AccountNumber, vector<sClient>& vClients
    , sClient& Client)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool UpdateClientInfo()
{

    if (!CheckAccessPermission(pcUpdate_Client))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    MessagesScreens("Update Client Screen");

    string AccNum = "";  sClient Client;
    cout << "Who Is The Account Number You Want To Update: ";
    cin >> AccNum;

    if (!MarkClientForUpdateByAccountNumber(AccNum, vClients, Client))
    {
        cout << "The Account Number (" << AccNum << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }

    PrintClientCard(Client);
    char Choose = 'Y';
    cin.ignore();
    cout << "\nDo You Want Update This Account Y/N: "; cin >> Choose;

    if (tolower(Choose) == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccNum)
            {
                C = UpdateClient(AccNum);
                break;
            }
        }
        SaveClientsDataToFile(ClientsFileName, vClients);
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout << "\nUpdated Successfully!\n";
    }

    PressKey_GoOut();
    return true;

}


bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindClient()
{

    if (!CheckAccessPermission(pcFind_Client))
    {
        ShowAccessMessage();
        SwitchOpenMainMenu();
    }
    MessagesScreens("Find Client Screen");
    string AccNum = "";
    sClient Client;

    cin.ignore();
    cout << "Who Is The Account Number You Want To Find: ";
    cin >> AccNum;

    if (!FindClientByAccountNumber(AccNum, vClients, Client))
    {
        cout << "The Account Number (" << AccNum << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }
    PrintClientCard(Client);
    PressKey_GoOut();

    return true;
}


bool Program_Ends_Screen()
{
    system("cls");
    cout << "___________________________\n\n";
    cout << "      Program Ends :-)     \n";
    cout << "___________________________\n\n";
    return true;
}

bool DepositOrWithdrawBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{

    char Answer = 'n';

    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                vClients = LoadClientsDataFromFile(ClientsFileName);
                PressKey_GoOut();
                return true;
            }
        }
    }
    PressKey_GoOut();
    return false;
}


void HandleTransaction(string ScreenTritle, bool IsDeposit)
{

    string AccNum; sClient Client;
    bool IsExit = false;
    MessagesScreens(ScreenTritle);
    do
    {
        cout << "Enter Account Number: "; cin >> AccNum;
        if (!FindClientByAccountNumber(AccNum, vClients, Client))
        {
            cout << "The account number (" << AccNum << ") is not found\n";
        }

    } while (!FindClientByAccountNumber(AccNum, vClients, Client));

    system("cls");
    double amount;
    PrintClientCard(Client);

    cout << "Enter the amount of your transaction: "; cin >> amount;
    while(!IsDeposit && amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds Balance, You Can Withdraw Up To: " <<
        Client.AccountBalance << endl;
        cout << "Enter the amount of your transaction: "; cin >> amount;
    } 

    double FinalAmount = IsDeposit ? amount : -amount;
    DepositOrWithdrawBalanceToClientByAccountNumber(AccNum, FinalAmount, vClients);
}

void PrintClientRecord_Withdrawlist(sClient Client)
{
    cout << left << "| " << setw(25) << Client.AccountNumber;
    cout << left << "| " << setw(40) << Client.Name;
    cout << left << "| " << setw(25) << Client.AccountBalance;
}
void ClientBalancesTable()
{
    system("cls");
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(25) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(25) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    double TotalBalance = 0;
    for (sClient& C : vClients)
    {
        PrintClientRecord_Withdrawlist(C);
        TotalBalance += C.AccountBalance;
        cout << endl;

    }
    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "\t\t\t\tTotal Balance = " << TotalBalance;
    PressKey_GoOut();
}

sUser ConvertUserLineToRecord(string line)
{
    sUser User;
    vector<string> vString = SplitString(line, "//");

    if (vString.size() >= 3 && !vString[2].empty())
    {
        User.Uname = vString[0];
        User.Pass = vString[1];
        User.Permissions = stoi(vString[2]);
    }
    else
        User.Permissions = 0;


    return User;
}
vector<sUser> LoadUsersDataFromFile(string UsersFileName)
{
    fstream MyFile;
    vector<sUser> vUsers;

    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
        {
            vUsers.push_back(ConvertUserLineToRecord(line));
        }
        MyFile.close();
    }
    return vUsers;
}
sUser GetUserInfo(vector <sUser>& vUsers, string &name, string &pass)
{
    for (sUser &U: vUsers)
    {
        if (U.Uname == name && U.Pass == pass)
        {
            return U;
        }
    }
    return sUser{ "",""};
}


void PrintUsersRecord(sUser User)
{
    cout << left << "| " << setw(40) << User.Uname;
    cout << left << "| " << setw(30) << User.Pass;
    cout << left << "| " << setw(30) << User.Permissions;
}
void PrintAllUsersData(vector <sUser> vUsers)
{
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";  
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(40) << "User Name";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(30) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\n\t\t\t\t\t No Users Available in the system! ";
    else

        for (sUser User : vUsers)
        {
            PrintUsersRecord(User);
            cout << endl;
        }

    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
vector <sUser>vUsers = LoadUsersDataFromFile(UsersFileName);

void ShowUserList()
{
    system("cls");
    PrintAllUsersData(vUsers);
    PressKey_GoOut();
}


short ReadUserPermissions()
{
    char choose;
    short Permission = 0;
    cout << "Do you want to give full access?Y/N  ";
    cin >> choose;

    if (tolower(choose) == 'y')
        return -1 ;
    else
    {
        cout << "\nDo you want let him show Client List?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
            Permission += pcClientList;
   
        
        cout << "\nDo you want let him Add New Client ?Y/N  ";
        cin >> choose;
        cout << endl;

        if (tolower(choose) == 'y')
            Permission += pcNew_Client;
        

        cout << "\nDo you want let him Delete Account ?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
            Permission += pcDeleteAcc;


        cout << "\nDo you want let him Update Client List?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
        {
            Permission += pcUpdate_Client;
        }

        cout << "\nDo you want let him Find Client?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
        {
            Permission += pcFind_Client;
        }

        cout << "\nDo you want let him Show Transactions List?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
        {
            Permission += pcTrans_actions;
        }

        cout << "\nDo you want let him show Manage Users List?Y/N  ";
        cin >> choose;
        cout << endl;
        if (tolower(choose) == 'y')
        {
            Permission += pcManage_Users;
        }  
    }
    return Permission;
}
sUser ReadNewUser()
{
    sUser User;
    bool IsExit = false;
    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    do
    {
        IsExit = false;
        cout << "Enter Account Name? ";
        getline(cin >> ws, User.Uname);

        for (sUser& U : vUsers)
        {
            if (U.Uname == User.Uname)
            {
                IsExit = true;
                cout << "The Name [" << User.Uname << "] already There is\nTry Again\n";
                break;
            }
        }
    } while (IsExit);
    cout << "Enter Account Password? ";
    cin >> User.Pass;
    User.Permissions = ReadUserPermissions();

    return User;
}
string ConvertRecord_ToLine(sUser User, string delim = "//")
{
    string s1 = "";
    s1 += User.Uname + delim;
    s1 += User.Pass + delim;
    s1 += to_string(User.Permissions);
    return s1;
}
bool CheckAccessPermission(short UserPermission, int RequiredPermission)
{
    if ((UserPermission & RequiredPermission) == RequiredPermission)
        return true;

    cout << "\n\nYou don't have permission to perform this action.\n";
    PressKey_GoOut();
    return false;
}

void Add_New_User()
{
    MessagesScreens("Add User Screen");
    sUser NewUser = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecord_ToLine(NewUser));
    vUsers.push_back(NewUser);

    cin.ignore();
    char AddUser = 'Y';
    cout << "\nDo You Want To Add New User Y/N? ";
    cin >> AddUser;

    while (tolower(AddUser) == 'y')
    {
        sUser NewUser = ReadNewUser();
        AddDataLineToFile(UsersFileName, ConvertRecord_ToLine(NewUser));
        vUsers.push_back(NewUser);
        cout << "\nDo You Want To Add New User Y/N? ";
        cin >> AddUser;
    }
    cout << "User successfully added \n\n ";
    PressKey_GoOut();
}


bool MarkUserForDeleteByUserName(string Uname, vector<sUser>& vUsers
    , sUser& User)
{
    for (sUser& U : vUsers)
    {
        if (U.Uname == Uname)
        {
            U.MarkForDelete = true;
            User = U;
            return true;
        }
    }
    return false;
}
vector<sUser> SaveUsersDataToFile(string FileName, vector<sUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (sUser& U : vUsers)
        {
            if (!U.MarkForDelete)
            {
                string DataLine = ConvertRecord_ToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}
void PrintUserCard(sUser User)
{
    cout << "The Following Is The User Details\n\n";
    cout << "____________________________________\n";
    cout << "\nUser Name         : " << User.Uname << '\n';
    cout << "\nPassword           : " << User.Pass  << '\n';
    cout << "\n____________________________________\n";
}
string ToLowerString(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool Delete_Users()
{

    MessagesScreens("Delete Users Screen");
    string UName;  sUser User;
    cout << "Which User Name You Want To Delete: ";
    cin >> UName;

    if (!MarkUserForDeleteByUserName(UName, vUsers, User))
    {
        cout << "This Name (" << UName << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }

    if(ToLowerString(UName) == "admin")
    { 
        cout << "You Cannot Delete This User.\n";
        PressKey_GoOut();
        return false;
    }

    PrintUserCard(User);
    cin.ignore();
    char Choose = 'Y';
    cout << "\nDo You Want Delete This User Y/N: "; cin >> Choose;

    if (tolower(Choose) == 'y')
    {
        SaveUsersDataToFile(UsersFileName, vUsers);
        vUsers = LoadUsersDataFromFile(UsersFileName);
        cout << "Deleted Successfully!\n";
    }
    PressKey_GoOut();
    return true;
}


bool MarkUserForUpdateByUserName(string UserName, vector<sUser>& vUsers
    , sUser& User)
{
    for (sUser& U : vUsers)
    {
        if (U.Uname == UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool UpdateUserInfo()
{
    MessagesScreens("Update User Screen");

    string Uname = "";  sUser User;
    cout << "Who Is The User Account You Want To Update: ";
    cin >> Uname;

    if (!MarkUserForUpdateByUserName(Uname, vUsers, User))
    {
        cout << "This Name (" << Uname << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }

    PrintUserCard(User);
    char Choose = 'Y';
    cin.ignore();
    cout << "\nDo You Want Update This Account Y/N: "; cin >> Choose;

    if (tolower(Choose) == 'y')
    {
        for (sUser& U : vUsers)
        {
            if ( U.Uname == Uname)
            {
                cout << "Enter New Password? ";
                getline(cin >> ws, U.Pass);
                break;
            }
        }
        SaveUsersDataToFile(UsersFileName, vUsers);
        cout << "\nUpdated Successfully!\n";
    }

    PressKey_GoOut();
    return true;
}


bool FindUserByUserName(string UserName, vector<sUser>& vUsers, sUser& User)
{
    for (sUser& U : vUsers)
    {
        if (U.Uname == UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}


bool FindUser()
{
    MessagesScreens("Find User Screen");
    string Uname = "";
    sUser User;

    cin.ignore();
    cout << "Which User Name You Want To Find: ";
    cin >> Uname;

    if (!FindUserByUserName(Uname, vUsers, User))
    {
        cout << "Account Name (" << Uname << ") Is Not Found\n\n";
        PressKey_GoOut();
        return false;
    }
    PrintUserCard(User);
    PressKey_GoOut();
    return true;
}

void SwitchOpenManageUsers()
{
    EnManageUsersOptions Manage_UsersOptions;

    do
    {
        switch (Manage_UsersOptions = (EnManageUsersOptions)ManageUsersMinuScreen())
        {
        case LUsers: ShowUserList();      break;
        case AUsers: Add_New_User();      break;
        case DUsers: Delete_Users();      break;
        case UUsers: UpdateUserInfo();    break;
        case FUsers: FindUser();          break;
        case MMinue: return;              break;
        }

    } while (Manage_UsersOptions != MMinue);
}
void LoginScreen()
{
    string pass, Uname;
    MessagesScreens("Login Screen");
    char Ans ;

    do
    {
        cout << "Enter Username: "; cin >> Uname;
        cout << "Enter Password: "; cin >> pass;
        CurrentUser = GetUserInfo(vUsers, Uname, pass);

        if (CurrentUser.Uname == "")
        {
            system("cls");
            MessagesScreens("Login Screen");
            cout << "Invalid Username/Password\n";
        }
    } while (CurrentUser.Uname == "");
    system("cls");
    SwitchOpenMainMenu();
}
void SwitchOpenMainMenu()
{
    EnMainMenuOptions MainMenuOptions;
    bool ExitProgram = false;
    do
    {

        MainMenuOptions = (EnMainMenuOptions)MainMenu();

        switch (MainMenuOptions)
        {

        case ClientList:        ShowClientList();             break;
        case New_Client:        Add_New_Client();             break;
        case DeleteAcc:         DeleteAccount();              break;
        case Update_Client:     UpdateClientInfo();           break;
        case Find_Client:       FindClient();                 break;
        case Trans_actions:     SwitchOpenTransactionsMenu(); break;
        case Manage_Users:      SwitchOpenManageUsers();      break;
        case Log_out:           LoginScreen();                break;
        }

    } while (MainMenuOptions != Program_Ends);
}
void SwitchOpenTransactionsMenu()
{
    EnTransactionsMenuOptions TransactionsMenuOptions;
    do
    {
        TransactionsMenuOptions = (EnTransactionsMenuOptions)TransactionMenuScreen();

        switch (TransactionsMenuOptions)
        {
        case Deposit:        HandleTransaction("Deposit Screen", true);     break;
        case Withdraw:      HandleTransaction("Withdraw Screen", false);   break;
        case Total_Balance: ClientBalancesTable();                         break;
        case Main_Menu:     SwitchOpenMainMenu();                          break;
        }
    } while (TransactionsMenuOptions != Main_Menu);

}


int main()
{
   LoginScreen();
 
   return 0;
}
