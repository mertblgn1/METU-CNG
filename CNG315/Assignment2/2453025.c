// Name: Mert Can Bilgin
// Student ID: 2453025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct email
{
	int id;
	char sender[51];
	char recipient[51];
	int day;
	int words;
};

struct HashTable
{
	struct email email;
	int key;
};

int getKey(struct email);
int hash(int, int);
int hash2(int);
int getNewPrime(int);
int isPrime(int);
int countWords(char*);
struct HashTable*readEmails(char*, int, struct HashTable*, int*, int);
void resetHashTable(struct HashTable*, int);
void printTable(struct HashTable*, int);
struct HashTable* rehash(struct HashTable*, int, int, int);
void searchEmail(struct HashTable*, int, int);

int main()
{
	//create an string array for the path
	char pathName[50];
	int numberOfDataFiles;
	int option;
	int size = 11;
	int command;
	double readEmail = 0;
	double doubleSize;
	doubleSize = size;
	double factor;
	int oldSize;

	do
	{
		printf("How do you want to resolve collisions?\n");
		printf("1) Linear Probing\n2) Double Hashing\n");
		printf("Decision: ");
		scanf("%d", &option);
		fflush(stdin); //clear the buffer
	}while((option < 1) || (option > 2));


	//get the information from the user for the first reading
	// because without reading emails first, the other operations cannot be performed
	
	printf("Enter the path of the directory which contains data files: ");
	scanf("%s", pathName);
	printf("Enter the number of data files: ");
	scanf("%d", &numberOfDataFiles);
	

	struct HashTable *hashTable;
	// first hash table size is 11 as specified in the assignment
	hashTable = (struct HashTable*)malloc(sizeof(struct HashTable) * size);
	if(hashTable == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}
	resetHashTable(hashTable, size);
	hashTable = readEmails(pathName, numberOfDataFiles, hashTable, &size, option);
	readEmail++;
	printf("Email is read successfully!\n");
	printTable(hashTable,size);

	do
	{
		fflush(stdin); //clear the buffer
		printf("\nPlease choose one of the following options:\n");
		printf("\t(1) Read emails\n");
		printf("\t(2) Search an email\n");
		printf("\t(3) Print table\n");
		printf("\t(4) Exit\n");
		printf("Command: ");
		scanf("%d", &command);

		switch(command)
		{
			case 1:
				printf("Enter the path of the directory which contains data files: ");
				scanf("%s", pathName);
				printf("Enter the number of data file: ");
				scanf("%d", &numberOfDataFiles);
				doubleSize = size;
				readEmail++;
				factor = readEmail / doubleSize;
				if(factor > 0.5)
				{
					//REHASH
					oldSize = size;
					size = getNewPrime(2*oldSize);
			
					// get the correct positions by calling rehash
					hashTable = rehash(hashTable, size, oldSize, option);
					hashTable = readEmails(pathName, numberOfDataFiles, hashTable, &size, option);

				}
				else
					// pass the size by reference because we need to know updated data when we want to print
					hashTable = readEmails(pathName, numberOfDataFiles, hashTable, &size, option);
				printf("Email is read successfully!\n");
				printTable(hashTable,size);
				break;
			case 2:
				searchEmail(hashTable, option, size);
				break;
			case 3:
				printTable(hashTable,size);
				break;
			case 4:
				printf("Goodbye!\n");
				break;
			default:
				printf("Please choose one of the given commands!\n");
				break;
		}
	}while(command != 4);


	return 0;
}

void searchEmail(struct HashTable *hashTable, int option, int size)
{
	int searchId, searchKey;
	char searchSender[51];
	int found = 0, i, k = 1;

	// get the inputs
	printf("Enter unique identifier: ");
	scanf("%d", &searchId);
	printf("Enter sender: ");
	scanf("%s", searchSender);

	// calculate the key
	searchKey = searchId + searchSender[0] - 65;
	int searchIndex;
	searchIndex = hash(searchKey, size);

	
	while(found == 0)
	{
		if(hashTable[searchIndex].email.id == searchId)
		{
			found = 1;
			printf("Recipient: %s\n", hashTable[searchIndex].email.recipient);
			printf("Date: %d\n", hashTable[searchIndex].email.day);
			printf("Number of words: %d\n", hashTable[searchIndex].email.words);
		}
		else if(hashTable[searchIndex].key == -1)
		{
			found = 1;
			printf("Student is not found!\n");
		}
		else if(option == 1) //LINEAR PROBING
		{
			searchIndex++;
			searchIndex = searchIndex % size;
		}
		else if(option == 2) // DOUBLE HASHING
		{
			searchIndex = hash(searchKey, size) + (k * hash2(searchKey));
			k++;
		}
	}
	

}

struct HashTable* readEmails(char *path, int i, struct HashTable *hashTable, int *OriginalSize, int option)
{
	char pathName[51];
	strcpy(pathName, path);
	char content[1000]; //email content
	char strInt[5]; //it is the string version of variable i
	int size = *OriginalSize;

	//create a temporary email structure and hashIndex
	struct email temp;
	int hashIndex, oldSize;
	int tempKey;
	int tempKey2;
	int k = 1; // it is used for double hashing

	// open the file stream
	FILE *inFile;

	
		sprintf(strInt, "%d", i);
		// I am using macOS, that's why I need to use slash for path
		// For Windows users, backslash need to be used
		path = strcat(path, "/");
		path = strcat(path, strInt);
		path = strcat(path, ".txt");
		inFile = fopen(path, "r");

		//chech if the file is opened
		if(inFile == NULL)
		{
			printf("The file doesn't exist!\n");
			exit(1);
		}

		fscanf(inFile, "%d\nFrom: %s\nTo: %s\nDate: %d\n%[^\r]\n", &temp.id, temp.sender,  temp.recipient, &temp.day, content);
		temp.words = countWords(content);

		tempKey = getKey(temp);
		tempKey2 = tempKey;
		hashIndex = hash(tempKey, size);

		
		// copy the values
		if(hashTable[hashIndex].key == -1)
		{
			hashTable[hashIndex].key = tempKey;
			hashTable[hashIndex].email.id = temp.id;
			strcpy(hashTable[hashIndex].email.sender, temp.sender);
			strcpy(hashTable[hashIndex].email.recipient, temp.recipient);
			hashTable[hashIndex].email.day = temp.day;
			hashTable[hashIndex].email.words = temp.words;
		}
		//LINEAR PROBING
		else if(option == 1)
		{
			while(hashTable[hashIndex].key != -1)
			{
				tempKey2++;
				hashIndex = hash(tempKey2, size);
			}

			hashTable[hashIndex].key = tempKey;
			hashTable[hashIndex].email.id = temp.id;
			strcpy(hashTable[hashIndex].email.sender, temp.sender);
			strcpy(hashTable[hashIndex].email.recipient, temp.recipient);
			hashTable[hashIndex].email.day = temp.day;
			hashTable[hashIndex].email.words = temp.words;
		}
		// DOUBLE HASHING
		else if(option == 2)
		{
			while(hashTable[hashIndex].key != -1)
			{
				hashIndex = hash(tempKey, size) + (k * hash2(tempKey));
				k++;
			}
			k = 1;
			hashTable[hashIndex].key = tempKey;
			hashTable[hashIndex].email.id = temp.id;
			strcpy(hashTable[hashIndex].email.sender, temp.sender);
			strcpy(hashTable[hashIndex].email.recipient, temp.recipient);
			hashTable[hashIndex].email.day = temp.day;
			hashTable[hashIndex].email.words = temp.words;
		}

		
		path[0] = '\0'; //clear the string
		path = strcat(path, pathName);
	
	*OriginalSize = size;
	return hashTable;
}

struct HashTable* rehash(struct HashTable *hashTable, int newSize, int oldSize, int option)
{
	
	struct HashTable *newHashTable;
	newHashTable = (struct HashTable*)malloc(sizeof(struct HashTable) * newSize);
	if(newHashTable == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	resetHashTable(newHashTable, newSize);

	int tempKey2;
	//REALLOCATION
	// Traverse the old hash table, and reallocate each item
	// according to key and the new table size
	int i = 0, newIndex, k = 1;
	while(i < oldSize)
	{
		tempKey2 = hashTable[i].key;
		if(hashTable[i].key != 1)
		{
			// get the new index
			newIndex = hash(hashTable[i].key, newSize);
			// copy the values
			newHashTable[newIndex].key = hashTable[i].key;
			newHashTable[newIndex].email.id = hashTable[i].email.id;
			strcpy(newHashTable[newIndex].email.sender, hashTable[i].email.sender);
			strcpy(newHashTable[newIndex].email.recipient, hashTable[i].email.recipient);
			newHashTable[newIndex].email.day = hashTable[i].email.day;
			newHashTable[newIndex].email.words = hashTable[i].email.words;
		}
		// LINEAR PROBING
		else if(option == 1)
		{
			while(hashTable[i].key != -1)
			{
				tempKey2++;
				newIndex = hash(tempKey2, newSize);
			}

			newHashTable[newIndex].key = hashTable[i].key;
			newHashTable[newIndex].email.id = hashTable[i].email.id;
			strcpy(newHashTable[newIndex].email.sender, hashTable[i].email.sender);
			strcpy(newHashTable[newIndex].email.recipient, hashTable[i].email.recipient);
			newHashTable[newIndex].email.day = hashTable[i].email.day;
			newHashTable[newIndex].email.words = hashTable[i].email.words;
		}
		// DOUBLE HASHING
		else if(option == 2)
		{
			while(hashTable[i].key != -1)
			{
				newIndex = hash(hashTable[i].key, newSize) + (k * hash2(hashTable[i].key));
				k++;
			}
			k = 1;
			newHashTable[newIndex].key = hashTable[i].key;
			newHashTable[newIndex].email.id = hashTable[i].email.id;
			strcpy(newHashTable[newIndex].email.sender, hashTable[i].email.sender);
			strcpy(newHashTable[newIndex].email.recipient, hashTable[i].email.recipient);
			newHashTable[newIndex].email.day = hashTable[i].email.day;
			newHashTable[newIndex].email.words = hashTable[i].email.words;
		}

		i++;
	}
	free(hashTable);//destroy the old hash table
	return newHashTable;


}

void printTable(struct HashTable *hashTable, int size)
{
	int i;
	printf("Index\tID\tSender\tRecipient\tDate\tWords\n");
	for(i = 0; i < size; i++)
	{
		if(hashTable[i].key != -1)
			printf("%d\t%d\t%s\t%s\t\t%d\t%d\n", i, hashTable[i].email.id, hashTable[i].email.sender, hashTable[i].email.recipient, hashTable[i].email.day, hashTable[i].email.words);
		else
			printf("%d\n", i);
	}
}

void resetHashTable(struct HashTable *hashTable, int size)
{
	//this function sets the keys as -1
	// so that we can understand that index is empty
	int i;
	for(i = 0; i < size; i++)
	{
		hashTable[i].key = -1;
	}
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

int getKey(struct email A)
{
	return (A.id + A.sender[0] - 65);
}

int hash(int key, int size)
{
	return (key % size);
}

int hash2(int key)
{
	return (5 - (key % 5));
}

int isPrime(int number)
{
	int i;
	for(i = 2; i <= (number / 2); i++)
	{
		if(number % i == 0)
			return 0;
	}
	return 1;
}

int getNewPrime(int number)
{
	number++;
	while(!isPrime(number))
	{
		number++;
	}
	return number;
}