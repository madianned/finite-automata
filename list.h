//list.h
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


#define MAX 128


#ifndef LIST_H
#define LIST_H
				//Qnode can hold both states and final states
struct Qnode {
	char state[MAX];
	struct Qnode* next;
}Qnode;
				//Enode has single characters, works for the accepted inputs
struct Enode {
	char input;
  	struct Enode* next;
}Enode;
				//Tnode records transitions in sets of: a string for the initial state, a char for the input,
				//followed by another string for the final state
struct Tnode {
	char istate[MAX];
  	char input;
  	char fstate[MAX];
  	struct Tnode* next;
}Tnode;


				//Tadd adds transitions to the list
struct Tnode * Tadd(struct Tnode* head, char *istate, char input, char*fstate, int k, int l)
{
	struct Tnode* new = (struct Tnode*) malloc(sizeof(struct Tnode)); 
    struct Tnode *curr = head;  
  	new->input=input;
  	new->next=NULL;
  	int i,j;
  
  	for(i=0;i<k;i++)
  		{new->istate[i]=istate[i];}
  	for(i=0;i<l;i++)
  		{new->fstate[i]=fstate[i];}

  	new->istate[k]=0;
  	new->fstate[l]=0;

  	if(head->input==0)
  	{
   		head->input=new->input;
   		
  		for(i=0;i<k;i++)
  			{head->istate[i]=istate[i];}
  		for(i=0;i<l;i++)
  			{head->fstate[i]=fstate[i];}
   		
   		head->next=NULL;
   		head->istate[k]=0;
  		head->fstate[l]=0;
  		
   		return head;
  	}
  	else
  	{ 
   		while (1) 
   		{
   			if(curr->next==NULL)
   			{
   				curr->next=new;
   				curr->fstate[k]=0;
   				break;
   			} 			
   			curr = curr->next;
   		} 
		return head; 
	}
}


				//Eadd adds inputs to the list
struct Enode* Eadd(struct Enode* head,char input)
{
    struct Enode* new = (struct Enode*) malloc(sizeof(struct Enode)); 
    struct Enode *curr = head;  
  	
  	if(head->input==0)
  	{
  		head->input=input;
  		return head;
  	}
  	
  	while(curr->next!=NULL)
  		{curr=curr->next;}
  	
  	curr->next=new;
  	new->input=input;
  	new->next=NULL;
 	
return head;
}


				//Qadd adds states to the list
struct Qnode* Qadd(char* str, struct Qnode* head, int length)
{
	char string[length];
    int i;
    
    for(i=0;i<length;i++)
    	{string[i]=str[i];}
	
	string[i]=0;
    struct Qnode* qnew = (struct Qnode*) malloc(sizeof(struct Qnode)); 
    struct Qnode *curr = head; 
     
    for(i=0;i<length;i++)
    	{qnew->state[i] = string[i];}
    
    qnew->state[i]=0; 
    qnew->next = NULL; 
    
    if(head->state[0]==0)
	{
		for(i=0;i<length;i++)
			{head->state[i]=qnew->state[i];}
		head->next=NULL;
		head->state[i]=0;
		return head;
	}

    while (1) 
    {
        if(curr->next==NULL)
        {
        	curr->next=qnew;
        	break;
        }
        curr = curr->next;
    } 
return head; 
}


				//returns how many transitions there are
int howmanytransitions(struct Tnode *Thead)
{
	struct Tnode*curr=Thead;
	int i;
	i=0;
	
	while(curr!=NULL)
	{
		i++;
		curr=curr->next;
	}
return i;
}


				//returns number of states
int howmanystates(struct Qnode *Qhead)
{
	struct Qnode*curr=Qhead;
	int i;
	i=0;
	
	while(curr!=NULL)
	{
		i++;
		curr=curr->next;
	}
return i;
}

			//returns the size of the alphabet
int howmanyE(struct Enode *Ehead)
{
	struct Enode*curr=Ehead;
	int i;
	i=0;
	
	while(curr!=NULL)
	{
		i++;
		curr=curr->next;
	}
return i;
}

#endif