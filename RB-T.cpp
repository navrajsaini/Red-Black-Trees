#include <iostream>

using namespace std;

struct node
{
	int key;
	node *parent, *left, *right;
	char colour; // 0 = red, 1 = black
};

class R_B_tree
{
	private:
		node *root;
		node *q;
	
	public:
		//functions
		void LRotate (node*);
		void RRotate (node*);
		void Delete (node*);
		void Insert (node*);
		void Insertfix (node*);
		void Deletefix (node*);
		void Transplant (node*, node*);
		void t_min (node*);
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
	
	elseif (x == x -> parent -> left)
		x -> parant -> left = y;
	
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
	
	elseif (x == x -> parent -> right)
		x -> parant -> right = y;
	
	else
		x -> parent -> left = y;
	y -> right = x;
	x -> parent = y;
}

void R_B_tree::Transplant (node* u, node* v)
{
	if (u -> parent == NULL)
		root = v;
	elseif (u == u -> parent -> left)
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
		Transplant (z, z -> right)
	}
	elseif (z -> right == NULL)
	{
		x = z -> left;
		Transplant (z, z -> left);
	}
	else
	{
		y = t_min (z -> right);
		y_og_colour = y -> colour;
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
	
	if (y_og_colour == 'b')
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
			
			if (s -> left -> colour 'b' && s -> rihgt -> colour == 'b')
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
			
			if(s->color=='r')
			{
				s->color='b';
				x->parent->color='r';
				RRotate(x->parent);
				s=x->parent->left;
			}
			if(s->left->color=='b' && s->right->color=='b')
			{
				s->color='r';
				x=x->parent;
			}
			else
			{
				if(s->left->color=='b')
				{
					s->right->color='b';
					s->color='r';
					LRotate(s);
					s=x->parent->left;
				}
				s->color=x->parent->color;
				x->parent->color='b';
				s->left->color='b';
				RRotate(x->parent);
				x=root;
			}
		}
		x -> colour = 'b';
		root -> colour = 'b';
	}
}

void R_B_tree::t_min (node* x)
{
	while (x -> left != NULL)
		x = x -> left;
	return x;
}

void R_B_tree::insert (node* z)
{
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
	
	elseif (z -> key < y -> key)
	{
		y -> left = z;
	}// end of elseif
	else
		y -> right = z;
	z -> right = NULL;
	z -> left = NULL;
	z -> colour = 'r';
	Insertfix(z);
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
