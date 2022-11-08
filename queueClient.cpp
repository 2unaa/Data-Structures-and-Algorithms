/*********************************************************
Template provided by Kazumi Slott

Name:
This client tests the queue class memeber functions.
********************************************************/
#include <iostream>
#include "queue.h"
#include "/cs/slott/cs211/checkInput.h"
using namespace std;
//prototypes
void showMenu();

int main()
{
  Queue q;
  int choice;
  do
    {
      showMenu();
      cout << "Enter a choice: "; 
      choice = getData(1, 7, "Invalid choice. Enter again: ");
      switch(choice)
	{
	case 1:
	  char e;
	  cout << "add an element to the queue: ";
	  cin >> e;
	  if(q.isFull())
	    {
	      cout << "can't add, queue full." << endl;
	    }
	  else
	    {
	  q.add(e);
	    }
	  break;
	case 2:
	  cout << "removing front element " << endl;
	  if(q.isEmpty())
	    {
	      cout << "can't remove, queue empty. " << endl;
	    }
	  else
	    {
	  q.remove();
	    }
	  break;
	case 3:
	  if(q.isEmpty())
            {
              cout << "empty queue. " << endl;
            }
	  else
	    {
	  cout << "The front is " << q.getFront() << endl;
	    }
	  break;
	case 4:
	  if(q.isEmpty())
            {
              cout << "empty queue. " << endl;
            }
	  else
	    {
	  cout << "putting front back to rear" << endl;
	  q.goToBack();
	    }
	  break;
	case 5: 
	  cout << "The size of the queue is: " << q.getSize() << endl;
	  break;
	case 6:
	  q.displayAll();
	    break;
	case 7:
	  break;
	}
    } while(choice != 7);
  return 0;
}


void showMenu()
{
  cout << "=================================" << endl;
  cout << "1: add a new element" << endl; //(testing add(), isFull())
  cout << "2: remove an element" << endl; // (testing remove(), isEmpty())
  cout << "3: check the front element" << endl; //(testing getFront(), isEmpty())
  cout << "4: go back to the rear" << endl; //(testing goToBack())
  cout << "5: get the number of elements in the queue" << endl; //(testing getSize()) 
  cout << "6: display all the elements in the queue" << endl; //(testing displayAll()) 
  cout << "7: quit program" << endl;
  cout << "=================================" << endl;
}
