/****************
Template created by Kazumi Slott
CS311

Your name: Tuan Tran
Your programmer number: 38
Hours spent?:  12
Any difficulties?: 
*****************/

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
using namespace std;

template <class T> //forward declaration needed so we can make stack class a friend of node
class AVL;

template <class T> //forward declaration needed so we can make operator<< a friend of node and Stack
  ostream& operator<<(ostream& o, const AVL<T>& s);


template <class T>  //make it a templare class
class Node
{
  friend class AVL<T>; //BST wants to access private members of Node
private:
  T el;
  Node<T>* right;
  Node<T>* left;
  Node<T>* up;
  int BF;
 public:
  Node() {right = left = up = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e; right = NULL; left = NULL; up = NULL; BF = 0;}; 
  T getEl() const {return el;} //returns el
};


template <class T>//Make it a template class
class AVL
{
private:
  Node<T>* root; //check stack_L_T.h to see how to declare top
  void inOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  void destroy(Node<T>* p);
  Node<T>* rightRotation(Node<T>* P);  
  Node<T>* leftRotation(Node<T>* P); 
  void balanceTree(Node<T>* newNode); 
  Node<T>* updateBF(Node<T>* Q); 
 public:
  AVL() {root = NULL;} //implement constructor here
  ~AVL(); 
  void insertNodeI(const T& e);
  void inOrderPrint();
  int getMaxLength();
  void BFTprint();
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
AVL<T>::~AVL()
{
  destroy(root);
}

template <class T>
void AVL<T>::destroy(Node<T>* p) //private function. WHY?
{
  if(p == NULL)
    {
    return;
    }
  destroy(p->left);
  destroy(p->right);
  delete p;
  //destroy all nodes
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void AVL<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e);
  Node<T>* p = root;
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if(e < p->el) 
	p = p->left; 
      else //if(p->el <= e)
	p = p->right;
    }
  
  if(parent == NULL) //tree is empty
    root = newNode;
  else if(e < parent->el) //insert a child as the parent's left child
    {
      parent->left = newNode;
    }
  else if(parent->el <= e) //insert a child as the parent's left child
    {
      parent->right = newNode;
    }
  newNode->up = parent;
  balanceTree(newNode);
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void AVL<T>::inOrderPrint(Node<T>* p)
{
  if(p== NULL)
    {
      return;
    }
 
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
 
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int AVL<T>::getMaxLength()
{
  return getMaxLength(root);
}

template <class T>
int AVL<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p == NULL)
    {
      return 0;
    }
  else
    {
      int left = getMaxLength(p->left) + 1; //get the value of the left sid \
      
      int right = getMaxLength(p->right) + 1; //get the value of the right \
      
      if(left >= right) //if left is greater than right
	{
	  return left;
	}
      else //if right is greater than left
	{
	  return right;
	}
    }  
}

template <class T>
void AVL<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://cplusplus.com/reference/queue/queue/

  //Make sure to include <queue> at the top
  queue<Node <T>*> q;  //create a queue obj of POINTERS to Nodes
  //algorithm is discussed in lecture

  //NOTICE
  //front() gives you the front element but it doesn't remove it from the qu\eue.
  //pop() removes the front element
  if(root != NULL)
    {
      q.push(root);
    }
   //cout << front-> el << "-->" << front->BF; 
  while(!q.empty()) //while its not empty
    {
      cout << q.front()->el << " " << q.front()->BF << " "; //prints front 
      if(q.front()-> up != NULL) //if the there is a parent of front
	{
	  cout << q.front()->up->el << "-->";
	}
      else
	{
	  cout << "-->";
	}
      if(q.front()->left != NULL)//if the left has pointers 
	{
	  q.push(q.front()->left);//push to the left side
	}
      if(q.front()->right != NULL)//if the right has pointers
	{
	  q.push(q.front()->right);//push to the right side
	}
      q.pop();
    }
}

template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* P)
{
  Node<T>* l = P->left; //left of p
  Node<T>* temp = l->right;//temp is left child of p's right child
  l->up = P->up; //connect left to its grandparent
  P->up = l;//set the parent's up with the left childs left
  if(temp != NULL) //if there is a right
    {
      temp->up = P; //temp up is p
    }
  l->right = P;//left child right is what the parent was
  P->left = temp; //root left equal to temp
  //calculate BF
  P->BF = getMaxLength(P->left) - getMaxLength(P->right);
  l->BF = getMaxLength(P->left) - getMaxLength(P->right);
  
  return l;//returns the rotation of the right
}

template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* P)
{
  Node<T>* r = P->right; //right of p
  Node<T>* temp = r->left;//temp is right child of p's left child
  r->up = P->up; //connect right to its grandparent
  P->up = r;//set the parent's up with the left childs left
  if(temp != NULL) //if there is a left
    {
      temp->up = P; //temp up is p
    }
  r->left = P;//rights left is what the parent was
  P->right = temp; //root right equal to temp
  //calculate BF
  P->BF = getMaxLength(P->left) - getMaxLength(P->right);
  r->BF = getMaxLength(P->left) - getMaxLength(P->right);

  return r;//returns the rotation of the left
}


template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)
{
  Node<T>* v = updateBF(newNode); //violation node
 if(v == NULL)
   {
     return;
   }
 Node<T>* temp; //temp node
     if(v->BF == 2 && v->left != NULL && v->left->BF == 1)//LL violation
       {
	 temp = rightRotation(v); //rotate right
       }
     else if(v->BF == -2 && v->right != NULL && v->right->BF == -1)//RR
       {
         temp = leftRotation(v); //rotate left
       }
     else if(v->BF == 2 && v->left != NULL && v->left->BF == -1)//LR violation
       {
	 //make left and right rotate
	 temp = leftRotation(v->left); //temp point to v left rotation
	 v->left = temp;//have that node's up be the violation
	 //set the vNode to the right rotation after the left rotation
	 temp = rightRotation(v); //rotate right
       }
     else//RL
       {
	 //makes a right then left rotation
	 temp = rightRotation(v->right); //temp point to v right rotation
	 v->right = temp; //node up is the violation 
	 //left rotation once the right rotation is completed
	 temp = leftRotation(v); //rotate left
       }

     Node<T>* p = temp->up; //parent of temp (root)

     if(v == root)//if the original was root
       {
	 root = temp;//new root
       }
     else if(v == p->left) //violating node was parents left child 
       {
	 p->left = temp;
       }    
     else //violating node was parents right
       {
	 p->right = temp;
       }
}



template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)
{
  Node<T>* p = Q->up; 
  if(Q->up == NULL) //if the q is the root
    {
      return NULL;
    }
  if(p->left == Q) //if q is left child of p
    {
      p->BF++; //increment bf
    }
  else
    {
      p->BF--; //decrement bf
    }
  while(p!= root && p->BF != 2 && p-> BF != -2)//violation
    {
      Q = p;
      p = p->up;
      if(Q->BF == 0) //balanced
	{
	  return NULL;
	}
      if(p->left == Q) //left side 
	{
	  p->BF++;
	}
      else //right side
	{
	  p->BF--;
	}
    }
  if(p->BF == 2 || p->BF == -2)//return violating node
    return p;
  return NULL; //no violation
}
#endif
