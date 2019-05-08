#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar(int isString)
{
    char charValue;

    if (isString == 1){ //get random ordering or r,e,s,t
      char possibleStringValues[4] = "rest";
      charValue = possibleStringValues[rand() % 4];
    }
    else{ //get random ascii value
      int asciiTotalValues = 128;
      charValue = rand() % asciiTotalValues;
    }

    return charValue;
}

char *inputString()
{
    int isString = 1; //true
    int sLength = 6;
    char *stringVal = malloc(sLength * sizeof(char));

    //fill c-string with random chars
    int i;
    for (i = 0; i < 6; i++){
      stringVal[i] = inputChar(isString);
    }
    //put the null terminator at the end of the c-string
    stringVal[5] = '\0';

    return stringVal;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1) 
  {
    tcCount++;
    int isString = 0; //initialize isString variable to 0, false
    c = inputChar(isString);
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }

    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
