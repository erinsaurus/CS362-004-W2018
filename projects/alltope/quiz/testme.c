#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//This function simply picks a random character from the list of characters
char inputChar()
{
  char randChar = "abcdefghijklmnopqrstuvwxyz[({})] "[rand () % 33];
  return randChar;
}

//this function picks a random character from a string
char *inputString()
{
	char myChar;
    int stringSize = 6; //hardcode size of string to limit run time
    char *myString = malloc(stringSize + 1); //allocate string size +1 for null char

    for( int i = 0; i < stringSize - 1; i++ ) 
    {
        myChar = "abcdefghijklmnopqrstuvwxyz"[rand () % 26]; //pick a random char from the string
        myString[i]=myChar; //assign the char to string at i 
    }
    
    myString[6] = '\0';
    return myString;
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
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
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
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
