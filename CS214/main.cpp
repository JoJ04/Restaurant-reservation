#include <iostream>
#include "RRS.h" 

using namespace std;

int main() {
    RestaurantReservationSystem rrs;
    Reservation newReservation;
    int choice;
    string dateTime;

    do {
        cout << "\n === Welcome to the Restaurant Reservation System ===\n"
             << "1. Add Reservation\n"
             << "2. Cancel Reservation\n"
             << "3. Search for a Reservation\n"
             << "4. Make a payment\n"
             << "5. Display the Reservations\n"
             << "6. Calculate the daily income\n"
             << "7. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, newReservation.name);
                cout << "Enter date and time (YYYY-MM-DD HH:MM): ";
                getline(cin, newReservation.dateTime);
                cout << "Enter number of people: ";
                cin >> newReservation.numberOfPeople;
                cout << "Enter contact number: ";
                cin.ignore();
                getline(cin, newReservation.contactNumber);
                cout << "Reservation Fee: " << newReservation.reservationFee << " SAR\n";
                rrs.addReservation(newReservation);
                break;
            }
            case 2: {
                cout << "Enter date & time of reservation to cancel (YYYY-MM-DD HH:MM): ";
                 cin.ignore();
                 getline(cin, dateTime);
                 rrs.cancelReservation(rrs.getRoot(),dateTime);
                 cout << "Reservation canceled successfully.\n";
                break;
            }
            case 3: {
                string searchDateTime;
                cout << "Enter date and time to search for a reservation (YYYY-MM-DD HH:MM): ";
                cin.ignore();
                getline(cin, searchDateTime);

                node* resultNode = rrs.search(rrs.getRoot(), searchDateTime);

                if (resultNode != nullptr) {
                    cout << "\nReservation found!" << endl;
                    cout << "Name:                " << resultNode->reservation.name << endl;
                    cout << "DateTime:            " << resultNode->reservation.dateTime << endl;
                    cout << "Number of People:    " << resultNode->reservation.numberOfPeople << endl;
                    cout << "Contact Number:      " << resultNode->reservation.contactNumber << endl;
                    cout << "Status:              " << resultNode->reservation.status << endl;
                } else {
                    cout << "Reservation not found." << endl;
                }
                break;
            }
            case 4: {
                int bill;
                cout << "To make a payment, Please enter your reservation date and time (YYYY-MM-DD HH:MM): ";
                cin.ignore();
                getline(cin, dateTime);
                cout << "Enter the total bill: ";
                cin >> bill;
                rrs.makePayment(dateTime, bill);
                break;
            }
            case 5: {
                rrs.displayReservations();
                break;
            }
            case 6: {
                cout << "Enter date & time of reservation to calculate the daily income (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, dateTime);
                cout << "The Daily Income is: " << rrs.calculateDailyIncome(rrs.getRoot(),dateTime) << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 7);
    
    return 0;
}