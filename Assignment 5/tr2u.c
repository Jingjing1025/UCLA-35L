//tr2u.c
//Name: Jingjing Nie
//UID: 304567417


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		write(2, "error: number of arguments should be 3\n", 39);
		exit(1);
	}

	int fromLen = strlen(argv[1]);
	int toLen = strlen(argv[2]);
	if (fromLen != toLen)
	{
		write(2, "Error: from and to should have same length\n", 43);
		exit(1);
	}

	int i = 0;
	for (; i < fromLen-1; i++)
	{
		if (argv[1][i] == argv[1][i+1])
		{
			write(2, "Error: from argument shouldn't have duplicates\n", 47);
		    exit(1);
		}
	}

	char currChar;
	while(read(0, &currChar, 1) > 0)
	{
		if (ferror(stdin))
	    {
		    write(2, "Error reading from standard input.\n", 35);
		    exit(1);
	    }

	    int found = 0;

		for (i = 0; i < fromLen; i++)
		{
			if (argv[1][i] == currChar)
			{
				write(1, &argv[2][i], 1);
				found = 1;
				break;
			}
		}
		if (found == 0)
			write(1, &currChar, 1);
	}
}