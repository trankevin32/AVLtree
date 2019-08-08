//
//  student.h
//  Homework 2 Version 2
//
//  Created by Kevin Tran on 6/26/19.
//  Copyright © 2019 Kevin Tran. All rights reserved.
//
#ifndef student_h
#define student_h

using namespace std;

class Student{
private:
    string idNumber;
    string first_name;
    string last_name;
    string email;
    
public:
    Student();
    Student(string idNum, string firstName, string lastName, string emailAddress);
    
    void setID(string idNum);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setEmailAddress(string emailAddress);
    
    string getID() const;
    string getFirstName() const;
    string getLastName() const;
    string getEmailAddress() const;
    
    void print() const;
};

Student::Student(){
    idNumber = "";
    first_name = "";
    last_name = "";
    email = "";
}

Student::Student(string idNum, string firstName, string lastName, string emailAddress){
    idNumber = idNum;
    first_name = firstName;
    last_name = lastName;
    email = emailAddress;
}

void Student::setID(string idNum){
    idNumber = idNum;
}

void Student::setFirstName(string firstName){
    first_name = firstName;
}

void Student::setLastName(string lastName){
    last_name = lastName;
}

void Student::setEmailAddress(string emailAddress){
    email = emailAddress;
}

string Student::getID() const{
    return idNumber;
}

string Student::getFirstName() const{
    return first_name;
}

string Student::getLastName() const{
    return last_name;
}

string Student::getEmailAddress() const{
    return email;
}

void Student::print() const{
    cout << getID() << " " << getFirstName() << " " << getLastName() << " " << getEmailAddress() << endl;
}
#endif /* student_h */
