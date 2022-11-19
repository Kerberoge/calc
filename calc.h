#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 32
#define LENGTH 8

char data [SIZE][LENGTH] = {0};



void multiply ( int i )
{
    int prev, next;
    for (prev = i - 1; prev > 0 && data[prev][0] == '\0'; prev--);
    for (next = i + 1; next < SIZE && data[next][0] == '\0'; next++);
    
    float temp_result = atof(data[prev]) * atof(data[next]);
    sprintf( data[prev], "%f", temp_result        ); // print temporary result to number before operator
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



void calculate_parentheses ( int start, int end )
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



void process_parentheses ( int location )
{
    for ( int i = location; i < SIZE; i++ )
    {
        if ( strchr(data[i], '(') != NULL )
        {
            for (int j = i+1; j < SIZE; j++)
            {
                if ( strchr(data[j], '(') != NULL )
                {
                    process_parentheses(j);
                }
                else if ( strchr(data[j], ')') != NULL )
                {
                    calculate_parentheses(i,j);
                    break;
                }
            }
        }
    }
}


/*
void print_arr ( char* str )
{
    printf("%s", str);
    for (int i = 0; i < SIZE; i++)
    {
	    printf("'%s' ", data[i]);
    }
    printf("\n");
}
*/