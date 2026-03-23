#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

struct Date
{
    int day, month, year;
};

struct Room
{
    int number;
    string type;
    int price;
    bool isOccupied;
};

struct Customer
{
    string name;
    int roomNumber;
    Date checkIn, checkOut;
    int bill;
};

vector<Room> rooms;
vector<Customer> bookings;

bool isDateBefore(Date d1, Date d2)
{
    if (d1.year != d2.year)
        return d1.year < d2.year;
    if (d1.month != d2.month)
        return d1.month < d2.month;
    return d1.day < d2.day;
}

int calculateStayDays(Date in, Date out)
{
    return out.day - in.day + (out.month - in.month) * 30 + (out.year - in.year) * 365;
}

int getRoomPrice(int roomNumber)
{
    for (Room &room : rooms)
        if (room.number == roomNumber)
            return room.price;
    return 0;
}

void initializeRooms()
{
    for (int i = 101; i <= 105; ++i)
        rooms.push_back({i, "Single", 1000, false});
    for (int i = 106; i <= 110; ++i)
        rooms.push_back({i, "Double", 2000, false});
    for (int i = 201; i <= 205; ++i)
        rooms.push_back({i, "Deluxe", 3000, false});
}

bool isRoomAvailable(int roomNumber, Date checkIn, Date checkOut)
{
    for (auto &b : bookings)
    {
        if (b.roomNumber == roomNumber)
        {
            if (!(checkOut.day <= b.checkIn.day || checkIn.day >= b.checkOut.day))
            {
                return false;
            }
        }
    }
    return true;
}

void bookRoom()
{
    string customerName, type;
    Date in, out;
    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter check-in date (DD MM YYYY): ";
    cin >> in.day >> in.month >> in.year;
    cout << "Enter check-out date (DD MM YYYY): ";
    cin >> out.day >> out.month >> out.year;
    cout << "Enter room type (Single/Double/Deluxe): ";
    cin >> type;

    for (Room &room : rooms)
    {
        if (room.type == type && isRoomAvailable(room.number, in, out))
        {
            int days = calculateStayDays(in, out);
            int total = days * room.price;
            bookings.push_back({customerName, room.number, in, out, total});
            room.isOccupied = true;
            cout << " Room " << room.number << " booked successfully! Total bill: Rs." << total << "\n";
            return;
        }
    }
    cout << " No available rooms of type " << type << " for the given dates.\n";
}

void viewBookings()
{
    if (bookings.empty())
    {
        cout << "No bookings right now.\n";
        return;
    }
    cout << "Current Bookings:\n";
    for (auto &b : bookings)
    {
        cout << "Name: " << b.name << ", Room: " << b.roomNumber
             << ", Check-In: " << b.checkIn.day << "/" << b.checkIn.month
             << "/" << b.checkIn.year << ", Check-Out: " << b.checkOut.day
             << "/" << b.checkOut.month << "/" << b.checkOut.year
             << ", Bill: Rs." << b.bill << "\n";
    }
}

void checkOutCustomer()
{
    int roomNumber;
    cout << "Enter room number to check-out: ";
    cin >> roomNumber;

    auto it = remove_if(bookings.begin(), bookings.end(),
                        [roomNumber](Customer &c)
                        { return c.roomNumber == roomNumber; });

    if (it != bookings.end())
    {
        bookings.erase(it, bookings.end());
        for (Room &room : rooms)
            if (room.number == roomNumber)
                room.isOccupied = false;
        cout << " Room " << roomNumber << " is now available.\n";
    }
    else
    {
        cout << " No such booking found.\n";
    }
}

void extendStay()
{
    int roomNumber, extraDays;
    cout << "Enter room number to extend stay: ";
    cin >> roomNumber;

    auto it = find_if(bookings.begin(), bookings.end(),
                      [roomNumber](Customer &c)
                      { return c.roomNumber == roomNumber; });

    if (it != bookings.end())
    {
        cout << "Enter number of extra days to extend: ";
        cin >> extraDays;

        Date newCheckout = it->checkOut;
        newCheckout.day += extraDays;

        for (auto &b : bookings)
        {
            if (b.roomNumber == roomNumber && b.name != it->name)
            {
                if (!(newCheckout.day <= b.checkIn.day || it->checkOut.day >= b.checkOut.day))
                {
                    cout << " Cannot extend stay. Room is already booked after current checkout date.\n";
                    return;
                }
            }
        }

        int addedBill = extraDays * getRoomPrice(roomNumber);
        it->checkOut = newCheckout;
        it->bill += addedBill;

        cout << " Stay extended by " << extraDays << " day(s). New bill: Rs." << it->bill << "\n";
    }
    else
    {
        cout << " Booking not found for Room " << roomNumber << ".\n";
    }
}

void occupancyReport()
{
    int occupied = 0;
    for (Room &room : rooms)
        if (room.isOccupied)
            occupied++;

    cout << "Total Rooms: " << rooms.size() << ", Occupied: " << occupied
         << ", Available: " << rooms.size() - occupied << "\n";
}

void revenueReport()
{
    int total = 0;
    for (auto &b : bookings)
        total += b.bill;
    cout << "Total Revenue from current bookings: Rs." << total << "\n";
}

void viewAvailableRooms()
{
    bool anyAvailable = false;
    cout << "Available Rooms:\n";
    for (Room &room : rooms)
    {
        if (!room.isOccupied)
        {
            cout << "Room " << room.number << " - Type: " << room.type << ", Price: Rs." << room.price << "\n";
            anyAvailable = true;
        }
    }
    if (!anyAvailable)
    {
        cout << "No rooms available at the moment.\n";
    }
}

void menu()
{
    cout << "\n--- Hotel Management System ---\n";
    cout << "1. Book Room\n";
    cout << "2. View All Bookings\n";
    cout << "3. Check-Out\n";
    cout << "4. Extend Stay\n";
    cout << "5. Occupancy Report\n";
    cout << "6. Revenue Report\n";
    cout << "7. Exit\n";
    cout << "8. View Available Rooms\n";
    cout << "Enter your choice: ";
}

int main()
{
    initializeRooms();
    int choice;
    do
    {
        menu();
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number: ";
                continue;
            }
            break;
        }

        switch (choice)
        {
        case 1:
            bookRoom();
            break;
        case 2:
            viewBookings();
            break;
        case 3:
            checkOutCustomer();
            break;
        case 4:
            extendStay();
            break;
        case 5:
            occupancyReport();
            break;
        case 6:
            revenueReport();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        case 8:
            viewAvailableRooms();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
