#include <iostream>
using namespace std;

class Node
{
public:
    Node* next;
    int data;

    Node()
    {
        data = -1;
        next = NULL;
    }

    Node(int elem) {
        data = elem;
        next = NULL;
    }

};


class LinkedList
{
private:
    Node* Head;
    Node* Tail;
    int size;

public:
    LinkedList() {
        Head = NULL;
        Tail = NULL;
        size = 0;
    }

    Node* getHead() {
        return Head;
    }

    int getSize() {
        return size;
    }

    void insertFirst(int data) {
        Node* temp = new Node(data);
        if (Head == NULL)
        {
            Head = temp;
            Tail = temp;
            size = 1;
        }
        else
        {
            temp->next = Head;
            Head = temp;
            size++;
        }

    }

    void inssertLast(int data) {
        Node* temp = new Node(data);
        if (Tail == NULL)
        {
            Head = temp;
            Tail = temp;
            size = 1;
        }
        else
        {
            Tail->next = temp;
            Tail = temp;
            size++;
        }
    }

    void insertAt(int pos, int data) {
        if (pos<0 || pos>size)
            cout << "invalied index" << endl;
        else if (pos == 0)
            insertFirst(data);
        else if (pos == size)
            inssertLast(data);
        else
        {
            Node* temp = new Node(data);
            Node* current = Head;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
            size++;

        }
    }

    void deleteFirst()
    {
        if (Head == NULL)
            cout << "Empty List.." << endl;
        else {
            Node* temp = Head;
            if (size == 1)
            {
                delete temp;
                Head = NULL;
                Tail = NULL;
                size = 0;
            }
            else
            {
                Head = temp->next;
                delete temp;
                size--;
            }

        }
    }

    void deleteLast()
    {
        if (Head == NULL)
            cout << "Empty List " << endl;
        else
        {
            Node* temp = Tail;
            if (size == 1)
            {
                delete temp;
                Head = NULL;
                Tail = NULL;
                size = 0;
            }
            else
            {
                Node* current = Head;
                for (int i = 0; i < size - 2; i++)
                {
                    current = current->next;
                }
                delete temp;
                Tail = current;
                Tail->next = NULL;
                size--;
            }

        }

    }

    void deleteAt(int pos)
    {
        if (Head == NULL)
        {
            cout << "Empty List " << endl;
        }
        else if (pos == 0)
        {
            deleteFirst();
        }
        else if (pos == size - 1)
        {
            deleteLast();
        }
        else
        {
            Node* current = Head;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
        }
    }



    void printList()
    {
        Node* current = Head;
        for (int i = 0; i < size; i++)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    bool isAvalable(int Code) {
        if (Head == NULL)
            return false;
        else {
            Node* current = Head;
            for (int i = 0; i < getSize(); i++) {
                if (current->data == Code) 
                    return true;             
                current = current->next;
            }
            return false;
        }
        
    }





};

