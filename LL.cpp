#include "LL.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//this function will display an error message
void LL::LLError(string msg)
{
  cout << msg << endl;
  exit(1);
}

//constructor
LL::LL()
{
  front = NULL;
  rear = NULL;
  count = 0;
}

//this function will check to see if the queue is empty
bool LL::isEmpty() const
{
  return (front == NULL && rear == NULL && count == 0) ? true : false;
}

//destructor
LL::~LL()
{
  while(!isEmpty()) //while its not empty
    {
      deleteFront(); //call deleteFront until empty
    }
}

//copy constructor
LL::LL(const LL& l)
{
  this->front = this->rear = NULL;
  this->count = 0;
  node* p = l.front;
  while(p != NULL) //go through entire array
    {
      addRear(p->elem);
      p = p-> next;
    }
}

//this function will delete the front element and set the new front to the second
el_t LL::deleteFront()
{
  if(isEmpty()) //if its empty
    {
      LLError("Error: list is empty.");
    }
  if(count == 1) //if count is 1
    {
      el_t temp = front -> elem; //set temp to front element
      delete front; //delete front
      front = NULL; //set front and rear to null
      rear = NULL;
      count--; //decrement count
      return temp; //return value of front
    }
  else
   {
     el_t temp = front -> elem; //set temp to front element
     node* second = front -> next; //make a node second that is at the second spot
     delete front; //delete front
     front = second; //make second the new front
     count--; //decrement count
     return temp; //return value of front
   }
}
//this function will delete the rear of the linked list
el_t LL::deleteRear()
{
  if(isEmpty())
    {
      LLError("Error: List is empty.");
    }
  el_t temp = rear -> elem; //temp equals to rear elem
  if(count == 1)
    {
      delete rear;
      front = NULL; //set front and rear to null
      rear = NULL;
    }
  else
    {
      node* p;
      for(p = front; p->next != rear; p = p->next) //for loop to find the node before rear
        {
	  ;
	}
      delete rear; //delete rear
      rear = p; //set rear equal to node before rear
      rear->next = NULL; //rear next to null
    }
  count--; //decrement count
  return temp;
}



//this function will add an element to the rear
void LL::addRear(el_t el)
{
  if(isEmpty() == true) //if its empty
    {
      front = new node; //sets front to a new node
      front -> elem = el; //puts data in front node
      rear = front; //sets rear to front
    }
  else
    {
  rear -> next = new node; //make the node of the rear point to a new one
  rear = rear -> next; //rear points to the new node
  rear -> next = NULL; //new node points to NULL
  rear -> elem = el; //put data in rear node
    }
  count++; //increment count
}

//this function will add to the front of the linked list
void LL::addFront(el_t el)
{
  if(isEmpty())
    {
      front = new node; //set front and rear to a new node
      front->elem = el; //put data into front
      rear = front; //front and rear are the same
      rear->next = NULL;
    }
  else
    {
      node* p; //create pointer
      p = new node; //create a new node
      p->next = front; // p next points to front which is now second
      p->elem = el; //put element in p elem
      front = p; //put p as the new front
    }
  count++; //increment count
}

//this function will display each element of the queue starting from front
void LL::displayAll() const
{
  if(isEmpty()) //if its empty
    {
      cout << "[Empty]" << endl;
    }
  else
    {
      node* p = front; //set p to front
      while(p != NULL) //while p isnt null
	{
	  cout << "[" << p -> elem << "] "; //print them out
	  p = p -> next; 
	}
    }
}

//this public function calls the other printAllReverse so we can use it in client. 
void LL::printAllReverse() 
{
  printAllReverse(front);
}

//private function because u cant call with front from client.
void LL::printAllReverse(node* p)
{

  if(p == NULL) //base case
    return;
  else
    {
      printAllReverse (p -> next); //recursion
      cout << p -> elem; //prints out elements after popping them
    }
}

//This function will return true if e is found in the linked list. Otherwise return false
bool LL::search(el_t e)
{
  int count = 0;
  bool found = false;
  for(node* p = front; p != NULL; p = p->next) //for loop that goes through entire list
    {
      if(p-> elem == e) //if e is found 
	{
	  found = true; //returns true
	  break;
	}
      else
	  {
	    count++;
	  }
    }
  cout << count << " nodes checked." << endl;
  return found;
}
  //  cout << count << " nodes checked." << endl;

//this function will delete the node that holds element e. only the first one will be deleted
void LL::deleteNode(el_t e)
{
  node* pre;
  node* del;
  if(isEmpty()) //if empty
    {
      return; //do nothing
    }
  if(e == front-> elem) //if e is the front element
    {
      deleteFront(); //call delete front
    }
  else //if e is not the front
    {
      for(pre = front, del = front->next; del != NULL && del-> elem != e; pre = del, del = del->next)  //makes del the element wanted to be deleted. makes pre to be the node before del
	{
	  ;
	}
      if(del != NULL) //if del is not null, e is found
	{
	  pre->next = del->next; //set pre next to point to the node after del
	  if(del == rear) //if del equals rear 
            {
	      rear = pre; //set pre as the new rear 
            }
	  delete del; //delete del
	  count--; //decrement count
	}
    }
}

void LL::deleteNodes(el_t e)
{
  node* pre;
  node* del;
  if(isEmpty()) //if empty
    {
      return; //do nothing
    }
  if(e == front-> elem) //if e is the front element
    {
      deleteFront(); //call delete front
    }
  if(!isEmpty()) //if e is not the front or empty
    {
      for(pre = front, del = front->next; del != NULL && del-> elem != e; pre = del, del = del->next)  //makes del the element wanted to be deleted. makes pre to be the node before del
        {
          ;
        }
      while(del != NULL) //if del is not null
        {
	  if(del->elem == e) //if the element u want to delete is found
	    {
	      pre->next = del->next; //set pre next to point to the node after del
	      if(del == rear) //if del equals rear
		{
		  rear = pre; //set pre as the new rear
		}
	      delete del; //delete del
	      count--; //decrement count
	      del = pre->next; //set del to pre next
	    }      
	  else //if its not found
	    {
	      del = del-> next; //set del to pre next
	      pre = pre-> next; //set pre to pre next
	    }
	}
    }
}

//add a new node in ascending order
void LL::addInOrderAscend(el_t e)
{
  if(isEmpty()) //if its empty
    {
      addFront(e);
    }
  else if(e < front->elem) //if you want to insert the element to the very front
    {
      addFront(e);
    }
  else //if its somewhere else, in middle or end
    {
      node* p; //create node p
      p = front; //p starts at front
      while(p->next != NULL && p->next->elem < e) //p pointst to node before insertion
	{
	  p = p-> next; //increment p
	}
	 node* x = new node; //create a new node
	  x -> elem = e; //put e in the element of x node  
	  x -> next = p-> next; //x next points to what p next was pointing to
	  p->next = x; //p next now points to x node
	  count++; //increment count
    }
}
//this function will add a new node in order descending
void LL::addInOrderDescend(el_t e)
{
  if(isEmpty()) //if its empty
    {
      addFront(e);
    }
  else if(e > front->elem) //if you want to insert the element to the very front
    {
      addFront(e);
    }
  else //if its somewhere else, in middle or end
    {
      node* p;
      p = front;
      while(p->next != NULL && p->next->elem > e) //p pointst to node before insertion
        {
          p = p-> next; //increment p
        }
      node* x; //create a new pointer
      x = new node; //create a new node
      x -> elem = e; //put e in the element of x node
      x -> next = p-> next; //x next points to what p next was pointing to
      p->next = x; //p next now points to x node
      count++; //increment count
    }
}

