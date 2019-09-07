#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct nodeTree
{
	int key;
	struct nodeTree *left;
	struct nodeTree *right;
	struct nodeTree *p;
};

void InorderTreeWalk(struct nodeTree *x)
{
	if (x != NULL)
	{
		InorderTreeWalk(x->left);
		printf(" %d", x->key);
		InorderTreeWalk(x->right);
	}
}

struct nodeTree *TreeSearch(struct nodeTree *x, int k)
{
	if((x == NULL) || (k == x->key))
        return x;
	if(k < x->key)
        return TreeSearch(x->left, k);
	else
        return TreeSearch(x->right, k);
}

struct nodeTree *TreeMinimum(struct nodeTree *x)
{
	while(x->left != NULL)
        x = x->left;
	return x;
}

struct nodeTree *TreeMaximum(struct nodeTree *x)
{
	while(x -> right != NULL)
        x = x->right;
	return x;
}

struct nodeTree *TreeSuccessor(struct nodeTree *x)
{
	struct nodeTree *y;

	if(x->right != NULL)
        return TreeMinimum(x->right);

	y=x->p;

	while((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->p;
	}
	return y;
}

struct nodeTree *TreePredeccessor(struct nodeTree *x)
{
	struct nodeTree *y;

	if(x->left != NULL)
        return TreeMaximum(x->left);

	y=x->p;

	while((y != NULL) && (x == y->left))
	{
		x = y;
		y = y->p;
	}
	return y;
}

struct nodeTree *TreeInsert(struct nodeTree *T,
                            struct nodeTree *z)
{
	struct nodeTree *x, *y;
	y = NULL;
	x = T;

	while(x != NULL)
	{
		y = x;
		if(z->key < x->key)
            x = x->left;
		else
            x = x->right;
	}

	z->p = y;

	if(y == NULL)
        T = z;
	else
	{
		if(z->key < y->key)
            y->left = z;
		else
            y->right = z;
	}

	return T;
}

struct nodeTree *TreeDelete(struct nodeTree *T,
                            struct nodeTree *Z)
{
	struct nodeTree *Y, *X;

	if((Z->left == NULL) || (Z->right == NULL))
        Y = Z;
	else
		Y = TreeSuccessor(Z);

	if(Y->left != NULL)
        X = Y->left;
	else
		X = Y->right;

	if(X != NULL)
        X->p = Y->p;

	if(Y->p == NULL)
        T = X;
	else
	{
		 if(Y == Y->p->left)
            Y->p->left = X;
		 else
			 Y->p->right = X;
	}

    if(Y != Z)
	{
		Z->key = Y->key;
		/* Copy all infortation fields */
	}

	free(Y);

	return T;
}

int main()
{
	struct nodeTree *T, *z, *temp;
	int operation, element;
    T = NULL;

	while(scanf("%d %d", &operation, &element) != EOF)
	{
	    if(operation == 1)
        {
            z = (struct nodeTree *)malloc(sizeof(struct nodeTree));
            z->key = element;
            z->left = NULL;
            z->right = NULL;
            T = TreeInsert(T, z);
            InorderTreeWalk(T);
            printf("\n");
        }
        else
        {
            if(operation == 2)
            {
                z = TreeSearch(T, element);
                if(z != NULL)
                {
                    T = TreeDelete(T, z);
                    InorderTreeWalk(T);
                    printf("\n");
                }
                else
                    printf("The element %d is not in the Tree\n", element);
            }
            else
                printf("Bad used. Use: \n 1. Insert\n 2. Delete\n");
        }
    }
    return 0;
}
