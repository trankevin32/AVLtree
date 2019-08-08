//
//  main.cpp
//  Homework 2 Version 2
//
//  Created by Kevin Tran on 6/26/19.
//  Copyright © 2019 Kevin Tran. All rights reserved.
//

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include "student.h"
#include "studentList.h"
#include "AVLtree.h"

int main() {
    
    cout << "Number of inputs?" << endl;
    int numOfInputs;
    cin >> numOfInputs;
    cin.ignore();
    
    
    StudentList list(numOfInputs);
    Student student;
    class index stuff("hello", 1);
    
    //index class doesn't work if its is lowercase i.
    
    AVLTree<class index> emailTree;
    AVLTree<class index> firstNameTree;
    AVLTree<class index> lastNameTree;
    
    
    
    for(int k = 0; k < numOfInputs; k++){
        string record[4];
        char str[100];
        //cout << "Enter a string " << endl;
        cin.getline(str,100);
        char* point;
        point = strtok(str, ", ");
        
        int i = 0;
        while(point != NULL){
            //cout << point << endl;
            record[i] = point;
            point = strtok(NULL, ", ");
            i++;
        }
        
        student.setID(record[0]);
        student.setFirstName(record[1]);
        student.setLastName(record[2]);
        student.setEmailAddress(record[3]);
        
        list.addStudent(student);
        
    }
    
    list.sort();
    
    //create index object of email, firstName, lastName, and insert it into the respective tree.
    for(int i = 0; i < numOfInputs; i++){
        class index emailString(list.getStudentAt(i).getEmailAddress(),i);
        emailTree.insert(emailString); //passing in an object of class index
        
        class index fnString(list.getStudentAt(i).getFirstName(),i);
        firstNameTree.insert(fnString);
        
        class index lnString(list.getStudentAt(i).getLastName(),i);
        lastNameTree.insert(lnString);
        
    }
    /*
    //create tree of first names.
    for(int i = 0; i < numOfInputs; i++){
        //firstNameTree.insert(list.getStudentAt(i).getFirstName());
        class index fnString(list.getStudentAt(i).getFirstName(),i);
        firstNameTree.insert(fnString);
    }
    
    //create tree of last names.
    for(int i = 0; i < numOfInputs; i++){
        //lastNameTree.insert(list.getStudentAt(i).getLastName());
        class index lnString(list.getStudentAt(i).getLastName(),i);
        lastNameTree.insert(lnString);
    }
    */
    string command;
    cin >> command;
    
    if(command == "ID"){
        
        string idNumber;
        cin >> idNumber;
        cout << list.binarySearchID(idNumber);
        cout << " in array list." << endl;
    }
    
    if(command == "EMAIL"){
        string email;
        cin >> email;
        class index emailObj(email, -1);
        list.seqSearchEmail(email);
        emailTree.search(emailObj);
        cout << "Index " <<emailObj.getPos() << " in array list." << endl; //try this way
        //cout << "Index " << list.seqSearchEmailindex(email) << " in array list." << endl;
        
    }
    
    if(command == "FIRSTNAME"){
        
        string firstName;
        cin >> firstName;
        class index firstNameObj(firstName, -1);
        list.seqSearchFirstName(firstName);
        firstNameTree.search(firstNameObj);
        cout << "Index " <<firstNameObj.getPos() << " in array list." << endl;
        //cout << "Index " << list.seqSearchFirstNameindex(firstName) << " in array list." << endl;
    }
    
    if(command == "LASTNAME"){
        //list.sortLastName();
        string lastName;
        cin >> lastName;
        class index lastNameObj(lastName, -1);
        list.seqSearchLastName(lastName);
        lastNameTree.search(lastNameObj);
        cout << "Index " <<lastNameObj.getPos() << " in array list." << endl;
        //cout << "Index " << list.seqSearchLastNameindex(lastName) << " in array list." << endl;
    }
    
    
    return 0;
}

