/*
 Mert Can Bilgin - 2453025
 I read and accept the submission rules and the extra rules specified in each question.
 This is my own work that is done by myself only
 */

#ifndef Header_h
#define Header_h
#include <iostream>
using namespace std;

enum apartType {Minimalist, Modern, Classic};


class Apartment
{
protected:
    int apartmentID;
    int numberofRooms;
    int price;
    int size;
public:
    Apartment();
    Apartment(int, int, int, int);
    void setID(int);
    void setNumberOfRooms(int);
    void setPrice(int);
    void setSize(int);
    int getID();
    int getNumberOfRooms();
    int getPrice();
    int getSize();
    void printApartment();
};

class MonthlyRentalApartment: virtual public Apartment
{
protected:
    bool hasFurniture;
public:
    MonthlyRentalApartment();
    MonthlyRentalApartment(int, int, int, int, bool);
    bool getHasFurniture();
    void setHasFurniture(int);
    int calculateRent(int);
    void printDetails();
};

class DailyRentalApartment: virtual public Apartment
{
protected:
    enum apartType decorationStyle;
public:
    DailyRentalApartment();
    DailyRentalApartment(int, int, int, int, enum apartType);
    enum apartType getApartType();
    void setApartType(int);
    int calculateRent(int);
    void printDetails();
};

class Building: public MonthlyRentalApartment, public DailyRentalApartment
{
protected:
    int buildingID;
    char *address;
    MonthlyRentalApartment *monthly[50];
    DailyRentalApartment *daily[50];
public:
    Building();
    Building(int, char*, MonthlyRentalApartment*, DailyRentalApartment*);
    char* getAddress();
    void setAddress(char*);
    MonthlyRentalApartment* getMonthlyRentalApartments();
    DailyRentalApartment* getDailyRentalApartments();
    MonthlyRentalApartment* getSpecifiedMonthlyRentalApartment(int);
    DailyRentalApartment* getSpecifiedDailyRentalApartment(int);
    void addMonthlyApartment();
    void addDailyApartment();
    void printApt_Room_Daily(int);
    void printApt_Room_Monthly(int);
    void printApt_Size_Monthly(int);
    void printApt_Size_Daily(int);
    void printApt_Cheaper_Daily(int, int);
    void printApt_Cheaper_Monthly(int, int);
    void printApt_Daily();
    void printApt_Monthly();
    void calculate(int, int);
    void showtheBuildingWithAddress();
    void showtheBuildingsWithApartments();
};

class Agency: public Building
{
protected:
    char *Name;
    Building *Buildings[50];
public:
    Agency();
    Agency(char*, Building*);
    void setName(char*);
    char* getName();
    Building* getBuildings();
    Building* getSpecifiedBuilding(int);
    void addBuilding();
    void printBuildings();
    void printApartments_Room(int);
    void printApartments_Size(int);
    void printApartments_Cheaper();
    void printApartments_DailyorMonthly();
    void calculateRent();
};





#endif /* Header_h */
