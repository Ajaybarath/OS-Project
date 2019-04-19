#include<stdio.h>


void insert(int);
int pop();
int show();
int queue_array[50];
int rear = - 1;
int front = - 1;


int main(){
	
	int n = 0;
	
	printf("Enter the number of process : ");
	scanf("%d", &n);
	
	int process[n];
	int arrivalTime[n];
	int priority[n];
	int turnAroundTime[n];
	int waitingTime[n];
	int burstTime[n];
	int remainingBurstTime[n];
	int completionTime[n];	
	int processChecker[n];	
	int readyQueue[500];
   
    
    
    int timeQuantum = 1;
    printf("Enter the time quantum : ");
    scanf("%d", &timeQuantum);
    
    printf("Enter the arrival time, burst time, periority of each process one by one \n");
    
    int i =0 ;
    
    printf("--------------------------- \n");
    
    for (i=0; i<n ; i++){
        process[i] = i;
        
        printf("Enter the arrival time : ");
        scanf("%d", &arrivalTime[i]);
        
        printf("Enter the burst time   : ");
        scanf("%d", &burstTime[i]);
        remainingBurstTime[i] = burstTime[i];
        
        printf("Enter the priority     : ");
        scanf("%d", &priority[i]);
        
        processChecker[i] = 1;
        turnAroundTime[i] = 0;
        
        printf("--------------------------- \n");
        
    }
    
    
    int j; 
   	for (i = 0; i < n-1; i++){  
	        
         for (j = 0; j < n-i-1; j++){
         	
           if (priority[j] < priority[j+1]){
               int temp = priority[j];
               priority[j] = priority[j+1];
               priority[j+1] = temp;
               
               temp = process[j];
               process[j] = process[j+1];
               process[j+1] = temp;
               
               temp = arrivalTime[j];
               arrivalTime[j] = arrivalTime[j+1];
               arrivalTime[j+1] = temp;
               
               temp = burstTime[j];
               burstTime[j] = burstTime[j+1];
               burstTime[j+1] = temp;
               
               temp = remainingBurstTime[j];
               remainingBurstTime[j] = remainingBurstTime[j+1];
               remainingBurstTime[j+1] = temp;
               
           }	
           
       }
   }
        
		   
	int time = 0;
	
	int q = 0;
	int pos = -1;
	
	while(q < n){
		
		
		for (i = 0; i<n; i++){
						
			if (arrivalTime[i] <= time && processChecker[i] == 1){
				
				pos = i;
				break;
				
			}
			
		}
		
		if(pos != -1){
					
			if (remainingBurstTime[pos] > timeQuantum){
				
				remainingBurstTime[pos] = remainingBurstTime[pos] - timeQuantum;
				time = time + timeQuantum-1;
				
				processChecker[pos] = 0;
				
				insert(pos);
				
				q++;
	
				
			}		
			else{
				
				time += remainingBurstTime[pos] - 1;
				remainingBurstTime[pos] = 0;
				
				processChecker[pos] = 5;
				
				completionTime[pos] = time;
				
				q++;
	
			}
			
			pos = -1;
			
		}
		
		time++;
				
	}	   
	
	
	while(show() != -1){
		
		int pos = pop();
		
		if (remainingBurstTime[pos] > timeQuantum){
			
			remainingBurstTime[pos] = remainingBurstTime[pos] - timeQuantum;
			time = time + timeQuantum;
			
			processChecker[pos] = 0;
			
			insert(pos);
			
			
		}		
		else{
			
			time += remainingBurstTime[pos];
			remainingBurstTime[pos] = 0;
			
			processChecker[pos] = 5;
			
			completionTime[pos] = time - 1;
			
		}
						
	}
	
	
	for (i=0;i<n;i++){
		turnAroundTime[i] = completionTime[i] - arrivalTime[i] + 1;
		waitingTime[i] = turnAroundTime[i] - burstTime[i];
	}
	
	printf("AT \t BT \t Pr \t CT \t TAT \t WT \n");
	
	for (i=0;i<n;i++){
		printf("%d \t  %d \t %d \t %d \t %d \t %d \n",arrivalTime[i], burstTime[i],priority[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
	}
	
	return 0;
}



void insert(int p)
{
    int add_item = p;
    if (rear == 50 - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1)
        front = 0;
        rear = rear + 1;
        queue_array[rear] = add_item;	
    }
}
 
int pop()
{
    if (front == - 1 || front > rear)
    {
        return ;
    }
    else
    {
    	
        front = front + 1;
        return queue_array[front-1];
        
    }
} 
 
 
int show()
{
    if (front == - 1 || front > rear)
    {
        return -1;
    }
    else
    {
        return queue_array[front];
    }
} 
