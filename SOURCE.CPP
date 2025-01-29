#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>
using namespace std;
//MOMINA HAROON
class Person {
private:
    string name;
    string phoneNumber;
public:
    Person(string n = "", string p = "") : name(n), phoneNumber(p){}
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }};
class Flight {
protected:
    Person customer;
    string reservation;
    static map<string, bool> seatAvailability;
    static map<string, double> ticketPrices;
public:
    Flight(string name, string phoneNumber) : customer(name, phoneNumber){}
    virtual void displayFlights() const = 0;
    virtual void setReservation() = 0;
    virtual void saveToFile() const = 0;
    static void initializeFlights() {
    initializeSeatAvailability();
    initializeTicketPrices();}
    static void initializeSeatAvailability() {
    seatAvailability["F101 Skardu to Islamabad"] = true;
    seatAvailability["F102 Islamabad to Karachi"] = true;
    seatAvailability["F103 Karachi to Skardu"] = true;
    seatAvailability["F201 New York to London"] = true;
    seatAvailability["F202 London to Dubai"] = true;
    seatAvailability["F203 Dubai to New York"] = true;}
    static void initializeTicketPrices() {
    ticketPrices["F101 Skardu to Islamabad"] = 100.0;
    ticketPrices["F102 Islamabad to Karachi"] = 120.0;
    ticketPrices["F103 Karachi to Skardu"] = 110.0;
    ticketPrices["F201 New York to London"] = 500.0;
    ticketPrices["F202 London to Dubai"] = 450.0;
    ticketPrices["F203 Dubai to New York"] = 600.0;}
    bool checkSeatAvailability(const string& flight) {
    return seatAvailability[flight];}
    double getTicketPrice(const string& flight) {
    return ticketPrices[flight];}
    string getReservation() const { return reservation; }};
    map<string, bool> Flight::seatAvailability;
    map<string, double> Flight::ticketPrices;
    class DomesticFlight : public Flight {
    public:
    DomesticFlight(string name, string phoneNumber) : Flight(name, phoneNumber) {}
    void displayFlights() const {
    cout << "Available Domestic Flights\n1. F101 Skardu to Islamabad\n2. F102 Islamabad to Karachi\n3. F103 Karachi to Skardu\n";}
    void setReservation() {
    int choice;
    displayFlights();
    cout << "Enter the serial number of your flight: ";
    while (!(cin >> choice) || choice < 1 || choice > 3) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a number between 1 and 3: ";}
    string flights[3] = {"F101 Skardu to Islamabad", "F102 Islamabad to Karachi", "F103 Karachi to Skardu"};
    reservation = flights[choice - 1];
    if (checkSeatAvailability(reservation)) {
    cout << "Seat is available for " << reservation << ". Ticket price: $" << getTicketPrice(reservation) << endl;} 
	else {cout << "No seats available for " << reservation << "." << endl;
    reservation = "";}}
    void saveToFile() const {
    ofstream file("reservation.txt", ios::app);
    if (file.is_open()) {
    file << customer.getName() << "\t" << customer.getPhoneNumber() << "\t" << reservation << endl;
    file.close();
    cout << "Your seat has been reserved for " << reservation << "." << endl;} 
	else{cerr << "Error opening file for writing." << endl;}}};
    class InternationalFlight : public Flight {
    private:
    string passportNumber;
    bool visaStatus;
    public:
    InternationalFlight(string name, string phoneNumber, string passport, bool visa)
    : Flight(name, phoneNumber), passportNumber(passport), visaStatus(visa) {}
    void displayFlights() const {
    cout << "Available International Flights\n1. F201 New York to London\n2. F202 London to Dubai\n3. F203 Dubai to New York\n"; }
    void setReservation() {
    int choice;
    displayFlights();
    cout << "Enter the serial number of your flight: ";
    while (!(cin >> choice) || choice < 1 || choice > 3) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a number between 1 and 3: ";}
    string flights[3] = {"F201 New York to London", "F202 London to Dubai", "F203 Dubai to New York"};
    reservation = flights[choice - 1];
    if (checkSeatAvailability(reservation)) {
    cout << "Seat is available for " << reservation << ". Ticket price: $" << getTicketPrice(reservation) << endl;} 
	else {cout << "No seats available for " << reservation << "." << endl;
    reservation = "";}}
    void saveToFile() const {
    ofstream file("reservation.txt", ios::app);
    if (file.is_open()) {
    file << customer.getName() << "\t" << customer.getPhoneNumber() << "\t" << passportNumber << "\t" << (visaStatus ? "Visa Approved" : "Visa Not Approved") << "\t" << reservation << endl;
    file.close();
    cout << "Your seat has been reserved for " << reservation << "." << endl;} 
	else {cerr << "Error opening file for writing." << endl;}}};
    int main() {
    Flight::initializeFlights();
    string name, phoneNumber, passport;
    bool visaStatus;
    int flightType;
    system("cls");
    cout<<"\t WELCOME TO AIRLINE MANAGEMENT SYSTEM:"<<endl;
    cout<<"\t ************************************:"<<endl;
    cout << "Would you like to make a reservation? (yes/no): ";;
    string response;
    cin >> response;
    if (response == "no") {
    cout << "Thank You!\n";
    return 0;}
    cout << "Enter your Name without spaces: ";
    cin >> name;
    cout << "Enter Phone Number (Format:XXX-XXX-XXXX): ";
    cin >> phoneNumber;
    cout << "Select Flight Type:\n1. Domestic Flight\n2. International Flight\nEnter your choice: ";
    while (!(cin >> flightType) || flightType < 1 || flightType > 2) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter 1 for Domestic Flight or 2 for International Flight: ";}
    Flight* flight = NULL;
    if (flightType == 1) {
    flight = new DomesticFlight(name, phoneNumber);} 
	else {cout << "Enter Passport Number(Format:AAAA-1234567-AAA): "<<endl;
    cin >> passport;
    cout << "Visa Status (1 for Approved, 0 for Not Approved): ";
    while (!(cin >> visaStatus) || (visaStatus != 0 && visaStatus != 1)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter 1 for Approved or 0 for Not Approved: ";}
    flight = new InternationalFlight(name, phoneNumber, passport, visaStatus);}
    flight->setReservation();
    if (!flight->getReservation().empty()) {
    flight->saveToFile();}
    delete flight;
	}
