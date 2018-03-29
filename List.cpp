#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <vld.h>
#include "Header.h"


List::List() // Constructor
{
    size = 0;
    head = NULL;
    tail = NULL;
}

List::List(int v) // Constructor
{
    size = 0;
    head = NULL;
    tail = NULL;
    add_last(v);
}

List::~List() // Destructor 
{
    if (this->head != NULL) {
        Node *temp = this->head;
        for (int i = 0; i < this->size; i++) {
            Node *temp_2 = temp;
            temp = temp->next;
            delete temp_2;
        }
        this->size = 0;
        this->head = NULL;
        this->tail = NULL;
    }
}

int List::getsize() const {
    return (this->size);
}

int List::get(int n) // Getting element number n
{
    if (this->head != NULL && n <= this->size) {
        Node *temp = this->head;
        for (int i = 0; i < n - 1; i++) {
            temp = temp->next;
        }
        return (temp->value);
    }
    return -1;
}

int List::get() // Get value of the 1 element
{
    return (get(1));
}

void List::add(int n, int v) // adding at the #n place v value
{
    Node *new_element = new Node;
    if (this->head == NULL) // empty
    {
        this->head = new_element;
        this->tail = this->head;
        this->head->next = NULL;
        this->tail->prev = NULL;
        new_element->value = v;
    } else {
        if (n == 1) //begining
        {
            new_element->next = this->head;
            this->head = new_element;
            new_element->value = v;
        } else {
            if (n <= this->size) {
                Node *temp = this->head;
                for (int i = 0; i < n - 1; i++) {
                    temp = temp->next;
                }
                new_element->prev = temp->prev;
                temp->prev->next = new_element;
                new_element->next = temp;
				temp->prev = new_element;
            //    temp->next = new_element;
                new_element->value = v;
            } else { //end
                if (n == this->size +1) {
                    this->tail->next = new_element;
                    new_element->next = NULL;
                    this->tail = new_element;
                    new_element->value = v;
                }
            }
        }
    }
    this->size++;
}

void List::add_after(int n, int v) // adding the element after element number n
{
    add(n + 1, v);
}

void List::add_first(int v) // adding the element at the begining
{
    add(1, v);
}

void List::add_last(int v) // adding the element at the end
{
    add(this->size + 1, v);
}


void List::show() const {
    if (this->head != NULL) {
        Node *temp = this->head;
        for (int i = 0; i < this->size; i++) {
            std::cout << i + 1 << " Element: " << temp->value << std::endl;
            temp = temp->next;
        }
    }
}

void List::del(int n) // Delete elements from the n place 
{
    if (this->head != NULL && n <= this->size) {
        {
            Node *temp = this->head;
            if (this->size == 1) {
                delete temp;
                this->head = NULL;
                this->tail = NULL;
                this->size = 0;
            } else {
                Node *temp_2;
                if (n == 1) {//1 place
                    temp_2 = this->head;
                    this->head = this->head->next;
					this->head->prev = NULL;
                    delete temp_2;
                } else {
                    if (n == 2) {//2 place
                        temp_2 = this->head->next;
                        this->head->next = temp_2->next;
                        temp_2->next->prev = this->head;
                        delete temp_2;
                    } else {
                        if (n == size) {//end
                            temp = this->tail;
							temp->next = NULL;
                            this->tail = temp->prev;
                            delete temp;
                        } else {
                            if (n == size - 1) {//before end
                                temp = this->tail->prev;
								temp->prev->next = this->tail;
                                this->tail->prev = temp->prev;
                                delete temp;
                            } else {// Other
                                for (int i = 0; i < n - 2; i++) {
                                    temp = temp->next;
                                }
                                temp->prev->next = temp->next;
                                temp->next->prev = temp->prev;
                                delete temp;
                            }
                        }
                    }
                }
            }
        }
        this->size--;
    }
}

void List::del(int a, int b) // Delete elements by value [a;b]
{
    if (this->head != NULL) {
        int to_delete[10];
        int n = 0;
        Node *temp = this->head;
        for (int i = 1; i <= this->size; i++) {
            if (temp->value >= a && temp->value <= b)
                to_delete[n++] = i;
            temp = temp->next;
        }
        for (int k = 0; k < n - 1; k++) {
            for (int j = k + 1; j < n; j++) {
                if (to_delete[k] < to_delete[j]) {
                    int tempor = to_delete[k];
                    to_delete[k] = to_delete[j];
                    to_delete[j] = tempor;
                }
            }
        }
        for (int i = 0, a = 0; i < n; i++, a++) {
            this->del(to_delete[i]);
        }
    }
}


void List::del() // delete the last element
{
    del(size);
}

void List::del_first() // delete the first element
{
    del(1);
}

void List::del_all() // delete all the elements
{
    if (this->head != NULL) {
        Node *temp = this->head;
        for (int i = 0; i < this->size; i++) {
            Node *temp_2 = temp;
            temp = temp->next;
            delete temp_2;
        }
        this->head = 0;
        this->tail = 0;
        this->size = 0;
    }
}

void List::del_repeat() // delete iterative values
{
    if (this->head != NULL) {
        std::vector<int> vect;   // Values from the list
        std::vector<int> to_delete;        // places to delete

        Node *temp = this->head;
        for (int i = 0; i < this->size; i++) {
            vect.insert(vect.end(), temp->value);
            if (check(vect, temp->value)) //Inside circle
            {
                to_delete.insert(to_delete.end(), i + 1);
            }
            temp = temp->next;
        }

        for (int i = 0, a = 0; i < to_delete.size(); i++, a++)            // delete elements
        {
            this->del(to_delete[i] - a);
        }

        std::vector<int>().swap(vect);                                // delete
        std::vector<int>().swap(to_delete);
    }
}

List &List::operator=(const List &second) {  //copy
    if (*this != second) {      //exist?
        this->del_all();
        if (second.head != NULL) {
			 this->head = new Node;
            Node *temp_1 = this->head;
            Node *temp_2 = second.head;
            for (int i = 1; i <= second.getsize(); i++) {
//				std::cout << temp_1->value << " " << temp_2->value;
                temp_1->value = temp_2->value;
                temp_1->next = new Node;
                temp_1->prev = temp_1;
                temp_1 = temp_1->next;
                temp_2 = temp_2->next;
            }
            temp_1->value = temp_2->value;
            this->tail = temp_1;
            this->tail->prev = temp_1->prev;
            this->size = second.size;
        } else {
            this->size = 0;
            this->head = NULL;
            this->tail = NULL;
        }
    }
    return (*this);
}

List List::operator+(const List &second) const {
    if (second.head != nullptr) {
        List func_list;
        Node *temp;
        temp = this->head;

		func_list.add_first(temp->value);
		temp = temp->next;
        for (int i = 1; i < this->getsize(); i++) {
            func_list.add_last(temp->value);
            temp = temp->next;
        }

        temp = second.head;
        for (int i = 0; i < second.getsize(); i++) {
            func_list.add_last(temp->value);
            temp = temp->next;
        }
        return (func_list);
    }
    return (*this);
}

List List::operator-(const List &second) const {
    if (second.head != NULL && this->head != NULL) {
        std::vector<int> to_delete;
        List func_list = *this;
        Node *temp = second.head;
        Node *temp_2 = func_list.head;
        for (int i = 1; i <= second.getsize(); i++) {
            for (int n = 1; n <= func_list.getsize(); n++) {
                if (temp_2->value == temp->value) {
                    if (!(std::find(to_delete.begin(), to_delete.end(), n) !=
                          to_delete.end())) { //Returns an iterator to the element in the range [to_delete.begin(), to_delete.end()) that compares equal to n
                        to_delete.insert(to_delete.end(), n); //inserts n to to_delete.end()
                        temp_2 = func_list.head;
                        break;
                    }
                }
                temp_2 = temp_2->next;
            }
            temp = temp->next;
        }

        std::sort(to_delete.begin(), to_delete.end()); //down - up
        auto last = unique(to_delete.begin(),
                           to_delete.end()); //Removes all but the first element from every consecutive group of equivalent elements in the range [to_delete.begin(), to_delete.end()).
        to_delete.erase(last,
                        to_delete.end());   //Removes from the vector either a single element (position) or a range of elements [last, to_delete.end())
        for (int i = 0, a = 0; i < to_delete.size(); i++, a++)            // delete elements
        {
            func_list.del(to_delete[i] - a);
        }
        return (func_list);
    }
    return (*this);
}

bool List::operator==(const List &second) const // flag: check if exists
{
    if (this->size != second.size) {
        return (false);
    } else {
        Node *temp_1 = this->head;
        Node *temp_2 = second.head;
        for (int i = 0; i < size; i++) {
            if (temp_1->value != temp_2->value)
                return (false);
            temp_1 = temp_1->next;
            temp_2 = temp_2->next;
        }
        return (true);
    }
}

bool List::operator!=(const List &second) const {
    return (!(*this == second));
}

bool List::operator>(const List &second) const {
    if (*this == second || this->size < second.size)
        return (false);
    else {
        if (this->size == second.size) {
            Node *temp_1 = this->head;
            Node *temp_2 = second.head;
            for (int i = 0; i < size; i++) {
                if (temp_1->value < temp_2->value)
                    return (false);
                temp_1 = temp_1->next;
                temp_2 = temp_2->next;
            }
        }
        return (true);
    }
}

bool List::operator<(const List &second) const {
    return (!(*this == second || *this > second));
}

bool List::operator<=(const List &second) const {
    return (!(*this > second));
}

bool List::operator>=(const List &second) const {
    return (!(*this < second));
}

bool check(std::vector<int> &vect, int value) // Side_function for searching iterative values

{
    for (int i = 0; i < vect.size(); i++) {

        if (vect[i] == value)              // first time
        {
            for (int n = i + 1; n < vect.size(); n++)
                if (vect[n] == value)             // more than 1
                    return (true);
        }
    }
    return (false);
}

