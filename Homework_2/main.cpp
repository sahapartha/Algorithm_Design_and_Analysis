//Homework#2 - CS351
//main.cpp
//Author: (Partha Saha)
//         Date:
//         Homework#2, due date Mar. 10, 2020

#include <iostream>
#include <iomanip> //for formatting output
#include "Employee.hpp" //include Employee class
#include <fstream> //filestream
#include <sstream>
#include <unordered_set>
#include <iterator> 
using namespace std;
//node consists of the element or data and a pointer to the next node.
//This is defined using struct
struct node{
    Employee emp;
    node *next;
    
};

//do not change anything in the function declaration!
void displayList(node* head);
void viewEmployee(node* head, string ID);
void addNewEmployee(node** head,Employee newEmp);
void removeEmployee(node** head, string ID);
void displayEmployee(Employee * aEmp);
void printHeader();



class List{
private:
    int size;
    node *head;
    node *tail;
public:
    List(){
        head = NULL; //The constructer will make them NULL to avoid any garbage value.
        tail = NULL;
        size=0;
    }
    
    void insert_start(Employee * newEmp){
        node *temp = new node();
        temp->emp = *newEmp;
        temp->next = head;
        if (head==NULL){
            tail=temp;
        }
        head = temp;
        
        size++;
    }
    
    void insert_end(Employee * newEmp){
        node *temp = new node;
        temp->emp = *newEmp;
        temp->next = NULL;
        if (head==NULL){
            head = temp;
            tail = temp;
            temp=NULL;
        } else{
            tail->next  = temp;
            tail = temp;
        }
        size++;
        
    }
 
    
    void displayList (){
        
        node *temp = new node;
        temp =head;
        cout  << left<< setw(12) << setfill(' ') << "Employee ID"  ;
        cout  << left<< setw(12) << setfill(' ') << "Name"  ;
        cout  << left<< setw(12) << setfill(' ') << "Lastname"  ;
        cout  << left<< setw(35) << setfill(' ') << "Position"  ;
        cout  << left<< setw(0) << setfill(' ') << "Department"  ;
        cout << endl;
        cout  << left<< setw(12) << setfill('-') << "-"  ;
        cout  << left<< setw(12) << setfill('-') << "-"  ;
        cout  << left<< setw(12) << setfill('-') << "-"  ;
        cout  << left<< setw(35) << setfill('-') << "-"  ;
        cout  << left<< setw(20) << setfill('-') << "-"  ;
        cout << endl;
        while(temp!=NULL){
                cout  << left<< setw(12) << setfill(' ') << temp->emp.getEmpID();
                cout  << left<< setw(12) << setfill(' ') << temp->emp.getName();
                cout  << left<< setw(12) << setfill(' ') << temp->emp.getLastName();
                cout  << left<< setw(35) << setfill(' ') << temp->emp.getPosition();
                cout  << left<< setw(0) << setfill(' ') << temp->emp.getDepartment();
                cout << endl;
                temp = temp->next;
               
        }
        
    }
    int getsize(){
        return size;
    }
    
    void removeEmployee(string stringID){
        //*****INSERT YOUR CODE HERE FOR TASK4******
        node *cur = head;
        node *pre = new node;
        node *prev= head;
        
        while(cur!=NULL){
            if(cur->emp.getEmpID()==stringID){
            	prev->next=cur->next;
				delete cur;		
			}
			prev=cur;
            cur=cur->next;
        }

    }
    
 

    bool isEmpty(){
        return size==0;
    }
    
    void removeDuplicates(){
        //*****INSERT YOUR CODE HERE FOR TASK2******
        //use unordered_set STL
        node * cur;
        node * prev;
        cur = head;
        prev = head;
        unordered_set<string> tempSet;
        if (cur!= NULL) {
            //insert the first element to tempSet
            tempSet.insert(cur->emp.getEmpID());
            cur = cur->next;
        }
        		
        while (cur != NULL){
        	//insert your code here
        	auto search=tempSet.find(cur->emp.getEmpID());
        	if(search != tempSet.end()){
        		prev->next=cur->next;
			}
			else{
				tempSet.insert(cur->emp.getEmpID());
				prev=cur;
			}
			cur= prev->next;
		 
        }
      	
    }
    

    
    Employee * find(string stringID) {
        //*****INSERT YOUR CODE HERE FOR TASK3******
        //returns the employee object based on stringID matched, if the element cannot be found, return NULL.
        
        node *temp = head;
        while(temp!=NULL){
            //insert your code here
            if(temp->emp.getEmpID()==stringID)
            	return &temp->emp;
            temp=temp->next;
            
        }
        //if not found
        return NULL;

    }
    
    void sort(){
        mergeSort(&head);
    }
    
    void mergeSort(node ** tempHead){
        node * temp = *tempHead;
        node * a = NULL;
        node * b = NULL;
        
        //base case
        if (temp == NULL || temp->next == NULL){
            return;
        }
        findMid(temp,&a,&b);
        mergeSort(&a);
        mergeSort(&b);
        *tempHead = merge(a,b);
        
    }
    node* merge(node* a, node* b)
    {
        //*****INSERT YOUR CODE HERE FOR TASK5******
        //merge two sorted linked lists
        node* result = NULL;
		if (a == NULL){
        return b;
    	}
		else if (b == NULL){
        return a;
    	}

    if (a->emp.getEmpID() <= b->emp.getEmpID()){
        result = a;
        result->next = merge(a->next, b);
    	}else{
        result = b;
        result->next = merge(a, b->next);
    	}

        return result;

    }
    
    void findMid(node * headRef, node** front, node** back)
    {
        //*****INSERT YOUR CODE HERE FOR TASK5******
        //use the 'Runner Technique' - slow/fast pointers
        node* fast;
        node* slow;
        
        slow= headRef;
        fast=headRef->next;
        
        if (headRef == NULL || headRef->next == NULL){
            *front = headRef;
            *back = NULL;
        } else {
            //insert your code here
            while(fast !=NULL && fast->next != NULL){
				fast=fast->next->next;
				slow=slow->next;	
			}   
        }
        *front=headRef;
        *back=slow->next;
        slow->next=NULL;
        displayEmployee(&((*back)->emp));
		displayEmployee(&((*front)->emp));
    }
};


int main(int argc, const char * argv[]) {
    
    List empList; //Employee List Object
    fstream dataFile;
    string line;
    string delimiter = ",";
    string newEmpID,newName,newLastName,newPosition,newDepartment="";
    
    dataFile.open("EmployeeData2.csv", ios::in);
    cout << "Importing data " << endl;
    if (dataFile.is_open()) {
        printHeader();
        while ( getline (dataFile,line) )
        {
            //each line of the file is in this format
            //employeeID,name,lastname,position,department
            //each field is separated by a comma ,
            
            //*****INSERT YOUR CODE HERE FOR TASK1******
            //read each line from line variable
            //and assign the correct string to
            //newEmpID,newName,newLastName,newPosition,newDepartment
            stringstream ss(line);
            getline(ss, newEmpID, ',');
            getline(ss, newName, ',');
            getline(ss, newLastName, ',');
            getline(ss, newPosition, ',');
            getline(ss, newDepartment, ',');
       
//             int next_pos=0;
//             int del_counter=0;
//             while(del_counter<5){
//               	next_pos = line.find(delimiter);
//               	cout<<"delimiter: " <<next_pos<<endl;
//             	if(del_counter==0){
//             		newEmpID= line.substr(0, next_pos+1);	
//			 	}
//             	if(del_counter==1)
//             		newName= line.substr(0, next_pos+1);
//             	if(del_counter==2)
//             		newLastName= line.substr(0, next_pos+1);
//             	if(del_counter==3)
//             		newPosition= line.substr(0, next_pos+1);
//               	if(del_counter==4)
//             		newDepartment= line.substr(0, next_pos+1);
//              line.erase (0, next_pos);
//              del_counter++;
//			 }

            
            
            
            Employee * newEmp = new Employee(newEmpID, newName, newLastName, newPosition, newDepartment);
            empList.insert_end(newEmp);
            
            displayEmployee(newEmp); //display each employee's detail
            delete(newEmp);
            
        }
        cout << "Import done!" << endl;
        
    }
    
    dataFile.close();
    int choice;
    //call the function to remove any duplicate records
    empList.removeDuplicates();

    do
    {
        cout << endl
        << "***** My Employee Program (CS351) *****" << endl
        << " 1 - Display List of Employee" << endl
        << " 2 - View Employee" << endl
        << " 3 - Add New Employee" << endl
        << " 4 - Remove an Employee" << endl
        << " 5 - Sort List" << endl
        << " 6 - Exit" << endl
        << " Enter your choice and press return: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                if (!empList.isEmpty()) {
                    empList.displayList();
                } else {
                    cout << endl
                    << "The list is empty!" << endl;
                }
                break;
            case 2:
            {
                cout << endl
                << "Enter the ID of the employee that you would like to view!" << endl;         cin.ignore();
                getline(cin, newEmpID);
                //display the employee based on ID match
                displayEmployee(empList.find(newEmpID));
                break;
            }
            case 3:
            {
                cout << endl
                << "Enter information for the new employee!" << endl;
                cout << "Employee ID : " ;
                cin.ignore();
                getline(cin, newEmpID);
                
                cout << "Name : " ;
                getline(cin, newName);
                
                cout << "Lastname : " ;
                getline(cin, newLastName);
                
                cout << "Position : " ;
                getline(cin,newPosition);
                
                cout << "Department : " ;
                getline(cin,newDepartment);
                //add the new employee, create an object of Employee class
                //the new employee should be added at the END of the list
                Employee newEmp(newEmpID, newName, newLastName, newPosition, newDepartment);

                empList.insert_end(&newEmp);
                
                
                cout << "New Employee is added!!!" << endl;
                break;
            }
                
            case 4:
                if (!empList.isEmpty()){
                    cout << endl
                    << "Enter the ID of the employee that you would like to remove from the list!" << endl;
                    cin.ignore();
                    getline(cin, newEmpID);
                    empList.removeEmployee(newEmpID);
                } else {
                    cout << endl
                    << "The list is empty!" << endl;
                }
                break;
            case 5:
                if (!empList.isEmpty()){
                    empList.sort();
                } else {
                    cout << endl
                    << "The list is empty!" << endl;
                }
                break;

                
            case 6:
                cout << "End of Program.\n";
                break;
            default:
                cout << "Not a Valid Choice. \n"
                << "Choose again.\n";
                break;
        }
        
    }while (choice !=6); //the loop exists when user chooses 5 from the main menu
    return 0;
}

void printHeader(){
    cout  << left<< setw(12) << setfill(' ') << "Employee ID"  ;
    cout  << left<< setw(12) << setfill(' ') << "Name"  ;
    cout  << left<< setw(12) << setfill(' ') << "Lastname"  ;
    cout  << left<< setw(20) << setfill(' ') << "Position"  ;
    cout  << left<< setw(20) << setfill(' ') << "Department"  ;
    cout << endl;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(20) << setfill('-') << "-"  ;
    cout  << left<< setw(20) << setfill('-') << "-"  ;
    cout << endl;
}

void displayEmployee(Employee * aEmp){
	
    if (aEmp!= NULL){
         cout  << left<< setw(12) << setfill(' ') << aEmp->getEmpID()  ;
         cout  << left<< setw(12) << setfill(' ') << aEmp->getName()  ;
         cout  << left<< setw(12) << setfill(' ') << aEmp->getLastName()  ;
         cout  << left<< setw(20) << setfill(' ') << aEmp->getPosition()  ;
         cout  << left<< setw(20) << setfill(' ') << aEmp->getDepartment()  ;
         
        cout << endl;
        
    }
    
    
}
