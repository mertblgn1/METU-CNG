#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Songs{
	char name[20];
	char genre[20];
	char album[30];
	char artistName[30];
	int year;
	char date[40];
	struct Songs* next;
};

struct AVLTree{
	struct Songs *song;
	struct AVLTree *left;
	struct AVLTree *right;
	int height;
};

typedef struct AVLTree *AVLTree;
typedef struct Songs *Song;

int TreeHeight(AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
int countSongs(Song);