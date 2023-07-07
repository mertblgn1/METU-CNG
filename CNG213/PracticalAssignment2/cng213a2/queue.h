struct QueueRecord
{
	struct Node *front;
	struct Node *rear;
	int lenght;
};
typedef struct QueueRecord *Queue;

int IsEmptyQueue(Queue);