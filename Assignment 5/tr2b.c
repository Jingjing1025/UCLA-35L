//tr2b.c
//Name: Jingjing Nie
//UID: 304567417

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Error: number of arguments should be 3\n");
		exit(1);
	}

	int fromLen = strlen(argv[1]);
	int toLen = strlen(argv[2]);
	if (fromLen != toLen)
	{
		fprintf(stderr, "Error: from and to should have same length\n");
		exit(1);
	}

	int i = 0;
	for (; i < fromLen-1; i++)
	{
		if (argv[1][i] == argv[1][i+1])
		{
			fprintf(stderr, "Error: from arguments shouldn't have duplicates\n");
		    exit(1);
		}
	}

	char currChar = getchar();
	while(currChar != EOF)
	{
		if (ferror(stdin))
	    {
		    fprintf(stderr, "Error reading from standard input.\n");
		    exit(1);
	    }

	    int found = 0;

		for (i = 0; i < fromLen; i++)
		{
			if (argv[1][i] == currChar)
			{
				putchar(argv[2][i]);
				found = 1;
				break;
			}
		}
		if (found == 0)
			putchar(currChar);
		currChar = getchar();
	}
}