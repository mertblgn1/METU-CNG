//Name: Mert Can Bilgin
//Student ID: 2453025


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct email
{
	int id;
	char sender[50];
	char recipient[50];
	int day;
	int words;
};

struct email* readEmails(char*, int);
int countWords(char*);
void menu();
void printEmails(struct email*, int);
void swap(struct email*, struct email*);
void heapify(struct email*, int, int, int);
void BuildHeap(struct email*, int, int);
struct email* heapSort(struct email*, int, int);
int binSearch(struct email*, int, int, int);

int main()
{
	//create an string array for the path
	char pathName[50];
	int numberOfDataFiles;

	//get the information from the user
	printf("Enter the path of the directory which contains data files: ");
	scanf("%s", pathName);
	printf("Enter the number of data files: ");
	scanf("%d", &numberOfDataFiles);

	struct email *emailList;
	emailList = (struct email*)malloc(sizeof(struct email) * numberOfDataFiles);
	if(emailList == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	//read emails from the directory
	emailList = readEmails(pathName, numberOfDataFiles);
	printf("%d emails have been read successfully!\n", numberOfDataFiles);

	int exit = 0, command, searchKey;
	
	
	do
	{
		//clear the buffer
		fflush(stdin);
		menu();
		printf("Command: ");
		scanf("%d", &command);

		switch(command)
		{
			case 1:
				emailList = heapSort(emailList, numberOfDataFiles, 1);
				printEmails(emailList, numberOfDataFiles);
				break;
			
			case 2:
				emailList = heapSort(emailList, numberOfDataFiles, 2);
				printEmails(emailList, numberOfDataFiles);
				break;
			case 3:
				emailList = heapSort(emailList, numberOfDataFiles, 3);
				printEmails(emailList, numberOfDataFiles);
				break;
			case 4:
				fflush(stdin);
				printf("Enter the search key: ");
				scanf("%d", &searchKey);
				emailList = heapSort(emailList, numberOfDataFiles, 1);
				int found = binSearch(emailList, 0, numberOfDataFiles - 1, searchKey);
				if(found == -1)
				{
					printf("\nThe data doesn't exist!\n");
				}
				else
				{
					printf("\nId: %d\n", emailList[found].id);
					printf("Sender: %s\n", emailList[found].sender);
					printf("Recipient: %s\n", emailList[found].recipient);
					printf("Date: %d\n", emailList[found].day);
					printf("Words: %d\n", emailList[found].words);
				}
				break;
			case 5:
				exit = 1;
				printf("Goodbye!\n");
				break;
			default:
				printf("Command is not found!\n");
				break;
		}
	}while(exit == 0);
	
	
	
	return 0;
}

/*
TIME COMPLEXITY ANALYSIS OF readEmails
-------------------------------------
There is only one iteration, it performs until i equals to the number of data files.
Thus, the time complexity og this function is O(n).


*/

struct email* readEmails(char *path, int number)
{
	//create the array of email structure
	struct email *emails;
	emails = (struct email*)malloc(sizeof(struct email) * number);
	if(emails == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}
	char pathname[50];
	strcpy(pathname, path);
	char content[1000];//email content
	int i = 1; // because files start from 1
	char strInt[5]; //it is the string version of variable i
	//open the file stream
	FILE *inFile;

	while(i <= number)
	{
		sprintf(strInt, "%d", i);
		//I am using macOS, that's why I need to use slash
		//for Windows backslash need to be used for path
		path = strcat(path, "/");
		path = strcat(path, strInt);
		path = strcat(path, ".txt");
		inFile = fopen(path, "r");
		
		if(inFile == NULL)
		{
			printf("The file doesn't exist!\n");
			exit(1);
		}

		fscanf(inFile, "%d\nFrom: %s\nTo: %s\nDate: %d\n%[^\r]\n", &emails[i-1].id, emails[i-1].sender,  emails[i-1].recipient, &emails[i-1].day, content);
		emails[i-1].words = countWords(content);
		i++;
		path[0] = '\0'; //clear the string
		path = strcat(path, pathname);
		
	}

	return emails;
}

int countWords(char *content)
{
	//this function checks the space character
	//if there is a space it increases the #words by 1
	int i = 0, words = 1;
	while(content[i] != '\0')
	{
		if(content[i] == ' ')
			words++;
		i++;
	}

	return words;
}

/*
TIME COMPLEXITY ANALYSIS OF menu
-------------------------------------
There is no iteration, and it only performs 1 time.
Therefore, the time complexity is O(1)

*/

void menu()
{
	printf("\nPlease choose one of the following options:\n");
	printf("\t(1) Display emails sorted by id\n");
	printf("\t(2) Display emails sorted by number of words\n");
	printf("\t(3) Display emails sorted by date\n");
	printf("\t(4) Search email by ID\n");
	printf("\t(5) Exit\n");
}

/*
TIME COMPLEXITY ANALYSIS OF printEmails
-------------------------------------
The iteration will perform 'size' times, so
the time complexity is O(n)

*/

void printEmails(struct email *list, int size)
{
	int i = 0;
	while(i < size)
	{
		printf("\nId: %d\n", list[i].id);
		printf("Sender: %s\n", list[i].sender);
		printf("Recipient: %s\n", list[i].recipient);
		printf("Date: %d\n", list[i].day);
		printf("Words: %d\n", list[i].words);
		i++;
	}
}

void swap(struct email* a, struct email* b)
{
 
    struct email temp = *a;
 
    *a = *b;
 
    *b = temp;
}

void heapify(struct email* arr, int N, int i, int CriteriaID)
{
	int largest, left, right;

	largest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;

	//if criteria id is 1, it sorts by id. if it is 2
	//it sorts by words. if it is 3, it sorts by date
	if(CriteriaID == 1)
	{
		if(left < N && arr[left].id > arr[largest].id)
			largest = left;
		if(right < N && arr[right].id > arr[largest].id)
			largest = right;

		if(largest != i){
			swap(&arr[i], &arr[largest]);
			heapify(arr, N, largest, 1);
		}
	}
	else if(CriteriaID == 2)
	{
		if(left < N && arr[left].words > arr[largest].words)
			largest = left;
		if(right < N && arr[right].words > arr[largest].words)
			largest = right;

		if(largest != i){
			swap(&arr[i], &arr[largest]);
			heapify(arr, N, largest, 2);
		}
	}
	else if(CriteriaID == 3)
	{
		if(left < N && arr[left].day > arr[largest].day)
			largest = left;
		if(right < N && arr[right].day > arr[largest].day)
			largest = right;

		if(largest != i){
			swap(&arr[i], &arr[largest]);
			heapify(arr, N, largest, 3);
		}
	}


}

void BuildHeap(struct email* arr, int size, int criteria)
{
	int i;
	for(i = size/2 - 1; i >= 0; i--)
		heapify(arr, size, i, criteria);
}
/*
TIME COMPLEXITY ANALYSIS OF HEAP SORT
-------------------------------------
BuildHeap funtion takes O(n) time, and each of the
n - 1 calls in the for loop takes O(logn) (master theorem
that we see in the class) time. Therefore, it is O(n) + n-1*O(logn)
, and it is equal to O(nlogn)

*/
struct email* heapSort(struct email* arr, int size, int criteriaID)
{
	BuildHeap(arr, size, criteriaID);
	int i;
	for(i = size - 1; i >=0; i--)
	{
		swap(&arr[0], &arr[i]);
		size--;
		heapify(arr, size, 0, criteriaID);
	}

	return arr;
}

/*
TIME COMPLEXITY ANALYSIS OF BINARY SEARCH
-----------------------------------------
Best Case: O(1) because if the middle element of the array is the searchKey, it directly returns
Avg and Worst Case: until the middle element is not equal to searchKey the lenght of the array will
be divided by 2. Let's say it is divided by k times until it founds, so the length of the array will be equal to lenght/(2^k)
after some math operations k will be logn. Therefore the time complexity is O(logn)

*/

int binSearch(struct email* arr, int left, int right, int searchKey)
{
	int middle;
	//I used recursion method

	if(right >= left)
	{
		middle = left + (right-left) / 2;

		if(arr[middle].id == searchKey)
			return middle;
		if(arr[middle].id > searchKey)
			return binSearch(arr, left, middle - 1, searchKey);
		return binSearch(arr, middle + 1, right, searchKey);
	}

	//if size greater than key return bla bla


	return -1;
}



















