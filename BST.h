/****************
Template created by Kazumi Slott
CS311

Your name: ???????
Your programmer number: ?????
Hours spent?: ???
Any difficulties?: ??????
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
//?????
//?????

template <class T> //forward declaration needed so we can make stack class a friend of node
class BST;

template <class T> //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const BST<T>& s);


//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.


template <class T>  //make it a templare class
class Node
{
  friend class BST<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e; right = NULL; left = NULL;}; 
  T getEl() const {return el;} //returns el
};


template <class T>//Make it a template class
class BST
{
private:
  Node<T>* root; //check stack_L_T.h to see how to declare top
  //You will need 10 private functions here.  WHY private?
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p, const T& e);
  int getEvenNodes(Node<T>* p);
  void destroy(Node<T>* p);
  void remove(Node<T>*& p);
 public:
  BST() {root = NULL;} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
  bool remove(const T& e);
  void DFTprint();
  void BFTprint();
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T> 
BST<T>::~BST()
{
  destroy(root);
}

template <class T>
void BST<T>::destroy(Node<T>* p) //private function. WHY?
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



//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()
template <class T>
void BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

template <class T>
void BST<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY?
{
  if(p == NULL)
    {
      p = new Node<T>(e);
    }
  else if(e < p->el)
    {
      insertNodeR(p->left, e);
    }
  else if(e >= p->el)
    {
      insertNodeR(p->right, e);
    }
}



//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void BST<T>::insertNodeI(const T& e)
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
    parent->left = newNode;
  else if(parent->el <= e) //insert a child as the parent's left child
    parent->right = newNode;
}


//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if(p== NULL)
    {
      return;
    }
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
}



template <class T>
void BST<T>::preOrderPrint()
{
  preOrderPrint(root);  //pre means print parent->left child ->right child
}

template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p == NULL)
    {
      return;
    } 
  cout << p->el << "-->"; //print out 
  preOrderPrint(p->left); //left
  preOrderPrint(p->right); //right
}



template <class T>
void BST<T>::postOrderPrint()
{
  postOrderPrint(root);  //post means left->right->parent last
}

template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if(p == NULL)
    {
      return;
    }
  postOrderPrint(p->left); //left of tree
  postOrderPrint(p->right); //right of tree
  cout << p->el << "-->";
}



//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);  
}

template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if(p == NULL)
    {
      return 0;
    }
  else
    {
      return getNumNodes(p->left) + getNumNodes(p->right) + 1;
    }
}



//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root);
}

template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
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
int BST<T>::getMinLength()
{
  getMinLength(root);  
}

template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  if(p == NULL)
    {
      return 0;
    }
  else
    {
      int left, right;
      left = getMinLength(p->left) + 1;//left side 
      right = getMinLength(p->right) + 1;//right side 
      if(left < right)//if left side is less than right
	{
	  return left;//return left
	}
      if(right <= left)//if right side is less than left
	{
	  return right;//return right
	}
    }
}

//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                                            
{
  getEvenNodes(root);                                                            
}

template <class T>                                                                                  
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY?              
{                              
  int num = 0;                                             
  if(p == NULL)
    {
      return num;
    }          
  else
    {
      if(p->el % 2 == 0)
	{
	  num++;
	}
	  return num + getEvenNodes(p->left) + getEvenNodes(p->right);
    }
      
}

//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
 Node<T>* p = root;

  while(p != NULL)
    {
      if(p->el == e || p == NULL)
	{
	  return p;
	}
      else if(p->el > e)
	{
	  p = p->left;
	}
      else if(p-> el <= e)
	{
	  p = p->right;
	}
    }
  
}


//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
 return searchR(root, e);
}

template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{
 if(p == NULL)
   {
    return NULL; //if it is still not found after all the searching, return false
   }
  else if(p-> el == e) //if the element is found
    {
      return p;
    }
  else if(e > p-> el) //if the element is larger than the root
    {
      searchR(p->right, e); //search through the right side
    }
  else if(e < p-> el) //if the element is smaller than the root
      {
        searchR(p->left, e); //if it is still not found after, return fal\
      
      }

}

template <class T>
void BST<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://cplusplus.com/reference/queue/queue/

  //Make sure to include <queue> at the top
  queue<Node <T>*> q;  //create a queue obj of POINTERS to Nodes
  //algorithm is discussed in lecture

  //NOTICE
  //front() gives you the front element but it doesn't remove it from the qu\eue.
  //pop() removes the front element
  if(root == NULL)
    {
      return;
    }
  q.push(root);//push root in the queue
  while(!q.empty()) //while its not empty
    {
      Node<T>* front = q.front();//gets the front
      cout << front->el << "-->";
      q.pop();    
      if(front->left != NULL)//if the left has pointers 
	{
	  q.push(front->left);//push to the left side
	}
      if(front->right != NULL)//if the right has pointers
	{
	q.push(front->right);//push to the right side
	}
    }
}


template <class T>
void BST<T>::DFTprint()  //Depth First Traversal Print                      
{
  //Use the library's stack class. https://cplusplus.com/reference/stack/sta\ck/
  
  stack<Node <T>*> s;  //Make sure to include <stack> at the top	
  
  //create a stack of POINTERS to Nodes
  
  //top() will give you the top element but it will not remove it from the stack.
  //pop() removes the top element.                                          
  if(root == NULL)
    {
      return;
    }
  s.push(root);
  while(!s.empty())//if the stack is not empty
      {
	Node<T>* top = s.top();//set the top element to the top function
	cout << top->el << "-->";//pop top and print
	s.pop();
	if(top->right != NULL)//if the top's right is not empty
	  {
	    s.push(top->right);//push right kid if any
	  }
	if(top->left != NULL)
	  {
	    s.push(top->left);//push left kid if any
	  }
      } 
}

template <class T>
bool BST<T>::remove(const T& e) //public function
{
  Node<T>* del = root; //del will point to the node to be deleted
  Node<T>* parent = NULL; //parent will point to the parent of the node to be deleted
  
  //look for e in the tree
  while(del!=NULL && del->el != e) //If root is NULL, del is NULL to start with. While won't be entered and return false down below.
    {
      parent = del;//parent follows del. In other words, del is ahead of parent. --> you did something similar in insertI()
      //del will eventually point to the node to be deleted.
      if(del->el > e) //if the del is greater than e
	{
	  del = del->left; //move del to the left
	}
      else //if del is less than or equal to e
	{
	  del = del->right; //move del to the right
	}
    }
  
  //e doesn't exist or tree is empty.
  if(del == NULL)
    {
      return false;
    }
  //check to see if root should be removed
  if(parent==NULL) //if the element is the root
    remove(root); //root will change. call the other remove function down below
  //We are deleting a node other than the root node. Figure out if del's node is left or right child of parent's node
  else if(parent->left->el == e) //parent's left child to be removed
    remove(parent->left);
  else //parent's right child to be removed
    remove(parent->right);
  
  //deleted the node with e
  return true;
}


template <class T>
//p comes out of the parent node and points to the node to be deleted OR points to root if root is the one to be deleted.
//p will point to the grandchild (child node of the node to be deleted) if the node to be deleted has only one child or will point to NULL if p is root
//the node to be deleted has no children. p will change. That is why we need to use &.
void BST<T>::remove(Node<T>*& p) //private function
{
  Node<T>* temp = p; //temp points to the node to be deleted initially
  Node<T>* t_parent; //t_parent will point to the parent node of temp's node

  //the node to be deleted has no right child (Check Diagram1-Right and Left in the homework document "HMWK BST - BFT, DFT and remove" under "Assignment s")
  //If the node to be deleted has no children, the following if will be executed.(Check Diagram2-Right and Left)
  if(p->right == NULL) //if there is no right child
    p = p->left; //p(The left or right coming out of parent of del's node) now points to the root of the left subtree under del's node. DONE.  If the node to be deleted has no children, p is set to NULL because p->left is NULL.
  //the node to be deleted has no left child (Check Diagram 3-Right and Left \
  )
 else if(p->left == NULL) //if there is no left child
   p = p->right;//p(The left or right coming out of parent of del's node) now points to the root of the right subtree under del's node. DONE.
//If the node to be deleted has 2 children
 else
   {
      //we are going to replace e by the largest value in the left subtree
      temp = p->left; //temp points to the root of the left subtree under the node to be deleted to start with
      t_parent = p; //t_parent points to the node to be deleted to start with
      
      //go to the largest value in the left subtree under the node to be deleted by going all the way down to right
      while(temp->right != NULL)
        {
          t_parent = temp; //temp is ahead of t_parent
          temp = temp->right; //temp will eventually point to the largest value
        }
      //copy the largest value into the node to be deleted
      p->el=temp->el;
      if(temp == p->left) //the largest value is the direct left child of the node whose value was replaced by the largest (Diagram 4-one child or no children)
	p->left = temp->left; //connect the left of the node whose value was replaced by the largest value to the left child of the node that has the largest value
      else //the largest value is NOT the direct left child of the node whose value was replaced by the largest (Diagram 5-one child and no children)
	t_parent->right=temp->left; //If the node with the largest value doesn't have any chil dren, t_parent->right is set to NULL.
   }
//finally delete temp;
delete temp;
}




#endif
