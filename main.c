#include <stdio.h>
#include <string.h>

struct Pair
{
	char first[25];
	char second[25];
};

struct Pair createPair(char first[], char second[])
{
	struct Pair newPair;
	strcpy(newPair.first, first);
	strcpy(newPair.second, second);
	return newPair;
}

void populateList(struct Pair * list,  char filePath[])
{
	FILE *file;
	file = fopen(filePath, "r");

	int i = 0;
	char buffer[25];
	while (fgets(buffer, 25, file))
	{
		char test[25];
		memset(test, 0, 25);
		strncpy(test, buffer, strlen(buffer)-1);

		char *token;
		token = strtok(buffer, ":");
		list[i] = createPair(token, strtok(NULL, "\n"));
		i++;
	}

	fclose(file);
}

void printList(struct Pair * list, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s -> %s\n", list[i].first, list[i].second);
	}
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("pass in filename as argument");
		return 0;
	}

	struct Pair lociList[52];

	populateList(lociList, argv[1]);

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
			printList(lociList, sizeof(lociList)/sizeof(lociList[0]));

		if (c == '9')
			exit = 1;
	}
	
	return 0;
}
