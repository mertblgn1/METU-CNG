// Name: Mert Can Bilgin
// Student ID: 2453025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct email
{
	int id;
	char sender[51];
	char recipient[51];
	int day;
	char spam[8];
	char* content;
	struct email *next;
};

struct emailList
{
	struct email* head;
	int size;
};

struct emailList* createList();
void readEmails(char*, int, struct emailList*, struct emailList*);
void addEmail(struct emailList*, int, char*, char*, int, char*, char*);
void searchPattern(char*, struct emailList*, struct emailList*);
int RabinKarp(char*, char*, int, int, int*);

int main()
{
	struct emailList* spam, *nonspam;
	
	// Create the lists for spam and nonspam
	spam = createList();
	nonspam = createList();

	char path[100];
	int numberOfEmails;
	// I assumed that maximum pattern size is 20
	char pattern[20];
	
	// Get the inputs from the user
	printf("Enter the directory path containing the emails: ");
	scanf("%s", path);
	printf("Enter the number of emails to be read: ");
	scanf("%d", &numberOfEmails);
	printf("Enter the pattern: ");
	scanf("%s", pattern);

	readEmails(path, numberOfEmails, spam, nonspam);
	searchPattern(pattern, spam, nonspam);


	return 0;
}

void searchPattern(char* pattern, struct emailList* spam, struct emailList* nonspam)
{
	// count variable is for patterns found
	int i, j, count = 0;
	struct email* temp;
	int foundEmails = 1;
	
	// For spam emails, set temp as head of spams, then traverse the list
	// and call the RK function
	temp = spam->head;
	printf("\nSpam emails containing the pattern:");
	while(temp != NULL)
	{
		count += RabinKarp(temp->content, pattern, 128, 256, &foundEmails);
		temp = temp->next;
	}

	// foundEmails started from 1, so we need to subtract 1
	printf("\n%d pattern(s) detected in %d email(s)\n", count, foundEmails-1);

	// Reset the variables foundEmails and count
	// set temp as head of nonspam
	temp = nonspam->head;
	foundEmails = 1;
	count = 0;
	printf("\nNon-spam emails containing the pattern:");
	while(temp != NULL)
	{
		count += RabinKarp(temp->content, pattern, 128, 256, &foundEmails);
		temp = temp->next;
	}

	printf("\n%d pattern(s) detected in %d email(s)\n", count, foundEmails-1);


}

int RabinKarp(char* T, char* P, int d, int q, int *foundEmails)
{
	int n = strlen(T);
	int m = strlen(P);
	int h = d ^(m - 1) % q;
	int p = 0;
	int t = 0;
	int i,j, count = 0;
	int a = 0;

	// Convert uppercase letters in both text and pattern to lowercase
	// so the pattern will be case insensitive
	// however, don't loose the original text to display it
	char text[strlen(T)];
	for(j = 0; j < strlen(T);j++)
			text[j] = tolower(T[j]);
	for(j = 0; j < strlen(P); j++)
			P[j] = tolower(P[j]);

	for(i = 0; i < m; i++)
	{
		p = (d * p + P[i]) % q;
		t = (d * t + T[i]) % q;
	}

	for(i = 0; i <= n-m; i++)
	{
		if(p == t)
		{
			for(j = 0; j < m; j++)
			{
				if(text[i + j] != P[j])
					break;
			}

			if(j == m){
				if(count == 0){
					printf("\n%d. ", *foundEmails);
					*foundEmails = *foundEmails + 1;
				}

				while(a < i + m)
				{
					printf("%c", T[a]);
					if(a == i-1)
						printf("[");

					if(a == i + m - 1)
						printf("]");
					a++;
				}

				count++;
			}
		}

		if(i < n - m)
		{
			t = (d * (t - text[i]*h) + text[i + m]) % q;
			if(t < 0)
				t += q;
		}
	}

	while(a <= n && count > 0)
	{
		printf("%c", T[a]);
		a++;
	}

	// it returns the number of founded pattern
	return count;

}

void readEmails(char* path, int numberOfEmails, struct emailList* spam, struct emailList* nonspam)
{
	char pathName[51];
	strcpy(pathName, path);
	int i = 1; // file name starts from 1
	char strInt[5]; // string version of variable i

	// Open the file stream
	FILE *inFile;

	// temporary variables
	int tempId;
	char tempSender[51];
	char tempRecipient[51];
	int tempDay;
	char tempSpam[8];
	char *tempContent;
	tempContent = (char*)malloc(sizeof(char)*1000);
	if(tempContent == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	while(i <= numberOfEmails)
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

		fscanf(inFile, "%d\nFrom: %s\nTo: %s\nDate: %d\nType: %s\n%[^\r]\n", &tempId, tempSender, tempRecipient, &tempDay, tempSpam, tempContent);
		if(strcmp(tempSpam, "Spam") == 0)
		{
			// ADD TO SPAM
			addEmail(spam, tempId, tempSender, tempRecipient, tempDay, tempSpam, tempContent);
		}
		else if(strcmp(tempSpam, "Nonspam") == 0)
		{
			// ADD TO NONSPAM
			addEmail(nonspam, tempId, tempSender, tempRecipient, tempDay, tempSpam, tempContent);
		}

		i++;
		// Clear the string
		path[0] = '\0';
		path = strcat(path, pathName);
	}
}

void addEmail(struct emailList *list, int id, char* sender, char* recipient, int day, char*type, char*content)
{
	// Allocate the node

	// If the head of the list is empty
	if(list->head == NULL)
	{
		list->head = (struct email*)malloc(sizeof(struct email));
		if(list->head == NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}

		list->head->content = (char*)malloc(sizeof(char)*1000);
		if(list->head->content == NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}

		list->head->id = id;
		strcpy(list->head->sender, sender);
		strcpy(list->head->recipient, recipient);
		list->head->day = day;
		strcpy(list->head->spam, type);
		strcpy(list->head->content, content);
		list->head->next = NULL;
		list->size++;
	}
	else
	{
		// Create a new node and add it to the beginning of the list
		struct email *newEmail = (struct email*)malloc(sizeof(struct email));
		if(newEmail == NULL)
		{
			printf("Out of memory!\n");
			exit(-1);
		}
		newEmail->content = (char*)malloc(sizeof(char)*1000);
		if(newEmail->content == NULL)
		{
			printf("Out of memory!\n");
			exit(-1);
		} 

		newEmail->id = id;
		strcpy(newEmail->sender, sender);
		strcpy(newEmail->recipient, recipient);
		newEmail->day = day;
		strcpy(newEmail->spam, type);
		strcpy(newEmail->content, content);
		newEmail->next = list->head->next;
		list->head->next = newEmail;
		list->size++;
	}
}

struct emailList* createList()
{
	// Allocate the list
	struct emailList* E;
	E = (struct emailList*)malloc(sizeof(struct emailList));
	if(E == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	E->head = NULL;
	E->size = 0;

	return E;
}