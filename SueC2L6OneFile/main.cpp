//
//  main.cpp
//  SueC2L6OneFile
//
//  Created by cj on 4/26/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum COMMAND { EXIT_PROGRAM, READ, STATES, LIST, OLDEST, YOUNGEST, FIND, MOVE, MERGE, ERROR};

extern const string NULL_OBJECT = "NULLOBJECTSTRING";

string months[] = {"January", "February", "March", "April","May","June","July", "August", "September", "October", "November","December"};


//This function converts a string to an long
//It returns a variable of type long
//This function assumes that the string being converted is NOT a zero!!
long convertStringToLong(string myString){
    //Documentation Link http://www.cplusplus.com/reference/cstdlib/atol/
    long convertedNumber;
    convertedNumber = atol(myString.c_str());
    //Check if conversion failed
    if (convertedNumber == 0){
        cout << "***Error: Conversion to long Failed. Unicode bytes " << endl;
        cout << "***       detected in Data File." << endl;
        cout << "***Error Reading File. Remove Unicode Bytes in Data File." << endl;
        for (int i = 0; i < myString.length(); i++){
            //cout << i << ": " << myString[i] << " ";
            //If it is not a digit, remove it
            if (!isdigit(myString[i])){
                cout << " <--  ***** Not a integer *****"<< endl;
            }
        }
        //throw  "***Error Reading File. Remove Unicode Bytes from first line";
        string newString = myString.substr(3);
        convertedNumber = atol(newString.c_str());
    }
    return convertedNumber;
}


class Date {
    
private:
    int year;
    int month;
    int day;
    
public:
    //Constructor
    Date(); //Default Constructor
    Date(int y, int m, int d); //This is the constructor
    Date(string d); //Overloaded Constructor with accepting long date format
    //Deconstructor
    ~Date();
    
    //Member functions//
    void printInfo();
    void prettyPrint();
    void printInfoInline();
    
    //GETTERS//
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    
    //SETTERS//
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    
    bool operator>(const Date& object){
        if(this->getYear() > object.getYear()){
            return true;
        }else if(this->getYear() == object.getYear()){
            
            if(this->getMonth() > object.getMonth()){
                return true;
            }else if (this->getMonth() == object.getMonth()){
                if(this->getDay() > object.getDay()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    bool operator<(const Date& object){
        if(this->getYear() < object.getYear()){
            return true;
        }else if(this->getYear() == object.getYear()){
            if(this->getMonth() < object.getMonth()){
                return true;
            }else if (this->getMonth() == object.getMonth()){
                if(this->getDay() < object.getDay()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

//Default Constructor
Date::Date(){
    this->year = 0;
    this->month = 0;
    this->day = 0;
}

//Constructor with params
Date::Date(int y, int m, int d){
    this->year = y;
    this->month = m;
    this->day = d;
}

Date::Date(string d){
    
    //Change from string to a long
    long dateValue = convertStringToLong(d);
    
    /*
     //break the dateValue into Year Month Day
     this->year = int(dateValue/10000);
     this->month = (dateValue/100) % 100;
     this->day = dateValue % 100;
     */
    
    this->day = int(dateValue/1000000);
    this->month = (dateValue/10000) % 100;
    this->year = dateValue % 10000;
}

//Deconstructor
Date::~Date(){
}

//Member Functions//
//YYYYMMDD Format
void Date::printInfo(){
    
    int zero = 0;
    if(day < 10) printf("%d", zero);
    printf("%d", day);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    printf("%d\n", year);
    
    /*
     int zero = 0;
     printf("%d", year);
     if(month < 10) printf("%d", zero);
     printf("%d", month);
     if(day < 10) printf("%d", zero);
     printf("%d\n", day);
     */
}


void Date::printInfoInline(){
    
    int zero = 0;
    if(day < 10) printf("%d", zero);
    printf("%d", day);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    printf("%d", year);
    
    /*
     int zero = 0;
     printf("%d", year);
     if(month < 10) printf("%d", zero);
     printf("%d", month);
     if(day < 10) printf("%d", zero);
     printf("%d\n", day);
     */
}

void Date::prettyPrint(){
    printf("%d of %s %d\n", this->day, months[this->month].c_str(), this->year );
}

//GETTERS//
int Date::getYear() const{
    return this->year;
}
int Date::getMonth() const{
    return this->month;
}
int Date::getDay() const{
    return this->day;
}

//SETTERS//
void Date::setYear(int y){
    this->year = y;
}
void Date::setMonth(int m){
    this->month = m;
}
void Date::setDay(int d){
    this->day = d;
}



template<class Element>
class TreeNode{
protected:
    Element* data;
    TreeNode<Element>* left;
    TreeNode<Element>* right;
    
public:
    
    TreeNode(){
        this->data = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    
    TreeNode(Element* data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
    
    TreeNode(Element* data, TreeNode<Element>* left,TreeNode<Element>* right ){
        this->data = data;
        this->left = left;
        this->right = right;
    }
    
    ~TreeNode(){
        
    }
    
    
    //Deletes node and data
    void deleteWithData(){
        if(this->data){
            delete this->data;
            this->data = NULL;
        }
    }
    
    void deleteCascading(bool preserveData){
        this->deleteNode(preserveData);
        if(this->left){
            this->left->deleteCascading(preserveData);
            delete this->left;
            this->left = NULL;
        }
        if(this->right){
            this->right->deleteCascading(preserveData);
            delete this->right;
            this->right = NULL;
        }
    }
    
    void deleteNode(bool preserveData){
        if(preserveData){
            this->deleteWithoutData();
        }else{
            this->deleteWithData();
        }
    }
    
    //deletes node and preserves data
    void deleteWithoutData(){
        this->data = NULL;
    }
    
    void setLeft(TreeNode<Element>* left){
        this->left = left;
    }
    
    void setRight(TreeNode<Element>* right){
        this->right = right;
    }
    void setData(Element* data){
        this->data = data;
    }
    
    TreeNode<Element>* getLeft(){
        return this->left;
    }
    
    TreeNode<Element>* getRight(){
        return this->right;
    }
    
    Element* getData(){
        return this->data;
    }
    
    TreeNode<Element> *remove(TreeNode<Element> *node, TreeNode<Element> *parentNode){
        if(*node->getData() < *this->data){
            return (this->left != NULL) ? left->remove(node, this) : NULL;
            /*
             //Equivalent to
             if (this->left != NULL){
             return left->remove(node, this);
             }else{
             return NULL;
             }*/
        }else if(*node->getData() > *this->data){
            return (this->right != NULL) ? right->remove(node, this) : NULL;
            /*
             if(right != NULL){
             return right->remove(node, this);
             }else{
             return NULL;
             }*/
        }else{
            if (left != NULL && right != NULL){
                this->data = this->right->minNode();
                return this->right->remove(this, this);
                
            }else if(parentNode->left == this){
                parentNode->left = (this->left != NULL) ? this->left : this->right;
                return this;
            }else if(parentNode->right == this){
                parentNode->right = (this->left != NULL) ? this->left : this->right;
                return this;
            }
        }
        cout << "Error: Reached code that should have not been reached in: " << __PRETTY_FUNCTION__ << endl;
        return this;// should never reach this - Here for compiler warnings
    }
    
    Element* minNode(){
        
        return (this->left) ? this->left->minNode() : this->data;
        /*
         //Equivalent to
         if (this->left){
         return this->left->minNode();
         }else{
         return this->data;
         }
         */
    }
    
};


template<class Element>
class Tree {
    
protected:
    
    TreeNode<Element> *root;
    long size;
    bool enforceUniqueItems;
    
public:
    Tree() {
        this->root = NULL;
        this->size = 0;
        this->enforceUniqueItems = false;
    };
    
    Tree(TreeNode<Element> *root) {
        this->root = root;
        this->size = this->findSize(root);
        this->enforceUniqueItems = false;
    }
    
    Tree(TreeNode<Element> *root, int size) {
        this->root = root;
        this->size = size;
        this->enforceUniqueItems = false;
    }
    
    ~Tree() {
    }
    
    long heightOfTree(){
        return heightOfTree(this->root);
    }
    
    long heightOfTree(TreeNode<Element> *node){
        //If there is no element, return 0
        if(!node){
            return 0;
        }else{
            //find high of the left and right subtrees
            long leftHeight = heightOfTree(node->getLeft());
            long rightHeight = heightOfTree(node->getRight());
            
            return (leftHeight > rightHeight) ? (leftHeight+1) : (rightHeight + 1);
            /*
             //Equivalent to the line above
             if(leftHeight > rightHeight){
             return leftHeight + 1;
             }else{
             return rightHeight + 1;
             }*/
        }
    }
    
    void printTree(){
        long height = this->heightOfTree();
        cout << "Tree: "<< endl;
        for(long i = 1; i <= height; i++){
            printLevel(this->root, i);
            cout << endl;
        }
    }
    
    void printLevel(TreeNode<Element> *node, long level){
        if(!node){
            return;
        }
        if (level == 1){
            cout << node->getData()->getPrintData() << " ";
        }else if(level > 1){
            printLevel(node->getLeft(), level - 1);
            printLevel(node->getRight(), level - 1);
        }
    }
    
    
    long findSize(TreeNode<Element> *node){
        
        long leftChildren = 0;
        long rightChildren = 0;
        if (node->getLeft() != NULL){
            leftChildren = findSize(node->getLeft());
        }
        if (node->getRight() != NULL){
            rightChildren = findSize(node->getRight());
        }
        
        return 1 + rightChildren + leftChildren;
    }
    
    void deleteWithData() {
        if (this->root) {
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }
    
    void deleteWithoutData() {
        if (this->root) {
            this->root->deleteWithoutData();
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }
    
    TreeNode<Element> *find(Element* data){
        TreeNode<Element>* node = this->find(this->root, data);
        if(node){
            return node;
        }else{
            return NULL;
        }
    }
    
    TreeNode<Element> *find(TreeNode<Element> *node, Element *data) {
        
        if (!node) {
            return node;
        }
        
        if (*node->getData() == *data) {
            return node;
        }
        
        if (*node->getData() > *data) {
            return find(node->getLeft(), data);
        } else {
            return find(node->getRight(), data);
        }
    }
    
    TreeNode<Element> * insert(Element *data) {
        if (this->enforceUniqueItems) {
            TreeNode<Element> * aNode = this->find(data);
            
            if(aNode){
                return aNode;
            }
        }
        
        this->insert(this->root, data);
        return this->find(data);
    }
    
    TreeNode<Element> * insert(TreeNode<Element> *node, Element *data) {
        
        if(!this->root){
            this->root = new TreeNode<Element>(data);
            this->size ++;
            return this->root;
        }
        
        if (!node) {
            TreeNode<Element> * newNode = new TreeNode<Element>(data);
            this->size ++;
            return newNode;
        }else if (*node->getData() >= *data) {
            node->setLeft(insert(node->getLeft(), data));
        } else {
            node->setRight(insert(node->getRight(), data));
        }
        return node;
    }
    
    void print(){
        this->print(this->root);
    }
    
    void print(TreeNode<Element>*node){
        if(node == NULL){
            return;
        }
        
        print(node->getLeft());
        node->getData()->printInfo();
        print(node->getRight());
    }
    
    void printUnsorted(){
        this->printUnsorted(this->root);
    }
    
    void printUnsorted(TreeNode<Element>*node){
        if(node == NULL){
            return;
        }
        node->getData()->printInfo();
        printUnsorted(node->getLeft());
        printUnsorted(node->getRight());
    }
    
    //Setters and Getters
    void setRoot(TreeNode<Element> *node) {
        this->root = node;
    }
    
    TreeNode<Element> *getRoot() {
        return this->root;
    }
    
    void setEnforceUniqueItems(bool enforcement) {
        this->enforceUniqueItems = enforcement;
    }
    
    bool getEnforceUniqueItems() {
        return this->enforceUniqueItems;
    }
    
    long getSize() const {
        return this->size;
    }
    
    bool remove(TreeNode<Element> *node){
        return this->remove(node, false);
    }
    
    bool remove(TreeNode<Element> *node, bool preserveData){
        if(this->root == NULL){
            return false;
        }else{
            //Is the node we want to delete the root node
            if(*this->root->getData() == *node->getData()){
                TreeNode<Element> * tempNode = new TreeNode<Element>();
                tempNode->setLeft(this->root);
                TreeNode<Element> * removedNode = this->root->remove(node, tempNode);
                this->root = tempNode->getLeft();
                if(removedNode != NULL){
                    if(!preserveData){
                        delete removedNode->getData();
                    }
                    delete removedNode;
                    this->size --;
                    return true;
                }else{
                    return false;
                }
                
            }else{
                TreeNode<Element> * nodeToRemove = this->root->remove(node, NULL);
                if(nodeToRemove != NULL){
                    if(!preserveData){
                        delete nodeToRemove->getData();
                    }
                    delete nodeToRemove;
                    this->size --;
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
};




class Person; //Forward Declartion of Person class
class State{
    
protected:
    string stateAbbreviation;
    Tree<Person>* people;
    
public:
    
    State(){
        this->stateAbbreviation = "";
        this->people = new Tree<Person>();
    }
    
    State(string abbreviation){
        this->stateAbbreviation = abbreviation;
        this->people = new Tree<Person>();
    }
    
    ~State(){
        this->people->deleteWithoutData();
        delete this->people;
        this->people = NULL;
    };
    
    //Setters & Getters
    void setState(string abbreviation){
        this->stateAbbreviation = abbreviation;
    }
    
    string getState() const{
        return this->stateAbbreviation;
    }
    
    void addPerson(Person* person){
        this->people->insert(person);
    }
    
    Tree<Person>* getPeople(){
        return this->people;
    }
    
    string getPrintData(){
        return this->stateAbbreviation;
    }
    
    void printInfo(){
        cout << this->stateAbbreviation << endl;
    }
    
    bool operator==(const State& object){
        return (this->getState() == object.getState()) ? true : false;
        /*
         //Eq
         if(this->getState() == object.getState()){
         return true;
         }else{
         return false;
         }
         */
    }
    
    bool operator!=(const State& object){
        return (this->getState() == object.getState()) ? false : true;
        /*
         //eq
         if(this->getState() == object.getState()){
         return false;
         }else{
         return true;
         }
         */
    }
    
    bool operator>(const State& object){
        return (this->getState() > object.getState()) ? true : false;
        /*
         if(this->getState() > object.getState()){
         return true;
         }else{
         return false;
         }*/
    }
    
    bool operator<(const State& object){
        return (this->getState() < object.getState()) ? true : false;
        /*
         if(this->getState() < object.getState()){
         return true;
         }else{
         return false;
         }*/
    }
    
    bool operator>=(const State& object){
        return (this->getState() > object.getState()) ? true : false;
        /*
         if(this->getState() > object.getState()){
         return true;
         }else{
         return false;
         }*/
    }
    
    bool operator<=(const State& object){
        return (this->getState() < object.getState()) ? true : false;
        /*
         if(this->getState() < object.getState()){
         return true;
         }else{
         return false;
         }
         */
    }
    
};


//**************************
//  Class Person
//**************************

class Person {
    
private:
    string lastName;
    string firstName;
    string ssn;
    Date* birthday;
    State* state;
    
public:
    //Constructor
    Person(); //Default Constructor
    Person(string ssn, string firstName, string lastName, Date* birthday, State* state);
    Person(string ssn, string firstName, string lastName, string birthday, State* state);
    Person(string ssn);
    Person(string ssn, Date* birthday);
    Person(string firstName, string lastName);
    ~Person(); //Deconstructor
    
    //Member Functions//
    void printName();
    void printInfo(); //Print Name (first and last), SSN, Birthdate
    void printInfoInline();
    long age();     //Calculate the age of the person based on the birthdate
    
    //Setters and Getters
    
    //GETTERS//
    string getSsn() const;
    string getFirstName() const;
    string getLastName() const;
    Date* getBirthday() const;
    State* getState();
    string getPrintData();
    
    //SETTERS//
    void setSsn(string ssn);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setBirthday(Date *birthday);      //Overloaded!!
    void setBirthday(string birthday);    //Overloaded!!
    void setState(State* state);
    
    bool operator==(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator!=(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()) {
            return false;
        }else{
            return true;
        }
    }
    
    bool operator>(const Person& object){
        
        if(this->getLastName() > object.getLastName()) {
            return true;
        }else if(this->getLastName() == object.getLastName()){
            if(this->getFirstName() > object.getFirstName()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    bool operator<(const Person& object){
        
        if(this->getLastName() < object.getLastName()) {
            return true;
        }else if(this->getLastName() == object.getLastName()){
            if(this->getFirstName() < object.getFirstName()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    
    bool operator>=(const Person& object){
        if(this->getLastName() > object.getLastName()) {
            return true;
        }else if(this->getLastName() == object.getLastName()){
            if(this->getFirstName() >= object.getFirstName()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    bool operator<=(const Person& object){
        if(this->getLastName() < object.getLastName()) {
            return true;
        }
        else if (this->getLastName() == object.getLastName()){
            if(this->getFirstName() <= object.getFirstName()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    
    
    
};
//Default Constructor
Person::Person(){
    delete this->birthday;
    this->birthday = NULL;
    //delete this->state; //Dont need to delete. The Database Object will take care of that
    this->state = NULL;
}

//Constructor with params
Person::Person(string ssn, string firstName, string lastName, Date* birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
    this->state = state;
}

Person::Person(string ssn, string firstName, string lastName, string birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date(birthday);
    this->state =  state;
}

Person::Person(string ssn){
    this->ssn = ssn;
    this->firstName = NULL_OBJECT;
    this->lastName = NULL_OBJECT;
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

Person::Person(string ssn, Date* birthday){
    this->ssn = ssn;
    this->firstName = NULL_OBJECT;
    this->lastName = NULL_OBJECT;
    this->birthday = birthday;
    this->state =  new State("RANDOM");
}

Person::Person( string firstName, string lastName){
    this->ssn = "000000000";
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

//Deconstructor
Person::~Person(){
}

//Member Functions//
//Prints full name
void Person::printName(){
    printf("%s %s \n", firstName.c_str(), lastName.c_str());
}

void Person::printInfo(){
    
    printf("SSN: %s ", ssn.c_str());
    printf(" First Name: %s ", firstName.c_str());
    printf(" Last Name: %s ", lastName.c_str());
    printf(" Birthdate (DDMMYYYY): ");
    birthday->printInfoInline();
    printf(" State: %s\n", this->getState()->getState().c_str());
    /*
     printf("SSN: %s \n", ssn.c_str());
     printf("First Name: %s \n", firstName.c_str());
     printf("Last Name: %s \n", lastName.c_str());
     printf("Birthdate (DDMMYYYY): ");
     birthday->printInfo();
     printf("State: %s\n", this->getState()->getState().c_str());
     */
}

void Person::printInfoInline(){
    printf("SSN: %s ", ssn.c_str());
    printf(" First Name: %s ", firstName.c_str());
    printf(" Last Name: %s ", lastName.c_str());
    printf(" Birthdate (DDMMYYYY): ");
    birthday->printInfoInline();
    printf(" State: %s\n", this->getState()->getState().c_str());
}

long Person::age(){
    //This function computes the age to the nearest year.
    int age;
    age = 2014 - int(birthday->getYear());
    return age;
}

//Getters//
string Person::getSsn() const{
    return this->ssn; //Type of long
}
string Person::getFirstName() const{
    return this->firstName;
}
string Person::getLastName() const{
    return this->lastName;
}
Date* Person::getBirthday() const{
    return this->birthday;
}

State* Person::getState() {
    return this->state;
}


string Person::getPrintData(){
    return this->lastName;
}

//Setters//
void Person::setSsn(string ssn){
    this->ssn = ssn;
}
void Person::setFirstName(string firstName){
    this->firstName = firstName;
}
void Person::setLastName(string lastName){
    this->lastName = lastName;
}

//Overloading -- two different means to the same end.
void Person::setBirthday(Date* birthdate){
    this->birthday = birthdate;
}
void Person::setBirthday(string b){
    this->birthday = new Date(b);
}
void Person::setState(State* state){
    this->state = state;
}


class TreeDatabase{
    
protected:
    Tree<Person>* people;
    Tree<State>* states;
    
public:
    
    int numberOfRecordsCounted;
    TreeDatabase(){
        this->numberOfRecordsCounted = 0;
        this->people = new Tree<Person>();
        this->states = new Tree<State>();
        this->states->setEnforceUniqueItems(true);
    }
    
    ~TreeDatabase(){
        delete this->people;
        delete this->states;
    }
    
    void readfile(string filename){
        this->numberOfRecordsCounted = 1;
        
        ifstream infile(filename.c_str()); //Open the file
        string str; // Declares a string and is used for temporary storage
        if (infile.is_open()){
            while (getline(infile,str)){
                string dateString;
                string ssnString;
                string firstName;
                string lastName;
                string stateString;
                
                string token;
                stringstream stringStream(str);
                
                //Get Birthday
                if (getline(stringStream, token, ' ')){
                    dateString = token;
                }
                //Get SSN
                if (getline(stringStream, token, ' ')){
                    ssnString = token;
                }
                //Get First Name
                if (getline(stringStream, token, ' ')){
                    firstName = token;
                }
                //Get Last Name
                if (getline(stringStream, token, ' ')){
                    lastName = token;
                }
                //Get State
                if (getline(stringStream, token, ' ')){
                    stateString = token;
                }
                //cout << "Birthdate: " << dateString << " ssn: " << ssnString << " firstname: " << firstName << " lastname: " << lastName << " state: " << stateString << endl;
                Date* birthdate = new Date(dateString); //Creates a new date object
                
                State* state = new State(stateString); //creating a new state
                //cout << stateString << endl;
                state = this->states->insert(state)->getData(); //add it to the list BUT if there is already a state of the same name in it, return that state instead
                
                Person* person = new Person(ssnString, firstName, lastName, birthdate, state);
                state->addPerson(person);
                this->people->insert(person);
                
                this->numberOfRecordsCounted ++;
                
            }
            infile.close();
        }
        else{
            cout << "Error: Unable to open file" << endl;
        }
    }
    
    Tree<Person>* getPeople(){
        return this->people;
    }
    
    Tree<State>* getStates(){
        return this->states;
    }
    
    void listStates(){
        this->states->print();
    }
    
    void listPeople(){
        this->people->print();
    }
    
    void listPeopleInState(string stateAbrev){
        
        State* newState = new State(stateAbrev);
        TreeNode<State> * stateNode = this->states->find(newState);
        if(stateNode){
            State* state = stateNode->getData();
            cout << "State: " << state->getState() << " # of people: " <<  state->getPeople()->getSize() << endl;
            state->getPeople()->print();
            
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    Person* findPerson(string firstName, string lastName){
        Person* newPerson = new Person(firstName, lastName);
        return this->findPerson( newPerson);
    }
    
    Person* findPerson(string ssn){
        Person* newPerson = new Person(ssn); //Uses Null Object Pattern
        return this->findPersonSSNRec(this->people->getRoot(), newPerson);
    }
    
    Person *findPersonSSNRec(TreeNode<Person>*node, Person* person){
        if(node == NULL){
            return NULL;
        }
        if(node->getData()->getSsn() == person->getSsn()){
            return node->getData();
        }
        Person* leftSide = findPersonSSNRec(node->getLeft(), person);
        Person* rightSide = findPersonSSNRec(node->getRight(), person);
        
        if(leftSide){
            return leftSide;
        }else if(rightSide){
            return rightSide;
        }else{
            return NULL;
        }
    }
    
    Person* findPerson(Person* person){
        TreeNode<Person> *personNode = this->people->find(person);
        if(personNode){
            return personNode->getData();
        }else{
            return NULL;
        }
    }
    
    void findOldest(string stateAbrev){
        State* newState = new State(stateAbrev);
        TreeNode<State> * stateNode = this->states->find(newState);
        if(stateNode){
            State* stateObject = stateNode->getData();
            TreeNode<Person>*personNode = stateObject->getPeople()->getRoot();
            
            Person* oldest = findOldestRec(personNode);
            cout << "The oldest person in " << stateAbrev << " is  ";
            oldest->printInfo();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    Person* findOldestRec(TreeNode<Person>* node){
        
        if(node == NULL){
            return new Person("00000000", new Date(2015,4,22));
        }
        Person* leftSide = findOldestRec(node->getLeft());
        Person* rightSide = findOldestRec(node->getRight());
        if(*node->getData()->getBirthday() < *leftSide->getBirthday() &&
           *node->getData()->getBirthday() < *rightSide->getBirthday() ){
            return node->getData();
        }else{
            if(* leftSide->getBirthday() < *rightSide->getBirthday()){
                return leftSide;
            }else{
                return rightSide;
            }
        }
        
    }
    
    
    void findYoungest(string stateAbrev){
        State* newState = new State(stateAbrev);
        TreeNode<State> * stateNode = this->states->find(newState);
        if(stateNode){
            State* stateObject = stateNode->getData();
            TreeNode<Person>*personNode = stateObject->getPeople()->getRoot();
            
            Person* youngest = findYoungestRec(personNode);
            cout << "The youngest person in " << stateAbrev << " is  ";
            youngest->printInfo();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    Person* findYoungestRec(TreeNode<Person>* node){
        
        if(node == NULL){
            return new Person("00000000", new Date(1800,1,1));
        }
        Person* leftSide = findYoungestRec(node->getLeft());
        Person* rightSide = findYoungestRec(node->getRight());
        if(*node->getData()->getBirthday() > *leftSide->getBirthday() &&
           *node->getData()->getBirthday() > *rightSide->getBirthday() ){
            return node->getData();
        }else{
            if(* leftSide->getBirthday() > *rightSide->getBirthday()){
                return leftSide;
            }else{
                return rightSide;
            }
        }
        
    }
    
    State* findState(string stateAbreviation){
        State* newState = new State(stateAbreviation);
        TreeNode<State>*stateNode = this->states->find(newState);
        if(stateNode){
            return stateNode->getData();
        }else{
            return NULL;
        }
    }
    //move ssn oldstate newstate
    void movePerson(string ssn, string oldStateString, string newStateString){
        Person* person = this->findPerson(ssn);
        State* oldState = this->findState(oldStateString);
        State* newState = this->findState(newStateString);
        if(person == NULL){
            cout << " -- " << ssn << " is not in the list of people" << endl;
        }else if (oldState == NULL){
            cout << " -- " << oldStateString << " is not in the list of states (old state)" << endl;
        }else if (newState == NULL){
            cout << " -- " << newStateString << " is not in the list of states (new state)" << endl;
        }else if (*person->getState() != *oldState){
            cout << " -- " << person->getFirstName() << " " << person->getLastName() << " does not live in " << oldState->getState() << endl;
        }
        else{
            
            //setting the person's state to the new state
            person->setState(newState);
            //remove the person from the old states linked list but preserve the person data
            TreeNode<Person>* personNode = oldState->getPeople()->find(person);
            oldState->getPeople()->remove(personNode, true);
            //add the person to the new states data
            newState->getPeople()->insert(person);
        }
    }
    
    void movePerson(Person* person, string oldStateString, string newStateString){
        this->movePerson(person->getSsn(),   oldStateString,  newStateString);
    }
    
    void mergeStates(string stateString1, string stateString2){
        State* state1 = this->findState(stateString1);
        State* state2 = this->findState(stateString2);
        if(state1 == NULL){
            cout << " -- " << stateString1 << " is not in the list of states" << endl;
        }else if (state2 == NULL){
            cout << " -- " << stateString2 << " is not in the list of states" << endl;
        }else{
            mergeIntoState(state1->getPeople()->getRoot(), state2);
        }
    }
    
    void mergeIntoState(TreeNode<Person>*node, State* newState){
        if(node == NULL){
            return;
        }
        newState->getPeople()->insert(node->getData());
        mergeIntoState(node->getLeft(), newState);
        mergeIntoState(node->getRight(),newState);
    }
};



void testDateClass(){
    Date* date = new Date(2015,4,2);
    assert(date->getYear() == 2015);
    assert(date->getMonth() == 4);
    assert(date->getDay() == 2);
}

void testDateComparisonOperators(){
    
    Date* date1 = new Date("02021965");
    Date* date2 = new Date("24101947");
    Date* date3 = new Date("16061930");
    Date* date4 = new Date("13021922");
    
    assert(*date1 > *date2);
    assert(*date2 < *date1);
    assert(!(*date3 > *date2));
    assert(*date4 < *date1);
    
}

void testPersonClass(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);
    
    assert(person->getSsn() == "00000000" );
    assert(person->getFirstName() == "MyFirstName" );
    assert(person->getLastName() == "MyLastName" );
    
    Person* person1 = new Person("00000001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("00000002", "MyFirstName", "MyLastName", date, state);
    Person* person3 = new Person("00000003", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00000004", "MyFirstName", "MyLastName", date, state);
    
    assert(*person1 < *person2);
    assert(*person2 > *person1);
    assert(!(*person2 < *person1));
    assert(*person4 > *person2);
    assert(!(*person1 > *person4));
    assert(*person1 < *person3);
    
}

void testStateClass(){
    
    State* newyork = new State("NY");
    State* newyork1 = new State("NY");
    State* newjersey = new State("NJ");
    
    assert( *newyork == *newyork1);
    assert( *newyork != *newjersey);
    
    string NY = "NY";
    string NJ = "NJ";
    assert(NY > NJ);
    assert( *newyork > *newjersey);
    assert( *newjersey < *newyork);
    assert(!(*newjersey > *newyork));
    assert(!(*newyork < *newjersey));
}



void testTreeNodes(string databaseLocation){
    
    TreeDatabase*  database = new TreeDatabase();
    ///database->readfile(databaseLocation);
    
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    State* state8 = new State("OR");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");
    State* state6 = new State("NY");
    State* state7 = new State("NY");
    State* state9 = new State("NH");
    
    
    database->getStates()->insert(state);
    assert(*database->getStates()->insert(state8)->getData() == *state8);
    database->getStates()->insert(state1);
    database->getStates()->insert(state2);
    database->getStates()->insert(state3);
    database->getStates()->insert(state4);
    assert(*database->getStates()->insert(state6)->getData() == *state);
    assert(*database->getStates()->insert(state7)->getData() == *state);
    //State * aState = database->getStates()->insert(state9)->getData();
    //aState->printInfo();
    //cout << "here" << endl;
    
    //database->listStates();
    assert(*database->getStates()->insert(state9)->getData() == *state9);
    assert(database->getStates()->getSize() == 7);
    assert(*database->getStates()->find(state2)->getData() == *state2 );
    assert(*database->getStates()->find(state8)->getData() == *state8 );
    
    
    
    //database->listStates();
    
    Person* person = new Person("00100000", "NY MyFirstName1", "NY MyLastName1", date, state);
    Person* person1 = new Person("00030001", "NY MyFirstName2", "NY MyLastName2", date, state);
    Person* person2 = new Person("010000002", "NJ MyFirstName3", "NJ MyLastName3", date, state1);
    Person* person3 = new Person("00000103", "NJ MyFirstName4", "NJ MyLastName4", date, state1);
    Person* person4 = new Person("00100004", "MyFirstName5", "MyLastName5", date, state2);
    Person* person5 = new Person("00000103", "NJ MyFirstName4", "NJ MyLastName6", date, state);
    Person* person6 = new Person("00100004", "MyFirstName5", "MyLastName7", date, state);
    Person* person7 = new Person("00000103", "NJ MyFirstName4", "NJ MyLastName9", date, state);
    Person* person8 = new Person("00100004", "MyFirstName5", "MyLastName8", date, state);
    Person* person9 = new Person("10100022", "AAAA", "AAAA", date, state);
    database->getPeople()->insert(person);
    state->getPeople()->insert(person);
    database->getPeople()->insert(person1);
    state->getPeople()->insert(person1);
    database->getPeople()->insert(person2);
    state1->getPeople()->insert(person2);
    database->getPeople()->insert(person3);
    state1->getPeople()->insert(person3);
    database->getPeople()->insert(person4);
    state2->getPeople()->insert(person4);
    database->getPeople()->insert(person5);
    state->getPeople()->insert(person5);
    database->getPeople()->insert(person6);
    state->getPeople()->insert(person6);
    database->getPeople()->insert(person7);
    state->getPeople()->insert(person7);
    database->getPeople()->insert(person8);
    state->getPeople()->insert(person8);
    database->getPeople()->insert(person9);
    state->getPeople()->insert(person9);
    //database->getPeople()->print();
    
    //assert(database->getPeople()->getSize() == 5);
    assert(*database->getPeople()->find(person1)->getData() == *person1 );
    //database->listPeople();
    state->getPeople()->print();
    
}

void testListPeopleInState(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    
    //database->getStates()->print();
    //database->getPeople()->print();
    assert(database->getStates()->getSize() == 51);
    
    database->listPeopleInState("NY");
    database->listPeopleInState("NJ");
    database->listPeopleInState("DC");
    database->listPeopleInState("OR");
    
    database->findOldest("NY");
    database->findOldest("OR");
    database->findYoungest("NY");
    database->findYoungest("OR");
    
    
}

void testMergePeopleInState(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    database->listPeopleInState("NY");
    database->listPeopleInState("NJ");
    database->mergeStates("NY", "NJ");
    database->listPeopleInState("NJ");
    database->listPeopleInState("NY");
    
}

void testRemoveNode(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    database->listPeopleInState("NY");
    
    Date* date = new Date(2015,4,2);
    State* ny  = database->findState("NY");
    Person* newPerson = new Person("00100000", "NY MyFirstName1", "NY MyLastName1", date, ny);
    
    database->getPeople()->insert(newPerson);
    ny->getPeople()->insert(newPerson);
    
    database->listPeopleInState("NY");
    cout << endl;
    //ny->getPeople()->printUnsorted();
    
    TreeNode<Person>* newPersonNode = ny->getPeople()->find(newPerson);
    assert(ny->getPeople()->remove(newPersonNode));
    assert(!ny->getPeople()->remove(newPersonNode));
    cout << endl;
    //ny->getPeople()->printUnsorted();
    database->listPeopleInState("NY");
    
    Person* anotherPerson = database->findPerson("609690069"); //SSN: 609690069  First Name: Gallipoli  Last Name: DeMilt  Birthdate (DDMMYYYY): 10011925 State: NY
    TreeNode<Person>* anotherPersonNode = ny->getPeople()->find(anotherPerson);
    assert(ny->getPeople()->remove(anotherPersonNode));
    assert(!ny->getPeople()->remove(anotherPersonNode));
    
    database->listPeopleInState("NY");
    
}

void testMove(string databaseLocation){
    
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    
    //112200747
    database->listPeopleInState("OK");
    database->listPeopleInState("NY");
    //database->getStates()->printTree();
    //database->listStates();
    cout <<  "MOVE" << endl;
    database->movePerson("112200747", "OK","NY");
    cout <<  "MOVE ENDED" << endl;
    database->listPeopleInState("OK");
    database->listPeopleInState("NY");
    database->listPeopleInState("SD");
    database->listPeopleInState("NC");
    database->movePerson("122460462", "SD","NY");
    database->movePerson("123040628", "NC","NY");
    cout << "Move ended" << endl;
    database->listPeopleInState("NY");
    database->listPeopleInState("SD");
    database->listPeopleInState("NC");
    
}

void testHeightFunction(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    ///database->readfile(databaseLocation);
    
    State* state = new State("NY");
    State* state8 = new State("OR");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");
    State* state6 = new State("NY");
    State* state7 = new State("NY");
    State* state9 = new State("NH");
    
    
    database->getStates()->insert(state);
    assert(database->getStates()->heightOfTree() == 1);
    
    database->getStates()->printTree();
    
    assert(*database->getStates()->insert(state8)->getData() == *state8);
    assert(database->getStates()->heightOfTree() == 2);
    database->getStates()->printTree();
    database->getStates()->insert(state1);
    assert(database->getStates()->heightOfTree() == 2);
    database->getStates()->printTree();
    database->getStates()->insert(state2);
    assert(database->getStates()->heightOfTree() == 3);
    database->getStates()->printTree();
    database->getStates()->insert(state3);
    assert(database->getStates()->heightOfTree() == 4);
    database->getStates()->printTree();
    database->getStates()->insert(state4);
    assert(*database->getStates()->insert(state6)->getData() == *state);
    assert(*database->getStates()->insert(state7)->getData() == *state);
    database->getStates()->insert(state9);
    cout << database->getStates()->heightOfTree() << endl;
    database->getStates()->printTree();
    cout << "PRINTING" << endl << endl;
    database->getStates()->print();
    
    
}

void testFind(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    cout << "read database" << endl;
    
    Person* person = database->findPerson("161760131");
    assert(person);
    //person->printInfo();
    
    Person* person1 = database->findPerson("152720564");
    assert(person1);
    //person1->printInfo();
    
    Person* person2 = database->findPerson("163290682");
    assert(person2);
    //person2->printInfo();
    
}



vector<string> parseCommandString(string commandString){
    vector <string> arguments;
    
    string token;
    stringstream stringStream(commandString);
    
    while(getline(stringStream, token, ' ')){
        arguments.push_back(token);
    }
    
    if(arguments.size() == 0){
        arguments.push_back("ERROR");
    }
    return arguments;
}


COMMAND commandDetector(string s){
    
    
    //cout <<  s <<" is an operator "<<  endl;
    
    if(s == "exit" ){
        return EXIT_PROGRAM;
    }else if(s == "read" ){
        return READ;
    }else if(s == "states" ){
        return STATES;
    }else if(s == "list" ){
        return LIST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest"){
        return YOUNGEST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest") {
        return YOUNGEST;
    }else if (s == "find" ){
        return FIND;
    }else if (s == "move") {
        return MOVE;
    }else if (s == "merge") {
        return MERGE;
    }else{
        //cout << "Error" << endl;
        return ERROR;
    }
    
}


void commandLineInterpreter(){
    
    cout << "Enter a command:" << endl;
    int command = 100;
    string commandString;
    TreeDatabase* database;
    do{
        
        cout << "> ";
        std::getline(std::cin, commandString);
        vector<string> arguments = parseCommandString(commandString);
        COMMAND comm = commandDetector(arguments[0]);
        
        if(database == NULL && !(comm != READ || comm != EXIT_PROGRAM)){
            cout << "Error: There must be a data present prior to running commands against the database." << endl;
        }else{
            switch (comm){
                case READ:
                    cout << "READING" << endl;
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguements." << endl;
                        cout << "E.g. read /home/www/labs/152/dbfile1.txt" << endl;
                    }else{
                        database = new TreeDatabase();
                        database->readfile(arguments[1]);
                        cout << "Reading Complete" << endl;
                    }
                    
                    break;
                case STATES:
                    cout << "States" << endl;
                    if(arguments.size()>=2 ){
                        cout << "Error: Illegal number of arguments. This command takes one arguement." << endl;
                        cout << "E.g. states" << endl;
                    }else{
                        database->listStates();
                    }
                    break;
                case LIST:
                    cout << "List" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. list FL" << endl;
                    }else{
                        database->listPeopleInState(arguments[1]);
                    }
                    
                    break;
                case OLDEST:
                    
                    cout << "OLDEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. oldest NY" << endl;
                    }else{
                        database->findOldest(arguments[1]);
                    }
                    
                    break;
                case YOUNGEST:
                    cout << "YOUNGEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. youngest NY" << endl;
                    }else{
                        database->findYoungest(arguments[1]);
                    }
                    
                    break;
                    
                case FIND:
                    cout << "FIND" << endl;
                    
                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. find Larry Brown" << endl;
                    }else{
                        Person* person = database->findPerson(arguments[1], arguments[2]);
                        if(person){
                            cout << "  FOUND: " ;
                            person->printInfoInline();
                        }else{
                            cout << " -- " << arguments[1] << " " <<  arguments[2] << " is not in the list of people" << endl;
                        }
                    }
                    
                    break;
                    
                case MOVE:
                    
                    cout << "MOVE" << endl;
                    //FIXME: Insert in social security order
                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. move 108690448 KS MD" << endl;
                    }else{
                        database->movePerson(arguments[1], arguments[2], arguments[3]);
                    }
                    
                    break;
                    
                case MERGE:
                    cout << "merge" << endl;
                    
                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. merge NC SC" << endl;
                    }else{
                        database->mergeStates(arguments[1], arguments[2]);
                    }
                    break;
                case EXIT_PROGRAM:
                    command = 0;
                    cout << "EXITING" << endl;
                    break;
                    
                case ERROR:
                    cout<< "Error: Illegal Syntax in command" << endl;
                    
                default:
                    cout<< "Error: Illegal Syntax in command" << endl;
            }
        }
        
    }while(command != 0);
    cout << "Final EXIT" << endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    commandLineInterpreter();
    return 0;
}
