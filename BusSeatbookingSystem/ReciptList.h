#pragma once
#include <cstddef>
#include <iostream>


using namespace std;

class Recipt {
public:
	int ReciptNo;
	int numOfSeats;
	int* seats;
	int busCode;
	//int price;

	Recipt* next;
	Recipt* prev;

	Recipt() {
		ReciptNo = -1;
		numOfSeats = 0;
		seats = new int[numOfSeats];
		busCode = 0;
		next = NULL;
		prev = NULL;
	}

	Recipt(int e, int SeatsNum, int code) { //overloaded constructor
		ReciptNo = e;
		numOfSeats = SeatsNum;
		seats = new int[numOfSeats];
		busCode = code;
		next = NULL;
		prev = NULL;
	}

	void setSeatNum(int i, int num) {
		seats[i] = num;
	}

	void printBookedSeats() {
		if (numOfSeats == 0) {
			cout << "\nNo seats are booked..";
		}
		else {
			for (int i = 0; i < numOfSeats-1; i++) {
				cout << seats[i] << "/";
			}
			cout << seats[numOfSeats - 1] << endl;
		}

	}

	bool isItAvailable(int* soldSeats, int arrySize, int i) {
		for (int j = 0; j < arrySize; j++) {
			if (soldSeats[j] == i)
				return false;
		}
		return true;
	}

	void updateSeats(int* RemovedSeats, int RemovedseatsNum){
        int* NewSeats = new int[numOfSeats-RemovedseatsNum];
        int j = 0;
        for(int i=0; i<numOfSeats; i++){
            if(isItAvailable(RemovedSeats, RemovedseatsNum, seats[i])){
				NewSeats[j] = seats[i];
				j++;
            }
            else{
                
            }
        }
        numOfSeats = numOfSeats-RemovedseatsNum;
        seats = NewSeats;
	}




	void PrintRecipt() {
		cout << "\n\tRecipt No.\t: " << ReciptNo <<  endl;
		cout << "\tBus Code\t: " << busCode << endl;
		cout << "\tBooked Seats\t: ";
		printBookedSeats();
	}

	bool searchSeat(int seatNo){
        for(int i=0; i<numOfSeats; i++){
            if(seats[i] == seatNo)
                return true;
        }
        return false;
	}
};

class Recipt_List {
private:
	Recipt* head;
	Recipt* tail;
	int size;

public:
	Recipt_List() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	Recipt* getHead() {
		return head;
	}

	Recipt* getTail() {
		return tail;
	}

	void insertFirst(int e, int SeatsNum, int code) {
		//Create the node
		Recipt* temp = new Recipt(e, SeatsNum, code);

		if (head == NULL) { //empty list
			head = temp;
			tail = temp;
			size++;
		}
		else { //non empty list
			temp->next = head;
			head = temp;
			size++;
		}
	}

	void insertLast(int e, int SeatsNum, int code) {
		//Create the node
		Recipt* temp = new Recipt(e, SeatsNum, code);

		if (head == NULL) {
			head = temp;
			tail = temp;
			size++;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			size++;
		}
	}

	void insertAt(int pos, int e, int SeatsNum, int code) {

		if (pos < 0 || pos > size)
			cout << "Not a valid position" << endl;
		else if (pos == 0)
			insertFirst(e, SeatsNum, code);
		else if (pos == size)
			insertLast(e, SeatsNum, code);
		else {
			Recipt* temp = new Recipt(e, SeatsNum, code);
			Recipt* current = head;

			for (int i = 0; i < pos - 1; i++) {
				current = current->next;
			}

			temp->next = current->next;
			temp->prev = current;
			current->next = temp;
			(temp->next)->prev = temp;

			size++;
		}
	}

	void deleteFirst() {

		if (head == NULL)
			cout << "List is empty" << endl;
		else {
			Recipt* temp = head;

			if (size == 1) {
				delete temp;
				head = NULL;
				tail = NULL;
				size = 0;
			}
			else {
				head = head->next;
				head->prev = NULL;
				delete temp;
				size--;
			}
		}
	}

	void deleteLast() {

		if (head == NULL)
			cout << "List is empty" << endl;
		else {
			Recipt* temp = tail;
			if (size == 1) {
				delete temp;
				head = NULL;
				tail = NULL;
				size = 0;
			}
			else {
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
				size--;
			}
		}
	}

	void deleteAt(int pos) {

		if (pos < 0 || pos >= size)
			cout << "Invalid position" << endl;
		else if (pos == 0)
			deleteFirst();
		else if (pos == size - 1)
			deleteLast();
		else {

			Recipt* current = head;
			for (int i = 0; i < pos; i++) {
				current = current->next;
			}
			Recipt* temp = current;
			(current->prev)->next = temp->next;
			(current->next)->prev = temp->prev;
			delete temp;
			size--;

		}
	}

	void deleteWith(int elem) { //print the positions of the nodes with the given element
		/*/Node current = head;
		for (int i = 0; i < size; i++) {
			if (current->elem == elem)
				deleteAt(i);
			current = current->next;
		}*/
		Recipt* current = head;
		Recipt* prev = NULL;
		while (current != NULL) {
			if (current->ReciptNo == elem) {
				if (current == head) {
					Recipt* temp = current;
					current = current->next;
					head = current;
					delete temp;
				}
				else if (current == tail) {
					Recipt* temp = current;
					current = current->next;
					prev->next = current;
					tail = prev;
					delete temp;
				}
				else {
					Recipt* temp = current;
					current = current->next;
					prev->next = current;
					delete temp;
				}
				size--;
				continue;
			}
			prev = current;
			current = current->next;
		}
	}

	void search(int elem) { //print the positions of the nodes with the given element
		Recipt* current = head;
		cout << "Positions of the nodes with element " << elem << " : ";
		for (int i = 0; i < size; i++) {
			if (current->ReciptNo == elem)
				cout << i << " ";
			current = current->next;
		}
		cout << endl;
	}

	bool isAvailable(int billNo) {
		bool status = false;
		if (head == NULL) {
			return status;
		}
		else {
			Recipt* current = head;
			for (int i = 0; i < size; i++) {
				if (current->ReciptNo == billNo) {
					status = true;
					break;
				}
			}
			return status;

		}

	}

	Recipt* find(int elem) {
		Recipt* current = head;
		for (int i = 0; i < size; i++) {
			if (current->ReciptNo == elem)
				return current;
			current = current->next;
		}
		return NULL;
	}

	void printReciptList() {
		Recipt* current = head;

		while (current != NULL) {
			current->PrintRecipt();
			current = current->next;
		}

		cout << endl;
	}



};
