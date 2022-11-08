/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: sort strings of 3 lowercase letters using radix sort
Your name: Tuan Tran
Your programmer number: 38
Hours spent: ????
Any difficulties?: ?????
************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};

LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s); //the new node has NULL in the next field.

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at the end of this list
void LL::addRear(Node* p)
{
  //Don't make a new node.
  if(empty())
    {
      front = rear = p; //You need a special case when the list is empty
    }
  else
    {
      rear->next = p; 
      rear = rear->next;
      rear->next = NULL;//rear next null
    }
  num++; //increment num
}

//Implement this function
//appending another linked list at the end of this linked list 
void LL::append(const LL& other)
{
  //Do you need to think about a special case?
  //Don't forget to update num of this list
  if(empty())
    {
      front = other.front;
      rear = other.rear;
    }
  else
    {
      //Note: this function should have complexity O(1). There is no loop required.
      rear->next = other.front; //set this rear with other front
      rear = other.rear; //rear equals to other rear
    }
  num += other.num; //increment num
  rear-> next = NULL; //rear next to null
}

void radixSort(LL& all);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, LL buckets[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  radixSort(all);
  cout << "Final result ----" << endl;
  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
void radixSort(LL& all)
{
  //Each slot of the buckets array is a LL object.
  int index;
  LL buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.
  Node* front; //two pointers for new front and current
  Node* cur;
  for(int i = LEN - 1; i >= 0; i--) //going through word from least significant
    { 
      for(cur = all.begin(), front = all.begin(); cur != NULL; cur = front) //goes through each string in all list
	{
	  front = all.goToNext(front); //increment front
          string elem = cur->getElem(); //variable 
	  index = elem[i] - 'a'; //convert int using char - char
	  buckets[index].addRear(cur); //fill the buckets
	}
      combineLists(all, buckets); //combine the list
      
    }  
}

//Implement this function
//combining all lists from buckets
void combineLists(LL& all, LL buckets[])
{
  all.clear();//call clear() to reset the all list. All the nodes went to correct buckets already.
  //populate the all list by combining the lists from the buckets by calling append()
  for(int i = 0; i < ALPHABET; i++)
    {
      if(!buckets[i].empty()) //if bucket is not empty
	{
	  all.append(buckets[i]); //append LL and buckets
	  buckets[i].clear(); //clear buckets
	}
    }  //reset each list in b[i] by calling clear(). All the nodes were moved to the all list already.
}
 
//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  fstream fin;
  fin.open("radix.in");
  if(!fin)
    {
      cout << "The input file doesn't exist" << endl;
      exit(1); //quits the program if the input program doesn't exist.
    }

  fin >> s;
  while(fin)
    {
      all.addRear(s);
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  //iterate p from the first node to last node
  for (Node* p = l.begin(); p != NULL; p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

