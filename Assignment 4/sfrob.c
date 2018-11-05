// sfrob.c
// Name: Jingjing Nie
// UID: 304567417

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// int counter = 0;

int frobcmp(char const* a, char const* b)
{
	// counter++;
	while (1)
	{
		if (*a == ' ' && *b == ' ')
			return 0;
		else if (*a == ' ' )
			return -1;
		else if ((*a^42) < (*b^42))
			return -1;
		else if (*b ==' ' )
			return 1;
		else if ((*b^42) < (*a^42))
			return 1;
		a++;
		b++;
	}
}

int compar(const void *m, const void *n)
{
	const char * a = *(const char**) m;
    const char * b = *(const char**) n;
    int result = frobcmp(a, b);
    return result;
}

int main(void)
{
	char* word = (char*)malloc(sizeof(char));
	char** wordArr = (char**)malloc(sizeof(char*));

	int allocWordSize = 1;
	int currWordSize = 0;
	int allocWordArrSize = 1;
	int currWordArrSize = 0;

	// get current character
	char currChar = getchar();
	// get next character
	char nextChar = getchar();

	while (1)
	{
		if (ferror(stdin))
	    {
		    fprintf(stderr, "Error reading from standard input.\n");
		    exit(1);
	    }

		//Reallocate the word storage if the current size is not large enough
		if (allocWordSize <= currWordSize)
		{
			allocWordSize = allocWordSize * 2;
			word = (char*)realloc(word, (allocWordSize+1) * sizeof(char));
			//check if there is memory allocation error
			if (word == NULL)
			{
				fprintf(stderr, "Error allocating memory\n");
				exit(1);
			}
		}

		word[currWordSize] = currChar;
		currWordSize ++;

		if (currChar != ' ' && nextChar == EOF)
		{
			currChar = ' ';
			word[currWordSize] = currChar;
		}

		//put the word into word array if the character reaches the ending byte
		if (currChar == ' ')
		{
			wordArr[currWordArrSize] = word;
			currWordArrSize++;

			//Reallocate the word Array if the current size is not enough
			if (allocWordArrSize <= currWordArrSize)
			{
				allocWordArrSize = allocWordArrSize * 2;
				wordArr = (char**)realloc(wordArr, (allocWordArrSize+1) * sizeof(char*));
				if (wordArr == NULL)
				{
					fprintf(stderr, "Error allocating memory\n");
					exit(1);
				}
			}

			//free and empty the current word
			word = (char*)malloc(sizeof(char));
			if (word == NULL)
			{
				fprintf(stderr, "Error allocating memory\n");
				exit(1);
			}
			allocWordSize = 1;
			currWordSize = 0;
		}

		currChar = nextChar;
		if (currChar == EOF)
			break;
		nextChar = getchar();
	}

    //sort the frobnicated words
	qsort(wordArr, currWordArrSize, sizeof(char*), compar);
	// printf("%d\n", counter);
	//print out all words and free the memory
	int i = 0;
	for (; i < currWordArrSize; i++)
	{
		int j = 0;
		while (wordArr[i][j] != ' ')
		{
			putchar(wordArr[i][j]);
			if (ferror(stdin))
			{
				fprintf(stderr, "Error reading from standard input.\n");
				exit(1);
			}
			j++; 
		}
		putchar(' ');
		free(wordArr[i]);
	}

	//free all memory
	free(word);
	free(wordArr);
	exit(0);
}