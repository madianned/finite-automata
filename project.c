//project.c
//michael alberda
//madi dabolt
#include "init.h"
#include "distlist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


int main(int argc, char* argv[])
{
			//initiallize the lists
    struct Qnode* qhead;
		qhead=(struct Qnode*)malloc(sizeof(Qnode));
		qhead->state[0]=0;
		qhead->next=NULL;
    struct Enode* ehead;
		ehead=(struct Enode*)malloc(sizeof(Enode));
		ehead->input=0;
		ehead->next=NULL;
    struct Qnode* fhead;
		fhead=(struct Qnode*)malloc(sizeof(Qnode));
		fhead->state[0]=0;
		fhead->next=NULL;
    struct Tnode* thead;
		thead=(struct Tnode*)malloc(sizeof(Tnode));
		thead->input=0;
		thead->next=NULL;
			//makes sure that the input and output are valid terms
	if(strcmp(argv[1],"")==0 || strcmp(argv[2],"")==0)
	{
		printf("bad input\n");
		return 0;
	}
			//finds initial states and initializes the lists to have all necessary strings
	char *initstate=(char *)malloc(MAX*sizeof(char));
	strcpy(initstate,InitLists(argv[1], qhead, ehead, fhead, thead));
	
	bool a;
	int i, j, maximum, maximumt;						
	char *** parray;
	char *** iarray;	
		
	maximum=howmanystates(qhead);
	maximumt=howmanytransitions(thead);
	parray=initpartitions(qhead, ehead, fhead, thead, initstate); //creates the array parray that has the following values

	/*
	**parray[0][i] is the ith state
	**parray[1][i] is the ith final state
	**parray[2][0] is the initial state, there are no other values in parray[2]
	**parray[3][i] is the ith transition's starting position
	**parray[4][i] is the ith transition's input
	**parray[5][i] is the ith transition's ending position
	*/

			//states that cannot be reached by the initial state are deleted, along with any transitions in which they occur
	parray=deleteunreachables(maximum, maximumt, parray, initstate);
			//reduces the amount of states
	parray=reduce(maximum, maximumt, parray, howmanyE(ehead), ehead);
			//prints the values in parray to the second command line input as a file.
	printtofile(argv[2], maximum, maximumt, parray, ehead);
		
	return 1;
}

 