//
//  LinkedList.h
//  Generic Type Linked List
//

#ifndef LINKEDLIST_h
#define LINKEDLIST_h

#include <iostream>

//
// Generic Type Node
//
template <class T>
struct node{
    T data;
    node <T> *next;
};

//
// Generic Linked List
//
template <class T>
class LinkedList{
public:
    //
    //  Variables
    //
    int sizeOfList = 0;
    node<T> *head; // Head node
    node<T> *tail; // Tail node

    //
    // LinkedList Constructor
    //
    LinkedList<T>(){
        head = NULL; // Head node
        tail = NULL; // Tail node
    }

    //
    // Insert data to linkedlist
    //
    void insert(T data){
        if(!head){
            // Create new node type T
            head = new node<T>;
            head->data = data;
            head->next = NULL;
            tail = head;
            sizeOfList++;
        }
        else {
            // The list isn't empty
            if(tail == head){
                tail = new node < T > ;
                tail->data = data;
                tail->next = NULL;
                head->next = tail;
                sizeOfList++;
            }
            else{
                // The list has more than one element
                node<T> *insdata = new node<T>;
                insdata->data = data;
                insdata->next = NULL;
                tail->next = insdata;
                tail = insdata;
                sizeOfList++;
            } // end of the if
        } // end of the else
    } // end of the insert

    //
    //  Get element with index
    //
    T get(int index){
        if(index == 0){
            // Get the head element
            return this->head->data;
        }
        else{
            // Get the element at position of 'index'
            node<T> * curr = this->head;
            for(int i = 0; i < index; ++i){
                curr = curr->next;
            }
            return curr->data;
        }
    }// end of the get

    //
    //  Get with index by operator
    //
    T operator[](int index){
        return get(index);
    }

    //
    //  Get size of the linked list
    //
    int getSize(){
        return sizeOfList;
    }

    //
    //  Remove first
    //
    void removeFirst(){
        if(head == NULL){
            return;
        }
        else{
            node<T> *removeNode;
            removeNode = head;
            if(head == tail){
                head = NULL;
                tail = NULL;
            }
            else{
                head = head->next;
            }
            delete removeNode;
            sizeOfList--;
        }
    }

    //
    //  Remove last
    //
    void removeLast(){
        if(tail == NULL){
            return;
        }
        else{
            node<T> *removeNode;
            removeNode = tail;
            if(head == tail){
                head = NULL;
                tail = NULL;
            }
            else{
                node<T> previousToTail = head;
                while(previousToTail->next != tail){
                    previousToTail = previousToTail->next;
                }
                tail = previousToTail;
                tail->next = NULL;
            }
            delete removeNode;
            sizeOfList--;
        }
    }

    //
    //  Remove Next
    //
    void removeNext(node <T> *previous){
        if (previous == NULL){
            removeFirst();
        }
        else if(previous->next == tail){
            node<T> *removedNode = previous->next;
            tail = previous;
            tail->next = NULL;
            delete removedNode;
            sizeOfList--;
        }
        else if(previous==tail){
            return;
        }
        else{
            node<T> *removedNode = previous->next;
            previous->next = removedNode->next;
            delete removedNode;
            sizeOfList--;
        }
    }

    //
    //  Remove as index number
    //
    void remove(int index){
        if(index == 0){
            return;
        }
        else{
            node<T> *previous = head;
            node<T> *curr = this->head;
            for(int i = 0; i < index; ++i){
                previous = curr;
                curr = curr->next;
            }
            previous->next = curr->next;
            delete curr;
            sizeOfList--;
        }
    } // end of the remove
};// end of the LinkedList
#endif
