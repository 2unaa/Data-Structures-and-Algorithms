/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Tuan Tran
Your programmer number: 38
Hours spent making and testing your min heap class: ????
Any difficulties?: ????
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int* curDist, int* locator, int i);
  //void build_min_heap();
  void bubbleUp(int* curDist, int* locator, int i);
  void insert(int* curDist, int* locator, const T& el);
  int find(int key) const;
  void remove(int* curDist, int* locator, int i);
  T getMin(int* curDist, int* locator);
  int getNum() const;
  void fixHeap(int* curDist, int* locator, int i);
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

template <class T>
minHeap<T>::minHeap(int c)
{
  capacity = c;
  ar = new T[capacity];
  num = 0;
}

template <class T>
void minHeap<T>::min_heapify(int* curDist, int* locator, int i)
{
  
  int l = 2 * i + 1; //the index of the left child of i
  int r = 2 * i + 2; //the index of the right child of i
  int smallest = i; //the index of the largest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  if(l < num && curDist[ar[l]] < curDist[ar[smallest]]) //make sure l is in range and greater than largest
    {
      smallest = l; //largest is left child h
    }
  //I have 4 lines of code here. You can have more or less.
  if(r < num && curDist[ar[r]] < curDist[ar[smallest]])
    {
      smallest = r;
    }
  //The largest is either the right or left child. We need to exchange the parent with it.
  if(smallest != i)
    {
      locator[ar[i]] = smallest; //swap locator
      locator[ar[smallest]] = i;
      mySwap(ar[i], ar[smallest]);
      min_heapify(curDist, locator, smallest);
      //exchange the 2 values
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
    }
}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
/*template <class T>
void minHeap<T>::build_min_heap()
{
  //2 lines of code in this function
  for(int i = num/2; i >= 0; i--) //for each non leaf node
    {
      min_heapify(i); //call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
    }
    }*/

//this function corrects a violiation at i by bubbling it up to the correct place                             
//a is a heap  
template <class T>                                                                                              
void minHeap<T>::bubbleUp(int* curDist, int* locator, int i)
{
  int parent = (i-1) / 2; //find the parent node
  int child = i;
  while(child > 0 && curDist[ar[parent]] > curDist[ar[child]]) //the child is smaller 
    {
      locator[ar[child]] = parent;//swap locator
      locator[ar[parent]] = child;
      mySwap(ar[parent], ar[child]); //swap
      child=parent; //make i the new parent
      parent = (parent-1) / 2; //find the parent of i
    }
}

template <class T>
void minHeap<T>::insert(int* curDist, int* locator, const T& el)
{
  if(num >= capacity) //  if(/* array is full */)
    {
      throw Overflow(); //"The array is full"; 
    }
  else //if not
    {
      ar[num++] = el;
      bubbleUp(curDist, locator, num-1);
    }
}
  
template <class T>
int minHeap<T>::find(int key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

template <class T>
void minHeap<T>::remove(int* curDist, int* locator, int i)
{
  if(i < 0 || i > num-1) //|| i < 0) //if its invalid
      {
	throw BadIndex();
      }
    else
      {
	locator[ar[i]] = num - 1; //exchange elements
	locator[ar[num-1]] = i;
	mySwap(ar[num-1], ar[i]);//swap the current element with last element
	num--; //decrement
	fixHeap(curDist, locator, i); //call fixheap
      }
}

template <class T>
T minHeap<T>::getMin(int* curDist, int* locator)
{
  T val = ar[0];
  remove(curDist, locator, 0);
  return val;
  //This function removes the top element and returns it.
  //You should be calling remove()
}


template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h)
{
  if(h.num == 0)
    {
      o << "none";
    }
  for(int i = 0; i < h.num; i++) //going through the entire heap
    {
      o << h.ar[i] << " "; //print out the index
    }
  o << endl;
  return o;
}

//return the number of elements in the heap.
template <class T>
int minHeap<T>::getNum() const
{
  return num;
}

//i is the index (within heap) of the vertex whose distance was changed.
//For example, if vertex 0's distance changed when it is located at 3, i is 3. This is where the heap needs to be fixed by either going up or down.
//curDist is the array that contains the shortest distance from start to every other vertex.
//locator is the array that contains the location of each vertex within the heap. Make sure you understand the homework document posted on Canvas to understand how locator works.
template <class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{

  //We need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. Make sure you understand how each array works by reading the homework document (there are pictures to explain).

    //From i, either bubble up or down.  

  if(i<num && i >= 0) //if fixheap is less than amount of element 
    {
      if(curDist[ar[i]] < curDist[ar[(i-1)/2]]) //if its less than parent
	bubbleUp(curDist, locator, i);
      else if(curDist[ar[i]] > curDist[ar[2*i+1]] || curDist[ar[i]] > curDist[ar[2*i+2]]) //if its more
	min_heapify(curDist, locator, i);
    }
    //For up, call bubbleUp(). For down, call min_heapify().               


    //Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.

    //Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.
}


#endif
