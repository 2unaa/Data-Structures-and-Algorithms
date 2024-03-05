/***************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons.                                            
                                                                                   
Your name: Tuan Tran
Your programmer number: 38
Hours spent: ??????                                                                
Any difficulties?: ?????                                                           
****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "swap.h"  //<=== include your swap.h if you made it so you can call your mySwap() in stableSort(). 
                      //     If you didn't make it, you can make a swap function in this file or call the library's swap(). 
using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("/cs/slott/cs311/stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()
bool fname(person l, person r)
{
  return(r.fN >= l.fN) ? true : false;
}

bool year(person l, person r)
{
  return(r.grade >= l.grade) ? true : false;
}

bool lname(person l, person r)
{
  return(r.lN <= l.lN) ? true : false;
}


void stableSort(person ar[], bool(&func)(person, person))
{
  //You can use a stable sort algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().                    
  for(int i = 1; i < SIZE; i++)//for loop going through elements
    {
      int right = i;
      int left = i-1;
      while(right > 0, func(ar[right], ar[left]))//call the function, while right is greater than left
        {
     	  mySwap(ar[right], ar[left]); //swap
	  right--; //decrement right side
	  left--; //decrement left side
	}
    }

}

int main()
{
  person ar[SIZE];
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      //You need to sort the array here
      //HINT: call stableSort multiple times.
     
      stableSort(ar, fname);
      stableSort(ar, lname);
      stableSort(ar, year);

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  return 0;
}


