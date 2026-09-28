#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

string ClientsFile = "AllClientsData.txt";
string UsersFile = "AllUsersData.txt";

struct stClientInfo
{
    string Name = "";
    string PINCode = "";
    string PhoneNum = "";
    string AccountNum = "";
    double AccountBalance = 0;
    bool DeletionFlag = false;
};

struct stUserInfo
{
    string UserName = "";
    string Password = "";
    bool DeletionFlag = false;
    int Permissions = 0;
};

stUserInfo CurrentUser;

string ReadString(string Message)
{
    string S;

    cout << Message;
    getline(cin >> ws, S);

    return S;
}

bool IsAccountNumberAvailable(string AccNum, vector<stClientInfo>& Clients)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccNum)
            return false;
    }
    return true;
}

bool IsUserNameAvailable(string UserName, vector<stUserInfo>& Users)
{

    for (stUserInfo& C : Users)
    {
        if (C.UserName == UserName)
            return false;
    }
    return true;
}

string ReadNewAccountNumber(vector<stClientInfo>& Clients)
{
    string Num;

    do
    {
        cout << "\nPlease Enter Unique Account Number : ";
        getline(cin >> ws, Num);



    } while (!IsAccountNumberAvailable(Num, Clients));

    return Num;
}

string ReadNewUserName(vector<stUserInfo>& Users)
{
    string UserName;

    do
    {
        cout << "\nPlease Enter Unique UserName : ";
        getline(cin >> ws, UserName);



    } while (!IsUserNameAvailable(UserName, Users));

    return UserName;
}

double ReadDoubleNumber(string Message)
{
    double D;
    cout << Message;
    cin >> D;
    return D;
}

void PrintMainMenue()
{
    system("cls");
    cout << "=====================================================" << endl;
    cout << " Logged In As : " << CurrentUser.UserName << endl;
    cout << "=====================================================" << endl;
    cout << "                    Bank Main Menue                     " << endl;
    cout << "=====================================================" << endl;
    cout << " 1-Show All Clients List" << endl;
    cout << " 2-Add Client" << endl;
    cout << " 3-Delete Client" << endl;
    cout << " 4-Update Client" << endl;
    cout << " 5-Find Client" << endl;
    cout << " 6-Transactions Menue" << endl;
    cout << " 7-Manage Users Menue" << endl;
    cout << " 8-Logout" << endl;
    cout << " 9-End Program" << endl;
    cout << "=====================================================" << endl;
}

vector<string> vSplitFunction(string S, string Seperator = "#//#")
{
    string SWord = "";
    short Pos = 0;
    vector<string> V;

    while ((Pos = S.find(Seperator)) != std::string::npos)
    {
        if ((SWord = S.substr(0, Pos)) != "")
        {
            V.push_back(SWord);
        }
        S.erase(0, Pos + Seperator.length());
    }
    if (S != "")
        V.push_back(S);

    return V;
}

stUserInfo GetUserInfoFromLineToStruct(string S, string Seperator = "#//#")
{
    stUserInfo User;
    vector<string> vSplit = vSplitFunction(S);

    User.UserName = vSplit[0];
    User.Password = vSplit[1];
    User.Permissions = stoi(vSplit[2]);

    return User;
}

stClientInfo GetClientInfoFromLineToStruct(string S, string Seperator = "#//#")
{
    stClientInfo Client;
    vector<string> vSplit = vSplitFunction(S);

    Client.AccountNum = vSplit[0];
    Client.PINCode = vSplit[1];
    Client.Name = vSplit[2];
    Client.PhoneNum = vSplit[3];
    Client.AccountBalance = stod(vSplit[4]);

    return Client;
}

vector<stClientInfo> LoadClientsInfoFromFileToVector(string FileName, string Seperator = "#//#")
{
    fstream MyFile;
    vector<stClientInfo> vClients;
    stClientInfo Client;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";
        while (getline(MyFile, Line))
        {
            Client = GetClientInfoFromLineToStruct(Line);
            vClients.push_back(Client);
        }
    }
    return vClients;
}

vector<stUserInfo> LoadUsersInfoFromFileToVector(string FileName, string Seperator = "#//#")
{
    fstream MyFile;
    vector<stUserInfo> vUsers;
    stUserInfo User;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";
        while (getline(MyFile, Line))
        {
            User = GetUserInfoFromLineToStruct(Line);
            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return vUsers;
}

enum enMenueOptions 
{ eClientsList = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogout = 8, eEndProgram = 9 };

enum enTransactionsOptions
{
    eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, etMainMenue = 4
};

enum enManageUsersOptions
{eUsersList = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, emMainMenue = 6 };    

enum enUserPermissions
{epFullAccess = -1, epClientsList = 1, epAddClient = 2, epDeleteClient = 4, epUpdateClient = 8, epFindClient = 16, epTransactionsMenue = 32, epManageUsersMenue = 64 };

bool CheckPermission(enUserPermissions Permission)
{
    return (CurrentUser.Permissions & Permission) == Permission;
}

enMenueOptions GetUserMenueOption(short From, short To)
{
    short S;

    do
    {
        cout << "Please Enter Your Choice ? ";
        cin >> S;

    } while (S < From || S > To);

    return enMenueOptions(S);
}

enTransactionsOptions GetUserTransactionsOption(short From, short To)
{
    short S;

    do
    {
        cout << "Please Enter Your Choice ? ";
        cin >> S;

    } while (S < From || S > To);

    return enTransactionsOptions(S);
}

enManageUsersOptions GetUserManageUsersOption(short From, short To)
{
    short S;
    
    do
    {
        cout << "Please Enter Your Choice ? ";
        cin >> S;
    
    } while (S < From || S > To);
    
    return enManageUsersOptions(S);
}

void PrintClientInfo(stClientInfo& Client)
{
    cout << "\nThe Following Are Client Info : \n" << endl;

    cout << "Account Number  : " << Client.AccountNum << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "PIN Code        : " << Client.PINCode << endl;
    cout << "Phone Number    : " << Client.PhoneNum << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
}

void PrintUserInfo(stUserInfo& User)
{
    cout << "\nThe Following Are User Info : \n" << endl;

    cout << "UserName     : " << User.UserName << endl;
    cout << "Password     : " << User.Password << endl;
    cout << "Permetions   : " << User.Permissions << endl;
}

void ShowAllClientsInfo(vector<stClientInfo>& vClients)
{
    system("cls");

    cout << "                     Client List (" << vClients.size() << ") Client(s)";
    cout << "\n-----------------------------------------------------------------------------------" << endl;
    cout << "| Acount Number | PIN Code | Client Name                | Phone          | Balance  " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;

    for (stClientInfo& C : vClients)
    {
        cout << left
            << "| " << setw(14) << C.AccountNum
            << "| " << setw(9) << C.PINCode
            << "| " << setw(27) << C.Name
            << "| " << setw(15) << C.PhoneNum
            << "| " << C.AccountBalance << endl;
    }
    cout << "-----------------------------------------------------------------------------------" << endl;

    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

stClientInfo ReadNewClientInfo(vector<stClientInfo>& Clients)
{
    stClientInfo C;

    C.AccountNum = ReadNewAccountNumber(Clients);
    C.Name = ReadString("Please Enter Name : ");
    C.PINCode = ReadString("Please Enter PIN Code : ");
    C.PhoneNum = ReadString("Please Enter Phone Number : ");
    C.AccountBalance = ReadDoubleNumber("Please Enter Account Balance : ");

    return C;
}

short ReadUserPermissions()
{
    char Per = 'n';
    short Permision = 0;

    cout << "Do You Want To Give The User All Permisions ? ";
    cin >> Per;

    if (toupper(Per) == 'Y')
    {
        Permision = -1;
    }
    else
    {
        cout << "Do You Want To Give The User Show Clients Permision ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 1;

        cout << "Do You Want To Give The User Add Client Permision ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 2;

        cout << "Do You Want To Give The User Delete Client Permision ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision  += 4;

        cout << "Do You Want To Give The User Update Client Permision ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 8;

        cout << "Do You Want To Give The User Find Client Permision ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 16;

        cout << "Do You Want To Give The User Access To Transactions Menue  ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 32;

        cout << "Do You Want To Give The User Access To Manage Users Menue  ? ";
        cin >> Per;
        if (toupper(Per) == 'Y')
            Permision += 64;
    }

    return Permision;
}

stUserInfo ReadNewUserInfo(vector<stUserInfo>& Users)
{
    stUserInfo User;

    User.UserName = ReadNewUserName(Users);
    User.Password = ReadString("Please Enter Strong Password : ");
    User.Permissions = ReadUserPermissions();

    return User;
}

string ConvertClientDataToOneLine(stClientInfo C, string Seperator = "#//#")
{
    string S = "";

    S = C.AccountNum + Seperator + C.PINCode + Seperator + C.Name
        + Seperator + C.PhoneNum + Seperator + to_string(C.AccountBalance);

    return S;
}

string ConvertUserDataToOneLine(stUserInfo C, string Seperator = "#//#")
{
    string S = "";

    S = C.UserName + Seperator + C.Password + Seperator + to_string(C.Permissions);

    return S;
}

void AddClientFun(string FileName, vector<stClientInfo>& Clients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        stClientInfo Client;
        char More = 'n';
        do
        {
            system("cls");

            cout << "----------------------------------------------" << endl;
            cout << "                Add Client Screen             " << endl;
            cout << "----------------------------------------------" << endl;


            Client = ReadNewClientInfo(Clients);
            MyFile << ConvertClientDataToOneLine(Client) << endl;
            Clients.push_back(Client);

            cout << "\nClient Added Successfully" << endl;

            cout << "\n Do You Want To Add More Clients ? ";
            cin >> More;

        } while (toupper(More) == 'Y');

        MyFile.close();
    }

}

void AddUserFun(string FileName, vector<stUserInfo>& Users)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        stUserInfo User;
        char More = 'n';
        do
        {
            system("cls");

            cout << "----------------------------------------------" << endl;
            cout << "                Add User Screen             " << endl;
            cout << "----------------------------------------------" << endl;


            User = ReadNewUserInfo(Users);
            MyFile << ConvertUserDataToOneLine(User) << endl;
            Users.push_back(User);

            cout << "\nUser Added Successfully" << endl;

            cout << "\n Do You Want To Add More Clients ? ";
            cin >> More;

        } while (toupper(More) == 'Y');

        MyFile.close();
    }

}

bool FindClientByAccountNum(string AccNum, vector<stClientInfo>& Clients, stClientInfo& Client)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccNum)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUserName(string UserName, vector<stUserInfo>& Users, stUserInfo& User)
{
    for (stUserInfo& C : Users)
    {
        if (C.UserName == UserName)
        {
            User = C;
            return true;
        }
    }
    return false;
}

void MarkClientToDelete(string AccNum, vector<stClientInfo>& Clients)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccNum)
        {
            C.DeletionFlag = true;
            return;
        }
    }
}

void MarkUserToDelete(string UserName, vector<stUserInfo>& Users)
{
    for (stUserInfo& C : Users)
    {
        if (C.UserName == UserName)
        {
            C.DeletionFlag = true;
            return;
        }
    }
}

void SaveClientsDataToFile(string FileName, vector<stClientInfo>& Clients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClientInfo& C : Clients)
        {
            if (!C.DeletionFlag)
            {
                MyFile << ConvertClientDataToOneLine(C) << endl;
            }
        }

        MyFile.close();
    }
}

void SaveUsersDataToFile(string FileName, vector<stUserInfo>& Users)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stUserInfo& C : Users)
        {
            if (!C.DeletionFlag)
            {
                MyFile << ConvertUserDataToOneLine(C) << endl;
            }
        }

        MyFile.close();
    }
}

void DeleteClientByAccountNum(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "---------------------------------------" << endl;
    cout << "           Delete Client Screen        " << endl;
    cout << "---------------------------------------" << endl;

    string AccNum = ReadString("Please Enter Account Number : ");
    stClientInfo Client;
    char Sure;

    if (FindClientByAccountNum(AccNum, Clients, Client))
    {
        PrintClientInfo(Client);

        cout << "\n Are You Sure You Want To Delete This Client ?? : ";
        cin >> Sure;

        if (toupper(Sure) == 'Y')
        {
            MarkClientToDelete(AccNum, Clients);
            SaveClientsDataToFile(ClientsFile, Clients);
            Clients = LoadClientsInfoFromFileToVector(ClientsFile);
            cout << "Client Has Been Deleted...." << endl;

            cout << "\nPress Any Key To Go Back To Main Menue" << endl;
            system("pause > 0");
        }
    }
    else
    {
        cout << "\n Client With Account Number " << AccNum << " Not Found ): " << endl;

        cout << "\nPress Any Key To Go Back To Main Menue" << endl;
        system("pause > 0");
    }
}

void DeleteUserByUserName(vector<stUserInfo>& Users)
{
    system("cls");
    cout << "---------------------------------------" << endl;
    cout << "           Delete User Screen        " << endl;
    cout << "---------------------------------------" << endl;

    string UserName = ReadString("Please Enter UserName : ");
    stUserInfo User;
    char Sure;

    if (FindUserByUserName(UserName, Users, User))
    {
        if (User.UserName == "Laith Alhafez")
        {
            cout << "You Can't Delete The Admin -_- " << endl;
            cout << "\nPress Any Key To Go Back To Main Menue" << endl;

            system("pause > 0");
            return;
        }

        PrintUserInfo(User);

        cout << "\n Are You Sure You Want To Delete This User ?? : ";
        cin >> Sure;

        if (toupper(Sure) == 'Y')
        {
            MarkUserToDelete(UserName, Users);
            SaveUsersDataToFile(UsersFile, Users);
            Users = LoadUsersInfoFromFileToVector(UsersFile);
            cout << "User Has Been Deleted...." << endl;
        }
    }
    else
    {
        cout << "\n User With UserName " << UserName << " Not Found ): " << endl;
    }

    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void UpdateClientInfo(string AccNum, vector<stClientInfo>& Clients)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccNum)
        {
            C.PINCode = ReadString("Please Enter New PIN Code : ");
            C.Name = ReadString("Please Enter New Name : ");
            C.PhoneNum = ReadString("Please Enter New Phone Number : ");
            C.AccountBalance = ReadDoubleNumber("Please Enter New Account Balance : ");
            return;
        }
    }
}

void UpdateUserInfo(string UserName, vector<stUserInfo>& Users)
{
    for (stUserInfo& C : Users)
    {
        if (C.UserName == UserName)
        {
            C.UserName = ReadString("Please Enter New UserName : ");
            C.Password = ReadString("Please Enter New Password : ");
            C.Permissions = ReadUserPermissions();

            return;
        }
    }
}

void UpdateClientFun(vector <stClientInfo>& Clients)
{
    system("cls");
    cout << "--------------------------------------" << endl;
    cout << "         Update Client Screen" << endl;
    cout << "--------------------------------------" << endl;

    string AccNum = ReadString("Please Enter Account Number : ");
    stClientInfo Client;
    if (FindClientByAccountNum(AccNum, Clients, Client))
    {
        PrintClientInfo(Client);
        char Sure;
        cout << "\n Are You Sure You Want To Update This Client? ";
        cin >> Sure;
        if (toupper(Sure) == 'Y')
        {
            UpdateClientInfo(AccNum, Clients);
            SaveClientsDataToFile(ClientsFile, Clients);
            cout << "\n Client Info Updated Successfully...." << endl;
        }
    }
    else
    {
        cout << "\nClient Was Not Found ):" << endl;
    }
    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void UpdateUserFun(vector <stUserInfo>& Users)
{
    system("cls");
    cout << "--------------------------------------" << endl;
    cout << "         Update User Screen" << endl;
    cout << "--------------------------------------" << endl;

    string UserName = ReadString("Please Enter UserName : ");
    stUserInfo User;
    if (FindUserByUserName(UserName, Users, User))
    {
        PrintUserInfo(User);
        char Sure;
        cout << "\n Are You Sure You Want To Update This User? ";
        cin >> Sure;
        if (toupper(Sure) == 'Y')
        {
            UpdateUserInfo(UserName, Users);
            SaveUsersDataToFile(UsersFile, Users);
            cout << "\n User Info Updated Successfully...." << endl;
        }
    }
    else
    {
        cout << "\nClient Was Not Found ):" << endl;
    }
    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void FindClientFun(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "                 Find Client Screen" << endl;
    cout << "---------------------------------------------------" << endl;

    string AccNum = ReadString("\nPlease Enter Client Account Number To Find : ");
    stClientInfo Client;
    if (FindClientByAccountNum(AccNum, Clients, Client))
    {
        cout << "Client Was Found (: " << endl;
        PrintClientInfo(Client);
    }
    else
    {
        cout << "Client Was Not Found ):" << endl;
    }

    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void FindUserFun(vector<stUserInfo>& Users)
{
    system("cls");
    cout << "---------------------------------------------------" << endl;
    cout << "                 Find User Screen" << endl;
    cout << "---------------------------------------------------" << endl;

    string UserName = ReadString("\nPlease Enter UserName To Find : ");
    stUserInfo User;
    if (FindUserByUserName(UserName, Users, User))
    {
        cout << "User Was Found (: " << endl;
        PrintUserInfo(User);
    }
    else
    {
        cout << "User Was Not Found ):" << endl;
    }

    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void PrintTransactionsMenue()
{
    system("cls");
    cout << "-------------------------------------------------" << endl;
    cout << "                Transactions Menue" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " 1-Deposit" << endl;
    cout << " 2-Withdraw" << endl;
    cout << " 3-Total Balances" << endl;
    cout << " 4-Main Menue" << endl;
    cout << "-------------------------------------------------" << endl;

}

void Deposit(double Amount, string AccNum, vector<stClientInfo>& Clients)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccNum)
        {
            C.AccountBalance += Amount;
            return;
        }
    }
}

void DepositByAccountNumber(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "-----------------------------------------------------" << endl;
    cout << "                   Deposit Screen" << endl;
    cout << "-----------------------------------------------------" << endl;

    string AccNum = ReadString("Please Enter Account Number : ");
    stClientInfo Client;

    if (FindClientByAccountNum(AccNum, Clients, Client))
    {
        cout << "\n Client Was Found " << endl;
        PrintClientInfo(Client);

        double Amount = ReadDoubleNumber("Please Enter Amount To Deposit : ");
        char Sure;

        cout << "\n\n Are You Sure ?? ";
        cin >> Sure;
        if (toupper(Sure) == 'Y')
        {
            Deposit(Amount, AccNum, Clients);
            SaveClientsDataToFile(ClientsFile, Clients);
            cout << "\nSuccessfully Deposited...." << endl;

            cout << "\nPress Any Key To Go Back To Transactions Menue";
            system("pause>0");
        }
    }
    else
    {
        cout << "\nClient Was Not Found ): " << endl;

        cout << "\nPress Any Key To Go Back To Transactions Menue";
        system("pause>0");

    }

}

double ReadWithdrawAmmount(stClientInfo& Client)
{
    double D;

    cout << "Please Enter Amount To Withdraw : ";
    cin >> D;

    while (D > Client.AccountBalance)
    {
        cout << "\nNo Enough Cash, You Can Withdraw Up To " << Client.AccountBalance << " ,Try Again : ";
        cin >> D;
    }
    return D;
}

void WithdrawByAccountNumber(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "-----------------------------------------------------" << endl;
    cout << "                   Withdraw Screen" << endl;
    cout << "-----------------------------------------------------" << endl;

    string AccNum = ReadString("Please Enter Account Number : ");
    stClientInfo Client;

    if (FindClientByAccountNum(AccNum, Clients, Client))
    {
        cout << "\n Client Was Found " << endl;
        PrintClientInfo(Client);

        double Amount = ReadWithdrawAmmount(Client);
        char Sure;

        cout << "\n\n Are You Sure ?? ";
        cin >> Sure;
        if (toupper(Sure) == 'Y')
        {
            Deposit(Amount * -1, AccNum, Clients);
            SaveClientsDataToFile(ClientsFile, Clients);
            cout << "\nSuccessfully Withdrawed...." << endl;

            cout << "\nPress Any Key To Go Back To Transactions Menue";
            system("pause>0");
        }
    }
    else
    {
        cout << "\nClient Was Not Found ): " << endl;

        cout << "\nPress Any Key To Go Back To Transactions Menue";
        system("pause>0");

    }


}

double CalculateAllClientsBalances(vector<stClientInfo>& Clients)
{
    double Sum = 0;

    for (stClientInfo C : Clients)
    {
        Sum += C.AccountBalance;
    }
    return Sum;
}

void ShowAllBalances(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "                  Clients List (" << Clients.size() << ") Client(s)" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "| Account Number       | Name                        | Balance               " << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    for (stClientInfo& C : Clients)
    {
        cout << left << "| " << setw(21) << C.AccountNum << "| " << 
            
        setw(28) << C.Name << "| " << setw(22) << C.AccountBalance << endl;
    }
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "                      Total Balances = " << CalculateAllClientsBalances(Clients) << endl;

    cout << "\nPress Any Key To Go Back To Transactions Menue ";
    system("pause > 0");
}

void PrintManageUsersMenue()
{
    system("cls");
    cout << "==========================================" << endl;
    cout << "            Manage Users Menue" << endl;
    cout << "==========================================" << endl;
    cout << " 1-Show All Users List" << endl;
    cout << " 2-Add User" << endl;
    cout << " 3-Delete User" << endl;
    cout << " 4-Update User" << endl;
    cout << " 5-Find User" << endl;
    cout << " 6-Main Menue" << endl;
    cout << "==========================================" << endl;

}

void RespondToTransactionsMenue(enTransactionsOptions UserOption, vector<stClientInfo>& Clients)
{
    switch (UserOption)
    {
        case enTransactionsOptions::eDeposit:
        {
            DepositByAccountNumber(Clients);
            break;
        }
        case enTransactionsOptions::eWithdraw:
        {
            WithdrawByAccountNumber(Clients);
            break;
        }
        case enTransactionsOptions::eTotalBalances:
        {
            ShowAllBalances(Clients);
            break;
        }
    }
}

void StartTransacionsMenue(vector<stClientInfo>& Clients)
{
    enTransactionsOptions UserOption;
    do
    {
        PrintTransactionsMenue();
        UserOption = GetUserTransactionsOption(1, 4);
        RespondToTransactionsMenue(UserOption, Clients);

    } while (UserOption != enTransactionsOptions::etMainMenue);

}

void ShowAllUsersInfo(vector<stUserInfo>& vUsers)
{
    system("cls");

    cout << "                     Users List (" << vUsers.size() << ") User(s)";
    cout << "\n-----------------------------------------------------------------------------------" << endl;
    cout << "| UserName                 | Password                | Permesions                    " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;

    for (stUserInfo& C : vUsers)
    {
        cout << left
            << "| " << setw(25) << C.UserName
            << "| " << setw(24) << C.Password
            << "| " << setw(10) << C.Permissions
            << endl;
    }       
    cout << "-----------------------------------------------------------------------------------" << endl;

    cout << "\nPress Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");

}

void RespondToManageUsersMenue(enManageUsersOptions UserOption, vector<stUserInfo>& Users)
{
    switch (UserOption)
    {
        case enManageUsersOptions::eUsersList:
            {
            ShowAllUsersInfo(Users);
            break;
            }

        case enManageUsersOptions::eAddUser:
        {
            AddUserFun(UsersFile, Users);
            break;
        }

        case enManageUsersOptions::eDeleteUser:
        {
            DeleteUserByUserName(Users);
            break;
        }

        case enManageUsersOptions::eFindUser:
        {
            FindUserFun(Users);
            break;
        }

        case enManageUsersOptions::eUpdateUser:
        {
            UpdateUserFun(Users);
            break;
        }
    }
}

void StartManageUsersMenue(vector<stUserInfo>& Users)
{
    enManageUsersOptions UserOption;

    do
    {
        PrintManageUsersMenue();
        UserOption = GetUserManageUsersOption(1, 6);
        RespondToManageUsersMenue(UserOption, Users);

    } while (UserOption != enManageUsersOptions::emMainMenue);

}

void PrintAccessDeniedMessage()
{
    system("cls");
    cout << "Sorry, Access Denied.." << endl;
    cout << "Call Your Admin To Help You " << endl;

    cout << "Press Any Key To Go Back To Main Menue" << endl;
    system("pause > 0");
}

bool IsTrueLoginInfo(vector<stUserInfo>& Users, stUserInfo& User, string UserName, string Password)
{
    for (stUserInfo& U : Users)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            return true;
        }
    }
    return false;
}

void Login(vector<stUserInfo>& Users)
{
    system("cls");
    cout << "========================================" << endl;
    cout << "              Login Screen" << endl;
    cout << "========================================" << endl;

    string UserName = ReadString("Please Enter UserName : ");
    string Password = ReadString("Please Enter Password : ");

    while (!IsTrueLoginInfo(Users, CurrentUser, UserName, Password))
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "              Login Screen" << endl;
        cout << "========================================" << endl;
        cout << "Wrong UserName Or Password, Try Again" << endl;

        UserName = ReadString("Please Enter UserName : ");
        Password = ReadString("Please Enter Password : ");
    }

}

void RespondToMainMenue(enMenueOptions UserChoice, vector<stClientInfo>& Clients, vector<stUserInfo>& Users)
{
    switch (UserChoice)
    {
        case enMenueOptions::eClientsList :
        {
            if (CheckPermission(enUserPermissions::epClientsList))
            {
                ShowAllClientsInfo(Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eAddClient:
        {
            if (CheckPermission(enUserPermissions::epAddClient))
            {
                AddClientFun(ClientsFile, Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eDeleteClient:
        {
            if (CheckPermission(enUserPermissions::epDeleteClient))
            {
                DeleteClientByAccountNum(Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eUpdateClient:
        {
            if (CheckPermission(enUserPermissions::epUpdateClient))
            {
                UpdateClientFun(Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eFindClient:
        {
            if (CheckPermission(enUserPermissions::epFindClient))
            {
                FindClientFun(Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eTransactions:
        {
            if (CheckPermission(enUserPermissions::epTransactionsMenue))
            {
                StartTransacionsMenue(Clients);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;

        }

        case enMenueOptions::eManageUsers:
        {
            if (CheckPermission(enUserPermissions::epManageUsersMenue))
            {
                StartManageUsersMenue(Users);
            }
            else
            {
                PrintAccessDeniedMessage();
            }
            break;
        }

        case enMenueOptions::eLogout:
        {
            Login(Users);
            break;
        }
    }
}

void StartProgram()
{
    vector<stClientInfo> Clients = LoadClientsInfoFromFileToVector(ClientsFile);
    vector<stUserInfo> Users = LoadUsersInfoFromFileToVector(UsersFile);

    enMenueOptions UserOption;

    Login(Users);

    do
    {
        PrintMainMenue();
        UserOption = GetUserMenueOption(1, 9);
        RespondToMainMenue(UserOption, Clients, Users);

    } while (UserOption != enMenueOptions::eEndProgram);

}

int main()
{
    StartProgram();

    return 0;
}