struct Node
{
	int arrival;
	int serviceTime;
	int serviceStartTime;
	int id;
	int insurance;
	int type;
	struct Node *next;
};

struct ListRecord
{
	struct Node *head;
	struct Node *tail;
	int size;
};

typedef struct ListRecord *List;

void InsertList(List, int, int, int, int, int, int);
