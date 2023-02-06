/**********************************
CS311 Kazumi Slott

Your name: Tuan Tran
Your program number: 38
Hours spent: 10 :(
Describe any difficulties here: Not sure why but algo C gives me -1 what it should be.
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runtime complexity of this algorithm? O(N^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
int algoA(const int a[], int sz)//Don't change the function headers
{
  int maxSum = 0;
  int sum = 0;
  
  for(int i = 0 ; i <= sz; i++)//goes through the array
    {
    for(int j = 0; j < sz - i; j++) //gets the current spot in the sub array
      {
	sum = 0;
      for(int k = j; k <= i; k++) //goes through the subarray
	{
	  sum += a[j+k]; //add the elements
	  if(sum > maxSum) //if sum is greater than the max
	    {
	    maxSum = sum; //the sum is now the max
	    }
	}
      }
    }
  return maxSum;
}

//What is the runtime complexity of this algorithm? O(N^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
  int maxSum = 0;
  int sum = 0;
  for(int j = 0; j < sz - 1; j++) //gets current spot
    {
    sum = 0;
    for(int k = j; k < sz; k++) //goes through the sub array
      {
	sum += a[k]; //add the elements
	if(sum > maxSum) //if sum is greater than the max
	  {
	  maxSum = sum; //the sum is now the max
	  }
      }
    }
  return maxSum;
}

//What is the runtime complexity of this algorithm? O(N)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{
    int maxSum = 0;
    int sum = 0;
    for(int i = 0; i < sz; i++)
      {
	sum += a[i];
	if(sum < 0) //if it is negative
	  {
	    sum = 0;
	  }
	else //if it isnt negative
	  {
	    maxSum = sum;
	  }
      }
    return maxSum;
  }
 
