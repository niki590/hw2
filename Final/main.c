
//  main.c
//  Mamat2
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SocialNetwork.h"

#define MAX_LEN 256
#define TK " \n\t"

//*****************************************************
//* function name : Remove
//* Description :	gets 2 names of users in netwrok and
//*					deletes the friend relationship between them
//* Parameters : input1 - first name , input2- second name
//* return value : NA
//*****************************************************
void Remove(char* input1, char* input2)
{
	if (input1 == NULL || input2 == NULL)
	{
		fprintf(stderr,"Remove Relationship failed: not enough parameters\n");
		return;
	}
	Result achieved = Network_removeRelationship(input1, input2);
	if (!achieved)
	{
		fprintf(stderr, "Remove Relationship execution failed\n");
		return;
	}
}

//*****************************************************
//* function name : Add
//* Description :	gets 2 names of users in netwrok and
//*					creates the friend relationship between them
//* Parameters : input1 - first name , input2- second name
//* return value : NA
//*****************************************************
void Add(char* input1, char* input2)
{
	if (input1 == NULL || input2 == NULL)
	{
		fprintf(stderr, "Add Relationship failed: not enough parameters\n");
		return;
	}
	Result achieved = Network_addRelationship(input1, input2);
	if (!achieved)
	{
		fprintf(stderr, "Add Relationship execution failed\n");
		return;
	}
}

//*****************************************************
//* function name : main
//* Description :	get commands and execute them until EOF or Exit
//* Parameters : none
//* return value : 0 for success 1 for some failure in way
//*****************************************************
int main()
{
	Result is_first = SUCCESS;
	char line[MAX_LEN];
	char *command;
	while (fgets(line, MAX_LEN, stdin))
	{
		command = strtok(line, TK);
		char *splited[3];
		for (int i = 0; i < 3; i++)
			splited[i] = NULL;
		int counter = 0;
		if (command == NULL)
			continue;
		while ((command != NULL)&&(counter<3))
		{
			splited[counter] = command;
			command = strtok(NULL, TK);
			counter++;
		}
		if (!strcmp(splited[0], "Insert")) //Inert cmd
		{
			if (is_first) 			   //check if the first  
			{
				if (splited[2] == NULL)
				{
					Network_addUser(splited[1], NULL);
					is_first = FAILURE;
				}
				else
				{
					fprintf(stderr, "Insert failed: not enough parameters\n");
					continue;
				}

			}
			else
			{
				if ((splited[1] == NULL) || (splited[2] == NULL))
				{
					fprintf(stderr, "Insert failed: not enough parameters\n");
					continue;
				}
				if (!Network_addUser(splited[1], splited[2]))
				{
					fprintf(stderr, "Insert User execution failed\n");
					continue;
				}
			}
		}
		else if (!strcmp(splited[0], "Add"))
			Add(splited[1], splited[2]);
		else if (!strcmp(splited[0], "Remove"))
			Remove(splited[1], splited[2]);
		else if (!strcmp(splited[0], "Print"))
			Network_print();
		else if (!strcmp(splited[0], "Exit"))
		{
			Network_delete();
			return 1;
		}
		else
		{
			fprintf(stderr, "Command not found\n");
		}
	}
	Network_delete();
	return 0;
}