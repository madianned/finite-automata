//distinguish_list.h

#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>

char *** combine(int maximum, int maximumt, char ***parray, char *temp1, char *temp2);
char ***deleterepititions(char *** parray, int maxt);
char ***deleterepeatedstates(char *** parray, int max);
char ***removet(int maxt, char *** parray, char * str);
bool *checkreachables(int max, int maxt, char *** parray, char * initstate, bool * c);
char ***reduce(int qmax, int tmax, char ***parray, int imax, struct Enode*ehead);
bool canitreachafinalstate(char ***parray, int max, int maxt, char **iarray, int stringnum, char*str1);
bool doesitreachafinalstate(char ***parray, char *str1, int maxt, int max, char *input);


			//deletes any node that cannot reach a final state
char *** pdeleteunnecessary(char *** parray, int max, int maxt, char ** iarray, int stringnum)
{
	int i,inputnum; 
	for(i=0;i<max;i++)
	{
		if(canitreachafinalstate(parray, max, maxt, iarray, stringnum, parray[0][i])==0)
		{
			parray=removet(maxt, parray, parray[0][i]);
			strcpy(parray[0][i],"");
		}
	}
return parray;
}


bool canitreachafinalstate(char ***parray, int max, int maxt, char **iarray, int stringnum, char*str1)
{
	int i;
	for(i=0;i<stringnum;i++)
	{
		if(doesitreachafinalstate(parray, str1, maxt, max, iarray[i])==1)
			return 1;
	}
return 0;
}


			//deletes any node that cannot be reached by the initial state
char *** deleteunreachables(int max, int maxt, char *** parray, char * initstate)
{
	int i,j,k;
	bool* c=(bool*)malloc(max*sizeof(bool));
	
	for(i=0;i<max;i++)
	{
		c[i]=0;
		if(strcmp(parray[0][i],initstate)==0)
			c[i]=1;
	}

	for(i=0;i<maxt;i++)
	{
		if(strcmp(parray[3][i],initstate)==0)
		{
			for(j=0;j<max;j++)
			{
				if(c[j]!=1)
				{
					if(strcmp(parray[0][j],parray[5][i])==0)
					{
						c[j]=1;
						c=checkreachables(max, maxt, parray, parray[0][j],c);
					}				
				}
			}
		}
	}

	for(i=0;i<max;i++)
	{
		if(c[i]==0)
		{
			parray=removet(maxt, parray, parray[0][i]); 
			strcpy(parray[0][i],"");
		}
	}
return parray;
}


			//checks to see what states can be reached by the initial state
bool *checkreachables(int max, int maxt, char *** parray, char * initstate, bool * c)
{
	int i,j;
	
	for(i=0;i<maxt;i++)
	{
		if(strcmp(parray[3][i],initstate)==0)
		{
			for(j=0;j<max;j++)
			{
				if(c[j]!=1)
					if(strcmp(parray[0][j],parray[5][i])==0)
					{
						c[j]=1;
						c=checkreachables(max, maxt, parray, parray[0][j],c);
					}				
			}
		}
	}
return c;
}


			//removes any transitions that have a istate or fstate with str in them
char ***removet(int maxt, char *** parray, char * str)
{
	int i;
	
	for(i=0;i<maxt;i++)
	{
		if(strcmp(parray[3][i],str)==0 || strcmp(parray[5][i],str)==0)
		{
			strcpy(parray[3][i],"");
			strcpy(parray[4][i],"");
			strcpy(parray[5][i],"");
		}
	}
return parray;
}


			//checks if a string is a final state
bool isfinalstate(char ***parray, int max, char *str)
{
	int i;
	for(i=0;i<max;i++)
	{
		if(strcmp(parray[1][i],str)==0)
			return 1;
	}
return 0;
}


				//checks if a state reaches a final state given an input string
bool doesitreachafinalstate(char ***parray, char *str1, int maxt, int max, char *input)
{
	int i,j,k;
	k=0;
	char temp[MAX];
	strcpy(temp,str1);
	
	for(i=0;i<strlen(input);i++)
	{
		for(k=0;k<maxt;k++)
		{
			if(strcmp(temp,parray[3][k])==0 && parray[4][k][0]==input[i])
			{
				strcpy(temp,parray[5][k]);	
				k=maxt;
			}
		}
	}
return isfinalstate(parray,max,temp);	
}


int amountofstrings(int imax, int max)
{
	if(max==0)
		return 0;
	else
		return(pow(imax,max)+amountofstrings(imax,max-1)) ;
}	


bool dotheyhavethesametransitions(char *** parray, char *str1, char*str2, int max, int maxt)
{
	int i,j;
	bool c;
	
	for(i=0;i<maxt;i++)
	{	
		if(strcmp(parray[3][i],"")!=0)
		{
			c=0;
			if(strcmp(str1,parray[3][i])!=0)
				continue;
			
			for(j=0;j<maxt;j++)
			{
				if(strcmp(parray[3][j],"")!=0)
				{
					if(strcmp(str2,parray[3][j])!=0)
						continue;
					else if(strcmp(parray[4][i],parray[4][j])==0)
					{
						c=1;
						break;
					}
				}
			}
			if(c==0)
				return 0;
		}
	}
return 1;
}


				//checks if two states are distinguishable
bool distinguishable(char *str1, char * str2, char *** parray, int maxt, int max, char ** iarray, int stringnum)
{
	int i,j;
	bool c;
	
	for(i=0;i<stringnum-1;i++)
	{
		for(j=0;j<strlen(iarray[i]);j++)
		{
			if(doesitreachafinalstate(parray, str1, maxt, max, iarray[i])!=doesitreachafinalstate(parray, str2, maxt, max, iarray[i]))
				return 1;
			if(dotheyhavethesametransitions(parray,str1,str2,max,maxt)==0 || dotheyhavethesametransitions(parray,str2,str1,max,maxt)==0)
				return 1;		
		}		
	}
	
	if(doesitreachafinalstate(parray, str1, maxt, max, iarray[i])!=doesitreachafinalstate(parray, str2, maxt, max, iarray[i]))
		return 1;
	
return 0;
}


					//full reduction function, calls all other ones.
char ***reduce(int max, int maxt, char ***parray, int imax, struct Enode*ehead)
{
	char*inputarray=malloc(imax*sizeof(char));
	int i,j,k,z,stringnum;
	z=0;j=0;k=0;
	bool c;
	
	for(i=0;i<imax;i++)
	{
		inputarray[i]=ehead->input;
		ehead=ehead->next;
	}
	
	stringnum=amountofstrings(imax, max)+1;
	char **iarray=malloc(stringnum*sizeof(char*));
	
	for(i=0;i<stringnum;i++)
	{
		iarray[i]=malloc(MAX*sizeof(char));
	}
	
	iarray[stringnum-1]="";
	for(i=0;i<stringnum-1;i++)
	{
		if(imax>1)
		{
			if(i<imax)
			{			
				iarray[i][0]=inputarray[k];
				iarray[i][1]=0;
			}	
			else
			{	
				strcpy(iarray[i],iarray[z]);
				iarray[i]=strcat(iarray[i],iarray[k]);
				
				if(i%imax==1)
					z++;
			}
		}
		else
		{
			if(i==0)
			{
				iarray[i][0]=inputarray[0];
				iarray[i][1]=0;
			}
			else
			{
				strcpy(iarray[i],iarray[i-1]);
				iarray[i]=strcat(iarray[i],iarray[0]);
			}		
		}
	j++;
	k++;
	k=k%imax;
	}
	
	parray=pdeleteunnecessary(parray,max,maxt,iarray,stringnum);

	for(k=1;k>=0;k--)
	{
		do{
			c=0;
		
			for (i=0;i<max;i++)
			{
				for(j=0;j<max;j++)
				{
					if(i!=j)
					{
						if(strcmp(parray[k][i],"")!=0 && strcmp(parray[k][i],"")!=0 && parray[k][i][0]!=0 && parray[k][j][0]!=0)
							if(distinguishable(parray[k][i],parray[k][j], parray, maxt, max, iarray, stringnum)==0)
							{	
								parray=combine(max, maxt, parray, parray[k][i], parray[k][j]);
								c=1;
								parray=deleterepeatedstates(parray, max);
								parray=deleterepititions(parray, maxt);
							}
					}
				}
			}
  		}while(c==1);
	}
		
	parray=deleterepititions(parray, maxt);
return parray;
}


			//deletes repeated transitions
char ***deleterepititions(char *** parray, int maxt)
{	
	int i,j;
	
	for(i=0;i<maxt;i++)
	{
		for(j=0;j<maxt;j++)
		{
			if(i!=j)
			{
				if(strcmp(parray[3][i],parray[3][j])==0 && strcmp(parray[4][i],parray[4][j])==0 && strcmp(parray[5][i],parray[5][j])==0) 	
				{
					strcpy(parray[3][i],"");
					strcpy(parray[4][i],"");
					strcpy(parray[5][i],"");
				}
			}
		}
	}
return parray;
}


				//deletes repeated states
char ***deleterepeatedstates(char *** parray, int max)
{	
	int i,j;
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			if(i!=j)
			{
				if(strcmp(parray[0][i],parray[0][j])==0) 	
					strcpy(parray[0][i],"");
				if(strcmp(parray[1][i],parray[1][j])==0) 	
					strcpy(parray[1][j],"");
			}
		}
	}
return parray;
}
			

					//combines two states and their transitions
char *** combine(int maximum, int maximumt, char ***parray, char *temp1, char *temp2)
{
	char temp[MAX];
	char str1[MAX];
	char str2[MAX];
	strcpy(str1, temp1);
	strcpy(str2, temp2);
	strcat(temp, str2);	
	int i;
	
	for(i=0;i<maximum;i++)
	{
		if(strcmp(parray[0][i],str1)==0)
			strcpy(parray[0][i],temp);
		if(strcmp(parray[0][i],str2)==0)
			strcpy(parray[0][i],temp);

		if(strcmp(parray[1][i],str1)==0)
			strcpy(parray[1][i],temp);
		if(strcmp(parray[1][i],str2)==0)
			strcpy(parray[1][i],temp);
	}
	
	if(strcmp(parray[2][0],str1)==0 || strcmp(parray[2][0],str2)==0)
		strcpy(parray[2][0],temp);
	
	for(i=0;i<maximumt;i++)
	{	
		if(strcmp(parray[3][i],str1)==0)
			strcpy(parray[3][i],temp);
		if(strcmp(parray[5][i],str1)==0)
			strcpy(parray[5][i],temp);
		
		if(strcmp(parray[3][i],str2)==0)
			strcpy(parray[3][i],temp);
		if(strcmp(parray[5][i],str2)==0)
			strcpy(parray[5][i],temp);
	}
	
	parray=deleterepeatedstates(parray, maximum);
return parray;
}


				//prints output to output.txt file.
void printtofile(char * output, int max, int maxt, char ***parray, struct Enode*ehead)
{
	int i;
	bool haveprinted;
	haveprinted=0;
	FILE *fo;
	char *outputname=output;   
	fo=fopen(outputname, "w");
	
	fprintf(fo,"Q={");
		for(i=0;i<max;i++)
		{
			if(strcmp(parray[0][i],"")!=0)
			{
				fprintf(fo, "%s",parray[0][i]);	
				haveprinted=1;
			}
			if(i<max-1)
			{
				if(strcmp(parray[0][i+1],"")!=0 && haveprinted==1)
					fprintf(fo, ",");
			}
		}
	
	fprintf(fo,"}\nE={");
	while(ehead!=NULL)
	{
		fprintf(fo,"%c",ehead->input);
		if(ehead->next!=NULL)fprintf(fo,",");
			ehead=ehead->next;
	}
	haveprinted=0;
	
	fprintf(fo,"}\nq={");
		fprintf(fo, "%s",parray[2][0]);
	fprintf(fo,"}\nF={");
		for(i=0;i<max;i++)
		{
			if(strcmp(parray[1][i],"")!=0)
			{
				fprintf(fo, "%s",parray[1][i]);
				haveprinted=1;
			}
			if(i<max-1)
			{
				if(strcmp(parray[1][i+1],"")!=0)
				fprintf(fo, ",");
			}
		}

	fprintf(fo,"}\nD=\n");
	fprintf(fo,"{\n");
		for(i=0;i<maxt;i++)
		{
			if(strcmp(parray[3][i],"")!=0 && strcmp(parray[4][i],"")!=0 && strcmp(parray[5][i],"")!=0)
			{	
				fprintf(fo, "(%s,%s)->(%s)\n",parray[3][i],parray[4][i],parray[5][i]);
			}
		}

	fprintf(fo,"}\n");
}	

