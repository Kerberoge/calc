#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*TODO:
    - floating point support
    - support for more than one set of parentheses:
        - enclosed parentheses ( ( ) )
        - parallel parentheses ( ) ( )
        - combination of the above ( ) ( ( ) )
    - run in interactive mode when called without arguments
*/

/*PSEUDO-CODE FOR COMBINATION PARENTHESES PROBLEM:

find_parentheses()
{
    search for '(' in array
    if another '(' is encountered before ')' is encountered
    {
        find_parentheses()
    }
    search for ')' in array
    when found, push index values back to an index array
}

*/

#define SIZE 16
#define LENGTH 16

char data [SIZE][LENGTH] = {0};
int decimals = 0;



void round ( int i )
{
    if (strchr(data[i], '.') != NULL)
    {
        // find out location of dot
        int dot_location;
        for (dot_location = 0; data[i][dot_location] != '.'; dot_location++);

        // increase the last decimal digit if the digit after it is equal to or greater than 5
        char* zeros = "0.";
        for (int j = 0; j < decimals - 1; j++)
        {
            strncat(zeros, '0', 1);
        }
        strncat(zeros, '1', 1);
    }
}



void multiply ( int i )
{
    int prev, next;
    for (prev = i - 1; prev > 0 && data[prev][0] == '\0'; prev--);
    for (next = i + 1; next < SIZE && data[next][0] == '\0'; next++);
    
    float temp_result = atof(data[prev]) * atof(data[next]);
    sprintf( data[prev], "%f", temp_result        ); // print temporary result to number before operator
    round  ( prev );                                 // round result
    memset ( data[i],   0,     sizeof(data[i])    ); // clear entry of operator
    memset ( data[next], 0,    sizeof(data[next]) ); // clear entry of number after operator
}



void divide ( int i )
{
    int prev, next;
    for (prev = i - 1; prev > 0 && data[prev][0] == '\0'; prev--);
    for (next = i + 1; next < SIZE && data[next][0] == '\0'; next++);

    float temp_result = atof(data[prev]) / atof(data[i+1]);
    sprintf( data[prev], "%f", temp_result       ); // print temporary result to number before operator
    memset ( data[i],   0,     sizeof(data[i])   ); // clear entry of operator
    memset ( data[i+1], 0,     sizeof(data[i+1]) ); // clear entry of number after operator
}



void add ( int i )
{
    int prev, next;
    for (prev = i - 1; prev > 0 && data[prev][0] == '\0'; prev--);
    for (next = i + 1; next < SIZE && data[next][0] == '\0'; next++);

    float temp_result = atof(data[prev]) + atof(data[i+1]);
    sprintf( data[prev], "%f", temp_result       ); // print temporary result to number before operator
    memset ( data[i],   0,     sizeof(data[i])   ); // clear entry of operator
    memset ( data[i+1], 0,     sizeof(data[i+1]) ); // clear entry of number after operator
}



void subtract ( int i )
{
    int prev, next;
    for (prev = i - 1; prev > 0 && data[prev][0] == '\0'; prev--);
    for (next = i + 1; next < SIZE && data[next][0] == '\0'; next++);

    float temp_result = atof(data[prev]) - atof(data[i+1]);
    sprintf( data[prev], "%f", temp_result       ); // print temporary result to number before operator
    memset ( data[i],   0,     sizeof(data[i])   ); // clear entry of operator
    memset ( data[i+1], 0,     sizeof(data[i+1]) ); // clear entry of number after operator
}



void parentheses ( int start, int end )
{
    for (int i = start + 1; i < end; i++)
    {
        if (strcmp(data[i], "*") == 0)
        {
            multiply(i);
        }
        else if (strcmp(data[i], "/") == 0)
        {
            divide(i);
        }
        else if (strcmp(data[i], "+") == 0)
        {
            add(i);
        }
        else if (strcmp(data[i], "-") == 0)
        {
            subtract(i);
        }               
    }
    memset ( data[start],   0, 1 ); // clear entry of first parenthesis
    memset ( data[end],     0, 1 ); // clear entry of second parenthesis
}



void print_arr ( char* str )
{
    printf("%s", str);
    for (int i = 0; i < SIZE; i++)
    {
	    printf("'%s' ", data[i]);
    }
    printf("\n");
}