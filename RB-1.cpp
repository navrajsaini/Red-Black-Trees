/************************************************************
BY: Navraj and Bhupender
Red Black Tree implementation
Resources:
Introduction to Algorithms Third ed by Thomas H. Cormen et al.
https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html

benchmark was used from: https://bruun.co/2012/02/07/easy-cpp-benchmarking
**************************************************************/

#include <iostream>
#include <sys/time.h>
using namespace std;

//node struct
struct node
{
   int key;
   node *parent, *left, *right;
   char colour;
   
};

//RB tree class
class R_B_tree
{
public :
   node *root;
   node *q;

   R_B_tree ()
   {
      q = NULL;
      root = NULL;
   }
   void Insert ();
   void LRotate (node*);
   void RRotate (node*);
   void Delete ();
   void Deletefix (node*);
   void Insertfix (node*);
   void print (node*);
};
/*
  insert requires a few cases
  the inserted node replaces an existing leaf and then
  has it's own leaves, instead of adding the new node as a leaf

  The insertion is done the same way as BST then Insertfix is called to
  fix and RB tree rule violations.
 */
void R_B_tree::Insert()
{

   // get the key to be inserted
   int z;
   cout << endl << "Enter the key to be inserted: ";
   cin >> z;
   
   struct timeval timeStart,
   timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);
   

   
   node *p, *q;
   node *t = new node; // make a new node to store the key
   t -> key = z;
   t -> left = NULL;
   t -> right = NULL;
   t -> colour = 'r'; // make the colour red based on the rules of RB-trees
   p = root;
   q = NULL;
   if (root == NULL)// if there is no root then T the root
   {
      root = t;
      t -> parent = NULL;
   }
   else// else find the location for t to be inserted and adjust accordingly
   {
      while (p != NULL)
      {
	 q = p;
	 if(p -> key < t -> key)
	    p = p -> right;
	 else
	    p = p -> left;
      }
      t -> parent = q;
      if(q -> key < t -> key)
	 q -> right = t;
      else
	 q -> left = t;
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The insert function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec) << "ms to execute." << endl;
   
   Insertfix(t);//fix the tree based on the RB tree rules
}

/*insert fix function
  to fix the tree after insertion, based on the RB tree rules

  if x is a newly inserted node:

  the fix steps are:

  1. Do following if color of x’s parent is not BLACK or x is not root.
  a) If x’s uncle is RED (Grand parent must have been black from property 4)
    (i) Change color of parent and uncle to BLACK.
    (ii) color of grandparent to RED.
    (iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
  b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g)
    (i) Left Left Case (p is left child of g and x is left child of p)
    (ii) Left Right Case (p is left child of g and x is right child of p)
    (iii) Right Right Case (Mirror of case a)
    (iv) Right Left Case (Mirror of case c)
*/
void R_B_tree::Insertfix(node *t)
{
   struct timeval timeStart,
   timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);

   
   node *u;
   if(root == t)// if the node is the root then change it's colour to black and return
   {
      t -> colour = 'b';
      return;
   }
   // while the parent exists and the colour of the parent is red
   while(t -> parent != NULL && t -> parent -> colour == 'r')
   {
      node *g = t -> parent -> parent;
      
      if (g -> left == t -> parent)
      {
	 if(g -> right != NULL)
	 {
	    u = g -> right;
	    if(u -> colour == 'r')
	    {
	       t -> parent -> colour = 'b';
	       u -> colour = 'b';
	       g -> colour = 'r';
	       t = g;
	    }
	 }
	 else
	 {
	    if(t -> parent -> right == t)
	    {
	       t = t -> parent;
	       LRotate(t);
	    }
	    t -> parent -> colour = 'b';
	    g -> colour = 'r';
	    RRotate(g);
	 }
      }
      else
      {
	 if(g -> left != NULL)
	 {
	    u = g -> left;
	    if(u -> colour == 'r')
	    {
	       t -> parent -> colour = 'b';
	       u -> colour = 'b';
	       g -> colour = 'r';
	       t = g;
	    }
	 }
	 else
	 {
	    if(t -> parent -> left == t)
	    {
	       t = t -> parent;
	       RRotate(t);
	    }
	    t -> parent -> colour = 'b';
	    g -> colour = 'r';
	    LRotate(g);
	 }
      }
      root -> colour = 'b';
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The insertfix function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec) << "ms to execute." << endl;
}
//delete function
void R_B_tree::Delete()
{
   //ask which node to delete
   int x;
   cout << "What node would you like to delete? ";
   cin >> x;
   struct timeval timeStart,
      timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);
   if(root == NULL)
   {
      cout << endl << "Empty Tree." ;
      return;
   }

   
   node *p;
   p = root;
   node *y = NULL;
   node *q = NULL;
   bool exists = 0;// a bool variable to make sure there is something that can be deleted

   // if the root exists find the node to be deleted and delete it
   // which is done when exists = TRUE.
   while(p != NULL && exists == 0)
   {
      if(p -> key == x)
	 exists = 1;
      if(exists == 0)
      {
	 if(p -> key < x)
	    p = p -> right;
	 else
	    p = p -> left;
      }
   }
   if(exists == 0)
   {
      return;
   }
   else
   {
      cout << "deleting " << p->key;
      
      if(p->left == NULL or p->right == NULL)
	 y = p;
      else
      {
	 if (p -> left != NULL)
	 {
	    y = p -> left;
	    while (y -> right != NULL)
	       y = y -> right;
	 }
	 else
	 {
	    y = p -> right;
	    while (y -> left != NULL)
	       y = y -> left;
	 }
      }
      if(y -> left != NULL)
	 q = y -> left;
      else
      {
	 if (y -> right != NULL)
	    q = y -> right;
	 else
	    q = NULL;
      }
      if(q != NULL)
	 q -> parent = y -> parent;
      if (y -> parent == NULL)
	 root = q;
      else
      {
	 if(y == y -> parent -> left)
	    y -> parent -> left = q;
	 else
	    y -> parent -> right = q;
      }
      if(y != p)
      {
	 p -> colour = y -> colour;
	 p -> key = y -> key;
      }
      if(y -> colour == 'b')
	 Deletefix(q);
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The delete function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec) << "ms to execute." << endl;
}
/* delete fix function
   fix the tree after deletion is complete based on the rules

   cases:
   1. p's sibling s is red:
   occurs when s is red. since s must have black childern, we switch
   the colour of s and p.parent then a LRotation is preformed on p.parent.
   This converts case 1 to one of the other 3 cases.

   case 2, 3, and 4 occur when s is black.

   2. p's sibling s is blakc and both of s's childern are black:
   since s is also black along with it's childern, we take one black off both p and s,
   leaving p with only one black and s red. the while loop is repeated with p.parent to
   add an extra black to p.parent.

   3. p's sibling s is black, s's left child is red and right child is black:
   s's colour is swaped with it's left child then we perform a RRotation.
   This transforms case 3 to 4, the new sibling s of p is not balck with a red right.

   4. p's sibling s is balkc and s's right child is red:
   We remove the extra balck on p by performing a left rotation on p.parent after recolouring is done.
   
   
*/
void R_B_tree::Deletefix(node *p)
{
   struct timeval timeStart,
   timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);

   
   node *s;
   while(p != root && p -> colour == 'b')
   {
      if(p -> parent -> left == p)
      {
	 s = p -> parent -> right;
	 //case 1.
	 if(s -> colour == 'r')
	 {
	    s -> colour = 'b';
	    p -> parent -> colour = 'r';
	    LRotate(p -> parent);
	    s = p -> parent -> right;
	 }
	 // case 2
	 if (s -> right -> colour == 'b' && s -> left -> colour == 'b')
	 {
	    s -> colour = 'r';
	    p = p -> parent;
	 }
	 // case 3
	 else
	 {
	    if(s -> right -> colour == 'b')
	    {
	       s -> left -> colour == 'b';
	       s -> colour = 'r';
	       RRotate (s);
	       s = p -> parent -> right;
	    }
	    // case 4
	    s -> colour = p -> parent -> colour;
	    p -> parent -> colour = 'b';
	    s -> right -> colour = 'b';
	    LRotate (p -> parent);
	    p = root;
	 }
      }
      else
      {
	 s = p -> parent -> left;
	 if(s -> colour == 'r')
	 {
	    s -> colour = 'b';
	    p -> parent -> colour = 'r';
	    RRotate (p -> parent);
	    s = p -> parent -> left;
	 }
	 if(s -> left -> colour == 'b' && s -> right -> colour == 'b')
	 {
	    s -> colour = 'r';
	    p = p -> parent;
	 }
	 else
	 {
	    if (s -> left -> colour == 'b')
	    {
	       s -> right -> colour = 'b';
	       s -> colour = 'r';
	       LRotate (s);
	       s = p -> parent -> left;
	    }
	    s -> colour = p -> parent -> colour;
	    p -> parent -> colour = 'b';
	    s -> left -> colour = 'b';
	    RRotate (p -> parent);
	    p = root;
	 }
      }
      p -> colour = 'b';
      root -> colour = 'b';
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The deletefix function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec) << "ms to execute." << endl;
}

// left rotate
void R_B_tree::LRotate(node *s)
{
   struct timeval timeStart,
   timeEnd;
   // benchmark:
   gettimeofday(&timeStart, NULL);
   
   if (s -> right == NULL)
      return;
   else
   {
      node *y = s -> right;
      if (y -> left != NULL)
      {
	 s -> right = y -> left;
	 y -> left -> parent = s;
      }
      else
	 s -> right = NULL;
      if (s -> parent != NULL)
	 y -> parent = s -> parent;
      if (s -> parent == NULL)
	 root = y;
      else
      {
	 if(s == s -> parent -> left)
	    s -> parent -> left = y;
	 else
	    s -> parent -> right = y;
      }
      y -> left = s;
      s -> parent = y;
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The left rotate function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec)
	<< "ms to execute." << endl;
}

//Right Rotate
void R_B_tree::RRotate(node *x)
{
   
   struct timeval timeStart,
      timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);
   
   if(x -> left == NULL)
      return;
   else
   {
      node *y = x -> left;
      if(y -> right != NULL)
      {
	 x -> left = y -> right;
	 y -> right -> parent = x;
      }
      else
	 x -> left = NULL;
      if(x -> parent != NULL)
	 y -> parent = x -> parent;
      if(x -> parent == NULL)
	 root = y;
      else
      {
	 if(x == x -> parent -> left)
	    x -> parent -> left = y;
	 else
	    x -> parent -> right = y;
      }
      y -> right = x;
      x -> parent = y;
   }
   gettimeofday(&timeEnd, NULL);
   cout << endl << "The Right Rotate function took " << ((timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + timeEnd.tv_usec - timeStart.tv_usec)
	<< "ms to execute." << endl;
}

// Print function
// Prints the Key, Parent, Left and Right keys
void R_B_tree::print(node* p)
{
   cout << endl;
   if(root == NULL)
   {
      cout << endl << "No nodes in this tree.";
      return;
   }

   if(p != NULL)
   {
      cout << endl << "Key: " << p -> key << endl;
      if(p -> colour == 'b')
	 cout << "Black" << endl;
      else
	 cout << "Red" << endl;
      
      if(p -> parent != NULL)
	 cout << endl << "Parent: " << p -> parent -> key;
            
      if(p -> left != NULL)
	 cout << endl << "Left: " << p -> left -> key;
      
      if(p -> right != NULL)
	 cout << endl << "Right: " << p -> right -> key;

      cout << endl;
      if(p -> left)
      {
	 cout << endl << "Left: ";
	 print (p -> left);
      }

      if(p -> right)
      {
	 cout << endl << "Right: ";
	 print (p -> right);
      }

   }
   
}

int main()
{
   char func = 'n';
   R_B_tree RB;
   while (func != 'y')
   {
      cout << endl << "What function would you like to preform? \n(I/i for insert, D/d for delete, P/p for print and y to exit): ";
      cin>> func;
      switch(func)
      {
	 case 'I' :
	 case 'i':
	    RB.Insert();
	    break;
	 case 'D' :
	 case 'd':
	    RB.Delete();
	    break;
	 case 'P':
	 case 'p':
	    RB.print(RB.root);
	    break;
	 case 'y':
	 case 'Y':
	    cout << endl;
	    return 0;
	 default : cout << "That is not a valid choice...";
      }
   }
}
   
   
