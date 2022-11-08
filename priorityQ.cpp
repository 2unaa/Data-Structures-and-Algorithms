/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: ?????
Your name: Tuan Tran
Your programmer number: 38
Hours spent making this application: 5
Are you rejecting invalid inputs?: ????
Any difficulties: ???????
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std;
#include "minHeap.h"
#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
int getNum();
int priority(int s, int n);
//int getPriority();


const int START = 1000; //assuming this number will not go over 9999
int num = 0;

int main()
{
  minHeap<int> h (9999);
  int num = 0; //number of patients
  int choice;
  do
  {
    showMenu(); //call showMenu() to show the menu
    choice = getNum();
    if(choice == 1) //if user enters 1
  {
    int severity;
    cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
    //severity = getPriority(); //get user entry
    cin >> severity; 
      int p = priority(severity, num); //saves the severity number ex: 41001
      h.insert(p);//insert that number into the heap
      num++; //increment
  }
    else if(choice == 2) //if user enters 2
    {
      try
	{
	  int first = h.getMin(); //get min value and print it out
	  cout << first << " is going to get treated now" << endl;
	}
      catch(minHeap <int>::BadIndex) //catch error if empty
	{
	  cout << "There are no patients waiting" << endl;
	}
    }
    cout << "The queue is " << h; //print out the queue each time
  
  }while(choice != 3); //do while until enter end
  
  return 0;
  
}
//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer only.
int getNum()
{
  string choice; //For example, when asking for 10, the user enters ab 
  bool bad;
  int num;

  do
    {
      bad = false;
      cout << "Enter a number: ";
      cin >> choice; 

      try
	 {
	   num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
	   if(num < 1 || num > 3) //if in range
	     {
	       cout << "Invalid choice. The choice between 1, 2, or 3. ";
	       bad = true;
	     }
	 }
      
      catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. ";
	   bad = true;
	 }	 
      
    }while(bad == true);
   
  return num;
}

//calculates the severity
int priority(int s, int n)
{
  int sev = (s * 10000) + START + n; //s is severity. multiply it by 10000. then add 1000 from start and add n to get the number of total patients added to 
  return sev; 
}

//commented out for submission test cases
/*
int getPriority()
{
  string choice; //For example, when asking for 10, the user enters ab
  bool bad;
  int num;
   
  do
    {
      bad = false;
      cout << "Enter a number: ";
      cin >> choice;
      
       try
         {
           num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
           if(num < 1 || num > 5)
             {
               cout << "Invalid choice, has to be between 1 and 5";
	       bad = true;
	     }
	 }
       
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. " << endl;
	   bad = true;
	 }
       
    }while(bad == true);
  
  return num;
  }*/
