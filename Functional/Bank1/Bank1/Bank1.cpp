// Bank1.

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

struct stUser
{
    string UserName;
    string Password;
    int Permission;
    bool MarkToDelete = false;

};

struct stClient
{
    string AcountNumber;
    string PinCod;
    string Name;
    string Phone;
    double AcountBalance;
    bool MarkToDelete=false;
};


void ShowMainMenue();
void ShowTransactionMenu();
void  ShowUserMangeMenu();
void LoginScreen();


const string ClientsFileName = "ClientsFile.txt";
const string UsersFileName = "UsersFiles";
stUser CurrentUser;


//2
vector <string> SplitString(string S, string Delimiter)
{

    vector<string> vString;
    short Pos = 0;
    string sWord;

    while ((Pos = S.find(Delimiter)) != std::string::npos)
    {
        sWord = S.substr(0, Pos);
        if (sWord != " ")
        {
            vString.push_back(sWord);
        }
        S.erase(0, Pos + Delimiter.length());
    }
    if (S != " ")
    {
        vString.push_back(S);
    }
    return vString;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    vector<string> vString;
    vString = SplitString(Line, Seperator);
    stClient Client;
    Client.AcountNumber = vString[0];
    Client.PinCod = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AcountBalance = stod(vString[4]);
    return Client;
}

stUser ConvertLineToUserRecord(string Line, string Seperator = "#//#")
{
    vector<string> vString;
    vString = SplitString(Line, Seperator);
    stUser User;
    User.UserName = vString[0];
    User.Password = vString[1];

    User.Permission = stod(vString[2]);
    return User;
}

string ConvertRecoredToLine(stClient Client, string Seperator = "#//#")
{
    string S = "";
    S = S + Client.AcountNumber + Seperator;
    S = S + Client.PinCod + Seperator;
    S = S + Client.Name + Seperator;
    S = S + Client.Phone + Seperator;
    S = S + to_string(Client.AcountBalance);
    return S;
}

string ConvertRecoredToLine(stUser User, string Seperator = "#//#")
{
    string S = "";
    S = S + User.UserName + Seperator;
    S = S + User.Password + Seperator;
   
    S = S + to_string(User.Permission);
    return S;
}

bool isClientExistByAcountNumber(string AcountNumber,string FileName)
{
    vector<stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stClient Client;
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AcountNumber == AcountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);

        }
        MyFile.close();
    }
    return false;
}

stClient ReadNewClient()
{
    stClient Client;
    cout << "\nClient information\n";

    cout << "\nEnter your Acount number : ";
    getline(cin >> ws, Client.AcountNumber);

    while (isClientExistByAcountNumber(Client.AcountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AcountNumber << "] already exist. Enter another one\n";
        getline(cin >> ws, Client.AcountNumber);
    }

    cout << "\nEnter your PinCod : ";
    getline(cin, Client.PinCod);

    cout << "\nEnter your Name : ";
    getline(cin, Client.Name);

    cout << "\nEnter your Phone number : ";
    getline(cin, Client.Phone);

    cout << "\nEnter your Acount number : ";
    cin >> Client.AcountBalance;

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

void AddNewClint()
{
    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecoredToLine(Client));
}

void Head(string Head)
{
    cout << "\n_________________________________";
    cout << "\n        " << Head << " Client Screen";
    cout << "\n_________________________________\n";
}

//1

vector <stClient> LoadDataFromFileToVector(string FileName)
{

    vector<stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stClient Client;
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);

        }
        MyFile.close();
    }
    return vClients;

}

vector <stUser> LoadUsersDataFromFileToVector(string FileName)
{

    vector<stUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stUser User;
        string Line;
        while (getline(MyFile, Line))
        {
            User = ConvertLineToUserRecord(Line);
            vUsers.push_back(User);

        }
        MyFile.close();
    }
    return vUsers;

}


void PrintClient2(stClient Client)
{

    cout << left << setw(13) << Client.AcountNumber << "|" << setw(7) << Client.PinCod << "|" << setw(20)
        << Client.Name << "|" << setw(10) << Client.Phone << "|" << setw(15)
        << Client.AcountBalance << "|" << endl;


}

void PrintUser(stUser User)
{

    cout << left << setw(20) << User.UserName << "|" << setw(10) << User.Password << "|" << setw(15)
        << User.Permission << "|" << endl;


}

void PrintHead(short NumberOfClient)
{
    cout << "\n                    Client List (" << NumberOfClient << ") Client(s).\n";
    cout << "__________________________________________________________________________\n";
    cout << left << setw(13) << "Acount Number" << "|" << setw(7) << "PinCod" << "|" << setw(20) << "Client Name"
        << "|" << setw(10) << "Phone" << "|" << setw(15) << "Acount Balance" << "|" << endl;
    cout << "__________________________________________________________________________\n";

}

//5
void PrintClient(stClient Client)
{
    cout << "The folowing client details : ";
    cout << "\n================================";
    cout << "\nAcount Number  : " << Client.AcountNumber;
    cout << "\nPinCod         : " << Client.PinCod;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAcount Balance : " << Client.AcountBalance;
    cout << "\n---------------------------------";
}

bool FindClientFromCountNumber(string RAcountNumber, vector <stClient> vClients
    , stClient& Client)
{

    for (stClient C : vClients)
    {
        if (C.AcountNumber == RAcountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

bool FindUsertFromUserName(string UserName, vector <stUser> vUsers
    , stUser& User)
{

    for (stUser U : vUsers)
    {
        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }

    }
    return false;
}

bool FindUsertFromUserNameAndPassword(string UserName, string Password, stUser& User)  
{
    vector <stUser> vUsers = LoadUsersDataFromFileToVector(UsersFileName);
    for (stUser U : vUsers)
    {
        if (U.UserName == UserName && U.Password==Password)
        {
            User = U;
            return true;
        }

    }
    return false;
}


string ReadString()
{
    string AcountNember = "";
    cout << "\nEnter Acount Number : ";
    getline(cin >> ws, AcountNember);
    return AcountNember;
}

string ReadUserName()
{
    string UserName = "";
    cout << "\nEnter User Name : ";
    getline(cin >> ws, UserName);
    return UserName;
}

string ReadPassword()
{
    string Password = "";
    cout << "\nEnter Password : ";
    getline(cin >> ws, Password);
    return Password;
}


//3
bool MarkClientForDeleteByAcountNumber(string AcountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AcountNumber == AcountNumber)
        {
            C.MarkToDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClient> SaveClintDataToFile(string FileName, vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        string Line;
        for (stClient C : vClients)
        {
            if (C.MarkToDelete == false)
            {
                Line = ConvertRecoredToLine(C);
                MyFile << Line << endl;
            }
        }
    }
    return vClients;
}

bool DeleteClientFromAcountNumber(string AcountNumber, vector<stClient>& vClients)
{
    stClient Client;
    if (FindClientFromCountNumber(AcountNumber, vClients, Client))
    {

        PrintClient(Client);
        char DeleteClient = 'n';

        cout << "\nAre you sure you want delete this Client ? y/n ?  ";
        cin >> DeleteClient;
        if (tolower(DeleteClient) == 'y')
        {
            MarkClientForDeleteByAcountNumber(AcountNumber, vClients);
            SaveClintDataToFile(ClientsFileName, vClients);
            vClients = LoadDataFromFileToVector(ClientsFileName);
            cout << "\nClient Deleted successfully \n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with acount number (" << AcountNumber << ") not foundd\n";
        return false;
    }

}

//4
stClient ReadUpdateDataClint(string AcountNember)
{
    stClient Client;

    Client.AcountNumber = AcountNember;

    cout << "\nEnter your PinCod : ";
    getline(cin >> ws, Client.PinCod);

    cout << "\nEnter your Name : ";
    getline(cin, Client.Name);

    cout << "\nEnter your Phone number : ";
    getline(cin, Client.Phone);

    cout << "\nEnter your Acount number : ";
    cin >> Client.AcountBalance;

    return Client;
}

bool UpdateClientData(string AcountNumber, vector<stClient>& vClients)
{
    stClient Client;
    if (FindClientFromCountNumber(AcountNumber, vClients, Client))
    {

        PrintClient(Client);
        char DeleteClient = 'n';

        cout << "\nAre you sure you want update this Client ? y/n ?  ";
        cin >> DeleteClient;
        if (tolower(DeleteClient) == 'y')
        {
            for (stClient& C : vClients)
            {
                if (C.AcountNumber == AcountNumber)
                {
                    C = ReadUpdateDataClint(AcountNumber);
                    break;
                }
            }

            SaveClintDataToFile(ClientsFileName, vClients);

            cout << "\nClient Updeted  successfully \n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with acount number (" << AcountNumber << ") not foundd\n";
        return false;
    }
}

//6

enum enMainOptions { List = 1, Add = 2, Delete = 3, Update = 4, Find = 5,
                    Transaction = 6, MangeUser = 7, Logout = 8 };

enum enTransactionOption { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };

enum enUserMangeOption { UsersList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, 
    FindUser = 5, ToMainMenu = 6 };

enum enMainMenuPermission {
    pAll = -1, pList = 1, pAdd = 2, pDelete = 4, pUpdate = 8, pFind = 16,
    pTransaction = 32, pMangeUser = 62
};



short ReadChooseNumber(string FromTo)
{
    short Number;
    cout << "Choose What do you want to do ? ["<<FromTo<<"] : ";
    cin >> Number;
    return Number;
}

bool DeposetBalanceToClientByAcountNumber(string AcountNumber,double UpdateAmount,vector<stClient> &vClients)
{
    char Answer = 'n';
    cout << "\nAre you sure you want performan this transaction? y/n? ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
    {
        for (stClient& C : vClients)
        {
            if (C.AcountNumber == AcountNumber)
            {
                C.AcountBalance += UpdateAmount;
                SaveClintDataToFile(ClientsFileName, vClients);
                cout << "\nDoin  successfully Your New Balance is : " << C.AcountBalance << "\n";
                return true;
            }
        }
        return false;
        
    }
   /* else
    {
        system("cls");
        GoBackToTransactionMenu();
    }*/
    
 

}


bool CheckAccessPermition(enMainMenuPermission Permition)
{
    if (CurrentUser.Permission == enMainMenuPermission::pAll)
        return true;
    if ((CurrentUser.Permission & Permition) == Permition)
        return true;
    else
        return false;
}

void ShowAccessDeniedMesage()
{
    cout << "\n----------------------------------------------------\n";
    cout << " Access Denied,\n You dont have access to do this,\n Contact with your Admin.\n";
    cout << "\n----------------------------------------------------\n";

}


//2
void AddClientsScreen()
{
    if (!CheckAccessPermition(enMainMenuPermission::pAdd))
    {
        ShowAccessDeniedMesage();
        return;
    }
    
    char AddMore = 'Y';
    do
    {
        system("cls");
        Head("Add");
        AddNewClint();
        cout << "\nClient added successfully , Do you want to add more client ? y/n ? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

//1
void ListClintsScreen()
{
    if (!CheckAccessPermition(enMainMenuPermission::pList))
    {
        ShowAccessDeniedMesage();
        return;
    }

    vector<stClient> vClients = LoadDataFromFileToVector(ClientsFileName);
    PrintHead(vClients.size());
    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tThere is No Clients Available in the system\n";
    }
    else
    {
        for (stClient& Client : vClients)
        {
            PrintClient2(Client);
        }
    }

}

//5
void FindClientScreen()
{

    if (!CheckAccessPermition(enMainMenuPermission::pFind))
    {
        ShowAccessDeniedMesage();
        return;
    }
   
    Head("Find");
    stClient Client;

    string AcountNumber = ReadString();

    vector <stClient> vClients = LoadDataFromFileToVector(ClientsFileName);

    if (FindClientFromCountNumber(AcountNumber, vClients, Client))
    {
        PrintClient(Client);
        char DeleteClient;
    }
    else
    {
        cout << "\nClient with acount number (" << AcountNumber << ") not foundd\n";
    }
    

}

//3
void DeleteClientScreen()
{
    if (!CheckAccessPermition(enMainMenuPermission::pDelete))
    {
        ShowAccessDeniedMesage();
        return;
    }
    
    Head("Delete");

    string AcountNumber = ReadString();

    vector <stClient> vClients = LoadDataFromFileToVector(ClientsFileName);

    DeleteClientFromAcountNumber(AcountNumber, vClients);
   

}

//4
void UpdateClientScreen()
{
    if (!CheckAccessPermition(enMainMenuPermission::pUpdate))
    {
        ShowAccessDeniedMesage();
        return;
    }

    Head("Update");
    vector<stClient> vClients = LoadDataFromFileToVector(ClientsFileName);
    string AcountNumber = ReadString();
    UpdateClientData(AcountNumber, vClients);
  
}

//6
void ShowEndScreen()
{
    cout << "\n------------------------------------------\n";
    cout << "\tProgram Ends";
    cout << "\n------------------------------------------\n";

}

//T
void GoBackToTransactionMenu()
{
    cout << "\n\nPress any key to go back to Transaction menu...";
    system("pause>0");
    ShowTransactionMenu();
}

//T1
void DepositScreen()
{
    cout << "\n------------------------------------------\n";
    cout << "\t\tDeposit Screen";
    cout << "\n------------------------------------------\n";
    
    double Deposit = 0;
    string AcountNumber = ReadString();
    stClient Client;
    vector<stClient> vClients = LoadDataFromFileToVector(ClientsFileName);
    
    while (!FindClientFromCountNumber(AcountNumber, vClients, Client))
    {
        cout << "\nClient with acount number (" << AcountNumber << ") not foundd\n";
         AcountNumber = ReadString();
    }
    
    PrintClient(Client);
    cout << "\nPlease enter deposit amount : ";
    cin >> Deposit;
  
    DeposetBalanceToClientByAcountNumber(AcountNumber, Deposit, vClients);
       
}
//T2
void WithdrawScreen()
{
    cout << "\n------------------------------------------\n";
    cout << "\t\tWithdraw Screen";
    cout << "\n------------------------------------------\n";
    char Answer;
    double Withdraw = 0;
    string AcountNumber = ReadString();
    stClient Client;
    vector<stClient> vClients = LoadDataFromFileToVector(ClientsFileName);

    while (!FindClientFromCountNumber(AcountNumber, vClients, Client))
    {
        cout << "\nClient with acount number (" << AcountNumber << ") not foundd\n";
        AcountNumber = ReadString();
    }

    PrintClient(Client);
    cout << "\nPlease enter Withdraw amount : ";
    cin >> Withdraw;
    while (Withdraw > Client.AcountBalance)
    {
        cout << "\nAmount Exceed the balance.You can Withdraw up to : " << Client.AcountBalance << endl;
        cout << "\nPlease enter Withdraw amount : ";
        cin >> Withdraw;
    }
        DeposetBalanceToClientByAcountNumber(AcountNumber, Withdraw*-1, vClients);
}
//3
void TotalBalanceScreen()
{
    vector<stClient> vClients = LoadDataFromFileToVector(ClientsFileName);
    double TotalBalance = 0;
    {
        cout << "\n                    Client List (" << vClients.size() << ") Client(s).\n";
        cout << "__________________________________________________________________________\n";
        cout << left << setw(13) << "Acount Number"  << setw(20) << "Client Name"
            << "|" << setw(15) << "Acount Balance" << "|" << endl;
        cout << "__________________________________________________________________________\n";

    }

    
    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tThere is No Clients Available in the system\n";
    }
    else
    {
        for (stClient& Client : vClients)
        {
            TotalBalance += Client.AcountBalance;
            cout << left << setw(13) << Client.AcountNumber << "|" << setw(20)
                << Client.Name << "|"  << setw(15)
                << Client.AcountBalance << "|" << endl;
        }
        cout << "__________________________________________________________________________\n";

        cout << "\n                        Total Acount = " << TotalBalance << endl;
    }
}

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to go back to main menue...";
    system("pause>0");
    ShowMainMenue();
}


//User
void ListUsersScreen()
{
    vector<stUser> vUsers = LoadUsersDataFromFileToVector(UsersFileName);
    cout << "\n                    Client List (" << vUsers.size() << ") Client(s).\n";
    cout << "__________________________________________________________________________\n";
    cout << left  << setw(20) << "User Name"
        << "|" << setw(10) << "Password" << "|" << setw(15) << "Permission" << "|" << endl;
    cout << "__________________________________________________________________________\n";
    
     for (stUser& User : vUsers)
     {
         PrintUser(User);
     }
    
}

void GoBackToMangeUsersMenu()
{
    cout << "\n\nPress any key to go back to Mange Users menu...";
    system("pause>0");
    ShowUserMangeMenu();
}

int ReadPermission()
{
    char Answer;
    int Permission=0;
    cout << "\nDo you want to give full access? y/n? : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }
   
    cout << "\nDo you want to give access to :\n";
    cout << "\nShow Client List?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pList;
    }
    cout << "\nAdd Client ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pAdd;
    }
    cout << "\nDelete Client ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pDelete;
    }
    cout << "\nUpdate Client ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pUpdate;
    }
    cout << "\nFind Client ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pFind;
    }
    cout << "\nTransaction ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pTransaction;
    }
    cout << "\nMange Users ?y/n : ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permission += enMainMenuPermission::pMangeUser;
    }

    return Permission;
    
}

bool isUserExistByUserName(string UserName, string FileName)
{
    vector<stUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stUser User;
        string Line;
        while (getline(MyFile, Line))
        {
            User = ConvertLineToUserRecord(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            vUsers.push_back(User);

        }
        MyFile.close();
    }
    return false;
}

stUser ReadNewUser()
{
    stUser User;

    cout << "\nEnter UserName : ";
    getline(cin >> ws, User.UserName);

    while (isUserExistByUserName(User.UserName, UsersFileName))
    {
        cout << "\nUser with [" << User.UserName << "] already exits ,Enter anether User Name \n";
        cout << "\nEnter UserName : ";
        getline(cin >> ws, User.UserName);
    }

    cout << "\nEnter Password : ";
    getline(cin >> ws, User.Password);
    User.Permission = ReadPermission();
    return User;
}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecoredToLine(User));
}

void AddUsersScreen()
{

    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "\n_________________________________";
        cout << "\n        Add Users Screen";
        cout << "\n_________________________________\n";
        AddNewUser();
        cout << "\nUser added successfully , Do you want to add more User ? y/n ? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            U.MarkToDelete = true;
            return true;
        }
    }
    return false;
}

vector<stUser> SaveUsersDataToFile(string FileName, vector<stUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        string Line;
        for (stUser U : vUsers)
        {
            if (U.MarkToDelete == false)
            {
                Line = ConvertRecoredToLine(U);
                MyFile << Line << endl;
            }
        }
    }
    return vUsers;
}

bool DeleteUserFromUserName(string UserName, vector<stUser>& vUsers)
{
    stUser User;
    if (FindUsertFromUserName(UserName, vUsers, User))
    {

        PrintUser(User);
        char DeleteUser = 'n';

        cout << "\nAre you sure you want delete this User ? y/n ?  ";
        cin >> DeleteUser;
        if (tolower(DeleteUser) == 'y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);
            vUsers = LoadUsersDataFromFileToVector(UsersFileName);
            cout << "\nUser Deleted successfully \n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") not found\n";
        return false;
    }

}

void DeleteUserScreen()
{

    cout << "\n_________________________________";
    cout << "\n        Delete User Screen";
    cout << "\n_________________________________\n";

    string UserName = ReadUserName();
    
    if (UserName == "Admin")
    {
        cout << "\nWe cant Delete Admin\n";
    }
    else
    {
        vector <stUser> vUsers = LoadUsersDataFromFileToVector(UsersFileName);

        DeleteUserFromUserName(UserName, vUsers);
    }


}

stUser ReadUpdateDataUser(string UserName)
{
    stUser User;

    User.UserName = UserName;

    cout << "\nEnter Password : ";
    getline(cin >> ws, User.Password);

    User.Permission = ReadPermission();

    return User;
}

bool UpdateUserData(string UserName, vector<stUser>& vUsers)
{
    stUser User;
    if (FindUsertFromUserName(UserName, vUsers, User))
    {

        PrintUser(User);
        char UpdateUser = 'n';

        cout << "\nAre you sure you want update this User ? y/n ?  ";
        cin >> UpdateUser;
        if (tolower(UpdateUser) == 'y')
        {
            for (stUser& U : vUsers)
            {
                if (U.UserName == UserName)
                {
                    U = ReadUpdateDataUser(UserName);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "\nUser Updeted  successfully \n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") not found\n";
        return false;
    }
}

void UpdateUserScreen()
{
    cout << "\n_________________________________";
    cout << "\n        Update User Screen";
    cout << "\n_________________________________\n";
    vector<stUser> vUsers = LoadUsersDataFromFileToVector(UsersFileName);
    string UserName = ReadUserName();
    UpdateUserData(UserName, vUsers);

}

void FindUserScreen()
{

    cout << "\n_________________________________";
    cout << "\n        Find User Screen";
    cout << "\n_________________________________\n";
    stUser User;

    string UserName = ReadUserName();

    vector <stUser> vUsers = LoadUsersDataFromFileToVector(UsersFileName);

    if (FindUsertFromUserName(UserName, vUsers, User))
    {
        PrintUser(User);
        
    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") not found\n";
    }


}



void PerformMainMenueOptions(enMainOptions Option )
{
    switch (Option)
    {
    case List:
    {
        system("cls");
        ListClintsScreen();
        GoBackToMainMenu();
        break;
    }
    case Add:
    {
        system("cls");
        AddClientsScreen();
        GoBackToMainMenu();
        break;
    }
    case Delete:
    {
        system("cls");
        DeleteClientScreen();
        GoBackToMainMenu();
        break;
    }
    case Update:
    {
        system("cls");
        UpdateClientScreen();
        GoBackToMainMenu();
        break;
    }
    case Find:
    {
        system("cls");
        FindClientScreen();
        GoBackToMainMenu();
        break;
    }
    case Transaction:
    {
        system("cls");
        ShowTransactionMenu();
        GoBackToMainMenu();
        break;
    }
    case MangeUser:
    {
        system("cls");
        ShowUserMangeMenu();
        GoBackToMainMenu();
        break;
    }
    case Logout:
    {
        system("cls");
        LoginScreen();
        break;
    }
    
    }
}

void PerformTransactionOption(enTransactionOption TransactionOption)
{
    switch (TransactionOption)
    {
    case Deposit:
    {
        system("cls");
        DepositScreen();
        GoBackToTransactionMenu();
        break;
    }
    case Withdraw:
    {
        system("cls");
        WithdrawScreen();
        GoBackToTransactionMenu();
        break;
    }
    case TotalBalance:
    {
        system("cls");
        TotalBalanceScreen();
        GoBackToTransactionMenu();
        break;
    }
    case MainMenu:
    {
        
        ShowMainMenue();
        break;
    }
    
    }
}

void PerformMangeUsersOption(enUserMangeOption UserOption)
{
    switch (UserOption)
    {
    case UsersList:
        system("cls");
        ListUsersScreen();
        GoBackToMangeUsersMenu();
        break;
    case AddUser:
        system("cls");
        AddUsersScreen();
        GoBackToMangeUsersMenu();
        break;
    case DeleteUser:
        system("cls");
        DeleteUserScreen();
        GoBackToMangeUsersMenu();
        break;
    case UpdateUser:
        system("cls");
        UpdateUserScreen();
        GoBackToMangeUsersMenu();
        break;
    case FindUser:
        system("cls");
        FindUserScreen();
        GoBackToMangeUsersMenu();
        break;
    case ToMainMenu:
        ShowMainMenue();
        break;
    default:
        break;
    }
}




void ShowMainMenue()
{
    system("cls");
    cout << "\n================================"
        << "\n           Main Menue Screen"
        << "\n================================\n";
    cout << "[1] Show Client List.\n"
        << "[2] Add New Client.\n"
        << "[3] Delete Client.\n"
        << "[4] Update Client Data.\n"
        << "[5] Find Client.\n"
        << "[6] Transaction.\n"
        << "[7] Mange User.\n"
        << "[8] Logout."
        << "\n================================\n";
    
    PerformMainMenueOptions((enMainOptions)ReadChooseNumber("1 to 8"));
    
}

void ShowTransactionMenu()
{
    if (!CheckAccessPermition(enMainMenuPermission::pTransaction))
    {
        ShowAccessDeniedMesage();
        return;
    }

    system("cls");
    cout << "\n================================"
        << "\n      Transaction Menu Screen"
        << "\n================================\n";
    cout << "[1] Deposit.\n"
        << "[2] Withdraw.\n"
        << "[3] Total Balance.\n"
        << "[4] Main Menu.\n"
        << "\n================================\n";

    PerformTransactionOption((enTransactionOption)ReadChooseNumber("1 to 4"));
}

void ShowUserMangeMenu()
{
    if (!CheckAccessPermition(enMainMenuPermission::pMangeUser))
    {
        ShowAccessDeniedMesage();
        return;
    }

    system("cls");
    cout << "\n================================"
        << "\n          Mange Users Menu Screen"
        << "\n================================\n";
    cout << "[1] User List.\n"
        << "[2] Add  User.\n"
        << "[3] Delete User.\n"
        << "[4] Update User Data.\n"
        << "[5] Find User.\n"
        << "[6] Mean Menu."
        << "\n================================\n";

    PerformMangeUsersOption((enUserMangeOption)ReadChooseNumber("1 to 6"));
}

bool LoadUserInfo(string UserName,string Password)
{
    if (FindUsertFromUserNameAndPassword(UserName, Password, CurrentUser))
        return true;
    else
        return false;

}

void LoginScreen()
{
    bool FaildLogin = false;
    string UserName, Password;

    do 
    {
        system("cls");
        cout << "\n================================"
            << "\n           Login Screen"
            << "\n================================\n";
       
        if (FaildLogin)
        {
            cout << "\nInvalaid UserName/Password\n";
        }
        cout << "\nEnter User Name : ";
        cin >> UserName;
        cout << "\nEnter Password : ";
        cin >> Password;
        FaildLogin = !LoadUserInfo(UserName, Password);

    } while (FaildLogin);

   
    ShowMainMenue();

}




int main()
{
   
    LoginScreen();
}

