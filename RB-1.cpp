#include<iostream>

using namespace std;

struct node
{
   int key;
   node *parent;
   char colour;
   node *left;
   node *right;
};
class R_B_tree
{
   node *root;
   node *q;
public :
   R_B_tree()
   {
      q = NULL;
      root = NULL;
   }
   void Insert ();
   void Insertfix (node*);
   void LRotate (node*);
   void RRotate (node*);
   void Delete ();
   node* successor (node*);
   void Deletefix (node*);
   void disp ();
   void print (node*);
};
void R_B_tree::Insert()
{
   int z, i = 0;
   cout << endl << "Enter the key to be inserted: ";
   cin >> z;
   node *p, *q;
   node *t = new node;
   t -> key = z;
   t -> left = NULL;
   t -> right = NULL;
   t -> colour = 'r';
   p = root;
   q = NULL;
   if (root == NULL)
   {
      root = t;
      t -> parent = NULL;
   }
   else
   {
      while (p != NULL)
      {
	 q = p;
	 if(p -> key < t -> key)
	    p = p -> right;
	 else
	    p = p -> left;
      }
      t->parent = q;
      if(q->key<t->key)
	 q->right = t;
      else
	 q->left = t;
   }
   Insertfix(t);
}
void R_B_tree::Insertfix(node *t)
{
   node *u;
   if(root==t)
   {
      t->colour = 'b';
      return;
   }
   while(t -> parent != NULL&& t -> parent -> colour=='r')
   {
      node *g = t->parent->parent;
      if(g->left==t->parent)
      {
	 if(g -> right != NULL)
	 {
	    u=g->right;
	    if(u->colour=='r')
	    {
	       t->parent->colour = 'b';
	       u->colour = 'b';
	       g->colour = 'r';
	       t = g;
	    }
	 }
	 else
	 {
	    if(t->parent->right==t)
	    {
	       t = t->parent;
	       LRotate(t);
	    }
	    t->parent->colour = 'b';
	    g->colour = 'r';
	    RRotate(g);
	 }
      }
      else
      {
	 if(g->left != NULL)
	 {
	    u = g->left;
	    if(u->colour=='r')
	    {
	       t->parent->colour = 'b';
	       u->colour = 'b';
	       g->colour = 'r';
	       t = g;
	    }
	 }
	 else
	 {
	    if(t->parent->left==t)
	    {
	       t = t->parent;
	       RRotate(t);
	    }
	    t->parent->colour = 'b';
	    g->colour = 'r';
	    LRotate(g);
	 }
      }
      root->colour = 'b';
   }
}

void R_B_tree::Delete()
{
   if(root==NULL)
   {
      cout<<"\nEmpty Tree." ;
      return ;
   }
   int x;
   cout << "What node would you like to delete? ";
   cin >> x;
   node *p;
   p = root;
   node *y = NULL;
   node *q = NULL;
   int found = 0;
   while(p != NULL&& found == 0)
   {
      if(p->key==x)
	 found = 1;
      if(found==0)
      {
	 if(p->key<x)
	    p = p->right;
	 else
	    p = p->left;
      }
   }
   if(found==0)
   {
      cout<<"\nElement Not Found.";
      return ;
   }
   else
   {
      cout<<"\nDeleteeted Element: "<<p->key;
      cout<<"\nColour: ";
      if(p->colour=='b')
	 cout<<"Black\n";
      else
	 cout<<"Red\n";

      if(p->parent!=NULL)
	 cout<<"\nParent: "<<p->parent->key;
      else
	 cout<<"\nThere is no parent of the node.  ";
      if(p->right != NULL)
	 cout<<"\nRight Child: "<<p->right->key;
      else
	 cout<<"\nThere is no right child of the node.  ";
      if(p->left != NULL)
	 cout<<"\nLeft Child: "<<p->left->key;
      else
	 cout<<"\nThere is no left child of the node.  ";
      cout<<"\nNode Deleteeted.";
      if(p->left == NULL||p->right == NULL)
	 y=p;
      else
	 y=successor(p);
      if(y->left!=NULL)
	 q=y->left;
      else
      {
	 if(y->right!=NULL)
	    q=y->right;
	 else
	    q=NULL;
      }
      if(q!=NULL)
	 q->parent=y->parent;
      if(y->parent==NULL)
	 root=q;
      else
      {
	 if(y==y->parent->left)
	    y->parent->left=q;
	 else
	    y->parent->right=q;
      }
      if(y!=p)
      {
	 p->colour=y->colour;
	 p->key=y->key;
      }
      if(y->colour=='b')
	 Deletefix(q);
   }
}

void R_B_tree::Deletefix(node *p)
{
   node *s;
   while(p!=root&&p->colour=='b')
   {
      if(p->parent->left==p)
      {
	 s=p->parent->right;
	 if(s->colour=='r')
	 {
	    s->colour='b';
	    p->parent->colour='r';
	    LRotate(p->parent);
	    s=p->parent->right;
	 }
	 if(s->right->colour=='b'&&s->left->colour=='b')
	 {
	    s->colour='r';
	    p=p->parent;
	 }
	 else
	 {
	    if(s->right->colour=='b')
	    {
	       s->left->colour=='b';
	       s->colour='r';
	       RRotate(s);
	       s=p->parent->right;
	    }
	    s->colour=p->parent->colour;
	    p->parent->colour='b';
	    s->right->colour='b';
	    LRotate(p->parent);
	    p=root;
	 }
      }
      else
      {
	 s=p->parent->left;
	 if(s->colour=='r')
	 {
	    s->colour='b';
	    p->parent->colour='r';
	    RRotate(p->parent);
	    s=p->parent->left;
	 }
	 if(s->left->colour=='b'&&s->right->colour=='b')
	 {
	    s->colour='r';
	    p=p->parent;
	 }
	 else
	 {
	    if(s->left->colour=='b')
	    {
	       s->right->colour='b';
	       s->colour='r';
	       LRotate(s);
	       s=p->parent->left;
	    }
	    s->colour=p->parent->colour;
	    p->parent->colour='b';
	    s->left->colour='b';
	    RRotate(p->parent);
	    p=root;
	 }
      }
      p->colour='b';
      root->colour='b';
   }
}

void R_B_tree::LRotate(node *p)
{
   if(p->right==NULL)
      return ;
   else
   {
      node *y=p->right;
      if(y->left!=NULL)
      {
	 p->right=y->left;
	 y->left->parent=p;
      }
      else
	 p->right=NULL;
      if(p->parent!=NULL)
	 y->parent=p->parent;
      if(p->parent==NULL)
	 root=y;
      else
      {
	 if(p==p->parent->left)
	    p->parent->left=y;
	 else
	    p->parent->right=y;
      }
      y->left=p;
      p->parent=y;
   }
}
void R_B_tree::RRotate(node *p)
{
   if(p->left==NULL)
      return ;
   else
   {
      node *y=p->left;
      if(y->right!=NULL)
      {
	 p->left=y->right;
	 y->right->parent=p;
      }
      else
	 p->left=NULL;
      if(p->parent!=NULL)
	 y->parent=p->parent;
      if(p->parent==NULL)
	 root=y;
      else
      {
	 if(p==p->parent->left)
	    p->parent->left=y;
	 else
	    p->parent->right=y;
      }
      y->right=p;
      p->parent=y;
   }
}

node* R_B_tree::successor(node *p)
{
   node *y=NULL;
   if(p->left!=NULL)
   {
      y=p->left;
      while(y->right!=NULL)
	 y=y->right;
   }
   else
   {
      y=p->right;
      while(y->left!=NULL)
	 y=y->left;
   }
   return y;
}

void R_B_tree::disp()
{
   print(root);
}
void R_B_tree::print(node *p)
{
   if(root==NULL)
   {
      cout << endl << "No nodes in this tree.";
      return;
   }
   if(p!=NULL)
   {
      cout << endl << " NODE: ";
      cout << endl << "Key: " << p->key;
      cout<<"\n Colour: ";
      if(p->colour=='b')
	 cout<<"Black";
      else
	 cout<<"Red";
      if(p->parent!=NULL)
	 cout<<"\n Parent: "<<p->parent->key;
      else
	 cout<<"\n There is no parent of the node.  ";
      if(p->right!=NULL)
	 cout<<"\n Right Child: "<<p->right->key;
      else
	 cout<<"\n There is no right child of the node.  ";
      if(p->left!=NULL)
	 cout<<"\n Left Child: "<<p->left->key;
      else
	 cout<<"\n There is no left child of the node.  ";
      cout<<endl;
      if(p->left)
      {
	 cout<<"\n\nLeft:\n";
	 print(p->left);
      }
      /*else
	cout<<"\nNo Left Child.\n";*/
      if(p->right)
      {
	 cout<<"\n\nRight:\n";
	 print(p->right);
      }
      /*else
	cout<<"\nNo Right Child.\n"*/
   }
}

int main()
{
   char func;
   R_B_tree RB;
   
   cout << "What function would you like to preform? (I/i for insert, D/d for delete, P/p for print): ";
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
	 RB.disp();
      default : cout << "That is not a valid choice...";
   }
}
