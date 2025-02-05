#pragma once
#include <iostream>
using namespace std;

class Seat
{
public:
	int No;
	int billNo;
	Seat* next;
	Seat* prev;

	Seat() {
		No = 0;
		billNo = 0;
		next = NULL;
		prev = NULL;
	}

	Seat(int no, int billno) {
		No = no;
		billNo = billno;
		next = NULL;
		prev = NULL;
	}
};

class seatList {
	Seat* head;
	Seat* tail;
	int size;
	int capacity;

public:
	

	seatList() {
		head = NULL;
		tail = NULL;
		capacity = 0;
		size = 0;
	}

	seatList(int NumofSeats) {
		head = NULL;
		tail = NULL;
		capacity = NumofSeats;
		size = 0;
	}

	void setCapacity(int numOfSeats) {
		capacity = numOfSeats;
	}

	int getCapacity() {
		return capacity;
	}

	int getSize() {
		return size;
	}

	bool isSeatsAvailable() {
		if (size == capacity)
			return false;
		else
			return true;
	}

	int availableSeats() {
		return capacity - size;
	}

	void seatBooking(int no, int billno) {
		if (size == capacity)
			cout << "Sorry, No bookings available in this bus.";

		Seat* temp = new Seat(no, billno);
		if (head == NULL) {
			head = temp;
			tail = temp;
			size = 1;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			size++;
		}
	}

	void cancelFirst() {
		if (head == NULL)
			cout << "Seats were not booked";
		else {
			Seat* temp = head;
			if (size == 1) {
				delete temp;
				head = NULL;
				tail = NULL;
			}
			else {
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			size--;
		}
	}

	void cancelLast() {
		if (head == NULL)
			cout << "Seats were not booked";
		else {
			Seat* temp = tail;
			if (size == 1) {
				delete temp;
				head = NULL;
				tail = NULL;
			}
			else {
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			size--;
		}
	}

	Seat* Seatsearch(int no) {
		Seat* current = head;
		while (current != NULL) {
			if (current->No == no) {
				return current;
			}
			else {
				current = current->next;
			}
		}
		return 0;
	}

	void cancelBooking(int no) {
		Seat* bookedSeat = Seatsearch(no);
		if (bookedSeat == NULL) {
			cout << "This seat has not been booked.";
		}
		else {
			if (bookedSeat == head) {
				cancelFirst();
			}
			else if (bookedSeat == tail) {
				cancelLast();
			}
			else {
				bookedSeat->prev->next = bookedSeat->next;
				bookedSeat->next->prev = bookedSeat->prev;
				bookedSeat->next = NULL;
				bookedSeat->prev = NULL;
				delete bookedSeat;
				size--;
			}
			cout << "Succesfuly canceled seat No." << no << " booking." << endl;

		}

	}

	int* bookedSeatNos() {
		
		
		if (head == NULL) {
			int* bookedSeats = new int[1];
			bookedSeats[0] = 0;
			return bookedSeats;
		}
		else {
			Seat* current = head;
			int* bookedSeats = new int[size];
			for (int i = 0; i < size; i++) {
				bookedSeats[i] = current->No;
				current = current->next;
			}
			return bookedSeats;
		}
	}

	void printBookedSeats() {
		if (head == NULL)
			cout << "No seats are booked";
		else {
			Seat* current = head;
			for (int i = 0; i < size; i++) {
				cout << current->No << " ";
				current = current->next;
			}
		}		
	}












};


