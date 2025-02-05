#include <iostream>
#include <string>
#include "Bus.h";
#include "Seat.h";
#include "Route.h";
#include "ReciptList.h";
#include "Functions.h";
//#include "LinkedList.h";


using namespace std;



int main()
{
    
    RouteList* RL = new RouteList();
    BusList* BL = new BusList();
    Recipt_List* RecL = new Recipt_List();
    int billNo = 0;
    string username = "admin";
    string password = "password";
    std::cout << "\t\t\t-------------------------------------------------------------------\n";
    std::cout << "\t\t\t------------ Welcome to Highway Bus Seat Booking System -----------\n";
    std::cout << "\t\t\t-------------------------------------------------------------------\n";
    //cout << "Select your mode\n1. Seat Booking\n2. Cancel Booking\n3. Admin Mode\n4. Details\n5. Exit"<<endl;

    int selection = 0;

    while (selection <= 0 || selection > 5) {
        cout << "\n\n\t\t\t-------------------------------------------------------------------"<< "\n\t\t\t\t\t------------ Main Menu -----------\n\t\t\t\t\t1.  Seat Booking\n\t\t\t\t\t2. Cancel Booking\n\t\t\t\t\t3. Admin Mode\n\t\t\t\t\t4. Details\n\t\t\t\t\t5. Exit" << endl << "\t\t\t-------------------------------------------------------------------\n";
        cout << "Enter your choice (1/2/3/4/5) : ";
        cin >> selection;
        if (selection <= 0 || selection > 5) {
            cout << "Enter a valied selection.\n";
        }
        else if (selection == 5) {
            break;
        }
        else if (selection == 1) {
            
            if (SeatBooking(BL, RL, billNo, RecL) == false) {
                selection = 0;
            }

            /*int outSelect = 0;
            LinkedList* busList = new LinkedList();
            busList = busSelectByRoute(BL, RL);
            if (busList->getSize() > 0) {
                if(BookingSeats(BL, busList, RecL, billNo))
                {
                    cout << "\n\n1. Book more seats.\n2. Exit to main menu\n ";
                    int select; cin >> select;
                    if (select == 1) {
                        // run agian the function..
                    }
                    else {
                        //return outselect -> 2
                    }
                }
            }


            int condition = busList->getSize();
            while (condition < 1) {
                busList = busSelectByRoute(BL, RL);
                condition = busList->getSize();
                if (condition > 0) {
                    bool booked = true;
                    while (booked == true) {
                        booked = BookingSeats(BL, busList, RecL, billNo);
                        int select;
                        cout << "\n\n1. Book more seats.\n2. Exit to main menu\n ";
                        cin >> select;
                        if (select == 1) {
                            booked = true;
                            condition = 0;
                            printBusList(busList, BL);
                            //busList->printList();
                        }                         

                        else  {
                            booked = false;
                            outSelect = 2;
                            break;
                        }                      

                        
                            
                    }
                    
                    if (outSelect == 2)
                        selection = 0;
                        break;

                    cout << "\n1. Select available bus \n2. Exit\n";
                    cin >> outSelect;
                    if (outSelect == 1) {
                        condition = 0;
                    }
                    else {
                        selection = 0;
                        break;
                    }

                    //complete this..
                }
            } */         

                     



        }
        else if (selection == 2) {
            //cancel booking

            cout << "\n\t\t\t-------------------------- Canceling Menu -------------------------";

            bool loop = true;
            int inSelection;
            while (loop) {
                cout << "\n\t\t\t\t\t1. Cancel your booking\n\t\t\t\t\t2. Cancel booked seats and update booking\n\t\t\t\t\t3. Back\n ";
                 cin >> inSelection;
                bool condition = false;
                if (inSelection == 1) {
                    condition = cancelBooking(BL, RecL);
                    selection = 0;
                    loop = false;
                }
                else if (inSelection == 2) {
                    condition = cancelBySeats(BL, RecL);
                    selection = 0;
                    loop = false;
                }
                else if (inSelection == 3) {
                    selection = 0;
                    loop = false;
                }
                else {
                    loop = true;
                }
            }
            

            /*bool condition = false;
            while (condition == false) {
                condition = cancelBooking(BL, RecL);
            }
            selection = 0;


            cancelBySeats(BL, RecL);*/
        }
        else if (selection == 3) {
            //admin mode
            if (AdminloginMenu(username, password)) {
                cout << "\n\t\t\t--------------------------- Admin Mode ---------------------------" << endl;
                cout << endl;
                //cout << "1. Editing Routes\n2. Editing Buses\n3. Change Password\n4. Exit " << endl;
                int adminSelect = 0;
                while (adminSelect <= 0 || adminSelect > 4) {
                    cout << "\n\t\t\t--------------------------- Admin Menu ---------------------------\n\t\t\t\t\t1. Editing Routes\n\t\t\t\t\t2. Editing Buses\n\t\t\t\t\t3. Change Password\n\t\t\t\t\t4. Exit " << endl;
                    cout << "Enter your choice (1/2/3/4) : " ;
                    cin >> adminSelect;
                    if (adminSelect <= 0 || adminSelect > 4) {
                        cout << "Enter a valied selection.";
                    }

                    else if (adminSelect == 4) {
                        selection = 0;
                        break;
                    }


                    else if (adminSelect == 1) {
                        //Editing routes
                        rootEditing(RL, adminSelect);
                        

                    }


                    else if (adminSelect == 2) {
                        //Editing Buses
                        busEditing(RL, BL, adminSelect);
                        

                    }
                    else if (adminSelect == 3) {
                        //Change Password
                        changePassword(password);
                        adminSelect = 0;

                    }
                }
            }        



        }
        else {
            //deatils
\
        }

    }
    return 0;







}

