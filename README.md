# 🏦 BankSphere – Banking Management System

A console-based Banking Management System developed using **C++17**, demonstrating Object-Oriented Programming, authentication, transaction management, and file handling.

## 🚀 Features

### 1. Account Management
- Create Savings and Current accounts.
- Deposit and withdraw money.
- Check account balance.
- Display and search account details.
- Update account holder information.
- Close accounts.

### 2. Authentication & Authorization
- Separate Admin and Customer login.
- Role-based access control.
- Customers can access only their own accounts.

### 3. Transaction Management
- Deposit and withdrawal records.
- Transfer money between accounts.
- Unique transaction IDs.
- Transaction history with timestamps.
- Transaction summaries.

### 4. File Handling
- Persistent account storage.
- Persistent user credentials.
- Transaction history stored in text files.
- Automatically loads saved data when the application starts.

## 🛠️ Tech Stack

- **Language:** C++
- **Standard:** C++17
- **Compiler:** GCC / MinGW
- **Concepts:** OOP, STL, File Handling

## 🧠 OOP Concepts Implemented

- **Encapsulation** – Data protection through classes.
- **Inheritance** – SavingsAccount and CurrentAccount inherit from Account.
- **Abstraction** – Abstract classes and pure virtual functions.
- **Polymorphism** – Runtime method overriding.
- **Smart Pointers** – `unique_ptr` for automatic memory management.

## 📂 Project Structure

```text
BankSphere/
├── main.cpp
├── data/
├── include/
│   ├── Transaction.h
│   ├── Account.h
│   ├── SavingsAccount.h
│   ├── CurrentAccount.h
│   ├── Bank.h
│   ├── User.h
│   ├── Admin.h
│   └── Customer.h
└── src/
    ├── Account.cpp
    ├── SavingsAccount.cpp
    ├── CurrentAccount.cpp
    ├── Bank.cpp
    ├── User.cpp
    ├── Admin.cpp
    └── Customer.cpp
```

## ⚙️ How to Run

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp src/Account.cpp src/SavingsAccount.cpp src/CurrentAccount.cpp src/Bank.cpp src/User.cpp src/Admin.cpp src/Customer.cpp -Iinclude -o BankSphere.exe
```

### Execute (Windows)

```bash
.\BankSphere.exe
```

## 🔐 Default Admin Credentials

- **Username:** `admin`
- **Password:** `admin123`

## ⚠️ Disclaimer

This project is developed for educational purposes. It uses local text files for persistence and stores passwords in plain text. It is not intended for real-world banking or production use.

## 👨‍💻 Author

Developed as a C++ Object-Oriented Programming project.