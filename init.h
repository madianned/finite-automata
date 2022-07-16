//init.h
 
#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *** initpartitions(struct Qnode*qhead, struct Enode* ehead, struct Qnode*fhead, struct Tnode*thead, char*initstate)
{
	int maximum, maximumt, i, j;
	maximum=howmanystates(qhead);
	maximumt=howmanytransitions(thead);
	char *** parray=malloc(6*sizeof(char ***));

	parray[0]=malloc(maximum*sizeof(char **));
	for(i=0;i<maximum;i++)
		{parray[0][i]=malloc(sizeof(char*));}
	
	parray[1]=malloc(maximum*sizeof(char **));
	for(i=0;i<maximum;i++)
		{parray[1][i]=malloc(sizeof(char*));}
	
	parray[2]=malloc(sizeof(char**));
	parray[2][0]=malloc(sizeof(char*));

	parray[3]=malloc(maximumt*sizeof(char **));
	for(i=0;i<maximumt;i++)
		{parray[3][i]=malloc(sizeof(char*));}
	
	parray[4]=malloc(maximumt*sizeof(char **));
	for(i=0;i<maximumt;i++)
		{parray[4][i]=malloc(sizeof(char*));}

	parray[5]=malloc(maximumt*sizeof(char **));
	for(i=0;i<maximumt;i++)
		{parray[5][i]=malloc(sizeof(char*));}

	struct Qnode*qcurr=qhead;i=0;	
	while(qcurr!=NULL)
	{
		strcpy(parray[0][i],qcurr->state);
		qcurr=qcurr->next;
		i++;
	}

	struct Qnode*fcurr=fhead;	
	j=0;
	
	while(fcurr!=NULL)
	{
		strcpy(parray[1][j],fcurr->state);
		fcurr=fcurr->next;
		j++;
	}

	strcpy(parray[2][0],initstate);

	struct Tnode*tcurr=thead;
	i=0;
	
	while(tcurr!=NULL)
	{
		strcpy(parray[3][i],tcurr->istate);
		parray[4][i][0]=tcurr->input; 
		parray[4][i][1]=0;
		strcpy(parray[5][i],tcurr->fstate);
		tcurr=tcurr->next;
		i++;
	}	
return parray;
}

		//Function that creates lists with correct information read from file
char* InitLists(char * input, struct Qnode * Qhead, struct Enode * Ehead, struct Qnode * Fhead, struct Tnode * Thead)
{

   char tempstr[MAX];
   char tempchar;
   FILE *fi;
   char *inputname=input;
   fi=fopen(inputname, "r");
   
   if (fi == NULL)
   {
        printf("Could not open file %s\n",inputname);
        return NULL;
   }
   
			//finds list of states
  tempchar=fgetc(fi);
    if(tempchar!='Q')
    {
     	printf("formatting is wrong at the beginning1\n");
     	return NULL;
    }
     
	tempchar=fgetc(fi);
	if(tempchar!='=')
    {
     	printf("formatting is wrong at the beginning2\n");
     	return NULL;
    }
    
	tempchar=fgetc(fi);
	if(tempchar!='{')
	{
     	printf("formatting is wrong at the beginning3\n");
     	return NULL;
    }
  
	int i;

	while(1)  
	{
    	i=0;
    	tempchar=fgetc(fi);

		while (tempchar!=',' && tempchar!='}')
		{
			tempstr[i]=tempchar;
			i++;
			tempchar=fgetc(fi);
		}

    	if (tempchar == ',')
    		Qhead=Qadd(tempstr,Qhead,i+1);

    	if (tempchar == '}')
    	{
    		Qhead=Qadd(tempstr,Qhead,i+1);
    		break;
    	}
	}
 
			//finds list of inputs
	tempchar=fgetc(fi);
	tempchar=fgetc(fi);
	
    if(tempchar!='E')
    {
     	printf("formatting is wrong at the beginning4\n");
     	return NULL;
    }
    
	tempchar=fgetc(fi);
    if(tempchar!='=')
	{
		printf("formatting is wrong at the beginning5\n");
     	return NULL;
	}
	
	tempchar=fgetc(fi);
    if(tempchar!='{')
    {
    	printf("formatting is wrong at the beginning6\n");
    	return NULL;
    }

	while(1)
	{
    	tempchar=fgetc(fi);
    	if(tempchar=='}')
    		break;
    	if(tempchar!=',')
    		Ehead=Eadd(Ehead, tempchar);
  	}

			//finds initial state
	char initstate[MAX];
	int j;
  
	for(i=0;i<5;i++)
		{tempchar=fgetc(fi);}
  	
	i=0;
	while(tempchar!='}')
	{
		initstate[i]=tempchar;
		tempchar=fgetc(fi);
		i++;
	}
	
	initstate[i]=0;     

    char *initialstate=(char *)malloc(MAX*sizeof(char));
    strcpy(initialstate,initstate);
	char tempstring[MAX];
	char tstring[MAX];
  	char tempc;
  	
  	for(i=0;i<5;i++)
  		{tempchar=fgetc(fi);}	
  	i=0;

	while(tempchar!='}')
  	{
    	if(tempchar==',')
    	{
    		Fhead=Qadd(tempstring, Fhead, i);
    		i=0;
    	}
		else
		{
			tempstring[i]=tempchar;
			i++;
		}

		tempchar=fgetc(fi);
  	}
  
	Fhead=Qadd(tempstring, Fhead, i);
  
			//creates linked list of transition functions
  	for(i=0;i<7;i++)
  		{tempchar=fgetc(fi);}
  	i=0;

	while(tempchar!='}')
 	{
   		tempchar=fgetc(fi);
   		i=0;
   		
   		while(tempchar!=',')
   		{
     		tempstring[i]=tempchar;
     		tempchar=fgetc(fi);
     		i++;
   		}
   		
		tempstring[i]=0;
   		tempc=fgetc(fi);
   		
   		for(j=0;j<5;j++)
   			{tempchar=fgetc(fi);}
   		j=0;
    
		while(tempchar!=')')
   		{
    		tstring[j]=tempchar;
    		tempchar=fgetc(fi);
    		j++;
		}

		tstring[j]=0;
   		Thead=Tadd(Thead, tempstring, tempc, tstring, i, j);
   		tempchar=fgetc(fi);
   		tempchar=fgetc(fi);
	}
return initialstate;
}

