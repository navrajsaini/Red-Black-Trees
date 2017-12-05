#include <iostream>

using namespace std;

struct node
{
	int key;
	node *parent, *left, *right;
	bool col; // 0 = red, 1 = black
};
