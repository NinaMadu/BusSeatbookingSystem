#pragma once
#include <iostream>
#include <string>
#include "Seat.h";
#include "LinkedList.h";



using namespace std;

class Bus
{
public:
	int bDate[3]; // {D,M,Y}
	int bTime[2]; // {h,m}
	int bNo[2]; // {start, end}
	int noOfSeats;
	int code;
	int ticketPrice;
	seatList bookedSeats;
	Bus* next;



	Bus() {
		for (int i = 0; i < 3; i++) {
			bDate[i] = 0;
		}
		bTime[0] = 0;
		bTime[1] = 0;

		bNo[0] = 0;
		bNo[1] = 0;

		noOfSeats = 0;
		bookedSeats.setCapacity(0);
		
		ticketPrice = 0;
		code = 0;
		next = NULL;

	}

	Bus(int* date, int* time, int* no, int seats, int price) {
		for (int i = 0; i < 3; i++) {
			bDate[i] = date[i];
		}
		bTime[0] = time[0];
		bTime[1] = time[1];

		bNo[0] = no[0];
		bNo[1] = no[1];

		noOfSeats = seats;
		ticketPrice = price;
		bookedSeats.setCapacity(noOfSeats);
		code = 0;
		next = NULL;
	}

	void PrintBus() {
		cout << "\n\tBus No.\t: " << code << "/" << bNo[0] << bNo[1];
		cout << "\n\tDate\t: " << bDate[0] << "/" << bDate[1] << "/" << bDate[2];
		cout << "\n\tTime\t: " << bTime[0] << ":" << bTime[1];
	}

};

class BusList {
	Bus* head;
	Bus* tail;
	int size;
	int lCode;
public:

	void insertBus(Bus* bus) {
		Bus* temp = bus;
		if (head == NULL) {
			head = temp;
			tail = temp;
			size = 1;
		}
		else {
			tail->next = temp;
			tail = temp;
			size++;
		}
		temp->code = size;
		lCode = size;
	}



	LinkedList* busTimeSearch(int* time) {
		LinkedList* codes = new LinkedList();
		Bus* current = head;
		for (int i = 0; i < size; i++) {
			if (current->bTime[0] == time[0] && current->bTime[1] == time[1])
				codes->inssertLast(current->code);
			current = current->next;
		}
		return codes;
	}

	LinkedList* busDateSearch(int* date) {
		LinkedList* codes = new LinkedList();
		Bus* current = head;
		for (int i = 0; i < size; i++) {
			if (current->bDate[0] == date[0] && current->bDate[1] == date[1] && current->bDate[2] == date[2])
				codes->inssertLast(current->code);
			current = current->next;
		}
		return codes;
	}

	LinkedList* busRouteSearch(int* No) {
		LinkedList* codes = new LinkedList();
		Bus* current = head;
		for (int i = 0; i < size; i++) {
			if (current->bNo[0] == No[0] && current->bNo[1] == No[1])
				codes->inssertLast(current->code);
			current = current->next;
		}
		return codes;
		//if (codes->getsize() != 0)
			//return codes;
		//else
			//cout << "\nNo buses are avaliable in selected route";
	}


	void printBusList() {
		if (head != NULL) {
			cout << "\n --List of Buses-- \n\tCode/Route\t\tNum of Seats" << endl;
			Bus* current = head;
			for (int i = 0; i < size; i++) {
				cout <<"\n"<< current->code << " / " << current->bNo[0] << current->bNo[1] << "\t\t" << current->noOfSeats << endl;
				current = current->next;
			}
		}
		else {
			cout << "\nbuses have not added yet.";
		}
	}

	void deleteFirst() {
		if (head == NULL)
			cout << "No any added Routes." << endl;
		else {
			Bus* temp = head;
			head = temp->next;
			temp->next = NULL;
			delete temp;
			size--;
		}
	}

	void deleteLast() {
		if (head == NULL)
			cout << "NO any added Routes." << endl;
		else {
			Bus* temp = tail;
			if (size == 1) {
				head = NULL;
				tail = NULL;
				delete temp;
			}
			else {
				Bus* current = head;
				for (int i = 0; i < size - 2; i++) {
					current = current->next;
				}
				tail = current;
				tail->next = NULL;
				delete temp;
			}
			size--;
		}
	}

	void deleteAt(int indx) {
		if (indx<1 || indx>size)
			cout << "unmatched route entered";
		else if (indx == 1)
			deleteFirst();
		else if (indx == size)
			deleteLast();
		else {
			Bus* current = head;
			for (int i = 1; i < indx - 1; i++) {
				current = current->next;
			}
			Bus* temp = current->next;
			current->next = temp->next;
			delete temp;
			size--;
		}

	}

	int searchByCode(int Code) {
		if (Code <= 0 || Code > lCode) {
			cout << "Enter a valied code\n";
			int nextCode;
			cin >> nextCode;
			searchByCode(nextCode);
		}
		else {
			Bus* current = head;
			int index = 1;
			while (current->code != Code) {
				current = current->next;
				index++;
				if (current->next == NULL) {
					//cout << "No bus found for enterd code.\n";
					break;
				}
			}
			return index;
		}
	}

	Bus* getByCode(int Code) {
		if (Code <= 0 || Code > lCode) {
			cout << "Enter a valied valied code :\n";
			cin >> Code;
			searchByCode(Code);
		}
		else {
			Bus* current = head;
			while (current->code != Code) {
				current = current->next;
				if (current->next == NULL) {
					//cout << "No bus found for enterd code.\n";
					break;
				}
			}
			return current;
		}
	}

	void printByCode(int Code) {
		Bus* bus = getByCode(Code);
		cout <<"\n"<< bus->code << " - " << "\t" << bus->bDate[0] <<"/" << bus->bDate[1] <<"/" << bus->bDate[2] << "\t"
			<< bus->bTime[0] << ":" << bus->bTime[1] << "\n";

	}





};



