# 📚 Library Management System (C++)

A console-based **Library Management System** built in C++ that efficiently manages books, members, and borrowing records using **Object-Oriented Programming (OOP)** and **file handling** for persistent data storage.

---

## 📋 Features

| Feature | Description |
|---|---|
| ✅ Add / Update / Delete Books | Full book catalog management |
| ✅ Search by Title or Author | Case-insensitive keyword search |
| ✅ Register / Remove Members | Member registration with borrow-limit enforcement |
| ✅ Issue Books | Assign books to members with date tracking |
| ✅ Return Books | Process returns and update availability |
| ✅ Borrow Records | Full history + active issues view |
| ✅ Persistent Storage | Data saved to `.dat` files, reloaded on startup |
| ✅ Input Validation | Guards against invalid input throughout |

---

## 🏗️ OOP Design

### Classes

| Class | Responsibility |
|---|---|
| `Book` | Stores book details, manages copy availability |
| `Member` | Stores member info, enforces 3-book borrow limit |
| `BorrowRecord` | Tracks issue/return with dates |
| `Library` | Main controller — all menus, CRUD, file I/O |

---

## 🗂️ Project Structure

```
library-management-system/
├── library_management.cpp   # Full C++ source code
├── Makefile                 # Build configuration
├── .gitignore               # Git exclusions
└── README.md                # Project documentation
```

> **Runtime data files** (`books.dat`, `members.dat`, `records.dat`) are created automatically when you run the program — they are excluded from Git via `.gitignore`.

---

## ⚙️ How to Compile & Run

### Using Make (recommended)
```bash
make
./lms
```

### Using g++ directly
```bash
g++ -std=c++17 -Wall -Wextra -o lms library_management.cpp
./lms
```

### On Windows (MinGW)
```bash
g++ -std=c++17 -o lms.exe library_management.cpp
lms.exe
```

---

## 🖥️ Application Flow

```
Main Menu
├── 1. Book Management
│       ├── Add Book
│       ├── Display All Books
│       ├── Search (Title / Author)
│       ├── Update Book
│       └── Delete Book
├── 2. Member Management
│       ├── Register Member
│       ├── Display All Members
│       ├── Search Member
│       └── Remove Member
├── 3. Issue / Return Books
│       ├── Issue Book to Member
│       ├── Return Book from Member
│       ├── View All Records
│       └── View Active Issues
└── 4. Exit
```

---

## 💾 Data Storage

Three separate data files handle persistence:

| File | Contents |
|---|---|
| `books.dat` | Book catalog with availability counts |
| `members.dat` | Member profiles and current borrow counts |
| `records.dat` | Full issue/return history with dates |

---

## 📌 Requirements

- C++17 or later
- GCC / G++ compiler (Linux, macOS, or Windows via MinGW)

---

## 🧪 Sample Output

```
══════════════════════════════════════════════════════════════
         CITY PUBLIC LIBRARY
══════════════════════════════════════════════════════════════
  1. Book Management
  2. Member Management
  3. Issue / Return Books
  4. Exit
──────────────────────────────────────────────────────────────
  Choice: 3

  ┌─ Borrow / Return ──────────────────────
  │  1. Issue Book to Member
  │  2. Return Book from Member
  ...

  ✔  "The Great Gatsby" issued to Alice on 2025-06-01
```

---

## 👨‍💻 Author

Developed as part of a C++ OOP and File Handling assignment.
