/*********************************
/ BY: Navraj Saini and Bhupender
/********************************/
#include<iostream>

using namespace std;

struct node
{
	int key;
	node *parent;
	char color;
	node *right;
	node *left;
};
class RBtree
{
	node *root;
	node *q;
	public :
	RBtree()
	{
		q=NULL;
		root=NULL;
	}
	void leftrotate(node *);
  void rightrotate(node *);
  void insert();
  void insertfix(node *);
  void delete();
  //node* successor(node *);
  void deletefix(node *);
  void disp();
  void display( node *);
  void search();
};

void leftrotate(node *z)
{
  node *y = z -> right;
	z -> right = y -> left;
	
  if(y -> left != NULL)
	{
		y -> left -> parent = z;
  }
	
  else
		z -> right = NULL;
	
	if(z -> parent != NULL)
		y -> parent = z -> parent;
	
	if(z -> parent == NULL)
		root = y;
	
	else
	{
		if(z == z -> parent -> left)
			z -> parent -> left = y;
    else
      z -> parent -> right = y;
	}
	y -> left = z;
  z -> parent = y;
}
void RBtree::rightrotate(node *p)
{
	node *y = p -> left;
  if(y -> right != NULL)
  {
  	p -> left = y -> right;
    y -> right -> parent = p;
	}
	else
		p -> left = NULL;
	if(p -> parent != NULL)
		y -> parent = p -> parent;
	if(p -> parent == NULL)
		root = y;
	else
	{
		if(p == p -> parent -> left)
			p -> parent -> left = y;
		else
			p -> parent -> right = y;
	}
	y -> right = p;
	p -> parent = y;
}
