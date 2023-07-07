//Name: Mert Can Bilgin
//Student ID: 2453025

#include "avltree.h"
#include "avltree.c"

AVLTree readData(char*);
AVLTree insertSong(char*, char*, char*, char*, int, char*, AVLTree);
void displaySong(AVLTree);
void popularArtist(AVLTree);
void oldestSong(AVLTree);

int main(int argc, char *argv[])
{	
	//if the file name is not correct, program will give error
	if(strcmp(argv[1], "songs.txt") != 0){
		printf("The file cannot be found!\n");
		return -1;
	}
	AVLTree t;
	t = readData(argv[1]);
	
	printf("Welcome to Song Indexing\n");
	int option, exit = 0;
	do{
		fflush(stdin);
		printf("-----------------------------------------------------------------------------\n");
		printf("1. Display the full index of songs\n");
		printf("2. Display the songs of popular artist\n");
		printf("3. Display the oldest song\n");
		printf("4. Exit\n");
		printf("\nOption: ");
		scanf("%d", &option);
		printf("\n");

		switch(option)
		{
			case 1:
			    displaySong(t);
			    break;
			case 2:
			    popularArtist(t);
			    break;
			case 3:
			    oldestSong(t);
			    break;
			case 4:
			    exit = 1;
			    break;
			default:
			    printf("Please choose the given options!\n");
			    break;
		}


	}while(exit == 0);

	return 0;
}

void oldestSong(AVLTree t)
{
	int oldest = t->song->year, temp;
	//p is my traveller, and pre is predecessor
	AVLTree p, pre, store;
	p = t;

	/*the main idea in this function is that travelling the tree without
	recursion. In addition, I choose inorder travelling
	*/
	while(p != NULL){
		if(p->left == NULL){
			temp = p->song->year;
			if(temp < oldest){
				oldest = temp;
				store = p;
			}
			p = p->right;
		}
		else{
			//find inorder predecessor of p
			pre = p->left;
			while(pre->right != NULL && pre->right != p)
				pre = pre->right;

			//make p as the right child of pre
			if(pre->right == NULL){
				pre->right = p;
				p = p->left;
			}
			//revert changes, fix the right child of pre
			else{
				pre->right = NULL;
				temp = p->song->year;
				if(temp < oldest){
					oldest = temp;
					store = p;
				}
				p = p->right;
			}
		}
	}

	printf("%s;%s;%s;%s;%d;%s\n", store->song->name, store->song->genre, store->song->album, store->song->artistName, store->song->year, store->song->date);

	/*Since the number of times the node will be traversed is constant, the time complexity is O(n).
		This function can be improved by using Release Year base AVLTree. Then, it 
		will be much easier to find the oldest song
	*/
}

void popularArtist(AVLTree t)
{
	int maxNumberofSongs = 0, temp;
	//p is my traveller, and pre is predecessor
	AVLTree p, pre, store;
	p = t;

	/*the main idea in this function is that travelling the tree without
	recursion. In addition, I choose inorder travelling
	*/
	while(p != NULL){
		if(p->left == NULL){
			temp = countSongs(p->song);
			if(temp > maxNumberofSongs){
				maxNumberofSongs = temp;
				store = p;
			}
			p = p->right;
		}
		else{
			//find inorder predecessor of p
			pre = p->left;
			while(pre->right != NULL && pre->right != p)
				pre = pre->right;

			//make p as the right child of pre
			if(pre->right == NULL){
				pre->right = p;
				p = p->left;
			}
			//revert changes, fix the right child of pre
			else{
				pre->right = NULL;
				temp = countSongs(p->song);
				if(temp > maxNumberofSongs){
					maxNumberofSongs = temp;
					store = p;
				}
				p = p->right;
			}
		}
	}

	Song s;
	s = store->song;
	//print the data
	while(s != NULL){
		printf("%s;%s;%s;%s;%d;%s\n", s->name, s->genre, s->album, s->artistName, s->year, s->date);
		s = s->next;
	}

	/*Since the number of times the node will be traversed is constant, the time complexity is O(n).
		This function can be improved by keep tracking of the songs for every
		artist. It will be so much easier because without doing that the process takes more time since it travels all the tree.
	*/

}

void displaySong(AVLTree t)
{
	if(t != NULL){
		displaySong(t->right);
		printf("%s;%s;%s;%s;%d;%s\n", t->song->name, t->song->genre, t->song->album, t->song->artistName, t->song->year, t->song->date);
		if(t->song->next != NULL){
			printf("%s;%s;%s;%s;%d;%s\n", t->song->next->name, t->song->next->genre, t->song->next->album, t->song->next->artistName, t->song->next->year, t->song->next->date);
		}
		displaySong(t->left);
	}
}

AVLTree readData(char *filename)
{
	AVLTree t;
	t = NULL;
	char name[20], genre[20], album[30], artistName[30], date[40];
	int year;

	//open the file
	FILE *inFile;
	inFile = fopen(filename, "r");
	if(inFile == NULL){
		printf("File cannot be opened!\n");
		exit(1);
	}
	//read the data, and insert it to AVLTree
	while((fscanf(inFile, "%[^;];%[^;];%[^;];%[^;];%d;%[^\n]\n", name, genre, album, artistName, &year, date)) != EOF){
		t = insertSong(name, genre, album, artistName, year, date, t);
	}
	//close the file
	fclose(inFile);

	return t;
}

AVLTree insertSong(char *name, char *genre, char *album, char *artistName, int year, char *date, AVLTree t)
{
	if(t == NULL){
		//Create and return a one-node tree
		t = malloc(sizeof(struct AVLTree));
		t->song = (struct Songs*)malloc(sizeof(struct Songs));
		if(t == NULL || t->song == NULL){
			printf("Out of memory!\n");
			exit(1);
		}
		else{
			//copy the data to node
			strcpy(t->song->name, name);
			strcpy(t->song->genre, genre);
			strcpy(t->song->album, album);
			strcpy(t->song->artistName, artistName);
			t->song->year = year;
			strcpy(t->song->date, date);
			t->height = 0;
			t->left = NULL;
			t->right = NULL;
			t->song->next = NULL;
		}
	}
	else if(strcmp(t->song->artistName, artistName) < 0){
		t->left = insertSong(name, genre, album, artistName, year, date, t->left);

		if(TreeHeight(t->left) - TreeHeight(t->right) == 2){
			if(strcmp(t->left->song->artistName, artistName) < 0)
				t = SingleRotateWithLeft(t);
			else
				t = DoubleRotateWithLeft(t);
		}
	}
	else if(strcmp(t->song->artistName, artistName) > 0){
		t->right = insertSong(name, genre, album, artistName, year, date, t->right);

		if(TreeHeight(t->right) - TreeHeight(t->left) == 2){
			if(strcmp(t->left->song->artistName, artistName) > 0)
				t = SingleRotateWithRight(t);
			else
				t = DoubleRotateWithRight(t);
		}
	}
	//this part will add a new song to the same artist
	else{
		//if its second song
		if(t->song->next == NULL){
			t->song->next = (struct Songs*)malloc(sizeof(struct Songs));
			if(t->song->next == NULL){
				printf("Out of memory!\n");
				exit(-1);
			}
			
			strcpy(t->song->next->name, name);
			strcpy(t->song->next->genre, genre);
			strcpy(t->song->next->album, album);
			strcpy(t->song->next->artistName, artistName);
			t->song->next->year = year;
			strcpy(t->song->next->date, date);
			t->song->next->next = NULL;
		}
		//if it has more than two songs
		else{
			while(t->song->next != NULL)
				t->song = t->song->next;

			t->song->next = (struct Songs*)malloc(sizeof(struct Songs));
			if(t->song->next == NULL){
				printf("Out of memory!\n");
				exit(-1);
			}

			strcpy(t->song->name, name);
			strcpy(t->song->genre, genre);
			strcpy(t->song->album, album);
			strcpy(t->song->artistName, artistName);
			t->song->year = year;
			strcpy(t->song->date, date);
			t->song->next = NULL;
		}
	}

	//update height
	t->height = TreeHeight(t);

	return t;
}