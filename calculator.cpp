#include <iostream>
#include "stack_L_T.h"
using namespace std;

int priority(char ch);//function to get an operator and return its priority number
bool isOperand(char ch);//function to check if the token is an operand
bool isOperator(char ch);//function to check if the token is an operator
int charToInt(char ch); //convert char to int
string infixToPost(const string infix);//function to convert from infix to postfix and returns postfix
double evaluation(const string postfix);//function to evaluate postfix and returns the answer
int charToInt(char ch); //function to convert char to int
double doMath(double operand1, char opt, double operand2);//to evaluate the postfix expression and return the number

int main()
{
  string infix;
  // cout << "Enter infix : ";
  cin >> infix;
try
  {
    string postfix = infixToPost(infix); // convert infix to postfix
    cout << postfix << endl;
    cout << evaluation(postfix) << endl; //does the math of the postfix
  }
 catch(Stack<char>::Underflow) //if pop is underflow
   {
     cout << "The expression is in a wrong format" << endl;
   }
 catch(Stack<double>::Underflow) //if pop is underflow
   { 
     cout << "The expression is in a wrong format" << endl;
   } 
 catch(const char* msg) //msg in evaluation function
   {
     cout << msg << endl;
   }
}

//checks if it is an operand
bool isOperand(char ch)
{
  if(ch >= '0' && ch <= '9') 
    return true;
  else 
    return false;
}

//checks if it is an operator
bool isOperator(char ch)
{
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  else
    return false;
}

//sets the prioriy order
//* and / higher than + and -
int priority(char ch)
{
  switch(ch)
    {
    case '+':
      return 1;
    case '-':
      return 1;
    case '*':
      return 2;
    case '/':
      return 2;
    }
}

//makes char to int
int charToInt(char ch)
{
  return ch - 48; 
}

//change the infix to postfix
string infixToPost(const string expr)
{
  Stack <char> s;
  string postfix;
  for(int i = 0; i < expr.length(); i++) //goes through the expression
    {
      if(isOperand(expr[i])) //if operand
	{
	  postfix+=expr[i]; 
	}
      else if(isOperator(expr[i])) //if operator
	{
	  while(!s.empty() && isOperator(s.getTop()) && priority(s.getTop()) >= priority(expr[i])) //need to make sure its not empty, priority is set and its an operator at the top
	    {
	      postfix += s.getTop(); //add it to the postfix 
	      s.pop();// pop top
	    }
	  s.push(expr[i]); //push it to the stack
	}
      else if(expr[i] == '(') //if its a (
	{
	  s.push(expr[i]); //push it to the stack
	}
      else if(expr[i] == ')') //if its a )
	{
	  while (s.getTop() != '(') //get the top til it hits (
	    {
	      postfix += s.getTop(); //add it to the postfix
	      s.pop(); //pop top
	    }
	  s.pop(); //pops the ( aswell
	}
      else 
	throw "The expression is in a wrong format";
    }
  while(!s.empty()) //gets the last one
    {
      postfix += s.getTop(); //add it to the postfix
      s.pop(); //pop top
    }
  return postfix; //return the postfix expression
}

//evaluating the postfix expression and getting the answer
double evaluation(const string postfix)
{
  Stack<double> s;
  double answer, n1, n2, current;
  for(int i = 0; i < postfix.length(); i++) //go through entire postfix expression
    {
      if(isOperand(postfix[i])) //if it is an operand
	s.push(charToInt(postfix[i])); //push to stack and convert to int
      else if(isOperator(postfix[i])) //if operator
	{
	  if(!s.empty()) //check if stack is empty
	    {
	      n1 = s.getTop();//get top value
	      s.pop();//pop top
	      if(!s.empty()) //if its still not empty
		{
		  n2 = s.getTop(); //get the top value
		  s.pop(); //pop top
		  current = doMath(n2, postfix[i], n1); //get the answer of the last two popped and do the math and put that into current
		  s.push(current); //push current into stack
		}
	      else //if empty throw
		throw "The expression is in a wrong format";
	    }
	  else //if empty throw
	    throw "The expression is in a wrong format";
	}
      else //if empty throw
	throw "The expression is in a wrong format";
    }
  if(!s.empty())// if not empty
    {
      answer = s.getTop(); //whatever is left is the answer
      s.pop(); //pop it
      if(!s.empty()) //if its empty, throw
	throw "The expression is in a wrong format"; 
      else 
	return answer; //return answer
    }
}

//does the math
double doMath(double operand1, char opt, double operand2)
{
  switch(opt)
    {
    case '+': 
      return operand1 + operand2;
    case '-': 
      return operand1 - operand2;
    case '*': 
      return operand1 * operand2;
    case '/': 
      return operand1 / operand2;
    }
}



