void InsertList(List patients, int arrival, int serviceTime, int serviceStartTime, int id, int insurance, int type)
{
	struct Node *insert, *temp, *p;
	int i;

	insert = (struct Node*)malloc(sizeof(struct Node));
	if(insert == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	insert->next = NULL;

	insert->arrival = arrival;
	insert->serviceTime = serviceTime;
	insert->serviceStartTime = serviceStartTime;
	insert->id = id;
	insert->insurance = insurance;
	insert->type = type;

	//find position that will be inserted by ascending order
	int pos = 1, found = 0;
	p = patients->head->next;
	while(p != NULL){
		if(insert->arrival < p->arrival)
			found = 1;
		else
			pos++;

		p = p->next;
	}

	//we know the position, so we can insert it now

	if(found == 0)
		pos = patients->size + 1;
	if(pos == patients->size + 1){
		patients->tail->next = insert;
		patients->tail = insert;
	}
	else{
		temp = patients->head;
		for(i = 1; i < pos; i++)
			temp = temp->next;

		insert->next = temp->next;
		temp->next = insert;
	}
	patients->size++;

}