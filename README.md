# 🏨 Hotel Management System

A console-based Hotel Management System built in C++ that simulates 
real-world hotel operations — from room booking to revenue tracking.

## 📌 Features

- **Room Booking** — Book Single, Double, or Deluxe rooms by name, 
  date range, and type. Automatically assigns the first available room.
- **Conflict-Free Reservations** — Validates date overlaps before 
  confirming any booking to prevent double-booking.
- **Check-Out** — Releases a room and marks it available instantly.
- **Stay Extension** — Extend a guest's stay by extra days with 
  automatic bill recalculation and conflict checking.
- **Occupancy Report** — Shows total, occupied, and available rooms 
  at a glance.
- **Revenue Report** — Calculates total revenue from all active bookings.
- **View Available Rooms** — Lists all unoccupied rooms with type 
  and price.

## 🏗️ Tech Stack

- **Language:** C++
- **Concepts Used:** STL (vector, algorithm), structs, modular 
  functions, date arithmetic, input validation

## 🏠 Room Categories

| Type    | Rooms       | Price/Night |
|---------|-------------|-------------|
| Single  | 101 – 105   | ₹1,000      |
| Double  | 106 – 110   | ₹2,000      |
| Deluxe  | 201 – 205   | ₹3,000      |

## 🚀 How to Run
```bash
g++ hotel1.cpp -o hotel
./hotel
```

## 📂 Project Structure
```
hotel1.cpp        # Single-file implementation
├── Date          # Struct for check-in/check-out dates
├── Room          # Struct for room info and availability
├── Customer      # Struct for booking details and bill
└── main()        # Menu-driven entry point
```

## 💡 Key Logic

- **Date comparison** uses year → month → day priority ordering
- **Stay duration** calculated as days + months×30 + years×365
- **Bill** = stay days × room price per night, updated on extension
- **Input validation** handles non-numeric menu input gracefully
