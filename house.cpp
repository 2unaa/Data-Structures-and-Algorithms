  /******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: Application of the Matrix class

Your name: Tuan Tran
Your programmer number: 38
Number of hours you spent: 10 mins
Any difficulties?: Matrix 2 file is function.in not cost.in
*******************************************/
//What do you need to include? HINT: What are you using in main()?
//include your matrix.h
#include <iostream>
#include "matrix.h"
#include <fstream>

using namespace std;
int main()
{  
  //?????
  //Your matrices need to be of the same data type.  When you do multiplication, the data types of the 2 matrices need to be the same.
  Matrix <double> m1(4,4); //4 rows by 4 columns
  Matrix <double> m2(4,3); //4 rows by 3 columns

  ifstream fin;							      
  fin.open("/cs/slott/cs311/house_info.in");
  fin >> m1;
  //load the data into the first matrix
  fin.close();

  fin.open("/cs/slott/cs311/house_function.in");
  fin >> m2;//load the data into the second matrix
  fin.close();

  // ?????
  //use try and catch
  //In catch, show the following message.
  try
    {
    Matrix<double> m3 = m1 * m2;
    cout << m3;
  }
 catch(Matrix<double>::size_error)
   {
  cout << "SIZE ERROR" << endl;
   }

  return 0;
}


