/**********************************
Template prepared by Kazumi Slott
CS311

matrix class

Replace the ?????s

For examples of matrix multiplication
https://matrix.reshish.com/multCalculation.php 

Your name: Tuan Tran
Your programmer number: 38
Hours spent?: 3
Any difficulties?:
***********************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//This forward declaration of Matrix class is necessary because the following operator>> and << are using Matrix as a parameter
template <class T>
class Matrix;

//This forward declaration of operator>> is necessary Since operator<< is a template function.
template<class T>
ifstream& operator>>(ifstream& o, Matrix<T>& m);

//This forward declaration of operator<< is necessary Since operator<< is a template function.
template <class T>
ostream& operator<<(ostream& o, const Matrix<T> & m);

//Template class so we can have a matrix of any data types, int or double
template <class T>
class Matrix
{
  //friend functions so they can access the private members 
  friend ostream& operator<< <T>(ostream& o, const Matrix<T> & m);
  friend ifstream& operator>> <T>(ifstream& o, Matrix<T>& m);

private: 
  T** m; //2 dimensional dynamic array
  const int R; //number of rows
  const int C; //number of columns

public: 
  Matrix(int R, int C);
  Matrix();
  ~Matrix();
  Matrix operator*(const Matrix& other);// matrix multiplication
  class size_error{};//exception class 
};

//default constructor
template<class T>
Matrix<T>::Matrix() : R(0), C(0) //setting const R and C to initial value, 0.
{
  m = NULL;
}

//constructor to create a matrix, row x col 
template<class T>
Matrix<T>::Matrix(int row, int col) : R(row), C(col) //setting const R and C 
{
  if(row <= 0 || col <= 0)
    {
      m = NULL;
      return;
    }

  //m = new T[R][C]; //this doesn't compile
  m = new T*[R]; //create a single dimensional array of pointers of the T type
  for (int i=0; i<R; i++) //create a single dimensional array for each slot of m
    m[i] = new T[C];

  //initialize each element to 0
  for(int rw = 0; rw < R; rw++)
    for(int cl = 0; cl < C; cl++)
	m[rw][cl] = 0;
}

//fill a matrix using an input file
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& mrx)
{
  for(int i = 0; i < mrx.R; i++) //go through row
    for(int j = 0; j < mrx.C; j++) //go through column 
      fin >> mrx.m[i][j];  //input it
  return fin; //return it
  
}

/*output the matrix to screen in the following format. Allocate 10 spaces for each value.
         1          1          1
         2          2          2
         3          3          3
         4          4          4 
*/
template<class T>
ostream& operator<<(ostream& o, const Matrix<T>& mrx)
{
  //multiple lines of code here
  for(int i = 0; i < mrx.R; i++) // go through the row
    {
      for(int j = 0; j < mrx.C; j++) //go through the column
      {
	o << setw(10) << mrx.m[i][j]; //print it out
      }
    o << endl;
    } 
  //use setw(10) to allocate 10 spaces to show each value
  return o;
  
}

//matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
  
  //check if the 2 matrices are comparable. If m1 is mxn, m2 has to be nxk. 
  if(this->C != other.R) //cannot compute because of incomparable sizes
    throw size_error(); //throw an exception 
  Matrix f(this->R, other.C); // creates final matrix, use this column and other row to get the new sizes.
  for(int k = 0; k < this->R; k++) //result for loop to multiply, goes through this row
    for(int j = 0; j < other.C; j++) //for loop going through other column for multiply
      for(int i = 0; i < this->C; i++) //for loop going through this column for multiply
	f.m[k][j] += (this->m[k][i] * other.m[i][j]); //multiply this row and column with other column and this column

  return f;  //return matrix
}

//destructor                                                                                                                                                                                        
template<class T>
Matrix<T>::~Matrix()
{
  //destroy what is created in heap memory                                                                                                                 
  if(m != NULL) //if not null, delete
    {
      for(int i = 0; i < R; i++)
	{
	  delete [] m[i];
	}
      delete [] m;
    }

  //if m is not NULL do the following                                   
     //HINT: delete each dynamic array pointed to by each slot of m                                                                                                                                  
     //delete m (m contains all rows)                                                                                
}
