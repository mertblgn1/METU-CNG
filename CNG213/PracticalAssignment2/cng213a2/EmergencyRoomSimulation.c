//Name: Mert Can
//Surname: Bilgin
//ID: 2453025

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "list.c"
#include "queue.h"
#include "queue.c"



void parseInput(int*, int*, int*, int*, char*, char*, char*, char*);
List createPatientsList(int, int, int, int);
void initialiseSimulator(Queue, int*, int);
void newPatient(Queue, int, int, int, int, int, int);
void reportStatistics(List, int, int, int*, int);
void servePatient(Queue);


int main(int argc, char *argv[])
{
	int noOfPatients, noOfDoctors, maxArrivalTime, maxServiceTime;
	
	//input is parsed
	parseInput(&noOfPatients, &noOfDoctors, &maxArrivalTime, &maxServiceTime, argv[1], argv[2], argv[3], argv[4]);

	srand(time(NULL));

	//list of patients is created
	List patients;
	patients = createPatientsList(noOfPatients, noOfDoctors, maxArrivalTime, maxServiceTime);

	int doctors[noOfDoctors];

	Queue Q;
	Q = (Queue)malloc(sizeof(Queue));
	if(Q == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	//the empty queue is created in this funtion and all the doctors are made available
	initialiseSimulator(Q, &doctors[0], noOfDoctors);

	int time = 0, j = 1, k, available = 0;

	//a node is created to traverse in the list
	struct Node *p;
	p = patients->head->next;

	//The worst case of the time is
	//(maxArrival) + (maxService)(noOfPatients - Doctors)
	//therefore, the loop will stop when the time comes to the worst case

	//I need to keep track of the list, and I need to get the patient to the queue
	//at the arrival time
	int stop = (maxArrivalTime) + (maxServiceTime)*(noOfPatients - noOfDoctors);
	while(time < stop){
		//I need to check the availability of the doctors

		for(k = 0; k < noOfDoctors; k++){
			if(doctors[k] == 1){
				available = 1;
				p->id = k;
			}
		}

		if(p->arrival == time){
			//new patient
			newPatient(Q, p->arrival, p->serviceTime, p->serviceStartTime, p->id, p->insurance, p->type);
			p = p->next;
			j++;
			time--;

		}
		if(available == 1 && !IsEmptyQueue(Q)){
			//serve patient
			servePatient(Q);
			p->serviceStartTime = time;
			//set the doctor as busy
			doctors[p->id] = 0;

			while(time != p->serviceStartTime + p->serviceTime){
				time++;
			}
			//set the doctor available again
			doctors[p->id] = 1;
			time--;
		}

		available = 0;
		time++;
	}
	reportStatistics(patients, noOfDoctors, noOfPatients, &doctors[0], time);




	return 0;
}

void servePatient(Queue Q)
{
	if(!IsEmptyQueue(Q)){
		struct Node *new = (struct Node*)malloc(sizeof(struct Node));
		if(new == NULL){
			printf("Out of memory!\n");
			exit(1);
		}

		struct Node *remove;
		remove = Q->front->next;
		Q->front->next = remove->next;

		new->arrival = remove->arrival;
		new->serviceTime = remove->serviceTime;
		new->serviceStartTime = remove->serviceStartTime;
		new->id = remove->id;
		new->insurance = remove->insurance;
		new->type = remove->type;

		//free(remove);

		Q->lenght--;
		if(Q->lenght == 0)
			Q->rear = Q->front;
	}
	else{
		printf("The queue is empty!\n");
	}
}

void newPatient(Queue Q, int arrival, int serviceTime, int serviceStartTime, int id, int insurance, int type)
{
	struct Node *newNode;
	newNode = (struct Node*)malloc(sizeof(struct Node));
	if(newNode == NULL){
		printf("Out of memory!\n");
		exit(1);
	}

	newNode->arrival = arrival;
	newNode->serviceTime = serviceTime;
	newNode->serviceStartTime = serviceStartTime;
	newNode->id = id;
	newNode->insurance = insurance;
	newNode->type = type;
	newNode->next = NULL;

	//I need to add the queue according to the priority
	//keep track of the queue to find the position I should insert

	struct Node *p, *temp;
	p = Q->front->next;

	int pos = 1, found = 0, i;
	while(p != NULL){
		if(newNode->type > p->type)
			found = 1;
		else
			pos++;
		p = p->next;
	}

	//we know the position according to the priority
	//so we can insert

	if(found == 0)
		pos = Q->lenght + 1;
	if(pos == Q->lenght + 1){
		Q->rear->next = newNode;
		Q->rear = newNode;
	}
	else{
		temp = Q->front;
		for(i = 1; i < pos; i++)
			temp = temp->next;

		newNode->next = temp->next;
		temp->next = newNode;
	}
	Q->lenght++;
}

List createPatientsList(int noOfPatients, int noOfDoctors, int maxArrivalTime, int maxServiceTime)
{
	List patients;
	patients = (List)malloc(sizeof(List));
	if(patients == NULL){
		printf("Out of memory!\n");
		exit(1);
	}

	//dummy node
	patients->size = 0;
	patients->head = (struct Node*)malloc(sizeof(struct Node));
	if(patients->head == NULL){
		printf("Out of memory!\n");
		exit(1);
	}

	patients->head->next = NULL;
	patients->tail = patients->head;

	//patients' inforation is generated randomly

	int i, arrival, serviceTime, insurance, type, id = 0, serviceStartTime = 0;
	for(i = 0; i < noOfPatients; i++){
		arrival = (rand() % maxArrivalTime) + 1;
		serviceTime = (rand() % maxServiceTime) + 1;
		insurance = rand() % 2;
		type = (rand() % 4) + 1;
		InsertList(patients, arrival, serviceTime, serviceStartTime, id, insurance, type);
	}

	return patients;
}

void initialiseSimulator(Queue Q, int *doctors, int numberOfDoctors)
{
	//create an empty queue
	
	Q->front = (struct Node*)malloc(sizeof(struct Node));
	if(Q->front == NULL){
		printf("Out of memory!\n");
		exit(1);
	}
	
	Q->front->next = NULL;
	Q->rear = Q->front;
	Q->lenght = 0;

	//make all doctors available
	int i;
	for(i = 0; i < numberOfDoctors; i++){
		*(doctors + i) = 1;
	}

}

void reportStatistics(List L, int doctors, int patient, int *doctor, int time)
{
	int red = 0, orange = 0, yellow = 0, green = 0, k, insurance = 0, maxWait;
	float avg, noP, waitingTime = 0;
	noP = patient;
	struct Node *p;
	p = L->head->next;
	maxWait = p->arrival - p->serviceStartTime;
	while(p != NULL){
		if(p->type == 4)
			red++;
		else if(p->type == 3)
			orange++;
		else if(p->type == 2)
			yellow++;
		else if(p->type == 1)
			green++;

		for(k = 0; k < doctors; k++){
			if(p->id == k)
				*(doctor + k) += 1;
		}
		if(p->insurance == 1)
			insurance++;

		if((p->arrival - p->serviceStartTime) > maxWait)
			maxWait = p->arrival - p->serviceStartTime;

		waitingTime += (p->arrival - p->serviceStartTime);
		p = p->next;
	}


	printf("****************Report*****************\n");
	printf("The number of doctors: %d\n", doctors);
	printf("The number of patients: %d\n", patient);
	printf("Number of patients for each patient type:\n");
	printf("\tred: %d\n", red);
	printf("\torange: %d\n", orange);
	printf("\tyellow: %d\n", yellow);
	printf("\tgreen: %d\n", green);
	printf("Number of patients for each Doctor:\n");
	for(k = 0; k < doctors; k++){
		printf("\tDoctor %d: %d\n", k+1, doctor[k] - 1);
	}
	printf("Completion time: %d\n", time);
	printf("Average time spent in the queue: %.1f\n", waitingTime/noP);
	printf("Maximum waiting time: %d\n", maxWait);
	printf("Number of patients with insurance: %d\n", insurance);
	printf("Number of patient without insurance: %d\n", patient - insurance);
}

void DisplayQueue(Queue q)
{
	struct Node *p;
	p = q->front->next;

	while(p != NULL){
		printf("arrival time: %d\n", p->arrival);
		printf("service time: %d\n", p->serviceTime);
		printf("service start time: %d\n", p->serviceStartTime);
		printf("id: %d\n", p->id);
		printf("insurance: %d\n", p->insurance);
		printf("type: %d\n", p->type);
		p = p->next;
	}
}


void parseInput(int *noOfPatients, int *noOfDoctors, int *maxArrivalTime, int *maxServiceTime, char *a, char *b, char *c, char *d)
{
	//int the command arguments part always char*, so I need to convert them to integers
	//I use atoi function to do that

	*noOfPatients = atoi(a);
	*noOfDoctors = atoi(b);
	*maxArrivalTime = atoi(c);
	*maxServiceTime = atoi(d);
}