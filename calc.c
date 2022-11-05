#include "calc.h"

int main ( int argc, char* argv[] )
{



    // store the contents of argv[1] in a usable format
    int n = 0;
    for (int i = 0; i < strlen(argv[1]); i++)
    {

        if ( isdigit(argv[1][i]) || argv[1][i] == '.' ) // char is a number or floating point
        {
            strncat(data[n], &argv[1][i], 1);
            
            if ( i + 1 < strlen(argv[1]) && !isdigit(argv[1][i + 1]) && argv[1][i + 1] != '.' )
            {
                n++;
            }
        }
        else if ( argv[1][i] == '*' || argv[1][i] == '/' || argv[1][i] == '+' || argv[1][i] == '(' || argv[1][i] == ')' ) // char is an operator (excluding minus)
        {
            strncat(data[n], &argv[1][i], 1);
            n++;
        }
        else if ( argv[1][i] == '-' ) // char is minus
        {
            if (i == 0 || !isdigit(argv[1][i-1])) // minus sign is part of negative number
            {
                strncat(data[n], &argv[1][i], 1);
            }
            else
            {
                strncat(data[n], &argv[1][i], 1);
                n++;
            }
        }

    }



    // find out the highest number of decimals
    for (int i = 0; i < SIZE; i++)
    {
        if (strchr(data[i], '.') != NULL)
        {
            char* dec = strchr(data[i], '.');
            int counter = 0;

            for (int j = 0; j < strlen(dec); j++)
            {
                if (dec[j] != '.')
                {
                    counter++;
                }
            }

            if (counter > decimals)
            {
                decimals = counter;
            }
        }
    }



    // verify contents of arrays before operations
    print_arr("Contents of array before operations: ");



    // print highest number of decimals
    printf("Highest number of decimals: %d\n", decimals);



    // perform operations inside parentheses
    int start, end;
    int par_open_found, par_close_found = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (strcmp(data[i], "(") == 0) {
            par_open_found = 1;
            start = i;
        }
    }

    for (int i = SIZE - 1; i >= 0; i--)
    {
        if (strcmp(data[i], ")") == 0) {
            par_close_found = 1;
            end = i;
        }
    }

    if (par_open_found == 1 && par_close_found == 1)
    {
        parentheses(start, end);
        printf("'(' is at %d and ')' is at %d\n", start, end);
    }



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



    // verify contents of arrays after operations
    print_arr("Contents of array after operations: ");



    // find out the index number of the result
    int result_index = 0;
    while (data[result_index][0] == '\0')
    {
        result_index++;
    }



    // round result
    int dot_location;
    for (dot_location = 0; data[result_index][dot_location] != '.'; dot_location++);
    // increase the last decimal if the decimal after it is equal to or greater than 5
    if ( atof( data[result_index][dot_location + decimals + 1] ) >= 5 )
    {
        char* zeros = "0.";
        for (int j = 1; j < decimals; j++)
        {
            strncat(zeros, "0", 1);
        }
        strncat(zeros, "1", 1);

        float round_result = atof( data[result_index] );
        round_result += atof( zeros );
        sprintf( data[result_index], "%f", round_result );
    }
    // truncate the resting decimals
    

    

    // the end result is the first non-empty entry of data[]
    printf("%s\n", data[result_index]);



    return 0;

}