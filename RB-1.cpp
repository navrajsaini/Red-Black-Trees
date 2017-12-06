/************************************************************
BY: Navraj and Bhupender
Red Black Tree implementation
Resources:
Introduction to Algorithms Third ed by Thomas H. Cormen et al.
https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
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
void R_B_tree::Insert()
{
   struct timeval timeStart,
   timeEnd;
   // benchmark for Insert:
   gettimeofday(&timeStart, NULL);
   
   // get the key to be inserted
   int z;
   cout << endl << "Enter the key to be inserted: ";
   cin >> z;
   
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

//insert fix function
// to fix the tree after insertion, based on the RB tree rules
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
   if(root == NULL)
   {
      cout << endl << "Empty Tree." ;
      return;
   }
   //ask which node to delete
   int x;
   cout << "What node would you like to delete? ";
   cin >> x;
   
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
}
// delete fix function
// fix the tree after deletion is complete based on the rules
void R_B_tree::Deletefix(node *p)
{
   node *s;
   while(p != root && p -> colour == 'b')
   {
      if(p -> parent -> left == p)
      {
	 s = p -> parent -> right;
	 if(s -> colour == 'r')
	 {
	    s -> colour = 'b';
	    p -> parent -> colour = 'r';
	    LRotate(p -> parent);
	    s = p -> parent -> right;
	 }
	 if (s -> right -> colour == 'b' && s -> left -> colour == 'b')
	 {
	    s -> colour = 'r';
	    p = p -> parent;
	 }
	 else
	 {
	    if(s -> right -> colour == 'b')
	    {
	       s -> left -> colour == 'b';
	       s -> colour = 'r';
	       RRotate (s);
	       s = p -> parent -> right;
	    }
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
}

// left rotate
void R_B_tree::LRotate(node *s)
{
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
}

//Right Rotate
void R_B_tree::RRotate(node *x)
{
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
      cout << endl << "What function would you like to preform? (I/i for insert, D/d for delete, P/p for print and y to exit): ";
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
   
   
