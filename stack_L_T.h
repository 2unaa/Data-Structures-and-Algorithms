/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Tuan Tran
Your programmer number here: 38
Hours spent: 5
Any problems you had? Explain here: Got sick again :(, flu. trying to fight through it
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template <class T> //forward declaration needed so we can make stack class a friend of node
class Stack;

template <class T> //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template <class T>
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;
  Node<T>* next;  //check how right and left pointers are declared in BST class --> /cs/slott/cs211/BST_T.h
 public:
  Node(){Node<T>* top = NULL; } //default constructor
  Node(const T& e){elem = e; next = NULL;} //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack
 private:
  Node<T>* top;
 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);
 public:
  Stack() {top = NULL;} //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{return (top == NULL) ? true : false; } //implement a small function inside the class definition
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an empty exception class here. Underflow or/and Overflow? - You need to figure out where to throw an exception - I am throwing in 3 functions.
  class Underflow{};//??????????
};


//Complexity of this operation: O(1)
template <class T>
void Stack<T>::push(const T& val)
{
  Node<T>* p = new Node<T>; //create pointer and node with
  p -> elem = val; //putting the value into p element
  p -> next = top; //point p next to the previous top
  top = p; //make p the new top

   //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h 
}


//Complexity of this operation: O(1)
template <class T>
void Stack<T>::pop()
{
  if(empty()) //if its empty
    {
      throw Underflow();
    }
  else
    {
      Node<T>* p = top; //make a pointer point to top
      top = top -> next; // become the new top, the 2nd one
      delete p; //delete the old top
    }
  //What do you do if the stack is empty?

}


//Complexity of this operation: O(1)
template <class T>
T& Stack<T>::getTop()
{
  if(empty()) //if empty
    {
      throw Underflow();
    }
  else
    {
  //What do you do if the stack is empty?
  return top -> elem; //return the top element. Since the return type is T&, the client can change the top.
    }
}



//Complexity of this operation: O(1)
template <class T>
const T& Stack<T>::getTop() const
{
  if(empty()) //if empty
    {
      throw Underflow();
    }
  else
    {
  //What do you do if the stack is empty?
  return top -> elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
    }
}


//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(N)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.
  Node<T>* p = s.top;
  cout << "--- Top ---" << endl;
 while(p!= NULL) //go through entire stack
    {
      o << p ->elem << endl ; //print element of p
      p = p -> next; //increment
    }
  cout << "--- Bottom ---" << endl;
}



template <class T>
Stack<T>::~Stack()
{
  destroy(); 
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(N)
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  //destroy all nodes
  //?????????????? 
  while(!empty()) //while not empty
    {
      Node<T>* p = top; //pointer to top
      top=top->next; //top equals next 
      delete[] p; //delete the pointer
      p=top; //increment p
    }
}


//Complexity of this operation: O(1)
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&). 
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;
  
  //deep copy
  if(this->top != rhs.top) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;             //You copy only if the left object is not the same as the right object.
    {
      this->destroy(); //destroy it
      this->copy(rhs); //copy it
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
    }
  return *this; //return the "this" object. Notice the return type is not void. 
                  //By returning the this object, we can use multiple assignment operators. 
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2). 
}



//Complexitey of this operation: O(N)
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  if(source.empty())//if source is empty
    {
      this->top = NULL;//lhs null
    }
  else
    {
      Node<T>* s = source.top; //make a node point to source top
      Node<T>* p = new Node<T>(s->elem); //make a node to point to a new node with elem
      this->top=p; //copy stack to p

      while(s!=NULL) //while s is not empty
	{
	  s=s->next; //increment s 
	  if(s!=NULL) //if s is not null
	    {
	      p->next=new Node<T>(s->elem); 
	      p=p->next; //increment p
	    }

	}
    }
  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty 
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().
}



//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data members.
  this->top= NULL;
  this->copy(other);

  //Then you can call the copy function
}



#endif // end the definition here
