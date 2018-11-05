// sfrobu.c
// Name: Jingjing Nie
// UID: 304567417

#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

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

int frobcmpIgnoCase(char const* a, char const* b)
{
	if ((*a ^ 42) > UCHAR_MAX || (*b ^ 42) > UCHAR_MAX || (*a ^ 42) < 0 || (*b ^ 42) < 0) 
	{
        write(2, "Error: invalid char for toUpper\n",32);
        exit(1);
    }

	while (1)
	{
		char frob_a = toupper((unsigned)(*a^42));
		char frob_b = toupper((unsigned)(*b^42));

		if (*a == ' ' && *b == ' ')
			return 0;
		else if (*a == ' ' )
			return -1;
		else if (frob_a < frob_b)
			return -1;
		else if (*b ==' ' )
			return 1;
		else if (frob_b < frob_a)
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

int comparIgnoCase(const void *m, const void *n)
{
	const char * a = *(const char**) m;
    const char * b = *(const char**) n;
    int result = frobcmpIgnoCase(a, b);
    return result;
}

int main(int argc, char const *argv[])
{
	int fOpt = 0;
	if (argc == 2 )
	{
		if (strcmp(argv[1], "-f")==0)
		    fOpt = 1;
		else
		{
			write(2, "Error: wrong number of arguments\n", 33);
		    exit(1);
		}
	}
	if (argc > 2 )
	{
		write(2, "Error: wrong number of arguments\n", 33);
		exit(1);
	}

	struct stat filStat;
    if(fstat(0, &filStat) < 0) {
        write(2, "Error: cannot file status\n", 26);
        exit(1);
    }

    char currChar;
    char nextChar;
    int filLength = 0;
    char* word = NULL;
    char** wordArr = NULL;
    int allocWordSize = 1;
	int currWordSize = 0;
	int allocWordArrSize = 1;
	int currWordArrSize = 0;

    if (S_ISREG(filStat.st_mode))
    {
    	filLength = filStat.st_size;
    	word = (char*)malloc(sizeof(char) * (filLength+2));
    	if (word == NULL)
		{
			write(2, "Error allocating memory\n", 24);
			exit(1);
		}

    	//store the whole file
    	int currWordSize = 0;

    	while (read(0, &currChar, 1) > 0)
    	{
    		if (filStat.st_size > filLength)
    		{
    			filLength = filStat.st_size;
    			word = (char*)realloc(word, sizeof(char) * (filLength+2));
    		}
    		word[currWordSize] = currChar;
    		currWordSize++;
    	}

    	if (word[currWordSize-1] != ' ')
    	{
    		word[currWordSize] = ' ';
       		currWordSize ++;
    	}

    	//partition the stored chars into words
    	int j;
    	int k = 0;
    	int m;
    	char* temp = NULL; //temporary holder for words
    	int tempSize = 0;
    	wordArr = (char**)malloc((currWordSize) * sizeof(char*));

    	for (j = 0; j < currWordSize; j++)
    	{
    		if (word[j] == ' ')
    		{
    			temp = (char*)malloc(sizeof(char)*(filLength+2));
    			if (temp == NULL)
				{
					write(2, "Error allocating memory\n", 24);
					exit(1);
				}
    			
    			for (m = k; m <= j; m++ )
    			{
    				temp[tempSize] = word[m];
    				tempSize++;
    			}
    		
    			wordArr[currWordArrSize] = temp;
    			currWordArrSize++;

				//Reallocate the word Array if the current size is not enough
				if (allocWordArrSize <= currWordArrSize)
				{
					allocWordArrSize = allocWordArrSize * 2;
					wordArr = (char**)realloc(wordArr, (allocWordArrSize+1) * sizeof(char*));
					if (wordArr == NULL)
					{
						write(2, "Error allocating memory\n", 24);
						exit(1);
					}
				}

				tempSize = 0;
    			k = j+1;

    		}
    	}

    }
    else
    {
    	word = (char*)malloc(sizeof(char));
    	wordArr = (char**)malloc(sizeof(char*));
    	read(0, &currChar, 1);
    	int b = read(0, &nextChar, 1);
    	if (b < 0)
	    {
		    write(2, "Error reading from standard input.\n", 35);
		    exit(1);
	    }
    	int end = 0;

  	    while (b >= 0)
	    {
		  //Reallocate the word storage if the current size is not large enough
		  if (allocWordSize <= currWordSize)
		  {
			allocWordSize = allocWordSize * 2;
			word = (char*)realloc(word, (allocWordSize+1) * sizeof(char));
			//check if there is memory allocation error
			if (word == NULL)
			{
				write(2, "Error allocating memory\n", 24);
				exit(1);
			}
		  }

		  word[currWordSize] = currChar;
		  currWordSize ++;

		  if (currChar != ' ' && b == 0)
		  {
			currChar = ' ';
			word[currWordSize] = currChar;
			end = 1;
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
					write(2, "Error allocating memory\n", 24);
					exit(1);
				}
			}

			//free and empty the current word
			word = (char*)malloc(sizeof(char));
			if (word == NULL)
			{
				write(2, "Error allocating memory\n", 24);
				exit(1);
			}
			allocWordSize = 1;
			currWordSize = 0;
		  }
		  currChar = nextChar;
		  if (end == 1)
		  	break;
		  b = read(0, &nextChar, 1);
	    }

    }

    // sort the frobnicated words
    if (fOpt == 1)
    	qsort(wordArr, currWordArrSize, sizeof(char*), comparIgnoCase);
    else
	    qsort(wordArr, currWordArrSize, sizeof(char*), compar);
	
	//print out all words and free the memory
	int i = 0;
	int status = 0;
	for (; i < currWordArrSize; i++)
	{
		int j = 0;
		while (wordArr[i][j] != ' ')
		{
			status = write(1, &wordArr[i][j], 1);
			if (status < 0)
			{
				write(2, "Error reading from standard input.\n", 35);
				exit(1);
			}
			j++; 
		}
		write(1, &wordArr[i][j], 1);
		free(wordArr[i]);
	}

	//free all memory
	free(word);
	free(wordArr);
	exit(0);
}