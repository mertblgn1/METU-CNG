/*
 Mert Can Bilgin - 2453025
 I read and accept the submission rules and the extra rules specified in each question.
 This is my own work that is done by myself only
 */

#include <iostream>
#include "Header.h"
using namespace std;

int main() {
    Agency *A;
    A = new Agency();
    A->setName("Manchester Comfort Apartments");
    
    int exit = 0, operation, apartmentType, buildingid, numberofrooms, size;
    
    cout << "!!!Welcome to Agency Management System!!!" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Please select an operation" << endl;
    cout << "1. Add a new building to the agency" << endl;
    cout << "2. Add a new apartment (monthly or daily rental) to a building" << endl;
    cout << "3. List all buildings" << endl;
    cout << "4. List all apartments available for the agency" << endl;
    cout << "5. List all apartments that have the specified number of rooms" << endl;
    cout << "6. List all apartments which are bigger than the specified apartment size" << endl;
    cout << "7. List all apartments which are cheaper than the price in a specified number of days" << endl;
    cout << "8. List all apartments that are either daily or monthly rental" << endl;
    cout << "9. Calculate the price of a specific apartment in a specified number of days" << endl;
    cout << "0. Exit" << endl;
    
    do{
        cin.clear();
        fflush(stdin);
        cout << "---------------------------------------------" << endl;
        cout << "Your selection: ";
        cin >> operation;
        switch (operation) {
            case 1:
                A->addBuilding();
                break;
            case 2:
                cout << "Which building you want to add apartment into?" << endl;
                cout << "Available Buildings:" << endl;
                A->printBuildings();
                cout << "\nBuilding id: ";
                cin >> buildingid;
                cout << "What is the type of the apartment?\n" << endl;
                cout << "1. Daily Rental Apartment\n2. Monthly Rental Apartment\n\nType: ";
                cin >> apartmentType;
                
                if(apartmentType == 1)
                {
                    A->getSpecifiedBuilding(buildingid)->addDailyApartment();
                }
                else if(apartmentType == 2)
                {
                    A->getSpecifiedBuilding(buildingid)->addMonthlyApartment();
                }
                break;
            case 3:
                cout << "Buildings:\n";
                A->printBuildings();
                break;
            case 4:
                for(int i = 0; A->getSpecifiedBuilding(i) != NULL; i++)
                {
                    if(strcmp(A->getSpecifiedBuilding(i)->getAddress(), "Non") != 0)
                        A->getSpecifiedBuilding(i)->showtheBuildingsWithApartments();
                }
                break;
            case 5:
                cout << "Enter the specified room number: ";
                cin >> numberofrooms;
                A->printApartments_Room(numberofrooms);
                break;
            case 6:
                cout << "Enter minimum size:";
                cin >> size;
                A->printApartments_Size(size);
                break;
            case 7:
                A->printApartments_Cheaper();
                break;
            case 8:
                A->printApartments_DailyorMonthly();
                break;
            case 9:
                A->calculateRent();
                break;
            case 0:
                exit = 1;
                cout << "Thanks for choosing Agency Management System!" << endl;
                break;
                
            default:
                cout << "Please choose the given options!" << endl;
                break;
        }
    }while(!exit);
    
    cout << "---------------------------------------------" << endl;
    
    return 0;
}
