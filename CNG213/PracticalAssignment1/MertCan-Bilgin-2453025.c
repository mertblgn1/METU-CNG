//Name: Mert Can Bilgin
//ID: 2453025


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Node includes first name, surname, title, mail, phone, and roomnumber
struct Node
{
	char firstName[20];
	char lastName[20];
	char title[20];
	char email[50];
	int phoneNumber;
	char roomNumber[10];
	struct Node *next;
};

//I will need the start and the end of the linked list
struct ListRecord
{
	struct Node *head;
	struct Node *tail;
	int size;
};

struct ListRecord* initialiseInstructorBook(char*);
void swap(struct Node *, struct Node *);
void InsertInstructor(struct ListRecord*);
void PrintInstructors(struct ListRecord*);
void SearchInstructor(struct ListRecord*, char*);
struct ListRecord* CurrentSemesterInstructors(struct ListRecord*, struct ListRecord*);
void printCurrentSemesterInstructors(struct ListRecord*);

int main(int argc, char *argv[])
{
	
	//open the file to read, if cannot be opened give error message
	FILE *inFile;
	inFile = fopen(argv[1], "r");

	if(inFile == NULL){
		printf("File cannot be found!\n");
		exit(1);
	}
	
	//Allocate the linked the list and call the fuction to load the txt file to linked list
	struct ListRecord *instructors;
	instructors = (struct ListRecord*)malloc(sizeof(struct ListRecord));
	if(instructors == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	else{
		//allocate dummy node
		instructors->head = (struct Node*)malloc(sizeof(struct Node));
		if(instructors->head == NULL){
			printf("Out of memory!\n");
			exit(1);
		}
		else{
			instructors->head->next = NULL;
			instructors->tail = instructors->head;
			instructors->size = 0;
		}
	}
	instructors = initialiseInstructorBook(argv[1]);

	//Define current instructors list, and allocate it
	struct ListRecord *CurrentInstructors;
	CurrentInstructors = (struct ListRecord*)malloc(sizeof(struct ListRecord));
	if(CurrentInstructors == NULL){
		printf("Out of memory!\n");
		return -1;
	}
	CurrentInstructors->head = (struct Node*)malloc(sizeof(struct Node));
	if(CurrentInstructors->head == NULL){
		printf("Out of memory!\n");
		return -1;
	}
	CurrentInstructors->tail = CurrentInstructors->head;
	CurrentInstructors->tail->next = NULL;


	//I need an exit variable to stop the loop, and an option for the user's chooses
	int exit = 0, option;
	
	struct Node *p;
	//define a name to ask for searching
	char name[20];

	do{
		fflush(stdin);
		printf("---- MENU ----\n");
		printf("1. Add Instructor\n");
		printf("2. Print Instructor\n");
		printf("3. Search Instructor\n");
		printf("4. Create Current Semester Instructors List\n");
		printf("5. Print Current Semester Instructors List\n");
		printf("6. Exit\n\n");
		printf("Enter your option: ");
		scanf("%d", &option);
		printf("\n");
		fflush(stdin);

		switch(option){
			case 1:
				InsertInstructor(instructors);
				printf("\nThe instructor has been added!!\n\n");
				break;
			case 2:
				PrintInstructors(instructors);
				break;
			case 3:
				printf("Enter the name of the instructor you want to search: ");
				scanf("%s", name);
				printf("\n");
				SearchInstructor(instructors, name);
				break;
			case 4:
				CurrentInstructors = CurrentSemesterInstructors(instructors, CurrentInstructors);
				break;
			case 5:
				printCurrentSemesterInstructors(CurrentInstructors);
				break;
			case 6:
				exit = 1;
				break;
			default:
				printf("Please choose the given options!\n");
				break;

		}


	}while(exit == 0);


	return 0;
}

void SearchInstructor(struct ListRecord *instructors, char *name)
{
	//I used the binary search algorithm which has O(logn) complexity

	//Define an index to keep the track of the list
	int index;
	int low = 0, high = instructors->size, i = 0, found = 0;
	struct Node *searched;
	//I am looking for "searched"
	searched = instructors->head->next;
	
	//I need to put the index to mid of the list, so I assigned low as 0 and high as size of the list
	//so index should be (low + high)/2
	while(low <= high && found == 0){
		index = (low + high)/2;
		//I need to keep track of searched by using 'i' variable
		while(i < index){
			searched = searched->next;
			i++;
		}
		//When the name is equal, display it
		if(strcmp(name, searched->firstName) == 0){
			printf("Results\n");
			printf("--------------------------------------------\n");
			printf("Instructor name: %s\n", searched->firstName);
			printf("Instructor surname: %s\n", searched->lastName);
			printf("Instructor title: %s\n", searched->title);
			printf("Instructor email: %s\n", searched->email);
			printf("Instructor phone number: %d\n", searched->phoneNumber);
			printf("Instructor room number: %s\n\n", searched->roomNumber);
			found = 1;
		}
		//if the searched name is behind the index, the index should be turn back
		else if(strcmp(name, searched->firstName) < 0){
			high = index - 1;
			searched = instructors->head->next;
			i = 0;
		}
		//if the searched name is ahead of the index, the index should be moved forward
		else{
			low = index + 1;
		}
	}
	if(found == 0){
		printf("Instructor not found!!!\n");
	}
}

struct ListRecord* CurrentSemesterInstructors(struct ListRecord *instructors, struct ListRecord *currentInstructors)
{
	char name[20];
	printf("Enter instructor name you want to add to your current semester list: ");
	scanf("%s", name);


	struct Node *searcher, *temp, *p, *removenode, *temp2;
	int found = 0, pos = 1, i, isEqual;

	searcher = (struct Node*)malloc(sizeof(struct Node));
	temp = (struct Node*)malloc(sizeof(struct Node));
	p = instructors->head->next;
	
	//temp2 will track the node before
	temp2 = (struct Node*)malloc(sizeof(struct Node));
	removenode = (struct Node*)malloc(sizeof(struct Node));

	temp2 = instructors->head;



	while(p != NULL){
		//When the names are the same, copy them to searcher
		if(strcmp(name, p->firstName) == 0){
			found = 1;
			strcpy(searcher->firstName, p->firstName);
			strcpy(searcher->lastName, p->lastName);
			strcpy(searcher->title, p->title);
			strcpy(searcher->email, p->email);
			searcher->phoneNumber = p->phoneNumber;
			strcpy(searcher->roomNumber, p->roomNumber);
			searcher->next = NULL;

			//delete, and don't forger to decrease the size of the list
			
			removenode = temp2->next;
			temp2->next = temp2->next->next;
			free(removenode);
			instructors->size--;
			//if the list size is zero, set the tail to head
			if(instructors->size == 0)
				instructors->tail = instructors->head;

		}
		p = p-> next;
		temp2 = temp2->next;
	}

	//insertion is here
	if(found == 1){
		//if the list is empty, set it as the first element
		if(currentInstructors->size == 0){
			currentInstructors->tail->next = searcher;
			currentInstructors->tail = searcher;
		}
		//if the list is not empty, find the appropriate solution according to alphabet order
		else{
			p = currentInstructors->head->next;
			//find position, then insert it 
			while(p != NULL){
				if(!(strcmp(searcher->firstName, p->firstName) < 0)){
					pos++;
				}
				p = p->next;
			}
			//keep the track of temp until the program reaches the position I want
			temp = currentInstructors->head;
			for(i = 1; i < pos; i++){
				temp = temp->next;
			}
			searcher->next = temp->next;
			temp->next = searcher;
		}
		printf("%s has been moved to current semester list\n\n", searcher->firstName);
		//don't forget to increate the size of the list
		currentInstructors->size++;

	}
	else{
		printf("Instructor not found!!!\n");
	}


	return(currentInstructors);
}


void InsertInstructor(struct ListRecord *instructors)
{
	struct Node *insert, *temp, *p;
	int i;

	insert = (struct Node*)malloc(sizeof(struct Node));
	if(insert == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	insert->next = NULL;

	//take the information from the user

	fflush(stdin);
	printf("Enter instructor name: ");
	scanf("%s", insert->firstName);
	fflush(stdin);
	printf("Enter instructor surname: ");
	scanf("%s", insert->lastName);
	fflush(stdin);
	printf("Enter instructor title: ");
	scanf("%[^\n]", insert->title);
	fflush(stdin);
	printf("Enter instructor email: ");
	scanf("%s", insert->email);
	fflush(stdin);
	printf("Enter phone number: ");
	scanf("%d", &insert->phoneNumber);
	fflush(stdin);
	printf("Enter instructor room number: ");
	scanf("%s", insert->roomNumber);

	//Firstly, we need to find the position we will insert according to alphabetical order
	//position starts by 1 because we have dummy node
	int pos = 1, found = 0;
	p = instructors->head->next;
	while(p != NULL){
		if(strcmp(insert->firstName, p->firstName) < 0)
			found = 1;
		else
			pos++;

		p = p->next;
	}

	//we know the position, so we can insert it

	if(found == 0){
		pos = instructors->size + 1;
	}
	if(pos == instructors->size + 1){
		instructors->tail->next = insert;
		instructors->tail = insert;
	}
	else{
		temp = instructors->head;
		for(i = 1; i < pos; i++){
			temp = temp->next;
		}
		insert->next = temp->next;
		temp->next = insert;
	}
	instructors->size++;

}


void swap(struct Node *a, struct Node *b)
{
	struct Node *temp;
	temp = (struct Node *)malloc(sizeof(struct Node));
	if(temp == NULL){
		printf("Out of memory!\n");
		exit(1);
	}

	//store the a to temp
	temp->phoneNumber = a->phoneNumber;
	strcpy(temp->firstName, a->firstName);
	strcpy(temp->lastName, a->lastName);
	strcpy(temp->title, a->title);
	strcpy(temp->email, a->email);
	strcpy(temp->roomNumber, a->roomNumber);

	//change the values of a with b
	strcpy(a->firstName, b->firstName);
	strcpy(a->lastName, b->lastName);
	strcpy(a->title, b->title);
	strcpy(a->email, b->email);
	a->phoneNumber = b->phoneNumber;
	strcpy(a->roomNumber, b->roomNumber);

	//change the values of a with b
	strcpy(b->firstName, temp->firstName);
	strcpy(b->lastName, temp->lastName);
	strcpy(b->title, temp->title);
	strcpy(b->email, temp->email);
	b->phoneNumber = temp->phoneNumber;
	strcpy(b->roomNumber, temp->roomNumber);
}

void printCurrentSemesterInstructors(struct ListRecord *currentInstructors)
{
	struct Node *p;
	p = currentInstructors->head->next;

	printf("Results\n");
	printf("------------------------------\n");
	while(p != NULL){
		printf("Instructor name: %s\n", p->firstName);
		printf("Instructor surname: %s\n", p->lastName);
		printf("Instructor title: %s\n", p->title);
		printf("Instructor email: %s\n", p->email);
		printf("Instructor phone number: %d\n", p->phoneNumber);
		printf("Instructor room number: %s\n", p->roomNumber);
		printf("\n");
		p = p->next;
	}
}

void PrintInstructors(struct ListRecord *instructors)
{
	struct Node *p;
	p = instructors->head->next->next;

	printf("\nInstructor in your database:\n");
	printf("--------------------------\n");

	while(p != NULL){
		printf("Instructor name: %s\n", p->firstName);
		printf("Instructor surname: %s\n", p->lastName);
		printf("Instructor title: %s\n", p->title);
		printf("Instructor email: %s\n", p->email);
		printf("Instructor phone number: %d\n", p->phoneNumber);
		printf("Instructor room number: %s\n", p->roomNumber);
		printf("\n");
		p = p->next;
	}
}

struct ListRecord* initialiseInstructorBook(char *filename)
{
	//open the file to read, and if cannot be opened give error message

	FILE *inFile;
	inFile = fopen(filename, "r");

	if(inFile == NULL){
		printf("File cannot be found\n");
		exit(1);
	}
	//allocate the linked list, and initialize it
	struct ListRecord *instructors;
	instructors = (struct ListRecord*)malloc(sizeof(struct ListRecord));
	if(instructors == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	else{
		//allocate dummy node
		instructors->head = (struct Node*)malloc(sizeof(struct Node));
		if(instructors->head == NULL){
			printf("Out of memory!\n");
			exit(1);
		}
		else{
			instructors->head->next = NULL;
			instructors->tail = instructors->head;
			instructors->size = 0;
		}
	}

	//now, read the file and load the information to linked list
	//to load the first line I need to allocate *next of dummy node

	instructors->head->next = (struct Node *)malloc(sizeof(struct Node));
	if(instructors->head->next == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	instructors->head->next->next = NULL;
	instructors->tail = instructors->head->next;


	//at the end of every line increase the size of the array, and allocate a new node
	while((fscanf(inFile, "%[^;];%[^;];%[^;];%[^;];%d;%s\n", instructors->tail->firstName, instructors->tail->lastName, instructors->tail->title, instructors->tail->email, &instructors->tail->phoneNumber, instructors->tail->roomNumber)) != EOF){
		instructors->tail->next = (struct Node *)malloc(sizeof(struct Node));
		if(instructors->tail->next == NULL){
			printf("Out of memory!\n");
			exit(1);
		}
		instructors->tail = instructors->tail->next;
		instructors->size++;
	}
	instructors->tail->next = NULL;

	//do not forget to close the file
	fclose(inFile);

	//I need to sort the list by the first names in alphabetical order

	//I will use the bubble sort algorithm to sort these
	struct Node *temp;
	struct Node *temp2 = NULL;

	int swapped;

	do{
		swapped = 0;
		temp = instructors->head;

		while(temp->next != temp2){
			if(strcmp(temp->firstName, temp->next->firstName) > 0){
				swap(temp, temp->next);
				swapped = 1;
			}
			temp = temp->next;
		}
		temp2 = temp;
	}while(swapped);


	printf("The %s file has been loaded successfully\n", filename);
	return (instructors);
}