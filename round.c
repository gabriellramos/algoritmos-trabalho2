#include<stdio.h>
#include<stdlib.h>
int processes[100][4], NP, quantum, scheduler[1000],WT[100];
unsigned int time = 0;
typedef struct el
{
	unsigned int p;
	struct el * next;
}Q;

Q * qeue = NULL;

void getSystem(){
	int i;
	
	for(i=0; i<NP; i++ )
	{
		//printf("\n Arrival Time of p%d: ", i);
		scanf("%d %d", &processes[i][0], &processes[i][1]);
		//printf("\n Burst time for p%d: ", i);
		processes[i][2] = processes[i][1];
		//printf("\n-----------");
	}
	
}

void printSystem()
{
	int i;
	printf("\n\t\tOur System is :");
	printf("\nQuantum: %d",quantum);
//	printf("\nPi:  AT  BT RT  TF");
	/*for(i=0; i<NP; i++)
	{
		printf("\nP%d:  %d  %d  %d  %d", i, processes[i][0], processes[i][1], processes[i][2], processes[i][3]);
	}
	*/
	printf("\nThe qeue: ");
	Q *n;
	for(n=qeue; n!=NULL; n=n->next)
	{
		printf("P%d ",n->p);
	}
}
unsigned int executionRemained()
{
	int i;
	unsigned int x = 0;
	for(i=0; i<NP; i++)
	{
		if(processes[i][2] > 0)
		{
			x = 1;
		}
	}
	return x;
}
void addToQeue(int i)
{
	Q *n, *n1;
	n = (Q *)malloc(sizeof(Q));
	n->next = NULL;
	n->p = i;
	if(qeue == NULL)
	{
		
		qeue = n;
	}
	else
	{
		for(n1 = qeue ; n1->next!=NULL; n1=n1->next);
		n1 -> next = n;
	}
}
void addArrivedProcessesToQeue()
{
	int i;
	for(i=0; i<NP; i++)
	{
		if(processes[i][0] == time)
		{
			addToQeue(i);
		}
	}
}
unsigned int getNextProcess()
{
	Q *n;
	int x;
	if(qeue == NULL)
	{
		return -1;
	}
	else
	{
		x = qeue -> p;
		n = qeue;
		qeue = qeue -> next;
		free(n);
		return x;
	}
}
void schedule()
{
	unsigned int np, toRun, q, i;
	q = 0;
	addArrivedProcessesToQeue();
	while(executionRemained())
	{
		np = getNextProcess();
		if(np == -1)
		{
			scheduler[time] = -1;
			time++;
			addArrivedProcessesToQeue();
		}
		else
		{
			q = quantum;
			if(processes[np][2] < q)
			{
				q = processes[np][2];
			}
			for(i = q; i>0; i--)
			{
				scheduler[time]=np;
				time++;
				processes[np][2]--;
				addArrivedProcessesToQeue();
			}
			if(processes[np][2] > 0)
			{
				addToQeue(np);
			}
			
			processes[np][3] = time;
		}
		
		
	//	printSystem();
		int x;
		
	}
}
void printScheduling()
{
	int i;
	printf("\n\nScheduling: \n");
	for(i=0; i<time; i++)
	{
		if (scheduler[i]!=-1){
			printf("P%d " ,scheduler[i]+1);
		}
		//printf(" (P%d) ",scheduler[i]);
	}
	printf("\n\nWaiting Time: \n");
	for(i=0; i<NP; i++)
	{ 
		printf("\nP%d: %d", i, WT[i]);
	}
	//counting Average Waiting Time...
	float AWT = 0.0;
	for(i=0; i<NP; i++)
	{
		AWT = AWT+WT[i];
	}
	AWT = AWT/NP;
	printf("\n\nAverage Waiting Time: %f", AWT);
	
}
void WatingTime()
{
	int i;
	unsigned int releaseTime, t;
	for(i=0; i<NP; i++)
	{
		
		for(t=time-1; scheduler[t]!= i; t--);
		releaseTime = t+1;
		
		WT[i] = processes[i][3] - (processes[i][0] + processes[i][1]);
	}
}

void turnaround()
{
	int i;
	float tmr = 0;
	for (i=0;i<NP; i++){
		tmr += processes[i][3] - processes[i][0];
	}
	
	tmr = tmr/NP;
	printf ("Turnaround: %f\n", tmr);
}

main()
{
	scanf("%d", &quantum);
	while(1){
		scanf("%d", &NP);
		if (NP == 0) break;
		getSystem();
		printSystem();
		schedule();
		WatingTime();
		turnaround();
		printScheduling();
	}
}
