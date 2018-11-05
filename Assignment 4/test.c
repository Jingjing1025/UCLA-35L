// //
// //  sfrob.c
// //
// //  Christopher Aziz
// //  UID 304806012
// //  Oct. 27, 2017
// //
// //  Homework: Sorting encrypted text
// //  --------------------------------
// //  Takes frobnicated words from
// //  stdin, sorts them, and prints
// //  them to stdout without ever
// //  storing unfrobnicated  words in
// //  memory.
// //
/*
#include <stdio.h>
#include <stdlib.h>

void checkIOError() {
    if(ferror(stdin)) {
        fprintf(stderr, "Error reading from stdin");
        exit(1);
    }
}

void checkMemError(void* ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Error in memory allocation");
        exit(1);
    }
}

// compare frobnicated c strings that end in a space
int frobcmp(char const *a, char const *b)
{
    // compare words char by char or until space is reached
    while(1) {
        if(*a == ' ' && *b == ' ') return 0;
        if((*a ^ 42) > (*b ^ 42) || *b == ' ') return 1;
        if((*b ^ 42) > (*a ^ 42) || *a == ' ') return -1;
        a++;
        b++;
    }
}

// wrapper function for qsort that takes pointers to c strings
int frobcmpWrapper(const void* a_ptr, const void* b_ptr) {
    const char* a = *(const char**)a_ptr;
    const char* b = *(const char**)b_ptr;
    return frobcmp(a,b);
}

int main() {
    // buffer to build each word
    char* buffer = (char*) malloc(sizeof(char));
    int buffer_size = 1;
    int buffer_index = 0;
    
    // array of unsorted frobnicated words
    char** frob_words = (char**) malloc(sizeof(char*));;
    int words_size = 1;
    int words_index = 0;
    
    // current character
    char cur_char = getchar();
    // boolean if reached EOF
    int end_of_file = 0;
    
    // continuously get characters until EOF
    while(cur_char != EOF) {
        // cur_char = getchar();
        checkIOError();

        // if EOF, append a space to the last word
        // if(cur_char == EOF) {
        //     end_of_file = 1;
        //     cur_char = ' ';
        // }

        // add current char to buffer
        buffer[buffer_index] = cur_char;
        buffer_index++;

        // if buffer is too small, double buffer size
        if(buffer_size <= buffer_index) {
            buffer_size *= 2;
            buffer = (char*)
                realloc(buffer, sizeof(char) * buffer_size);
            checkMemError(buffer);
        }
        
        // add current char to buffer
        // buffer[buffer_index++] = cur_char;
        
        // if the character was a space,
        // add buffer to frob_words and reset buffer
        if(cur_char == ' '){

            // add word from buffer to frob_words
            frob_words[words_index++] = buffer;

            // if frob_words is too small, double frob_words size
            if(words_size <= words_index) {
                words_size *= 2;
                frob_words = (char**)
                    realloc(frob_words, sizeof(char*) * words_size);
                checkMemError(frob_words);
            }
            // add word from buffer to frob_words
            // frob_words[words_index++] = buffer;
            
            // reset buffer for next word
            buffer = (char*) malloc(sizeof(char));
            checkMemError(buffer);
            buffer_size = 1;
            buffer_index = 0;
        }
        cur_char = getchar();
    }
    
    // sort frobnicated words from buffer
    qsort(frob_words, words_index, sizeof(char*), &frobcmpWrapper);
    
    // print frobnicated words in unfrobnicated sorted order
    for(int i = 0; i < words_index; i++) {
        for(int j = 0;;j++) {
            putchar(frob_words[i][j]);
            checkIOError();
            if(frob_words[i][j] == ' ') break;
        }
    }
    
    // free memory and exit
    free(buffer);
    for(int i = 0; i < words_index; i++)
        free(frob_words[i]);
    free(frob_words);
    exit(0);
}


// Name: Arpit Jasapara, UID: 504742401

#include<stdio.h>
#include<stdlib.h>

int frobcmp(const void* a, const void* b)
{
    char const * achar = *(char const **) a;
    char const * bchar = *(char const **) b;
    while (100 < 101) { // keeps loop running until value returned
        char froba = *achar ^ 42;
        char frobb = *bchar ^ 42;
        if (*achar == ' ' && *bchar == ' ') { 
            return 0;
        }
        else if (*achar == ' ' || froba < frobb) { 
            return -1; 
        }
        else if (*bchar == ' ' || froba > frobb) { 
            return 1; 
        }
        achar++;
        bchar++;
  }
}

void inputError(){
    fprintf(stderr, "Input Error!");
    exit(1);
}

void memoryError(){
    fprintf(stderr, "Memory Allocation Error!");
    exit(1);
}

int main (void) {
    char* curr = (char*) malloc (sizeof(char)); // current word
    char** arr = (char**) malloc (sizeof(char*)); // array of words
    int currSize = 1;
    int arrSize = 1;
    int currCount = 0;
    int arrCount = 0;
    char c, n;
    c = getchar(); // gets first/current character
    if (ferror(stdin))
        inputError();

    while(c != EOF) {   
        n = getchar(); // gets next character to check for repeating spaces/EOF
        if (ferror(stdin))
            inputError();

        if (currCount >= currSize-1){ // reallocates current word if more space is needed
            currSize *= 2;
            char* temp = realloc(curr, sizeof(char) * currSize);
            if (temp == NULL)
                memoryError();
            curr = temp;
        }
        curr[currCount] = c; // puts current character in current word

        if (c == ' ') { // puts curr in arr if end of word (space)
            if (arrCount >= arrSize-1) { // reallocates arr if more space is needed
                arrSize *= 2;
                char** tempArr = realloc(arr, sizeof(char*) * arrSize);
                if (tempArr == NULL)
                    memoryError();
                arr = tempArr;
            }
            arr[arrCount] = curr;
            arrCount++;
            curr = (char*) malloc (sizeof(char)); // starts over current word and stats
            currSize = 1;
            currCount = -1;
        }

        if (c == ' ' && n == ' ') { // if repeating spaces are encountered
            while (c == ' ') {
                c = getchar();
                if (ferror(stdin))
                    inputError();
            }
            n = c;
        }
        else if (n == EOF && c != ' '){ // if last character is not a space
            curr[++currCount] = ' ';
            arr[arrCount] = curr;
            arrCount++;
        }

        c = n;
        currCount++;
    }

    // qsort(arr, arrCount, sizeof(char*), frobcmp);

    int i;
    for (i = 0; i < arrCount; i++){
        int j;
        for (j = 0; arr[i][j] != ' '; j++)
            putchar(arr[i][j]);
        free(arr[i]);
        putchar(' ');
    }
    free(arr);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char decodeIt(const char character)
{
  return character^42;
}
//Finds problems with input or output
void findError(){
  if(ferror(stdin))
  {
    fprintf(stderr, "Error reading");
    exit(1);
  }
}

//Decode it fam 
int frobcmp (char const *a, char const *b)
{
    for(;; a++, b++)
    {
      if (*a == ' ' && *b == ' ')
      {
    return 0;
      }
      else if (*a == ' ')
      {
    return -1; 
      }
      else if(decodeIt(*a) < decodeIt(*b))
      {
    return -1;
      }
      else if (*b == ' ')
      {
    return 1;
      }
      else if(decodeIt(*a) > decodeIt(*b))
      {
    return 1;
      }
    }
}
//Compare the two characters
int cmp( const void* check1, const void* check2)
{
  char const* first = *(const char **) check1;
  char const* second = *(const char **) check2;

  return frobcmp(first,second);
}


int main(void)
{
  char* currentW;
  char** allWords;

  currentW = (char*)malloc(sizeof(char)); //Pointers to A word
  allWords = (char**)malloc(sizeof(char*)); //Pointer to hold multiple words. 
  //Check for error. 
  if (currentW == NULL || allWords == NULL){
    fprintf(stderr, "Error");
    exit(1);
  }
  
  int lNumber = 0;
  int wNumber = 0;
  
  char currentChar = getchar();
  findError();
  char nextChar = getchar();
  findError();

  while (currentChar != EOF)
  {
    currentW[lNumber] = currentChar;

    char* temparray = realloc(currentW, sizeof(char) * (lNumber + 2));

    if (temparray == NULL)
    {
      free(currentW);
      fprintf(stderr, "Error leak in memory");
      exit(1);
    }
    currentW = temparray;
    
    //If we hit the end of the word. 
    if (currentChar == ' ')
    {
      allWords[wNumber] = currentW;

      char** adder = realloc(allWords, (wNumber + 2)* sizeof(char*));

      if (adder != NULL)
      {
    allWords = adder;
    currentW = NULL;
    currentW = (char*)malloc(sizeof(char));
        lNumber = -1;
    wNumber+=1;
      }
      else{
    free(currentW);
    fprintf(stderr, "Error leak in memory");
    exit(1);
      }
    }

    if (nextChar == EOF && currentChar == ' ')
      break;

    else if(currentChar == ' ' && nextChar == ' ')
    {
      for(;;)
      {
    if (currentChar != ' ')
      break;
    else {
      currentChar = getchar();
      findError();
    }
      }

      nextChar = getchar();
      findError();
      lNumber++;
      continue;
    }
    else if(nextChar == EOF)
    {
      currentChar = ' ';
      lNumber++;
      continue;
    }

    currentChar = nextChar;
    nextChar = getchar();
    findError();
    lNumber +=1;
  }

  qsort(allWords, wNumber, sizeof(char*), cmp);

  size_t outer;
  size_t inner;

  for (outer = 0; outer < wNumber; outer++)
  {
    for (inner = 0;; inner++)
    {
        putchar(allWords[outer][inner]);
        findError();
    if (allWords[outer][inner] == ' ')
      break;
    }
  }

  long final;

  for (final = 0; final < wNumber; final++)
  {
    free(allWords[final]);
  }
  free(allWords);
  
  return 0;
}
*/
/*
#include <stdio.h>
#include <stdlib.h>

void checkIOError() {
    if(ferror(stdin)) {
        fprintf(stderr, "Error reading from stdin");
        exit(1);
    }
}

void checkMemError(void* ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Error in memory allocation");
        exit(1);
    }
}

// compare frobnicated c strings that end in a space
int frobcmp(char const *a, char const *b)
{
    // compare words char by char or until space is reached
    while(1) {
        if(*a == ' ' && *b == ' ') return 0;
        if((*a ^ 42) > (*b ^ 42) || *b == ' ') return 1;
        if((*b ^ 42) > (*a ^ 42) || *a == ' ') return -1;
        a++;
        b++;
    }
}

// wrapper function for qsort that takes pointers to c strings
int frobcmpWrapper(const void* a_ptr, const void* b_ptr) {
    const char* a = *(const char**)a_ptr;
    const char* b = *(const char**)b_ptr;
    return frobcmp(a,b);
}

int main(int argc, const char * argv[]) {
    // buffer to build each word
    char* buffer = (char*) malloc(sizeof(char));
    int buffer_size = 1;
    int buffer_index = 0;
    
    // array of unsorted frobnicated words
    char** frob_words = (char**) malloc(sizeof(char*));;
    int words_size = 1;
    int words_index = 0;
    
    // current character
    char cur_char;
    // boolean if reached EOF
    int end_of_file = 0;
    
    // continuously get characters until EOF
    while(!end_of_file) {
        cur_char = getchar();
        checkIOError();

        // if EOF, append a space to the last word
        if(cur_char == EOF) {
            end_of_file = 1;
            cur_char = ' ';
        }
        
        // if buffer is too small, double buffer size
        if(buffer_size <= buffer_index) {
            buffer_size *= 2;
            buffer = (char*)
                realloc(buffer, sizeof(char) * buffer_size);
            checkMemError(buffer);
        }
        
        // add current char to buffer
        buffer[buffer_index++] = cur_char;
        
        // if the character was a space,
        // add buffer to frob_words and reset buffer
        if(cur_char == ' '){
            // if frob_words is too small, double frob_words size
            if(words_size <= words_index) {
                words_size *= 2;
                frob_words = (char**)
                    realloc(frob_words, sizeof(char*) * words_size);
                checkMemError(frob_words);
            }
            // add word from buffer to frob_words
            frob_words[words_index++] = buffer;
            
            // reset buffer for next word
            buffer = (char*) malloc(sizeof(char));
            checkMemError(buffer);
            buffer_size = 1;
            buffer_index = 0;
        }
    }
    
    // sort frobnicated words from buffer
    qsort(frob_words, words_index, sizeof(char*), &frobcmpWrapper);
    
    // print frobnicated words in unfrobnicated sorted order
    for(int i = 0; i < words_index; i++) {
        for(int j = 0;;j++) {
            putchar(frob_words[i][j]);
            checkIOError();
            if(frob_words[i][j] == ' ') break;
        }
    }
    
    // free memory and exit
    free(buffer);
    for(int i = 0; i < words_index; i++)
        free(frob_words[i]);
    free(frob_words);
    exit(0);
}
*/

#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const * b) {
    for (;; a++, b++) {
        if (*a == ' ' && *b == ' ') {
            return 0;
        }
        else if (*a == ' ' || (*a ^ 42) < (*b ^ 42)) {  // decoding 00101010
            return -1;
        }
        else if (*b == ' ' || (*b ^ 42) < (*a ^ 42)) {
            return 1;
        }
    }
}

// compare the two input characters
int cmp(const void* input1, const void* input2) {
    char const * a = *(char const**) input1;
    char const * b = *(char const**) input2;
    return frobcmp(a, b);
}

void catchReadError()
{
    if(ferror(stdin))
    {
        fprintf(stderr, "Error reading file");
        exit(1);
    }
}

// while it's not the end of the file, keep getchar until you reach the end of the file. Output any errors you get and exit(1)
// Everytime you add anything to the line, add 1 to the amount to allocate
int main() {
    char* word;
    char** wordsPointer;
    int lCount = 0;
    int wCount = 0;
    word = (char*) malloc(sizeof(char));
    wordsPointer = (char**) malloc(sizeof(char*));

    //get two characters at a time so it's easier to handle end of file situations
    char currChar = getchar();
    catchReadError();
    char next = getchar();
    catchReadError();

    int resetLCount = 0;

    while(currChar != EOF && !ferror(stdin)) {
        word[lCount] = currChar;
        char* temp = realloc(word, (lCount+2)*sizeof(char));    // lCount + 2 because index is one less than actual element #,
                                                        //and allocate an extra space for the next char
        if (temp != NULL) {
            word = temp;
        }
        else {
            free(word);
            fprintf(stderr, "Error allocating memory");
            exit(1);
        }

        // handle empty files
        if (currChar == EOF) {
            exit(0);
        }

        if (currChar == ' ') {
            wordsPointer[wCount] = word;
            char** tempWord = realloc(wordsPointer, (wCount+2) * sizeof(char*));
            if (tempWord != NULL) {
                wordsPointer = tempWord;
                wCount++;
                word = NULL;
                word = (char* ) malloc(sizeof(char));
                resetLCount = 1;
            }
            else {
                free(wordsPointer);
                fprintf(stderr, "Error allocating memory");
                exit(1);
            }

            if (next == EOF) {
                //catch case if there's only 1 space
                if (wCount == 1 && lCount == 0) {
                    exit(0);
                }
                break;  // added the last space
            }
            if (next == ' ') {
                while (currChar == ' ') {
                    currChar = getchar();
                    catchReadError();
                }
                next = getchar();
                catchReadError();
                // check for file with only spaces: 
//lCount hasn't been reset yet, if only one letter then previous line was only spaces
                if (currChar == EOF && wCount == 1 && lCount == 0) {   // only added one word: of all spaces
                    exit(0);
                }
                resetLCount ? lCount = 0 : lCount++;
                resetLCount = 0;
                continue;
            }
        }

        else if (next == EOF) { // currChar is not ' ', need to add a space
            currChar = ' ';
            lCount++;
            continue;
        }

        currChar = next;
        next = getchar();
        catchReadError();
        resetLCount ? lCount = 0 : lCount++;
        resetLCount = 0;
    }

    qsort(wordsPointer, wCount, sizeof(char*), cmp);

    // output everything in the words array
    for (size_t i = 0; i < wCount; i++){
        for (size_t j = 0; ; j++) {
            if (putchar(wordsPointer[i][j]) == EOF) {
                fprintf(stderr, "Error writing output");
                exit(1);
            }
            if (wordsPointer[i][j] == ' ') {
                break;
            }
        }
    }

    // deallocate all the space allocated using malloc
    for (size_t i = 0; i < wCount; i++) {
        free(wordsPointer[i]);
    }
    free(wordsPointer);

    exit(0);
}