#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define error(...) (fprintf(stderr, __VA_ARGS__))
#define NUMBER_OF_PARAMS 2
#define MAX_SIZE_OF_LINE 1000

void adding_slash_n_symbol(char* line)
{
    int count_of_symbols = 0;
    while(line[ count_of_symbols ] != '\n' && line[ count_of_symbols ] !='\0' && count_of_symbols < MAX_SIZE_OF_LINE)
        count_of_symbols++;

    line[count_of_symbols] = '\n';
}
int comp (const void* first_line , const void* second_line) {
    const char **ia = (const char **) first_line;
    const char **ib = (const char **) second_line;
    return -strcmp(*ia, *ib);
}
void free_array(char **array , int i)
{
    for(int j = 0 ; j <= i ; j++)
    {
        free(array[j]);
    }
    free(array);
}
_Bool is_symbol_is_punctuation_mark(char symbol)
{
    if( ( symbol == '.' ) || ( symbol == ',' ) || ( symbol == ';' ) || ( symbol == ':' ) || ( symbol == '!' )
        || ( symbol == '?' ))
    {
        return 1;
    }
    else
        return 0;
}
void rewriting_symbols(char *line , int number_of_start)
{
    if(number_of_start  > MAX_SIZE_OF_LINE)
        return;
    while(line[number_of_start] != '\n' && line[number_of_start] != '\0' )
    {
        line[number_of_start] = line[number_of_start + 1];
        number_of_start ++;
    }
    line[number_of_start] = '\0';
    line[number_of_start + 1] = '\0';
}
void deleting_symbols_in_line(char *line)
{
    int number_of_symbol = 0;
    while( line[ number_of_symbol ] != '\n' && line[ number_of_symbol ] != '\0' )
    {
        if( is_symbol_is_punctuation_mark( line[ number_of_symbol ] ) )
        {
            rewriting_symbols( line , number_of_symbol );
        }
        else
        {
            number_of_symbol++;
        }
    }
}
void deleting_symbols(char **array , int const* number_of_lines)
{
    for(int i = 0 ; i < *number_of_lines ; i++)
    {
        deleting_symbols_in_line(array[ i ]);
    }
}

int main(int argc , char **argv)
{
    if(argc != NUMBER_OF_PARAMS)
    {
        error("Invalid number of arguments. Please enter %d argument\n", NUMBER_OF_PARAMS - 1);
        return -1;
    }
    FILE *input_file;
    input_file = fopen(argv[1] , "rb");
    if(input_file == NULL )
    {
        error("Can't find file %s\n" , argv[1]);
        return -1;
    }
    char **array_of_lines = (char**)malloc( sizeof(char*) * 5);
    if(array_of_lines == NULL)
    {
        error("Can't take memory\n");
        return -1;
    }
    int number_of_lines = 0;
    for(; ;)
    {
        if(number_of_lines != 0)
        {
            array_of_lines = (char**)realloc( array_of_lines , sizeof (char*) * (number_of_lines+1));
            if (array_of_lines == NULL)
            {
                fclose(input_file);
                free_array(array_of_lines , number_of_lines);
                error("Can't take memory\n");
                return -1;
            }
        }
        array_of_lines[number_of_lines] = (char*)malloc( sizeof(char) * MAX_SIZE_OF_LINE);
        if(array_of_lines[ number_of_lines ] == NULL)
        {
            fclose(input_file);
            free_array(array_of_lines , number_of_lines);
            error("Can't take memory\n");
            return -1;
        }

        if(fgets(array_of_lines[number_of_lines] , MAX_SIZE_OF_LINE , input_file) == NULL)
        {
            break;
        }

        number_of_lines++;
    }
    adding_slash_n_symbol(array_of_lines[number_of_lines - 1]);
    deleting_symbols( array_of_lines , &number_of_lines );
    qsort(array_of_lines , number_of_lines * sizeof(char) , sizeof(char *) , comp);
    int temp_for_print = 0;
    while(temp_for_print < 100 && temp_for_print < number_of_lines)
    {
        printf("%s" , array_of_lines[temp_for_print]);
        temp_for_print++;
    }
    free_array(array_of_lines , number_of_lines);
    fclose(input_file);
}