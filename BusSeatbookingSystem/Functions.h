#pragma once
#include <iostream>
#include <string>
#include "Bus.h";
#include "Seat.h";
#include "Route.h";
//#include "LinkedList.h";
#include "ReciptList.h";

using namespace std;

void reciptPrint(Recipt* recipt, Bus* selectdBus) {
	cout << "\n\t-----------------------\n\t--------Recipt---------\n\t-----------------------";
	recipt->PrintRecipt();
	selectdBus->PrintBus();
	cout << "\n\t-----------------------";
}

/*void seatConfigure(int* A, int size)

{
    
    int** B = new int* [2];
    B[0] = new int[size];
    B[1] = new int[size];

    

    for (int k = 0; k < size; k++)
    {
        B[0][k] = k + 1;
    }

    for (int i = 1; i <= size; i++)
    {
        bool exist = false;

        for (int j = 0; j < sizeof(A); j++)
        {
            if (A[j] == i)
            {
                exist = true;
            }

        }
        if (exist == true) { B[1][i - 1] = 1; }
        if (exist == false) { B[1][i - 1] = 0; }
    }

    cout << "1:Not Available" << endl;
    cout << "0:Available" << endl;
    cout << "\n\tFront\n";
    cout << endl;


    for (int j = 1; j <= size; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (i < 1)
            {
                cout << "[";
                cout << B[i][j - 1];
                cout << "|";
            }
            else if (i == 1)
            {
                cout << B[i][j - 1];
                cout << "]";
            }
        } cout << "\t";

        if (j != 0 && j % 5 == 0)
        {
            cout << endl;
            cout << endl;
        }
    }
}*/

bool isItAvailable(int* soldSeats, int arrySize, int i) {
    for (int j = 0; j < arrySize ; j++) {
        if (soldSeats[j] == i)
            return false;
    }
    return true;
}

void busSeatArragement(int* soldSeats,int bookedSeats, int NoofSeats) {
    cout << "\nSeat Arrangement of the Selected Bus :\n "; 
    cout << "The booked seats are shown as [*]\n\n\t\tFront\n\n";
    for (int i = 1; i <= NoofSeats; i++) {
        if (isItAvailable(soldSeats, bookedSeats, i))
            cout << "[" << i << "]\t";
        else
            cout << "[*]\t";
        if (i % 5 == 0)
            cout << endl;
    }
}

void printBusList(LinkedList* busList, BusList* BL) {
    Node* current = busList->getHead();
    for (int i = 0; i < busList->getSize(); i++) {

        BL->printByCode(current->data);
        current = current->next;
    }
    cout << "\n50 -\tBack\n";
}

LinkedList* busSelectByRoute(BusList* BL, RouteList* RL) {
    int* route = new int[2];
    bool selected = false;
    cout << "\n\t\t\t------------------------- Seat Booking Menu -----------------------";

    cout << "\n\t\t\t\t\tSelect your route from this city list : ... ";
    RL->printRoutes();
    cout << "\n\tSelect the start : "; cin >> route[0];
    cout << "\n\tSelect the end : "; cin >> route[1];
    cout << endl;
    LinkedList* busList = BL->busRouteSearch(route);
    if (busList->getSize() != 0) {
        int Code =0; // want to initialize
        Bus* bus = new Bus();
        printBusList(busList, BL);
        /*Node* current = busList->getHead();
        for (int i = 0; i < busList->getSize(); i++) {

            BL->printByCode(current->data);
            current = current->next;
        }*/
        
    }
    else {
        cout << "\nNo matching buses are available..";
    }
    return busList;
}

bool isSeatAvailable(int* soldSeats, int seatNo, Bus* selectedBus) {
    for (int j = 0; j < selectedBus->bookedSeats.getSize(); j++) {
        if (seatNo == soldSeats[j])
            return false;
    }
    return true;
}

bool ifNotItEntered(int* selectedSeats, int noOfSeats, int seatNo) {
    for (int i = 0; i < noOfSeats; i++) {
        if (seatNo == selectedSeats[i])
            return false;
    }
    return true;
}



bool BookingSeats(BusList* BL, LinkedList* busList, Recipt_List* RecL, int &billNo) {
    cout << "\nselect a bus : ";
    int busSelection; cin >> busSelection;
    if (busList->isAvalable(busSelection)) {
        //selecting the bus

        Bus* selectedBus = BL->getByCode(busSelection);

        cout << "You have selected :"; selectedBus->PrintBus();
        cout << endl;

        
        // geting the arry of booked seats
        int* soldSeats = selectedBus->bookedSeats.bookedSeatNos();        
        

        cout << "\nEnter the number of booking seats :";
        int bookingSeats; cin >> bookingSeats;
        //check whether the seats are available
        if (selectedBus->bookedSeats.isSeatsAvailable() && bookingSeats <= selectedBus->noOfSeats) {

            // printing available seats configuration;
            cout << "\nThe available seats in the selected bus :\n";
            soldSeats = selectedBus->bookedSeats.bookedSeatNos();

            //testing the arry
            
            //int numOfSoldSeats = selectedBus->bookedSeats.getSize();

            //seatConfigure(soldSeats, selectedBus->noOfSeats);
            busSeatArragement(soldSeats, selectedBus->bookedSeats.getSize(), selectedBus->noOfSeats);

            cout << "\nChoose seat numbers : ";
            int* seatNos = new int[bookingSeats];
            int EnterdseatNo;
            int* selectedSeats = new int[bookingSeats];
            for (int i = 0; i < bookingSeats; i++) {
                cout << "\n\tEnter seat No : ";
                cin >> EnterdseatNo;
                if (isItAvailable(soldSeats, selectedBus->bookedSeats.getSize(), EnterdseatNo) 
                    && ifNotItEntered(selectedSeats, bookingSeats, EnterdseatNo)&&
                    EnterdseatNo<=selectedBus->noOfSeats) {
                    seatNos[i] = EnterdseatNo;
                    selectedSeats[i] = EnterdseatNo;
                }                    
                else {
                    cout << "\n\tSeat No. " << EnterdseatNo << " is not available.\n\tPlease select other No :";
                    i--;
                }               
                
            }
            //complete this.......
            
            billNo++;
            RecL->insertLast(billNo, bookingSeats, selectedBus->code);

            for (int i = 0; i < bookingSeats; i++) {
                selectedBus->bookedSeats.seatBooking(seatNos[i], billNo);
                RecL->getTail()->seats[i] = seatNos[i];
                RecL->getTail()->setSeatNum(i, seatNos[i]);
            }
            //selectedBus->bookedSeats.printBookedSeats();

            //print recipt
            cout << "\nYour recipt :\n";
            reciptPrint(RecL->getTail(), selectedBus);

            return true;
        }
        else {
            cout << "Sorry, Only" << selectedBus->bookedSeats.availableSeats() << " are available..";
            return false;
            //recall to select seat booking or exit.
        }

    }
    else {
        cout << "\nNot vailed bus selection\n";
    }
}

bool SeatBooking(BusList* BL, RouteList* RL, int billNo, Recipt_List* RecL) {
    int outSelect = 0;
    bool booking;
    LinkedList* busList = new LinkedList();
    busList = busSelectByRoute(BL, RL);
    if (busList->getSize() > 0) {
        if (BookingSeats(BL, busList, RecL, billNo))
        {
            cout << "\n\n1. Book more seats.\n2. Exit to main menu\n ";
            int select; cin >> select;
            if (select == 1) {
                // run agian the function..
                //outSelect = 
                booking = SeatBooking(BL, RL, billNo, RecL);
            }
            else {
                //outSelect = 2;
                return false;
                //return outselect -> 2
            }
        }
        else {
            cout << "\n1. Select available bus \n2. Exit\n";
            cin >> outSelect;
            if (outSelect == 1) {
                booking = SeatBooking(BL, RL, billNo, RecL);
            }
            else {
                return false;
            }
        }
    }
}


bool cancelBooking(BusList* BL, Recipt_List* RecL) {
    int billNo;
    bool condition = false;
    while (condition == false) {
            cout << "\nEnter the bill number : "; cin >> billNo;
            if (RecL->isAvailable(billNo)) {
                Recipt* cancelingRecipt = RecL->find(billNo);
                Bus* cancelingBus = BL->getByCode(cancelingRecipt->busCode);

                reciptPrint(cancelingRecipt, cancelingBus);
                cout << "\nConform canceling..\n1.Conform\n2.Deline";
                int selection;
                cin >> selection;
                if (selection == 1) {
                    for (int i = 0; i < cancelingRecipt->numOfSeats; i++) {
                        cancelingBus->bookedSeats.cancelBooking(cancelingRecipt->seats[i]);
                    }
                    cout << "//Succesfully canceled your booking..";
                    condition = true;
                    break;
                }
                else
                    break;
            }
            else {
                cout << "\nEntered recipt No. is not available";
                cout << "\n1. Try again\n2. Exit to main menu";
                int selection;
                cin >> selection;
                if (selection == 1) {
                    continue;
                }
                else {
                    break;
                }
            }            
    }
    return condition;
}

bool eachSeatCancel(Bus* cancelingBus, Recipt* cancelingRecipt) {
    bool condition = false;
    int seatNo;
    cout << "\nEnter the num of seats you want to cancel : ";
    int numOfCancel; cin >> numOfCancel;
    
    if (numOfCancel <= cancelingRecipt->numOfSeats) {
        int* cancelingSeats = new int[numOfCancel];
        for (int i = 0; i < numOfCancel; i++) {
            cout << "\nEnter the seat No : "; cin >> seatNo;
            if (cancelingRecipt->searchSeat(seatNo)) {
                cancelingSeats[i] = seatNo;
                cancelingBus->bookedSeats.cancelBooking(seatNo);
            }
            else {
                cout << "\nThis is not booked..\nPlease enter a booked seat NO : ";
                i--;
            }               

        }
        cancelingRecipt->updateSeats(cancelingSeats, numOfCancel);
        cout << "\nThe selected seats are succesfully canceled..";
        reciptPrint(cancelingRecipt, cancelingBus);
        return true;

    }
    else {
        cout << "\nYou have entered invalied number of seats..";
        condition = eachSeatCancel(cancelingBus, cancelingRecipt);
    }

}


bool cancelBySeats(BusList* BL, Recipt_List* RecL) {
    int billNo;
    bool condition = false;
    while (condition == false) {
        cout << "\nEnter the bill number : "; cin >> billNo;
        if (RecL->isAvailable(billNo)) {
            Recipt* cancelingRecipt = RecL->find(billNo);
            Bus* cancelingBus = BL->getByCode(cancelingRecipt->busCode);

            reciptPrint(cancelingRecipt, cancelingBus);
            cout << "\nConform canceling..\n1.Conform\n2.Deline";
            int selection;
            cin >> selection;
            if (selection == 1) {
                condition = eachSeatCancel(cancelingBus, cancelingRecipt);
                break;
            }
            else
                break;
        }
        else {
            cout << "\nEntered recipt No. is not available";
            cout << "\n1. Try again\n2. Exit to main menu";
            int selection;
            cin >> selection;
            if (selection == 1) {
                continue;
            }
            else {
                break;
            }
        }
    }
    return condition;
}

bool passwordCheck(string &username, string &password) {
    bool condition = false;
    string enteredUsername, enteredPassword;
    if (username == "admin" && password == "password") {
        cout << "Username and Password is not set...\n\n\t\t\t------------------------ Admin Registration ----------------------- ";
        cout << "\nSet the Username\t:"; cin >> username;
        cout << "\nSet the password\t:"; cin >> password;
        condition = passwordCheck(username, password);

    }
    else {
        cout << "\n\t\t\t--------------------------- Admin Login ---------------------------";

        cout << "\nEnter Username\t:"; cin >> enteredUsername;
        cout << "\nEnter Password\t:"; cin >> enteredPassword;

        if (enteredUsername == username && enteredPassword == password) {
            return true;
        }          

        else {
            cout << "\nYou have entered incorrect username or password...";
            return false;
        }           

    }
    return condition;    
}

bool AdminloginMenu(string& username, string& password) {
    bool condition = false;
    condition = passwordCheck(username, password);
    if (condition == true) {
        //run admin menu
        return true;
    }
    else {
        int selection;
        cout << "\n1. Try again\n2. Exit\n"; cin >> selection;
        if (selection == 1) {
            condition = AdminloginMenu(username, password);
        }        
    }
}

void changePassword(string& password) {
    int enteredPassword1, enteredPassword2;
    cout << "\nEnter new password\t: "; cin >> enteredPassword1;
    cout << "\nConform new password\t: "; cin >> enteredPassword2;
    if (enteredPassword1 == enteredPassword2) {
        password = enteredPassword1;
        cout << "\nYour password has changed successfuly..";
    }
    else {
        cout << "\nYour passwords are not matching.";
        cout << "\nPlease conform your password corrently :";
        changePassword(password);
    }

}

void rootEditing(RouteList* RL, int &adminSelect) {
    int routeSelect = 0;

    while (routeSelect <= 0 || routeSelect > 4) {
        cout << "\n\t\t\t----------------------- Route Editing Menu -----------------------\n\t\t\t\t\t1. Insert New Routes\n\t\t\t\t\t2. Delete Routes\n\t\t\t\t\t3. Print Routes\n\t\t\t\t\t4. Exit " << endl;
        cout << "Enter your choice (1/2/3/4)" << endl;
        cin >> routeSelect;
        if (routeSelect <= 0 || routeSelect > 4) {
            cout << "Enter a valied selection.";
        }

        else if (routeSelect == 4) {
            adminSelect = 0;
            break;
        }


        else if (routeSelect == 1) {
            //insert routes
            cout << "Enter the new town to the route list :" << endl;
            string newTown;
            cin >> newTown;
            RL->insertRoute(newTown);
            routeSelect = 0;
        }

        else if (routeSelect == 2) {
            //delete routes
            RL->printRoutes();
            cout << "Enter the code of deleting route";
            int delTown;
            cin >> delTown;
            RL->deleteAt(delTown);
            routeSelect = 0;
        }
        else {
            //print routes
            RL->printRoutes();
            routeSelect = 0;
        }
    }
}

void busEditing(RouteList* RL, BusList* BL, int &adminSelect) {
    int busSelect = 0;

    while (busSelect <= 0 || busSelect > 4) {
        cout << "\n\t\t\t------------------------- Bus Editing Menu ------------------------\n\t\t\t\t\t1. Insert New Bus\n\t\t\t\t\t2. Delete Bus\n\t\t\t\t\t3. List of Buses\n\t\t\t\t\t4. Exit " << endl;
        cout << "Enter your choice (1/2/3/4)" << endl;
        cin >> busSelect;
        if (busSelect <= 0 || busSelect > 4) {
            cout << "Enter a valied selection.";
        }

        else if (busSelect == 4) {
            adminSelect = 0;
            break;
        }


        else if (busSelect == 1) {
            //insert bus
            RL->printRoutes();
            int* date = new int[3];
            int* time = new int[2];
            int* no = new int[2];
            int seats, price;
            cout << "Select the route by : ";
            cout << "\n\tSelect the Start : "; cin >> no[0];
            cout << "\n\tSelect the End :"; cin >> no[1];

            cout << "Enter the date :\n\tEnter the day :"; cin >> date[0];
            cout << "\n\tEnter the month :"; cin >> date[1];
            cout << "\n\tEnter the year :"; cin >> date[2];

            cout << "Enter the time in 24 hours format : \n\tEnter hour : "; cin >> time[0];
            cout << "\n\tEnter minutes :"; cin >> time[1];

            cout << "\nEnter the number of seats : "; cin >> seats;
            cout << "\nEnter the ticket price :"; cin >> price;

            Bus* bus = new Bus(date, time, no, seats, price);
            BL->insertBus(bus);

            busSelect = 0;

        }

        else if (busSelect == 2) {
            //delete routes
            int deleteCode;
            BL->printBusList();
            cout << "\nSelect the deleting bus : "; cin >> deleteCode;
            int index = BL->searchByCode(deleteCode);
            BL->deleteAt(index);

            busSelect = 0;

        }
        else {
            //List of Buses
            BL->printBusList();

            busSelect = 0;

        }

    }
}






