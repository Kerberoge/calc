#include "calc.h"

int main ( int argc, char* argv[] )
{

    char exp[SIZE*LENGTH];
    if ( argc == 2 )
    {
        strcpy(exp, argv[1]);
    }
    else if ( argc == 1 )
    {
        printf("Please enter your expression: ");
        scanf("%s", exp);
    }
    else
    {
        printf("Warning: too many arguments provided!\n");
        exit(1);
    }



    // store the contents of the expression in a usable format
    int n = 0;
    for (int i = 0; i < strlen(exp); i++)
    {

        if ( isdigit(exp[i]) || exp[i] == '.' ) // char is a number or floating point
        {
            strncat(data[n], &exp[i], 1);
            
            if ( i + 1 < strlen(exp) && !isdigit(exp[i + 1]) && exp[i + 1] != '.' )
            {
                n++;
            }
        }
        else if ( exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '(' || exp[i] == ')' ) // char is an operator (excluding minus)
        {
            strncat(data[n], &exp[i], 1);
            n++;
        }
        else if ( exp[i] == '-' ) // char is minus
        {
            if (i == 0 || !isdigit(exp[i-1])) // minus sign is part of negative number
            {
                strncat(data[n], &exp[i], 1);
            }
            else
            {
                strncat(data[n], &exp[i], 1);
                n++;
            }
        }

    }



    // find parentheses and process them
    process_parentheses(0);



    // perform multiplication and division
    for (int i = 0; i < SIZE; i++)
    {
        if (strcmp(data[i], "*") == 0)
        {
            multiply(i);
        }
        else if (strcmp(data[i], "/") == 0)
        {
            divide(i);
        }        
    }
    
    // perform addition and substraction
    for (int i = 0; i < SIZE; i++)
    {
        if (strcmp(data[i], "+") == 0)
        {
            add(i);
        }
        else if (strcmp(data[i], "-") == 0)
        {
            subtract(i);
        }
    }



    // find out the index number of the result
    int result_index = 0;
    while (data[result_index][0] == '\0')
    {
        result_index++;
    }



    // trim zeros from result
    for ( int i = strlen( data[result_index] ) - 1; data[result_index][i] == '0'; i-- )
    {
        memset( &data[result_index][i], 0, 1 );
    }
    if ( data[result_index][ strlen(data[result_index]) - 1 ] == '.' )
    {
        memset( &data[result_index][ strlen(data[result_index]) - 1 ], 0, 1 );
    }

    

    // the end result is the first non-empty entry of data[]
    printf("%s\n", data[result_index]);



    return 0;

}