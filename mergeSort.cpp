/**********************************
Templated created by Kazumi Slott
CS311

Your name: Tuan Tran
Your programmer number: 38
Hours spent: 1
Any difficulties?:??????????
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
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
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you are using a different technique, I assume you cheated and will give you zero points.

  //Don't forget to destroy temp array, which is created dynamically
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
}



  //For implementation of this function, refer to my lecture notes "merge sort"

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
