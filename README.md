# Bank Management System (C++)

A comprehensive console-based Bank Management System built with C++, featuring multi-user authentication, granular bitwise access permissions, full CRUD operations for clients/users, and transaction processing.

## 🎮 Features
- **User Authentication & Login:** Secure system login with session tracking.
- **Bitwise Permission System:** Granular access control allowing specific permissions for each user (Add, Edit, Delete, Transactions, etc.).
- **Client Management (CRUD):** Show, Add, Update, Delete, and Find client accounts.
- **Transactions Menu:**
  - 💵 **Deposit:** Add funds to client accounts.
  - 💸 **Withdraw:** Withdraw funds with built-in balance checks.
  - 📊 **Total Balances:** View combined bank balance reports.
- **User Management Menu:** Complete controls to manage system users and assign access rights.
- **Persistent Data Storage:** Automatic reading and writing of data using delimited text files (`#//#`).

## 🔑 Demo Credentials
You can test the permission system using these pre-configured user credentials:

| Role | Username | Password | Access Level |
| :--- | :--- | :--- | :--- |
| **Admin** | `Mohammad Laith Alhafez` | `mlh@2007` | Full Access (All Permissions) |
| **Restricted User** | `User4` | `4444` | Limited Access |

## 🛠️ Code & Concepts
- **Clean Code & SRP:** Modular function structure following the Single Responsibility Principle.
- **Bitwise Operations:** Used for checking and setting individual user permission flags (`CurrentUser.Permissions & Permission`).
- **Data Structures & Enums:** Structs for data modeling (`stClientInfo`, `stUserInfo`) and Enums for clean state management.
- **File I/O & Parsing:** Custom string parsing (`vSplitFunction`) and file streams (`fstream`) for seamless data handling.

## 🚀 How to Run

1. Open the project in **Visual Studio** or any C++ IDE.
2. Ensure `AllClientsData.txt` and `AllUsersData.txt` are in the project folder.
3. Compile and run the `Bank System.cpp` file.
4. Log in using one of the credentials above!
