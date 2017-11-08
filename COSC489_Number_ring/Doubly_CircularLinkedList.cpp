//
//  Doubly_CircularLinkedList.cpp
//  COSC489_Number_ring
//
//  Created by Aaron Davis on 11/7/17.
//  Copyright © 2017 Frostburg State University. All rights reserved.
//

#include "Doubly_CircularLinkedList.hpp"

/*
Node class with global start and end nodes
*/

struct Node {
    
    int data;
    struct Node *next;
    struct Node *prev;
}*start, *end;

int count = 0;
struct Node **pointr;

class Doubly_CircularLinkedList {
    
    public:
        Doubly_CircularLinkedList() {
            start = NULL;
            end = NULL;
        }
    
        /*
        Creates Node structure
        Called within methods so no need for a seperate call
        */
         
        Node *create_node(int a) {
            count++;
            
            struct Node *temp;
            temp = new(struct Node);
            temp->data = a;
            temp->next = NULL;
            temp->prev = NULL;
            
            return temp;
        }
    
        /*
         Insert at beginning or start or head of list
         */
        void insertAtBegin(int value) {
            struct Node *temp = create_node(value);
            
            //Empty List
            if(start == end && start == NULL) {
                start = end = temp;
                start->next = end->next = NULL;
                start->prev = end->prev = NULL;
            }
            
            else {
                temp->next = start;
                start->prev = temp;
                start = temp;
                start->prev = end;
                end->next = start;
                pointr = &start;
            }
        }
    
        void insertAtEnd(int value) {
            struct Node *temp = create_node(value);
            
            //Empty List
            if(start == end & start == NULL) {
                insertAtBegin(value);
            }
            else {
                end->next = temp;
                temp->prev = end;
                end = temp;
                start->prev = end;
                end->next = start;
            }
        }
    
        /*
         Insert node at certain position in list
        */
        void insertAtPos(int value, int pos) {
            struct Node *temp, *s_temp, *ptr;
            temp = create_node(value);
            
            if(start == end && start == NULL) {
                if(pos == 0) {
                    insertAtBegin(value);
                }
                else{
                    std::cout<<"Position out of range of empty list";
                    count--;
                }
            }
            else {
                
                if(pos < 0) {
                    pos = pos * -1;
                }
                
                if(count < pos) {
                    pos = pos-count;
                }
                
                s_temp = start;
                for(int i = 0; i < count; i++) {
                    ptr = s_temp;
                    s_temp = s_temp->next;
                    
                    if(i == pos) {
                        ptr->next = temp;
                        temp->prev = ptr;
                        temp->next = s_temp;
                        s_temp->prev = temp;
                        pointr = &ptr;
                        break;
                    }
                }
            }
        }
    
        void deleteNode(int pos) {
            
           struct Node *s_temp, *ptr;
            if(start == end && start == NULL) {
                std::cout<<"Nothing to delete";
                return;
            }
            
            if(pos < 0) {
                pos = pos * -1;
            }
            
            if(count < pos) {
                pos = pos - count;
            }
            
            s_temp = start;
            
            if(pos == 0) {
                count--;
                end->next = s_temp->next;
                s_temp->next->prev = end;
                start = s_temp;
                free(s_temp);
                return;
            }
            
            for(int i = 0; i < pos - 1; i++) {
                s_temp = s_temp->next;
                ptr = s_temp->prev;
            }
            
            ptr->next = s_temp->next;
            s_temp->next->prev = ptr;
            
            if(pos == count){
                end = ptr;
            }
            
            count--;
            free(s_temp);
        }
    
        void upDate(int value, int pos) {
            if(start == end && start == NULL) {
                std::cout<<"Cannot update empty list"<<std::endl;
                return;
            }
            
            if(pos > 0) {
                pos = pos * -1;
            }
            
            if(count < pos) {
                pos = pos-count;
            }
            
            struct Node *temp = start;
            
            if(pos ==0) {
                temp->data = value;
                return;
            }
            
            for(int i = 0; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            temp->data = value;
        }
    
        void sort() {
            struct Node *temp, *s_temp;
            int tempValue;
            
            if(start == end && start == NULL) {
                std::cout<<"Cannot sort empty list"<<std::endl;
            }
            
            s_temp = start;
            
            for(int i = 0; i < count; i++){
                temp = s_temp->next;
                
                while(temp != start) {
                    if(s_temp->data > temp->data) {
                        tempValue = s_temp->data;
                        s_temp->data = temp->data;
                        temp->data = tempValue;
                    }
                    temp = temp->next;
                }
                s_temp = s_temp->next;
            }
        }
    
        void display() {
            struct Node *temp;
            
            if(start == end && start == NULL) {
                std::cout<<"The list is empty"<<std::endl;
            }
            
            temp = start;
            for(int i = 0; i < count; i++) {
                std::cout<<temp->data<<"<->";
                temp = temp->next;
            }
        }
    
        void Keyword(std::ifstream & stream, std::string word) {
            std::string line;
            while(getline(stream, line)) {
                if(line.find(word) != std::string::npos) {
                    std::cout << line << std::endl;
                }
            }
        }
};

int main() {
    // insert code here...
    
    std::ifstream stream("COSC489_PT_Input_NR.txt");
    std::string dummyLine;
    std::getline(stream, dummyLine);
    
    Doubly_CircularLinkedList list;
    list.insertAtEnd(1);
    list.insertAtEnd(5);
    list.insertAtEnd(3);
    list.insertAtEnd(6);
    list.insertAtEnd(2);
    
    list.insertAtEnd(1);
    list.display();
    std::cout<<""<<std::endl;
    std::cout<<count<<std::endl;
    
    list.sort();
    std::cout<<""<<std::endl;
    list.display();
    
    return 0;
}

