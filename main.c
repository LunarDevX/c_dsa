#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

/*
64 32 16 8 4 2 1 0
0  0  0  0 0 0 1 0

String to Long -> strol

INT_MAX and INT_MIN --> limits.h +- 2 Billion; 
size_t size in bytes -- unsigned integer


*/

char *getString(const char *format, ...);
int getInt(const char *format, ...);

int main(void)
{

    printf("\n--- DSA CLI ---\n\n");

    char *input = getString("Name one Data Structure: ");
    
    int s = getInt("Choice: ");

}


char *getString(const char* format, ...)
{   
    // Growable buffer for characters
    char *buffer = NULL;  // 0x01 

    // Capicity of buffer
    size_t capicity = 0; 

    // Number of characters actually in buffer
    size_t size = 0;

    int c; 

    if (format != NULL)
    {
        va_list ap; 

        va_start(ap, format);
        vprintf(format, ap);
        va_end(ap);

    }

    // LF (Line Feed / \n) -> Linux -- CR (Carriage Return / '\r') -> Mac -- CRLF (Carriage Return + Line Feed / '\r\n' -> Windows
    
    // fgetc -> reads the next character from stream and returns it as an unsigned char (0 -- 255) cast to an int,
    // 'A' -> 65 dec -- '\r' -> 13 -- '\n' --> 10 -- EOF --> -1 
    // stdin -> Standard Input --> lifes on RAM -> Input Buffer --> WHat is an Input Buffer? 
    // 

    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF)
    {
        if (size + 1 > capicity)
        {
            if (capicity < SIZE_MAX)
            {
                capicity++;
            }
            else
            {
                free(buffer);
                return NULL;
            }

            char *tmp = realloc(buffer, capicity); // 0x02 --> smart 

            //char *tmp = malloc(capicity); memcpy(tmp, buffer, size); free(buffer);
            

            if (tmp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = tmp; // 0x01 = 0x02 -> same chunk of memeroy on the heap -- do i overwrite 
            
        }

        buffer[size++] = c; // postfix use the old value now, change it after the line finishes
        // Prefix change it before you use it on that line)
    }

    if (size == 0 && c == EOF)
    {
        return NULL;
    }

    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    // Mainly for windows --> not that important for now 
    if (c == '\r' && (c = fgetc(stdin)) != '\n')
    {
        if (c != EOF && ungetc(c, stdin) == EOF)
        {
            free(buffer);
            return NULL;
        }
    }

    char *string = realloc(buffer, size + 1);
    if (string == NULL)
    {
        free(buffer);
        return NULL;
    }

    string[size] = '\0';

    return string;
}


int getInt(const char* format, ...)
{

    for (;;)
    {
        char *line = getString(format);

        if (line == NULL)
        {
            return INT_MAX; 
        }

        if (strlen(line) > 0 && !isspace((unsigned char) line[0]))
        {
            char *tail; 
            errno = 0;
            long n = strtol(line, &tail, 10); // ['1', '2','\0'] -> '\0'['1', '2', 'a', '\0'] -> 'a'

            if (errno == 0 && *tail == '\0' && n >= INT_MIN && n < INT_MAX)
            {
                return n; 
            }
        }
    }
}
