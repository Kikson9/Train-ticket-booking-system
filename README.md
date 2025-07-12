# Train Ticket Booking System (C Project)

A command-line based train ticket booking system built in C, using **modular file structure**, **dynamic memory allocation**, and clean separation of logic for both admin and user roles.

---

## 📌 Project Overview

This system simulates a real-world train booking platform where:

- Admins can add, delete, and view train schedules
- Users can book tickets, view their orders, cancel bookings, and download tickets
- All data is saved persistently to local files

It was built for a university C programming course and showcases practical use of:
- Structures (`struct`)
- Dynamic arrays (`malloc`, `realloc`)
- File I/O (`fscanf`, `fprintf`)
- Time handling (`time.h`, `strftime`)
- Multi-file architecture with headers and source files

---

## 🗂️ File Structure

```
Train Ticket Booking System/
├── Sources/
│   ├── main.c         # Program entry, menu controller
│   ├── admin.c        # Admin features (Add, View, Delete trains)
│   └── user.c         # User features (Book, View, Cancel, Download)
├── Headers/
│   ├── admin.h        # Admin function declarations
│   └── user.h         # Shared structs, global vars, user function declarations
├── data/
│   ├── trains.txt     # Stores train schedule data
│   └── orders.txt     # Stores user booking data
```

✅ Each file has a clearly defined role, following modular design principles.

---

## 🚀 Features

### 👤 User Panel
- View available trains
- Book train tickets
- View personal bookings
- Cancel tickets
- Download tickets as text

### 🔐 Admin Panel
- Add new trains
- View all trains
- Delete train schedules

---

## ⚙️ How It Works

- On program start, trains are loaded from `trains.txt` into a **dynamically allocated array** of structs.
- Booking details are written to `orders.txt`, and include a **timestamp**.
- Dynamic memory ensures flexible scaling as more trains are added — no hard-coded array sizes.
- Shared variables like `Train *trains`, `trainCount`, and `trainCapacity` are managed safely using `extern` in header files.

---

## 🧠 Key Concepts Used

- ✅ Dynamic Arrays (`malloc`, `realloc`)
- ✅ Global Shared Variables (declared with `extern`)
- ✅ Time Handling (`time()` and `strftime()`)
- ✅ Modular Architecture (clean separation of `.c` and `.h` files)
- ✅ Persistent File Storage (with CSV-like formatting)

---

## 💡 What I Learned

Working on this project helped me:
- Understand real memory allocation patterns
- Debug across multiple files and header chains
- Write readable, maintainable C code
- Simulate realistic software design in C — not just console menus

---

## 📸 Sample Output

```
==== Train Ticket Booking System ====
1. Admin Panel
2. User Panel
3. Exit
Enter your choice: 
```

---

## 🛠️ Compile & Run

> This project was built and tested in **Code::Blocks IDE**.

To compile manually using GCC:
```bash
gcc Sources/*.c -o train_booking
./train_booking
```

---

## 📥 Data Note

All files in the `data/` folder will be created or updated at runtime:
- Make sure the folder exists before running
- No external database needed — it’s all plain `.txt`

---

## ✅ Status: **Complete & Functional**
