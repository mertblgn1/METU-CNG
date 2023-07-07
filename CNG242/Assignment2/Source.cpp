/*
 Mert Can Bilgin - 2453025
 I read and accept the submission rules and the extra rules specified in each question.
 This is my own work that is done by myself only
 */

#include <iostream>
#include <string.h>
#include "Header.h"
using namespace std;

//MONTHLY RENTAL APARTMENT
//constructors
MonthlyRentalApartment::MonthlyRentalApartment()
{
    this->hasFurniture = false;
}

MonthlyRentalApartment::MonthlyRentalApartment(int ID, int numberOfRooms, int price, int size, bool b): Apartment(ID, numberOfRooms, price, size)
{
    this->hasFurniture = b;
}
//this function calculates the rent by dividing the days by 30, then it multiplies it by #days
int MonthlyRentalApartment::calculateRent(int days)
{
    return (((days / 30) + 1) * this->price);
}

void MonthlyRentalApartment::setHasFurniture(int a)
{
    if(a)
        this->hasFurniture = true;
    else
        this->hasFurniture = false;
}

void MonthlyRentalApartment::printDetails()
{
    cout << "Room No: " << this->apartmentID << ", Number of Rooms: " << this->numberofRooms << ", Rent: " << this->price << ",\n";
    cout << "Size: " << this->size << ", Furnished: ";
    if(this->hasFurniture == true)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

bool MonthlyRentalApartment::getHasFurniture()
{
    return (this->hasFurniture);
}

//DAILY RENTAL APARTMENT

DailyRentalApartment::DailyRentalApartment()
{
    this->decorationStyle = Minimalist;
}

DailyRentalApartment::DailyRentalApartment(int ID, int numberOfRooms, int price, int size, enum apartType decoration):Apartment(ID, numberOfRooms, price, size)
{
    this->decorationStyle = decoration;
}
//this part calculates the rent by multiplying the price by #days
int DailyRentalApartment::calculateRent(int days)
{
    return (days * this->price);
}

void DailyRentalApartment::printDetails()
{
    cout << "Room No: " << this->apartmentID << ", Number of Rooms: " << this->numberofRooms << ", Rent: " << this->price << ",\n";
    cout << "Size: " << this->size << ", Decoration Style: ";
    if(this->decorationStyle == 0)
        cout << "Minimalist" << endl;
    else if(this->decorationStyle == 1)
        cout << "Modern" << endl;
    else if(this->decorationStyle == 2)
        cout << "Classic" << endl;
}

enum apartType DailyRentalApartment::getApartType()
{
    return (this->decorationStyle);
}

void DailyRentalApartment::setApartType(int a)
{
    if(a == 1)
        this->decorationStyle = Minimalist;
    else if(a == 2)
        this->decorationStyle = Modern;
    else if(a == 3)
        this->decorationStyle = Classic;
}

//APARTMENTS

Apartment::Apartment()
{
    this->apartmentID = 0;
    this->numberofRooms = 0;
    this->price = 0;
    this->size = 0;
}

Apartment::Apartment(int ID, int numberofrooms, int price, int size)
{
    this->apartmentID = ID;
    this->numberofRooms = numberofrooms;
    this->price = price;
    this->size = size;
}

void Apartment::setID(int ID)
{
    this->apartmentID = ID;
}

void Apartment::setNumberOfRooms(int numberofrooms)
{
    this->numberofRooms = numberofrooms;
}

void Apartment::setPrice(int price)
{
    this->price = price;
}

void Apartment::setSize(int size)
{
    this->size = size;
}

int Apartment::getID()
{
    return this->apartmentID;
}

int Apartment::getNumberOfRooms()
{
    return this->numberofRooms;
}

int Apartment::getPrice()
{
    return this->price;
}

int Apartment::getSize()
{
    return this->size;
}

void Apartment::printApartment()
{
    cout << "Daily Rental Apartments:" << endl;
    cout << "Room No: " << this->apartmentID << ", Number of Rooms: " << this->numberofRooms << ", Rent: " << this->price << ",\n";
    cout << "Size: " << this->size << endl;
}


//BUILDING
//constructs default by setting everythins as zero
Building::Building()
{
    this->buildingID = 0;
    this->address = new char[300];
    strcpy(address, "Non");
    for(int i = 0; i <= 50; i++)
    {
        monthly[i] = new MonthlyRentalApartment(0, 0, 0, 0, false);
        daily[i] = new DailyRentalApartment(0, 0, 0, 0, Minimalist);
    }
}

Building::Building(int ID, char *address, MonthlyRentalApartment *Month, DailyRentalApartment *Day):MonthlyRentalApartment(Month->getID(), Month->getNumberOfRooms(), Month->getPrice(), Month->getSize(), Month->getHasFurniture()), DailyRentalApartment(Day->getID(), Day->getNumberOfRooms(), Day->getPrice(), Day->getSize(), Day->getApartType())
{
    this->buildingID = ID;
    this->address = new char[300];
    strcpy(this->address, address);
    
    for(int i = 0; i <= 50; i++)
    {
        this->monthly[i] = &Month[i];
        this->daily[i] = &Day[i];
    }
}

char* Building::getAddress()
{
    return (this->address);
}

void Building::setAddress(char *addr)
{
    strcpy(this->address, addr);
}

MonthlyRentalApartment* Building::getMonthlyRentalApartments()
{
    return (this->monthly[0]);
}

DailyRentalApartment* Building::getDailyRentalApartments()
{
    return (this->daily[0]);
}

MonthlyRentalApartment* Building::getSpecifiedMonthlyRentalApartment(int a)
{
    return (this->monthly[a]);
}

DailyRentalApartment* Building::getSpecifiedDailyRentalApartment(int a)
{
    return (this->daily[a]);
}


void Building::addMonthlyApartment()
{
    int number, val;
    cout << "Enter room number: ";
    cin >> number;
    this->monthly[number] = new MonthlyRentalApartment();
    this->monthly[number]->setID(number);
    cout << "\nEnter number of rooms: ";
    cin >> val;
    this->monthly[number]->setNumberOfRooms(val);
    cout << "\nEnter rent (GBP): ";
    cin >> val;
    this->monthly[number]->setPrice(val);
    cout << "\nEnter size (m2): ";
    cin >> val;
    this->monthly[number]->setSize(val);
    cout << "Furnished (Yes(1) / No(0)): ";
    cin >> val;
    this->monthly[number]->setHasFurniture(val);
    cout << "Apartment successfully added!" << endl;
}

void Building::addDailyApartment()
{
    int number, val;
    cout << "Enter room number:";
    cin >> number;
    this->daily[number] = new DailyRentalApartment();
    this->daily[number]->setID(number);
    cout << "\nEnter number of rooms: ";
    cin >> val;
    this->daily[number]->setNumberOfRooms(val);
    cout << "\nEnter rent (GBP): ";
    cin >> val;
    this->daily[number]->setPrice(val);
    cout << "\nEnter size (m2): ";
    cin >> val;
    this->daily[number]->setSize(val);
    cout << "\nDecoration Style:\n1. Minimalist\n2. Modern\n3.Classic\nYour Selection: ";
    cin >> val;
    this->daily[number]->setApartType(val);
    cout << "Apartment successfully added!" << endl;
}

void Building::printApt_Room_Daily(int num)
{
    for(int i = 0; i < 50; i++)
    {
        if(this->getSpecifiedDailyRentalApartment(i)->getNumberOfRooms() == num)
            this->getSpecifiedDailyRentalApartment(i)->printDetails();
    }
}

void Building::printApt_Room_Monthly(int num)
{
    for(int j = 0; j < 50; j++)
    {
        if(this->getSpecifiedMonthlyRentalApartment(j)->getNumberOfRooms() == num)
            this->getSpecifiedMonthlyRentalApartment(j)->printDetails();
    }
}

void Building::printApt_Size_Monthly(int size)
{
    for(int i = 0; i < 50; i++)
    {
        if(this->getSpecifiedMonthlyRentalApartment(i)->getSize() >= size)
            this->getSpecifiedMonthlyRentalApartment(i)->printDetails();
    }
}

void Building::printApt_Size_Daily(int size)
{
    for(int i = 0; i < 50; i++)
    {
        if(this->getSpecifiedDailyRentalApartment(i)->getSize() >= size)
            this->getSpecifiedDailyRentalApartment(i)->printDetails();
    }
}

void Building::printApt_Cheaper_Daily(int price, int day)
{
    for(int i = 0; i < 50; i++)
    {
        if((this->getSpecifiedDailyRentalApartment(i)->calculateRent(day) < price) && (this->getSpecifiedDailyRentalApartment(i)->getNumberOfRooms() != 0))
            this->getSpecifiedDailyRentalApartment(i)->printDetails();
    }
}

void Building::printApt_Cheaper_Monthly(int price, int day)
{
    for(int i = 0; i < 50; i++)
    {
        if((this->getSpecifiedMonthlyRentalApartment(i)->calculateRent(day) < price) && (this->getSpecifiedMonthlyRentalApartment(i)->getNumberOfRooms() != 0))
            this->getSpecifiedMonthlyRentalApartment(i)->printDetails();
    }
}

void Building::printApt_Daily()
{
    int found = 0;
    for(int i = 0; i < 50; i++)
    {
        if(this->getSpecifiedDailyRentalApartment(i)->getNumberOfRooms() != 0)
        {
            this->getSpecifiedDailyRentalApartment(i)->printDetails();
            found = 1;
        }
    }
    if(!found)
        cout << "Not Found\n";
}

void Building::printApt_Monthly()
{
    int found = 0;
    for(int i = 0; i < 50; i++)
    {
        if(this->getSpecifiedMonthlyRentalApartment(i)->getNumberOfRooms() != 0)
        {
            this->getSpecifiedMonthlyRentalApartment(i)->printDetails();
            found = 1;
        }
    }
    if(!found)
        cout << "Not Found\n";
}

void Building::calculate(int roomNum, int day)
{
    if(this->getSpecifiedDailyRentalApartment(roomNum)->getNumberOfRooms() != 0)
    {
        cout << "The rent for your stay is ";
        cout << this->getSpecifiedDailyRentalApartment(roomNum)->calculateRent(day) << endl;
    }
    else if(this->getSpecifiedMonthlyRentalApartment(roomNum)->getNumberOfRooms() != 0)
    {
        cout << "The rent for your stay is ";
        cout << this->getSpecifiedMonthlyRentalApartment(roomNum)->calculateRent(day) << " GBP!" << endl;
    }
}

void Building::showtheBuildingWithAddress()
{
    cout << "ID: " << this->buildingID << ", Address: " << this->address << endl;
}

void Building::showtheBuildingsWithApartments()
{
    int found = 0;
    this->showtheBuildingWithAddress();
    cout << "Daily Rental Apartments:\n";
    for(int i = 0; i < 50; i++)
    {
        if(this->daily[i]->getPrice() != 0)
        {
            this->daily[i]->printDetails();
            found = 1;
        }
    }
    if(!found)
        cout << "Not Found" << endl;
    cout << "Monthly Rental Apartments:\n";
    found = 0;
    for(int j = 0; j < 50; j++)
    {
        if(this->monthly[j]->getPrice() != 0){
            this->monthly[j]->printDetails();
            found = 1;
        }
    }
    if(!found)
        cout << "Not Found" << endl;
}
//AGENCY

//Agency default constructor
Agency::Agency()
{
    this->Name = new char[60];
    strcpy(this->Name, "Non");
    for(int i = 0; i <= 50; i++)
    {
        Buildings[i] = new Building();
    }
}

Agency::Agency(char *name, Building *buildings):Building(buildings->getID(), buildings->getAddress(), buildings->getMonthlyRentalApartments(), buildings->getDailyRentalApartments())
{
    this->Name = new char[60];
    strcpy(this->Name, name);
    for(int i = 0; i < 50; i++)
    {
        this->Buildings[i] = &buildings[i];
    }
}

void Agency::setName(char *name)
{
    this->Name = new char[60];
    strcpy(this->Name, name);
}

char* Agency::getName()
{
    return (this->Name);
}

Building* Agency::getBuildings()
{
    return (this->Buildings[0]);
}

Building* Agency::getSpecifiedBuilding(int a)
{
    return (this->Buildings[a]);
}

void Agency::addBuilding()
{
    cin.clear();
    fflush(stdin);
    char addr[300];
    cout << "What is the address of your building:" << endl;
    cin.getline(addr, 300);
    this->Buildings[buildingID] = new Building();
    this->Buildings[buildingID]->setAddress(addr);
    
    cout << "The building is created with the id number " << buildingID << endl;
    buildingID++;
}

void Agency::printBuildings()
{
    int i;
    
    for(i = 0; strcmp(this->Buildings[i]->getAddress(), "Non") != 0; i++){
        this->Buildings[i]->showtheBuildingWithAddress();
    }
}

void Agency::printApartments_Room(int num)
{
    cout << "Daily Rental Apartments:\n";
    for(int i = 0; i < 50; i++)
    {
        if(strcmp(this->getSpecifiedBuilding(i)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(i)->printApt_Room_Daily(num);
        }
    }
   
    cout << "Monthly Rental Apartments:\n";
    for(int j = 0; j < 50; j++)
    {
        if(strcmp(this->getSpecifiedBuilding(j)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(j)->printApt_Room_Monthly(num);
        }
    }
}

void Agency::printApartments_Size(int size)
{
    cout << "Daily Rental Apartments:\n";
    for(int i = 0; i < 50; i++)
    {
        if(strcmp(this->getSpecifiedBuilding(i)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(i)->printApt_Size_Daily(size);
        }
    }
   
    cout << "Monthly Rental Apartments:\n";
    for(int j = 0; j < 50; j++)
    {
        if(strcmp(this->getSpecifiedBuilding(j)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(j)->printApt_Size_Monthly(size);
        }
    }
}

void Agency::printApartments_Cheaper()
{
    int price, day;
    cout << "Enter the price (GBP): ";
    cin >> price;
    cout << "Enter the days:";
    cin >> day;
    
    cout << "Daily Rental Apartments:\n";
    for(int i = 0; i < 50; i++)
    {
        if(strcmp(this->getSpecifiedBuilding(i)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(i)->printApt_Cheaper_Daily(price, day);
        }
    }
   
    cout << "Monthly Rental Apartments:\n";
    for(int j = 0; j < 50; j++)
    {
        if(strcmp(this->getSpecifiedBuilding(j)->getAddress(), "Non") != 0)
        {
            this->getSpecifiedBuilding(j)->printApt_Cheaper_Monthly(price, day);
        }
    }
}

void Agency::printApartments_DailyorMonthly()
{
    int select;
    cout << "Enter Daily/Monthly Rental (0/1): ";
    cin >> select;
    
    if(select == 0)
    {
        for(int i = 0; i < 50; i++)
        {
            this->getSpecifiedBuilding(i)->printApt_Daily();
        }
    }
    else if(select == 1)
    {
        for(int j = 0; j < 50; j++)
        {
            this->getSpecifiedBuilding(j)->printApt_Monthly();
        }
    }
        
}

void Agency::calculateRent()
{
    int buildingid, roomNo, days;
    cout << "Available Buildings:\n";
    this->printBuildings();
    cout << "Select Building: ";
    cin >> buildingid;
    cout << "Available Apartments:\n";
    cout << "Daily Rental Apartments:\n";
    this->getSpecifiedBuilding(buildingid)->printApt_Daily();
    cout << "Monthly Rental Apartments:\n";
    this->getSpecifiedBuilding(buildingid)->printApt_Monthly();
    cout << "Enter Room No: ";
    cin >> roomNo;
    cout << "Enter Number of Days: ";
    cin >> days;
    this->getSpecifiedBuilding(buildingid)->calculate(roomNo, days);
}

