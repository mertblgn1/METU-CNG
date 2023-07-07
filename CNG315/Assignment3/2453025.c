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

struct edge
{
	char name[51];
	int weight;
	struct edge* next;
};

struct vertex
{
	char name[51]; // it stores the data
	int receivedEmails; // inDegree shows the number of received emails
	int sentEmails; // outDegree shows the number of sent emails
	int isProcessed; // it is used for marking the vertices while traversing
	int receivedWords;
	struct edge* edges;
};

struct AdjacencyList
{
	struct vertex* head;
};

struct graph
{
	int size;
	struct AdjacencyList* list;
};

// Queue Structures

struct QueueNode
{
	struct vertex* Vertex;
	struct QueueNode* next;
};

struct Queue
{
	struct QueueNode* front;
	struct QueueNode* rear;
};


struct graph* readEmails(char*, int);
int countWords(char*);
void createVertex(struct graph*, char*);
void createEdge(struct graph*, char*, char*, int);
void printGraph(struct graph*);
int checkPath(struct graph*, char*, char*);

// Queue Functions
struct QueueNode* newNode(char*);
struct Queue* createQueue();
void enQueue(struct Queue*, struct graph*, char*);
void deQueue(struct Queue*);
int QueueFrontIndex(struct Queue*, struct graph*);
int getIndex(struct graph*, char*);


int main()
{
	char pathName[50];
	int numberOfDataFiles;

	//get the information from the user
	printf("Enter the path of the directory which contains data files: ");
	scanf("%s", pathName);
	printf("Enter the number of data files: ");
	scanf("%d", &numberOfDataFiles);


	struct graph* Graph = readEmails(pathName, numberOfDataFiles);
	
	printGraph(Graph);
	printf("\n\n");
	printf("Check a path for two people:\n");
	char f[51], s[51];
	printf("Enter the first name: ");
	scanf("%s", f);
	printf("Enter the second name: ");
	scanf("%s", s);
	
	if(checkPath(Graph, f, s))
		printf("Yes there is a path!\n");
	else
		printf("Sorry, there is no path\n");


	return 0;
}

int checkPath(struct graph* Graph, char* first, char* second)
{
	int currentVertex;
	// Base case
	if(!strcmp(first, second))
		return 1;

	// Use Breath-First Traversal
	// Create a queue
	struct Queue* Q;
	Q = createQueue();

	// Add first name to the queue and mark it as processed in enqueue funtion
	enQueue(Q, Graph, first);

	// If there is no sent email, return 0
	currentVertex = QueueFrontIndex(Q, Graph);
	if(Graph->list[currentVertex].head->edges == NULL)
			return 0;

	while(Q->rear != NULL)
	{
		currentVertex = QueueFrontIndex(Q, Graph);
		if(!strcmp(Graph->list[currentVertex].head->name, second))
			return 1;
		deQueue(Q);

		// Get all adjacent vertices and add to the queue
		struct edge* temp;
		
		for(temp = Graph->list[currentVertex].head->edges; temp != NULL; temp = temp->next)
		{
			if(!Graph->list[getIndex(Graph, temp->name)].head->isProcessed)
			{
				enQueue(Q, Graph, temp->name);
			}
		}
	}

	return 0;
}

void printGraph(struct graph* Graph)
{
	int i, maxSentEmail, maxWords;
	
	// Display adjacency list
	struct edge* temp;
	printf("The resulting graph's adjacency list:\n");
	for(i = 0; i < Graph->size; i++)
	{
		printf("%s -> ", Graph->list[i].head->name);
		temp = Graph->list[i].head->edges;
		while(temp != NULL)
		{
			printf("%s | %d ", temp->name, temp->weight);
			if(temp->next != NULL)
				printf("-> ");
			else
				printf("\n");
			temp = temp->next;
		}
	}

	// Display the person who sent max number of emails
	// Find the person
	// maxSentEmail indicates the index of the person
	maxSentEmail = 0;
	for(i = 1; i < Graph->size; i++)
	{
		if(Graph->list[i].head->sentEmails > Graph->list[maxSentEmail].head->sentEmails)
			maxSentEmail = i;
	}

	printf("\n\nPeople with the maximum number of emails sent:\n");
	printf("%s sent %d emails\n", Graph->list[maxSentEmail].head->name, Graph->list[maxSentEmail].head->sentEmails);



	// Display the person who received max number of words
	// Find the person
	// maxWords indicates the index of the person
	maxWords = 0;
	for(i = 1; i < Graph->size; i++)
	{
		if(Graph->list[i].head->receivedWords > Graph->list[maxSentEmail].head->receivedWords)
			maxWords = i;
	}

	printf("\nPeople with the maximum number of words received:\n");
	printf("%s received %d words\n", Graph->list[maxWords].head->name, Graph->list[maxWords].head->receivedWords);

}


struct graph* readEmails(char *path, int number)
{
	// Create a graph
	struct graph* Graph = (struct graph*)malloc(sizeof(struct graph));
	
	// Check if it is created successfully
	if(Graph == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	// The number of emails is the maximum number of vertices, so program is safe
	// Create the adjacency list and check if it is created successfully
	Graph->list = (struct AdjacencyList*)malloc(sizeof(struct AdjacencyList) * number);
	if(Graph->list == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}
	
	// Set the initial values of graph
	Graph->size = 0;
	int i;
	for(i = 0; i < number; i++)
		Graph->list[i].head = NULL;

	// Save the pathname for other files
	char pathname[51];
	strcpy(pathname, path);

	// We are not interested in email content, but the number of words are important
	// To count them we need to store the content
	char content[1000];

	// Assume that file name starts from 1
	// Such as 1.txt, 2.txt ...
	i = 1;
	// To concatenate the i variable with the file name, it need to be converted to string
	char strInt[5];
	// Open the file stream
	FILE *inFile;

	// To check if the edges or vertices already added, we need names
	struct email tempEmail;

	while(i <= number)
	{
		sprintf(strInt, "%d", i);
		// for macOS, use '/' for path
		// for Windows, use '\' for path

		path = strcat(path, "/");
		path = strcat(path, strInt);
		path = strcat(path, ".txt");


		// Open the file for read
		inFile = fopen(path, "r");

		// Check if it is opened successfully
		if(inFile == NULL)
		{
			printf("The file doesn't exist!\n");
			exit(1);
		}

		fscanf(inFile, "%d\nFrom: %s\nTo: %s\nDate: %d\n%[^\r]\n", &tempEmail.id, tempEmail.sender,  tempEmail.recipient, &tempEmail.day, content);
		tempEmail.words = countWords(content);

		// Create vertex for sender and recipient
		createVertex(Graph, tempEmail.sender);
		createVertex(Graph, tempEmail.recipient);
		// Create edge
		createEdge(Graph, tempEmail.sender, tempEmail.recipient, tempEmail.words);

		i++;

		// Clear the string
		path[0] = '\0';
		path = strcat(path, pathname);
	}


	return Graph;
}

void createEdge(struct graph* Graph, char* sender, char* recipient, int words)
{
	// Look for sender Vertex
	int found = 0;
	int i;
	for(i = 0; i < Graph->size && found == 0; i++)
	{
		if(strcmp(Graph->list[i].head->name, sender) == 0)
		{
			// Set the found variable as the index of sender
			found = i;
			// Increase the sentEmails
			Graph->list[i].head->sentEmails++;
		}
	}

	int exist = 0;
	// If there is no edge:
	if(Graph->list[found].head->edges == NULL)
	{
		Graph->list[found].head->edges = (struct edge*)malloc(sizeof(struct edge));
		strcpy(Graph->list[found].head->edges->name, recipient);
		Graph->list[found].head->edges->weight = words;
		Graph->list[found].head->edges->next = NULL;
	}
	// If there are edge(s):
	else
	{
		struct edge* temp = Graph->list[found].head->edges;
		int done = 0;

		while(!done)
		{
			if(temp->next == NULL)
			{
				struct edge *newEdge = (struct edge*)malloc(sizeof(struct edge));
				strcpy(newEdge->name, recipient);
				newEdge->weight = words;
				newEdge->next = NULL;
				temp->next = newEdge;
				done = 1;

			}
			// If the edge is already added:
			else if(!strcmp(temp->next->name, recipient))
			{
				temp->next->weight += words;
				done = 1;
			}
			temp = temp->next;
		}
	}

	// Increase the received emails and received words
	for(i = 0; i < Graph->size; i++)
	{
		if(!strcmp(Graph->list[i].head->name, recipient))
		{
			Graph->list[i].head->receivedEmails++;
			Graph->list[i].head->receivedWords += words;
		}
	}


}

int countWords(char *content)
{
	// Check the space character
	// If there is a space increase the #words by 1
	int i = 0, words = 1;
	while(content[i] != '\0')
	{
		if(content[i] == ' ')
			words++;
		i++;
	}

	return words;
}

void createVertex(struct graph* Graph, char* name)
{
	// CHECK IF THE VERTEX IS ALREADY ADDED
	int exist = 0;

	int i;
	for(i = 0; i < Graph->size; i++)
	{
		if(strcmp(name, Graph->list[i].head->name) == 0)
			exist = 1;
	}

	// Creating head
	if(!exist && Graph->size == 0)
	{
		Graph->list[Graph->size].head = (struct vertex*)malloc(sizeof(struct vertex));
		strcpy(Graph->list[Graph->size].head->name,name);
		Graph->list[Graph->size].head->receivedEmails = 0;
		Graph->list[Graph->size].head->sentEmails = 0;
		Graph->list[Graph->size].head->isProcessed = 0;
		Graph->list[Graph->size].head->receivedWords = 0;
		Graph->list[Graph->size].head->edges = NULL;
		Graph->size++;
	}
	else if(!exist && Graph->size > 0)
	{
		Graph->list[Graph->size].head = (struct vertex*)malloc(sizeof(struct vertex));
		strcpy(Graph->list[Graph->size].head->name,name);
		Graph->list[Graph->size].head->receivedEmails = 0;
		Graph->list[Graph->size].head->sentEmails = 0;
		Graph->list[Graph->size].head->isProcessed = 0;
		Graph->list[Graph->size].head->receivedWords = 0;
		Graph->list[Graph->size].head->edges = NULL;
		Graph->size++;
	}
}

struct QueueNode* newNode(char* name)
{
	struct QueueNode* temp;
	temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	temp->Vertex = (struct vertex*)malloc(sizeof(struct vertex));
	if(temp == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	strcpy(temp->Vertex->name, name);

	temp->next = NULL;
	temp->Vertex->edges = NULL;
	return temp;
}

struct Queue* createQueue()
{
	struct Queue* q;
	q = (struct Queue*)malloc(sizeof(struct Queue));
	if(q == NULL)
	{
		printf("Out of memory!\n");
		exit(-1);
	}

	q->front = q->rear = NULL;
	return q;
}

void enQueue(struct Queue* q, struct graph* Graph, char* name)
{
	// Create a new node
	struct QueueNode* temp = newNode(name);
	// If queue is empty:
	if(q->rear == NULL)
		q->front = q->rear = temp;

	// Add to the end
	q->rear->next = temp;
	q->rear = temp;

	// Find the node in the graph and mark it
	int i;
	for(i = 0; i < Graph->size; i++)
	{
		if(!strcmp(Graph->list[i].head->name, name))
			Graph->list[i].head->isProcessed = 1;
	}
}

void deQueue(struct Queue* q)
{
	// If q is empty:
	if(q->front == NULL)
		return;

	struct QueueNode* temp = q->front;
	q->front = q->front->next;

	// If front becomes NULL, then rear should be NULL
	if(q->front == NULL)
		q->rear = NULL;

	free(temp);
}

int QueueFrontIndex(struct Queue* q, struct graph* Graph)
{
	int i;
	for(i = 0; i < Graph->size; i++)
	{
		if(!strcmp(Graph->list[i].head->name, q->front->Vertex->name))
			return i;
	}

	return -1;
}

int getIndex(struct graph* Graph, char* name)
{
	int i;
	for(i = 0; i < Graph->size; i++)
	{
		if(!strcmp(Graph->list[i].head->name, name))
			return i;
	}

	return -1;
}



