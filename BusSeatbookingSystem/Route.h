#pragma once
#include <iostream>


using namespace std;

class Route
{
public:
	string town;
	int code;
	Route* next;

	Route(string atown) {
		town = atown;
		code = 0;
	}
};

class RouteList
{
public:
	Route* head;
	Route* tail;
	int index;

	void insertRoute(string atown) {
		Route* temp = new Route(atown);
		if (head == NULL) {
			head = temp;
			tail = temp;
			index = 1;
		}
		else {
			tail->next = temp;
			tail = temp;
			index++;
		}
		temp->code = index;
	}

	int routeSearch(string townName) {
		Route* current = head;
		for (int i = 0; i < index; i++) {
			if (current->town == townName)
				return current->code;
			current = current->next;
		}
		return -1;
	}

	void printRoutes() {
		cout << "\n\t\t\t\t\t------------ City List ------------\n";
		Route* current = head;
		for (int i = 0; i < index; i++) {
			cout << "\t\t\t\t\t" << current->code << " - " << current->town << endl;
			current = current->next;
		}
	}

	void deleteFirst() {
		if (head == NULL)
			cout << "No any added Routes." << endl;
		else {
			Route* temp = head;
			head = temp->next;
			temp->next = NULL;
			delete temp;
			index--;
		}
	}

	void deleteLast() {
		if (head == NULL)
			cout << "NO any added Routes." << endl;
		else {
			Route* temp = tail;
			if (index == 1) {
				head = NULL;
				tail = NULL;
				delete temp;
			}
			else {
				Route* current = head;
				for (int i = 0; i < index - 2; i++) {
					current = current->next;
				}
				tail = current;
				tail->next = NULL;
				delete temp;
			}
			index--;
		}
	}

	void deleteAt(int indx) {
		if (indx<1 || indx>index)
			cout << "unmatched route entered";
		else if (indx == 1)
			deleteFirst();
		else if (indx == index)
			deleteLast();
		else {
			Route* current = head;
			for (int i = 1; i < indx - 1; i++) {
				current = current->next;
			}
			Route* temp = current->next;
			current->next = temp->next;
			delete temp;
			index--;
		}
	}








};



