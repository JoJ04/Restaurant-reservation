#include "RRS.h"
#include <iostream>

using namespace std;

// Constructor
RestaurantReservationSystem::RestaurantReservationSystem() {
    root = nullptr;
}

// Destructor
RestaurantReservationSystem::~RestaurantReservationSystem() {
    clear(root);
}
// Function to clear all reservations and free memory
void RestaurantReservationSystem::clear(node* sr) {
    if (sr != nullptr) {
        clear(sr->left);
        clear(sr->right);
    }
    delete sr;
}
//Author: Rudi
// Function to insert a reservation into the binary search tree
void RestaurantReservationSystem::insert(node **sr, const Reservation& reservation) {
    if (*sr == nullptr) {
        *sr = new node;
        (*sr)->left = nullptr;
        (*sr)->reservation = reservation;
        (*sr)->right = nullptr;
        (*sr)->reservation.status = "Confirmed"; // Set status to Confirmed by default
    } else if (reservation.dateTime < (*sr)->reservation.dateTime) {
        insert(&((*sr)->left), reservation); // Traverse left
    } else if (reservation.dateTime > (*sr)->reservation.dateTime) {
        insert(&((*sr)->right), reservation); // Traverse right
    } else if (reservation.dateTime == (*sr)->reservation.dateTime && (*sr)->reservation.status == "Cancelled") {
        // Replace the canceled reservation with the new reservation
        (*sr)->reservation = reservation;
        (*sr)->reservation.status = "Confirmed";
        cout << "Canceled reservation replaced with the new reservation." << endl;
    } else {
        // Inform the user that a reservation already exists for that date and time
        cout << "A reservation already exists for the same date and time." << endl;
        return;
    }
}

// Function to add a reservation
void RestaurantReservationSystem::addReservation(const Reservation& reservation){ 
    
    insert(&root, reservation);
}

 // Function to cancel a reservation
 //Abeer
node* RestaurantReservationSystem::cancelReservation(node* sr, std::string dateTime) {
    if (sr == nullptr) {
        return nullptr;
    }
    if (sr->reservation.dateTime == dateTime) {
        sr->reservation.status = "cancelled";
    }
    sr->left = cancelReservation(sr->left, dateTime);
    sr->right = cancelReservation(sr->right, dateTime);

    return sr;
}
    
// Function definition for search
//Author: Lamees
node* RestaurantReservationSystem::search(node* sr, const std::string& dateTime) {
    if (sr == nullptr || sr->reservation.dateTime == dateTime) {
        return sr;
    }

    if (dateTime < sr->reservation.dateTime) {
        return search(sr->left, dateTime);
    }
    // If false, search in the right subtree
    return search(sr->right, dateTime);
}

//Function to handles the payment process
//Author: Sara 
void RestaurantReservationSystem::makePayment(string dateTime, double bill) {
    int i;
    bool found = search(root, dateTime);
    
    if (found) {
        node* resNode = search(root, dateTime);
        
        if (resNode-> reservation.status == "Confirmed") {
            
            resNode-> reservation.totalBillAmount =bill;
            
            cout << "\nYour total bill:                            " << bill <<
            " SAR\nTotal bill after deduction reservation fee: " <<  bill -resNode-> reservation.reservationFee << " SAR" << endl;
            cout << "\nChoose payment method:" << endl;
            cout << "1. Credit card or debit card " << endl;
            cout << "2. Cash" << endl;
            cin >> i;
            switch(i){
                    case 1:
                        resNode-> reservation.status = "Completed";
                        cout << "Payment done. Thank you!\n" << endl;
                        break;
                    case 2:
                        resNode-> reservation.status = "Completed";
                        cout << "Payment done. Thank you!\n" << endl;
                        break;
                    default:
                        cout << "Invalid payment method. Payment not processed." << endl;
            }
         }
         else if (resNode-> reservation.status == "Cancelled") {
            cout << "Reservation Cancelled. Cannot proceed with payment." << endl;
        }
    } 
    else {
        cout << "Reservation with date " << dateTime << " not found." << endl;
    }

}
// Function to display All Reservations after checking if there is any 
//author:Walah
void RestaurantReservationSystem::displayReservations() const {
    if (root == nullptr) {
        cout << "There are no reservations." << endl;
    } else {
        cout << "Current Reservations:" << endl;
        displayReservationsHelper(root);
    }
}
// The Function that really displays the Reservations using recursions
//author:Walah
void RestaurantReservationSystem::displayReservationsHelper(node* sr) const {
    if (sr != nullptr) {
        displayReservationsHelper(sr->left);  // Visit left subtree
        cout << "Name: " << sr->reservation.name << endl
             << "DateTime: " << sr->reservation.dateTime << endl
             << "Number of People: " << sr->reservation.numberOfPeople << endl
             << "Contact Number: " << sr->reservation.contactNumber << endl
             << "Status: " << sr->reservation.status << endl
             << "-------------------------------" << endl;
        displayReservationsHelper(sr->right); // Visit right subtree
    }
}

// Function to calculate the daily income recursively
//Author: Jory
int RestaurantReservationSystem::calculateDailyIncome(node* sr, string date) {
    if (sr == nullptr) {
        return 0;
    }
    int income = 0; 
   
    income += calculateDailyIncome(sr->left, date);
    income += calculateDailyIncome(sr->right, date);
   
    string reservationDate = sr->reservation.dateTime.substr(0, 10);
    
    if (reservationDate == date && sr->reservation.status == "Completed") {
        income += sr->reservation.totalBillAmount; // Only add the bill if the conditions are met
    } else {
        cout << "No completed reservation found for " << date << endl;
    }
    return income;
}
