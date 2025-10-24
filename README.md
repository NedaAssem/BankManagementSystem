# 🏦 Bank Management System (C++ Console Project)

A simple **console-based Bank Management System** built with C++ to simulate basic banking operations like   
user registration, login, account management, and transactions.   
This project demonstrates my learning progress — from **functional programming** to **object-oriented   
programming (OOP)** — using clean, structured code.

---

## 💡 Main Features

- **User Registration:**  
  New users can create their own accounts.

- **User Login System:**  
  Only registered users can log in with their credentials.

- **Permissions & Roles:**  
  - **Admin users** can manage clients, approve transactions, and control user permissions.  
  - **Client users** can check balances, deposit, and withdraw funds.

- **Account Management:**  
  - Create and manage bank accounts  
  - Deposit and withdraw money  
  - View account balance and transaction history  

- **Console Interface:**  
  Simple, text-based interface for easy navigation.


---


## 🧩 Versions

### 1️⃣ Functional Version – `/functional/`
- Implemented using **C++ functions** only  
- Focused on procedural programming, logic, and console I/O  
- Step-by-step implementation with no classes  

### 2️⃣ Object-Oriented Version – `/oop/`
- Refactored using **C++ classes** and **OOP principles**, including:  
  - Classes & Objects  
  - Encapsulation  
  - Inheritance  
  - Polymorphism  
- Cleaner, more maintainable, and modular design  

---


## ⚙️ Technologies Used

| Technology | Purpose |
|-------------|----------|
| C++ | Core programming language |
| Console I/O | User interaction |
| File handling | Saving and loading user data , client data and transection login |
| OOP | Structuring and organizing code |

---


## 📂 Project Structure

BankManagementSystem/   
│   
├── functional/   
│   ├── main.cpp   
│   ├── project.cpp   
│   ├── Users.txt   
│   └── Clients.txt   
│   
└── oop/   
│   ├── main.cpp   
│   ├── Core/    
│     ├── clsUser.h    
│     ├── clsCurrency.h   
│     └── clsClient.h   
│   
│   ├── Lib/   
│     ├── clsDate.h   
│     ├── clsInputValidation.h    
│     ├── clsString.h   
│     └── clsUtil.h  
│   
│   └── Screens/   
│      ├── clsScreen.h   
│      ├── clsMainScreen.h   
│      
│      ├── Users/       
│      │   ├── clsListUsersScreen.h   
│      │   ├── clsAddUserScreen.h   
│      │   └── ... (4 more user screens)   
│      
│      ├── Clients/    
│      │   ├── clsListClientsScreen.h   
│      │   ├── clsAddClientScreen.h    
│      │   └── ... (9 more client screens)   
│      
│      └── Currencies/    
│          ├── clsCurrenciesScreen.h    
│          └── ... (3 more currency screens)  

---


## 🚀 How to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/BankManagementSystem.git

2. Open the project in your favorite C++ IDE (e.g., Code::Blocks, Dev-C++, Visual Studio, or CLion).

3. Build and run either the functional or OOP version.

---

##🔑 Login Information

To access the system, use any of the user credentials listed in the Users.txt file located in the functional or oop folder.
Example (if included in your file):  
   
Username: admin  
Password: 1234   
   
   
📄 You can also edit Users.txt to add or remove users with different permissions.

## 📈 Learning Outcomes

- Through this project, I learned to:

- Build real-world applications using C++ console programming

- Design and implement user login and permission systems

- Understand the difference between functional and OOP design

- Write clean, reusable, and maintainable C++ code

---


## ✨ Future Improvements

- Improve security for user login (password hashing)

- Add Transaction History storage

- Extend features with more banking operations

- Migrate to GUI (C# Windows Forms or Web API)

---

## 📫 Contact

👤 Nedi Assem

📧 nadaalthbit@gmail.com

💼 LinkedIn
 | GitHub

⭐ If you found this project interesting, consider giving it a star!
