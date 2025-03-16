#ifndef RRS_H
#define RRS_H

#include <string>
using namespace std;

// Structure to hold reservation information
struct Reservation {
    string name;
    string contactNumber;
    int numberOfPeople;
    string dateTime;
    string status; // Confirmed, Cancelled, Completed
    double reservationFee = 150;
    double totalBillAmount;
};

// Node structure for BST
struct node {
    Reservation reservation;
    node* left;
    node* right;
};

class RestaurantReservationSystem {
private:
    void insert(node **sr, const Reservation&);
    node* root;
    void clear(node* sr);
    void displayReservationsHelper(node* sr) const;
public:
    RestaurantReservationSystem();
    ~RestaurantReservationSystem();
    void addReservation(const Reservation&);
    node* cancelReservation(node* sr, std::string dateTime);
    node* search(node* sr, const std::string& dateTime);
    void makePayment(string dateTime, double bill);
    int calculateDailyIncome(node* sr, string date);
    void displayReservations() const; 
    node* getRoot() const { return root; }

};

#endif
