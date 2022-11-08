/**************************************
Template created by Kazumi Slott
CS311

Your name: Tuan Tran
Your programmer number: 38
Hours spent: 1 hour
Any difficulties?:
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}


//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int ar[], int n)
{
  for(int i = 0; i < n; i++)//for loop going through elements
    {
      int right = i; 
      int left = i-1;
      while(ar[right] < ar[left])//while the left is greater than the right
	{
	  swap(ar[right], ar[left]); //swap 
	  right--; //decrement right side
	  left--; //decrement left side
	}
    }
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document
void selectionSort(int array[], int N)
{
  int smallIndx; //the index of the smallest value

  //first is the first index in unsorted part
  for(int first = 0; first < N-1; first++)
    {
      smallIndx = first; //assume the first item is the smallest
      //find the smallest in unsorted part ([0..last])
      for(int i = first+1; i <= N-1; i++)
	{
	  if(array[i] < array[smallIndx]) //The current item is larger
	    smallIndx = i;
	}
      //swap the smallest with the first item in the unsorted part
      swap(array[smallIndx],array[first]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  
  bool swapped = true; //true if there was swapping in the current iteration, false otherwise                                   
  int last = s-2; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(swapped) //swapping required in the previous iteration or the first iteration starts                        
    {
      swapped = false; //no swapping has happened yet when a new iteration starts.                                         

      for(int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
	  if(ar[i] > ar[i+1]) //the pair is out of order                                                          
	    {
	      swap(ar[i], ar[i+1]);
	      swapped = true; //swapping required - meaning we need to proceed to the next iteration.                            
	    }
        }
      last--; //the area to be checked shrinks down after each iteration                                         
    }//end of while                                                                                               
}


int partition(int a[], int start, int end)
{
  int pivot = end;
  int middle = (start+end)/2; //pick the pivot in the middle
  int swap_index = start;
  swap(a[middle], a[pivot]); //swap the middle with the end

  for(int i = start; i < end; i++) //goes through array but stops before pivot
    {
      if(a[i] <= a[pivot]) //if index is less than pivot
        {
          swap(a[swap_index], a[i]); //swap the swapIndex and i
          swap_index++; //increment swapIndex
        }
    }
  swap(a[swap_index], a[pivot]); //swap the swap index and the pivot after everything.
  return swap_index;
  //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).


  //copy and paste partition() from your quickSort.cpp
}

void quickSort(int ar[], int start, int end)
{
  if(start < end)  //If the partition has only one element or none, return.
                   //In other words, if the partition has at least 2 elements, go inside the if.
                   //use start and end to figure out how many elements you have in the partition.
    {
      int i = partition(ar, start, end);//call partition.
      quickSort(ar, start, i - 1);//quickSort on the left partition
      quickSort(ar, i + 1, end);//quickSort on the right partition
    }
  //copy and paste quickSort() from your quickSort.cpp   
}


void merge(int ar[], int first, int last)
{
  int mid = (first + last) / 2; //get the middle element
  int* temp = new int[first + last]; //make dynamic array for entire size of array
  int right = mid + 1; //right = start of right side of array
  int left = first; //left = start of left side of array
  int counter = 0; //counter for the temp array
  
  while(left <= mid && right <= last) //stops when the left endss at the end of the left side and the right ends at the end of the right side
    {
      if(ar[left] <= ar[right]) //if left element is less than the right
	{
	  temp[counter++] = ar[left++]; //set left array
	}
      else
	{
	  temp[counter++] = ar[right++]; //set right array
	}
    }
  while(left <= mid) //compare left array
    {
      temp[counter++] = ar[left++];
    }
  while(right <= last) //compare right array
    {
      temp[counter++] = ar[right++];
    }
  counter--; //decrement each part of the array that was merged and sorted
  while(counter >= 0) //to add it back to original array
    {
      ar[counter + first] = temp[counter];
      counter--;
    }
  
  //copy and paste merge() from your mergeSort.cpp   
}

void mergeSort(int ar[], int first, int last)
{
  if(first < last) //if array has at least 2 elements
    {
      int mid = (first + last) / 2; //get the middle element
      mergeSort(ar, first, mid); //call mergesort for left
      mergeSort(ar, mid + 1, last); //call mergesort for right
      merge(ar, first, last); //merge both arrays together
    }
  //copy and paste mergeSort()from your mergeSort.cpp   
}

