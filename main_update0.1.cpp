#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";

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
enum EnMainMenuOptions
{
    ClientList = 1, New_Client = 2, DeleteAcc = 3, Update_Client = 4,
    Find_Client = 5, Trans_actions = 6, Program_Ends = 7
};
enum EnTransactionsMenuOptions
{
    Deosit = 1, Withdraw = 2, Total_Balance = 3, Main_Menu = 4   
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
    cout << " [7] Exit.                                                    *\n\n";
    cout << "***************************************************************\n\n";
    cout << " -Choose What DO You Want To Do? [1 -> 7] ";
    cin >> num;
    return num;

}


void MessagesScreens(string Title)
{
    system("cls");
    cout << "_______________________________\n\n";
    cout << "      " << Title << "           \n";
    cout << "_______________________________\n\n";
}

short TransactionMinuScreen()
{
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
void PressKey_GoOut()
{
    cout << "\n\nPress Any Key To Close This Window....";
    system("pause>0");
}

vector<string> SplitString(string s1, string delim = " ")
{
    short pos = 0; string sword;
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
    vector<string> vString = SplitString(line, ",");

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

    MyFile.open(ClientsFileName, ios::in);

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
vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
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

    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;

    }
    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;


}

void ShowClientList()
{
    system("cls");
    PrintAllClientsData(vClients);
    PressKey_GoOut();
}


string ConvertRecordToLine(sClient Client, string delim = ",")
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
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void Add_New_Client()
{
    MessagesScreens("Add Client Screen");
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(ReadNewClient()));

    cin.ignore();
    char AddClient = 'Y';
    cout << "\nDo You Want To Add New Client_Y/N? ";
    cin >> AddClient;

    while (tolower(AddClient) == 'y')
    {
        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(ReadNewClient()));
        cout << "\nDo You Want To Add New Client_Y/N? ";
        cin >> AddClient;
    }
    vClients = LoadClientsDataFromFile(ClientsFileName);

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


void Program_Ends_Screen()
{
    system("cls");
    cout << "___________________________\n\n";
    cout << "      Program Ends :-)     \n";
    cout << "___________________________\n\n";
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

    do
    {
        cout << "Enter the amount of your transaction: "; cin >> amount;
        if (!IsDeposit && amount > Client.AccountBalance)
        {
            cout << "\nAmount Exceeds Balance, You Can Withdraw Up To: " << 
                Client.AccountBalance << endl;
        } 

    } while (amount > Client.AccountBalance);

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
    for (sClient & C : vClients)
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

void SwitchOpenTransactionsMenu()
{
    EnTransactionsMenuOptions TransactionsMenuOptions;
    do
    {
        TransactionsMenuOptions = (EnTransactionsMenuOptions)TransactionMinuScreen();

        switch (TransactionsMenuOptions)
        {
        case Deosit:       HandleTransaction("Deposit Screen", true);    break;
        case Withdraw:     HandleTransaction("Withdraw Screen", false);   break;
        case Total_Balance:ClientBalancesTable();   break;
        default: Main_Menu:                  break;

        }
    } while (TransactionsMenuOptions != Main_Menu);

}
void SwitchOpenMainMenu()
{
    EnMainMenuOptions MainMenuOptions;

    do
    {
        MainMenuOptions = (EnMainMenuOptions)MainMenu();

        switch (MainMenuOptions)
        {

        case ClientList:   ShowClientList();             break;
        case New_Client:   Add_New_Client();             break;
        case DeleteAcc:  DeleteAccount();                break;
        case Update_Client:   UpdateClientInfo();        break;
        case Find_Client:    FindClient();               break;
        case Trans_actions:    SwitchOpenTransactionsMenu();break;
        default:Program_Ends:   Program_Ends_Screen();   break;

        }

    } while (MainMenuOptions != Program_Ends);
}

int main()
{
    SwitchOpenMainMenu();
    return 0;
}
