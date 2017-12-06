#include <iostream>

using namespace std;

struct node
{
   int key;
   node *parent, *left, *right;
   char colour;
};

class R_B_tree
{
public:
   node *root;
   node *q;
   //functions
   void LRotate (node*);
   void RRotate (node*);
   void Delete (node*);
   void Insert (/*node*/);
   void Insertfix (node*);
   void Deletefix (node*);
   void Transplant (node*, node*);
   node* t_min (node*);

};

void R_B_tree::LRotate (node* x)
{
   node* y = x -> right;
   x -> right = y -> left;
	
   if (y -> left != NULL)
      y -> left -> parent = x;
   y -> parent = x -> parent;
	
   if (x -> parent == NULL)
      root = y;
	
   else
      if (x == x -> parent -> left)
	 x -> parent -> left = y;
   
      else
	 x -> parent -> right = y;
   y -> left = x;
   x -> parent = y;
}

void R_B_tree::RRotate (node* x)
{
   node* y = x -> left;
   x -> left = y -> right;
	
   if (y -> right != NULL)
      y -> right -> parent = x;
   y -> parent = x -> parent;
	
   if (x -> parent == NULL)
      root = y;
	
   else
      if (x == x -> parent -> right)
	 x -> parent -> right = y;
   
      else
	 x -> parent -> left = y;
   y -> right = x;
   x -> parent = y;
}

void R_B_tree::Transplant (node* u, node* v)
{
   if (u -> parent == NULL)
      root = v;
   else
      if (u == u -> parent -> left)
	 u -> parent -> left = v;
      else 
	 u -> parent -> right = v;
   v -> parent = u -> parent;
}

void R_B_tree::Delete (node* z)
{
   node* y = z;
   node* x;
   char y_og_col = y -> colour;
	
   if (z -> left == NULL)
   {
      x = z -> right;
      Transplant (z, z -> right);
   }
   else
      if (z -> right == NULL)
      {
	 x = z -> left;
	 Transplant (z, z -> left);
      }
      else
      {
	 y = t_min (z -> right);
	 y_og_col = y -> colour;
	 x = y -> right;
	 
	 if (y -> parent == z)
	    x -> parent = y;
	 else
	 {
	    Transplant (y, y -> right);
	    y -> right = z -> right;
	    y -> right -> parent = y;
	 }
	 Transplant (z, y);
	 y -> left = z -> left;
	 y -> left -> parent = y;
	 y -> colour = z -> colour;
      }
   
   if (y_og_col == 'b')
      Deletefix (x);
}

void R_B_tree::Deletefix (node* x)
{
   node* s;
   while (x != root && x -> colour == 0)
   {
		
      if (x == x -> parent -> left)
      {
	 s = x -> parent -> right;
			
	 if (s -> colour == 'r')
	 {
	    s -> colour = 'b';
	    x -> parent -> colour = 'r';
	    LRotate (x -> parent);
	    s = x -> parent -> right;
	 }
			
	 if (s -> left -> colour == 'b' && s -> right -> colour == 'b')
	 {
	    s -> colour = 'r';
	    x = x -> parent;
	 }
			
	 else
	 {
	    if (s -> right -> colour = 'b')
	    {
	       s -> left -> colour = 'b';
	       s -> colour = 'r';
	       RRotate (s);
	       s = x -> parent -> right;
	    }
	    s -> colour = x -> parent -> colour;
	    x -> parent -> colour = 'b';
	    s -> right -> colour = 'b';
	    LRotate (x -> parent);
	    x = root;
	 }
      }
      else
      {
	 s=x->parent->left;
			
	 if(s->colour=='r')
	 {
	    s->colour='b';
	    x->parent->colour='r';
	    RRotate(x->parent);
	    s=x->parent->left;
	 }
	 if(s->left->colour=='b' && s->right->colour=='b')
	 {
	    s->colour='r';
	    x=x->parent;
	 }
	 else
	 {
	    if(s->left->colour=='b')
	    {
	       s->right->colour='b';
	       s->colour='r';
	       LRotate(s);
	       s=x->parent->left;
	    }
	    s->colour=x->parent->colour;
	    x->parent->colour='b';
	    s->left->colour='b';
	    RRotate(x->parent);
	    x=root;
	 }
      }
      x -> colour = 'b';
      root -> colour = 'b';
   }
}

node* R_B_tree::t_min (node* x)
{
   while (x -> left != NULL)
      x = x -> left;
   return x;
}

void R_B_tree::Insert ()
{
   /*
     node* y = NULL;
     node* x = root;

     while (x != NULL)
     {
     y = x;
     if (z -> key < x -> key)
     x = x -> left;
     else
     x = x -> right;
     }//end of while
     z -> parent = y;
	
     if (y == NULL)
     {
     root = z;
     }// end of if(y==NULL)
	
     else
     {
     if (z -> key < y -> key)
     {
     y -> left = z;
     }// end of elseif
     else
     y -> right = z;
     }
     z -> right = NULL;
     z -> left = NULL;
     z -> colour = 'r';
     Insertfix(z);
   */
   int z, i=0;
   cout<< endl << "Which key would you like to insert? (must be an int): ";
   cin>>z;
   node *p,*q;
   node *t=new node;
   
   t->key=z;
   
   t->left=NULL;
   t->right=NULL;
   t->colour='r';

   p=root;
   q=NULL;
   
   if(root==NULL)
   {
      root=t;
      t->parent=NULL;

      cout << "finished root==NULL if loop..." << endl;
   }
   
   else
   {
      
      while(p!=NULL)
      {
	 q=p;
	 if(p->key < t->key)
	    p=p->right;
	 else
	    p=p->left;
      }
      t->parent=q;
      if(q->key<t->key)
	 q->right=t;
      else
	 q->left=t;
   }
   cout << "about to fix insert..." <<endl;
   Insertfix(t);
}

void R_B_tree::Insertfix (node* z)
{
   node* y;
   while (z -> parent -> colour == 'r')
   {
      if (z -> parent == z -> parent -> parent -> left)
      {
	 y = z -> parent -> parent -> right;
			
	 if (y -> colour == 'r')
	 {
	    z -> parent -> colour = 'b';
	    y -> colour = 'b';
	    z -> parent -> parent -> colour = 'r';
	 }//end of if (y.colour == 'r')
			
	 else
	 {
	    if (z == z -> parent -> right)
	    {
	       z = z -> parent;
	       LRotate(z);
	    }//end of if
	    z -> parent -> colour = 'b';
	    z -> parent -> parent -> colour = 'r';
	    RRotate(z -> parent -> parent);
	 }// end of else
      }// end of first if
		
      else
      {
	 if (y -> colour == 'r')
	 {
	    z -> parent -> colour = 'r';
	    y -> colour = 'r';
	    z -> parent -> parent -> colour = 'b';
	 }//end of if (y.colour == 'b')
			
	 else
	 {
	    if (z == z -> parent -> right)
	    {
	       z = z -> parent;
	       LRotate(z);
	    }//end of if
	    z -> parent -> colour = 'r';
	    z -> parent -> parent -> colour = 'b';
	    RRotate(z -> parent -> parent);
	 }// end of else
      }// end of first else
   }//end of while loop
   root -> colour = 'b';
}

int main ()
{
   char func;
   R_B_tree obj;
   cout << "What function would you like to test? (Insert (I), Delete (D)) ";
   cin >> func;

   switch (func)
   {
      case 'I':
	 obj.Insert();
	 break;
   }
}
