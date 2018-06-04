#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void append(char *str, char c)
{
	int len = strlen(str);
	str[len] = c;
	str[len+1] = '\0';
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("pass in filename as argument");
		return 0;
	}

	FILE *file = NULL;
	char *filename = argv[1];
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("could not open file %s for reading\n", filename);
		return 0;
	}

	int numLines = 0;

	char currChar;
	for (currChar = getc(file); currChar != EOF; currChar = getc(file))
	{
		if (currChar == '\n')
			numLines++;
	}

	rewind(file);

	char *first[numLines];
	char *second[numLines];

	int i = 0;
	int j = 0;
	char buffer[255];
	for (currChar = getc(file); currChar != EOF; currChar = getc(file))
	{
		if (currChar == ':')
		{
			first[i] = malloc(sizeof(buffer));
			strcpy(first[i++], buffer);
			buffer[0] = '\0';
		}
		else if (currChar == '\n')
		{
			second[j] = malloc(sizeof(buffer));
			strcpy(second[j++], buffer);
			buffer[0] = '\0';
		}
		else
		{
			int length = strlen(buffer);
			buffer[length] = currChar;
			buffer[length+1] = '\0';
		}
	}

	fclose(file);

	int exit = 0;
	int c;
	while (exit == 0)
	{
		printf("\n\n(1): Print loci list\n");
		printf("(9): Exit\n");
		printf(">");
		c = getchar();

		if (c == '\n')
			continue;

		//removing trailing newline, works but not pretty
		getchar();

		if (c == '1')
		{
			for (int j = 0; j < sizeof(first)/sizeof(first[0]); j++)
			{
				printf("%s -> %s\n", first[j], second[j]);
			}
		}

		if (c == '9')
			exit = 1;
	}

	for (int k = 0; k < numLines; k++)
	{
		free(first[i]);
		free(second[i]);
	}

	return 0;
}
