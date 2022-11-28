/****************************
Templated created by Kazumi Slott
CS311

Your name: Tuan Tran
Your programmer number: 38
Hours spent: 20
Any difficulties?:
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include "minHeap-graph.h"

using namespace std;

class edge
{
  friend class graph;  //You want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void DijkstraShortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  num_ver = num;
  ver_ar = new list<edge*>[num_ver];  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object 
}

graph::~graph()
{
  //destroy all the edge objects created in heap                                  
  for(int i = 0; i < num_ver; i++)
    {                                                                     
      for(list<edge*>::iterator u = ver_ar[i].begin(); u!= ver_ar[i].end(); u++) //For each vertex in ver_ar
	{
	  delete *u;  //go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.
	}
    }
  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/
  
  delete[] ver_ar; //destroy the ver_ar dynamic array
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  ver_ar[v].push_back(new edge(u, w)); //I have one line of code in this function.
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  int *num = new int[num_ver];  //I made dynamic array called "num"
  
  for(int j = 0; j < num_ver; j++) 
    {
      num[j] = 0;
    }
  int i = 1; //start i at 1
  queue<string> q;//I created a queue object of string data type from the librarya\

  do{//I used do-while
    DFT_helper(start, i, num, q); //call dft helper
    start = nextUnvisitedNodes(num, start, start + 1);    //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.
  }while(start != -1); 
  
  displayQueue(q);  //You could call displayQueue() implemented above to display all the paths. 
  cout << endl;
  
  delete[] num;  //Don't forget to destroy the dynamic array
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertex right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.
  for(int i = s % num_ver; i != start; i = (i+1)%num_ver){
    if(num[i] == 0) 
      {
	return i;
      }
  }
  return -1;
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  //The algorithm is in my lecture notes

  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  num[v] = i++; //iterate i
  cout << v <<" "; //output v
  for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++) 
    {
      if(num[((*u)->neighbor)] == 0) //if neighbor(u) = 0
	     {
	       q.push(to_string(v) + "->" + to_string((*u)->neighbor)); //push into queue
	       DFT_helper(((*u)->neighbor), i, num, q); 
	     }
      
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  
      
      //push each path e.g. 0->1 into q. to_string(int) converts int to string. 
      //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp

    }

  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp 
   **********************************************************************************************
   ***********************************************************************************************/
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  //The algorithm is in my lecture notes
  
  //Use the queue class from the library
  queue<int> q; //queue of ints
  queue<string> s;  //I used another queue of strings to save all the paths. 
  int*num = new int[num_ver]; 
  for(int j = 0; j < num_ver; j++)
    {
      num[j] = 0;
    }
  int i = 1; //start i at 1
  do
    {//I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited verteces.
      num[start] = i++; //increment i
      //Check the manual to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/
      q.push(start); //push the start
      while(!q.empty()) 
    {
      start = q.front(); //start att the front 
      q.pop(); //pop the front
      cout << start << " "; //print it out
      for (list<edge*>::iterator u = ver_ar[start].begin(); u != ver_ar[start].end(); u++)
	{
	  if(num[(*u)->neighbor] == 0)
	    {
	      num[(*u)->neighbor] = i++;
	      q.push((*u)->neighbor); //push the neighbor
	      s.push(to_string(start) + "->" + to_string((*u)->neighbor)); //put into the string queue
	    }
	}
    }

      start = nextUnvisitedNodes(num, start, start+1); //move start
    }while(start != -1);

  displayQueue(s); //You could call show all paths by calling displayQueue()                                                         
  
  delete[] num;  //Don't forget to destroy the dynamic array if you used one
}


//dijkstra's algorithm calculates the shortest distance from start to every other vertex
//This stand alone function shows the shortest path from start to destination in the following format.
//  The shortest path from 3 to 5 is 3 0 4 5
//  The distance is 8

void showShortestDistance(int* curDist, int* predecessor, int start)
{
  int dest; //destination
  cout << "Enter the destination: ";
  cin >> dest;

  //trace the shortest path from dest back to start
  stack<int> s; //I suggest you use either library's stack or queue. Which one will work?

  int current = curDist[dest]; //get the distance
  cout << "The shortest path from " << start << " to " << dest << " is ";
  while(dest!=start) //as long as dest isnt start
    {
      s.push(dest); //push the element 
      dest = predecessor[dest];
    }
  s.push(start); //push the start into stack
  while(!s.empty())
    {
      cout << s.top() << " "; //display top
      s.pop(); //pop
    }

  cout << "\nThe distance is " << current << endl;
}

//You don't need to change the following function.
//This function is for checking the heap and all the arrays. You may want to call it while you are developing Dijkstra's function
//This is not part of the graph class.  It is made for testing anyway.

void printHeapArrays(const minHeap<int>& h, int* curDist, int* locator, int* predecessor, int num_ver)
{
  cout << "heap ------" << endl;
  cout << h << endl;  //This works if you made operator<<() to display a heap

  cout << "locator ------" << endl;
  for(int i = 0; i < num_ver; i++)
    cout << locator[i] << " ";
  cout << endl;

  cout << "curDist ------- " << endl;
  for(int i = 0; i < num_ver; i++)
    cout << curDist[i] << " ";
  cout << endl << endl;

  cout << "Predecessor ------- " << endl;
  for(int i = 0; i < num_ver; i++)
    cout << predecessor[i] << " ";
  cout << endl << endl;
}

void graph::DijkstraShortestPath(int start)
{
  minHeap<int> toBeChecked(num_ver); //the top of this heap has the vertex with the shortest distance
  int *curDist = new int[num_ver];  //contains the current shortest distance from start to every other vertex
  int *predecessor= new int[num_ver]; //contains the predecessor of each vertex
  int *locator = new int[num_ver]; //tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertext 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap
  int v = start;
    //The algorithm is in my lecture notes. Make sure you understand how each array and heap changes by reading my homework document posted on Canvas.

  for(int i = 0; i < num_ver; i++)//initialize each array
    curDist[i] = 999;   //curDist should be 999 for all vertices to start with
  for(int i = 0; i < num_ver; i++)//populate toBeChecked heap
    {
      toBeChecked.insert(curDist, locator, i); //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers
      locator[i] = i;
      predecessor[i] = -1;
  }
  curDist[start] = 0; //set curDist to 0 first
  //A lof of code here - check the algorithm in my lecture notes
  while(toBeChecked.getNum()>0) //while its not empty
    {
      //printHeapArrays(toBeChecked, curDist, locator, predecessor, num_ver);  //print the heap array
      toBeChecked.fixHeap(curDist, locator, locator[v]); //fix heap 
      v = toBeChecked.getMin(curDist, locator); //v = vertex to beChecked with minimum currDist
      for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++) //for all vertices
	{
	  if(locator[(*u)->neighbor] < toBeChecked.getNum()) //if neighbor is less than the one to be checked
	    {
	      if(curDist[(*u)->neighbor] > ((*u)->wt+curDist[v])) //if neighbor is greater than wt and distance
		{
		  curDist[(*u)->neighbor] = ((*u)->wt+curDist[v]); //neighbor to wt + distance of v
		  predecessor[(*u)->neighbor] = v; //predecessor to v
		  toBeChecked.fixHeap(curDist, locator, locator[(*u)->neighbor]); //fix the heap
		}
	    }
	}
    }
    //Now currDist and predecessor have the info about the shortest distance from start to every other vertex and the predecessor of each vertex
    showShortestDistance(curDist, predecessor, start);//print the result
    //delete all the arrays
    delete[] curDist;
    delete[] predecessor;
    delete[] locator;
}


#endif
