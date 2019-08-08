//
//  studentList.h
//  Homework 2 Version 2
//
//  Created by Kevin Tran on 6/26/19.
//  Copyright © 2019 Kevin Tran. All rights reserved.
//

#include "student.h"
#include <iostream>
#include <string>

using namespace std;

#ifndef studentList_h
#define studentList_h

class StudentList
{
private:
    int size=0 ;
    int length=0 ;
    Student *list = NULL;
    
public:
    StudentList();
    StudentList(int listSize);
    StudentList& operator=(const StudentList &other); //
    int getSize() const;
    int getLength() const;
    StudentList(const StudentList &r);
    Student getStudentAt(int index) const;
    void addStudent(const Student &element); //Students can be added at the end of the array, and sorted later
    int binarySearchID(string ID) const;     //Search for a student using ID and binary search
    //Return index or -1 if not found
    
    int seqSearchFirstName(string fn) const; //Search for a student using first name and sequential search
    //int seqSearchFirstNameindex(string fn) const;
    //Return index or -1 if not found
    int seqSearchLastName(string ln) const;  //Search for a student using last name and sequential search
    // int seqSearchLastNameindex(string ln) const;
    //Return index or -1 if not found
    int seqSearchEmail(string em) const;     //Search for a student using email and sequential search
    //int seqSearchEmailindex(string em) const;
    //Return index or -1 if not found
    void sort();     //sort students by ID (can use any sorting algorithm - but don't change the function call
    
    ~StudentList();
};

//Default Constructor
StudentList::StudentList(){
    size = 0;
    length = 0;
    list = new Student[size];
}

//Constructor with parameter
StudentList::StudentList(int listSize){
    if(size < 0){
        size = 10;
    }
    else{
        size = listSize;
    }
    
    length = 0;
    
    list = new Student[size];
}

//Copy Constructor
StudentList::StudentList(const StudentList & r){
    size = r.size;
    length = r.length;
    list = new Student[size];
    
    for(int i = 0; i < length; i++){
        list[i] = r.list[i];
    }
}

//Overload Operator
StudentList& StudentList::operator=(const StudentList &other){
    if(&other != this){
        delete [] list;
        
        size = other.size;
        length = other.length;
        list = new Student[size];
        
        for(int i = 0; i < length; i++){
            list[i] = other.list[i];
        }
    }
    return *this;
}

//Destructor
StudentList::~StudentList(){
    if(list != NULL){
        delete [] list;
        list = NULL;
    }
}

int StudentList::getSize() const{
    return size;
}

int StudentList::getLength() const{
    return length;
}

Student StudentList::getStudentAt(int index) const{
    if(length == 0){
        cout << "list is empty" << endl;
        exit(0);
    }
    return list[index];
}

//add student at end of list and sort later
void StudentList::addStudent(const Student &element){
    if(length == size){
        cout << "list is full" << endl;
    }
    else if(length == 0){
        list[0] = element;
    }
    else{
        list[length] = element;
    }
    length++;
}

int StudentList::binarySearchID(string ID) const{
    int first = 0;
    int last = length - 1;
    int mid;
    bool found = false; //is this really necessary?
    int count = 0;
    
    
    while (!found && first <= last){
        count++;
        mid = (first+last) / 2;
        if(list[mid].getID() == ID){ //if the value in the array at mid a match
            found = true; //is this really necessary?
            //return mid;
            
        }
        else if(list[mid].getID() > ID){ //item is smaller so search left side
            last = mid  - 1; //chagne last to be 1 spot below mid.
        }
        else if(list[mid].getID() < ID){ //item is greater so search right side
            first = mid + 1; //change first to be 1 spot above mid.
        }
        
    }
    
    if(found == true){
        cout << "ID " << ID << " found with binary search after " << count << " accesses." << endl;
        cout << "Index ";
        return mid; //returns number of times it had to search
        //return mid; returns the index
    }
    
    else{
        exit(0);
        return -1;
    }
}

int StudentList::seqSearchFirstName(string fn) const{
    int count = 0;
    for(int i = 0; i < length; i++){
        count++;
        if(list[i].getFirstName() == fn){
            cout << "First name " << fn << " found with sequential search after " << count << " accesses." << endl;
            return i;
        }
    }
    exit(0);
    return -1;
}

int StudentList::seqSearchLastName(string ln) const{
    int count = 0;
    for(int i = 0; i < length; i++){
        count++;
        if(list[i].getLastName() == ln){
            cout << "Last name " << ln << " found with sequential search after " << count << " accesses." << endl;
            return i;
        }
    }
    exit(0);
    return -1;
}
/*
 int StudentList::seqSearchLastNameindex(string ln) const{
 int count = 0;
 for(int i = 0; i < length; i++){
 count++;
 if(list[i].getLastName() == ln){
 return i;
 }
 }
 exit(0);
 return -1;
 }
 */
int StudentList::seqSearchEmail(string em) const{
    int count = 0;
    for(int i = 0; i < length; i++){
        count++;
        if(list[i].getEmailAddress() == em){
            cout << "Email " << em << " found with sequential search after " << count << " accesses." << endl;
            return i;
        }
    }
    exit(0);
    return -1;
}
/*
 int StudentList::seqSearchEmailindex(string em) const{
 int count = 0;
 for(int i = 0; i < length; i++){
 count++;
 if(list[i].getEmailAddress() == em){
 return i;
 }
 }
 exit(0);
 return -1;
 }
 */

//using selection sort.
void StudentList::sort(){
    for(int i = 0; i < size - 1;i++){
        int indexSmallest = i;
        for(int j = i + 1; j < size; j++){
            if(list[j].getID() < list[indexSmallest].getID()){
                indexSmallest = j;
            }
        }
        
        //swap process
        Student temp;
        temp = list[i];
        list[i] = list[indexSmallest];
        list[indexSmallest] = temp;
    }
}



#endif /* studentList_h */

