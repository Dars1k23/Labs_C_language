#include <stdio.h>
#include <stdlib.h>
#define PROMPT "|<*>_<*>| ->"
#define DELIM " \t"


int is_delim(char c, const char *delim) {
    while (*delim != '\0') {
        if (c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *my_strtok(char *str, const char *delim) {
    static char *current = NULL;

    if (str != NULL) {
        current = str;
    }

    if (current == NULL || *current == '\0') {
        return NULL;
    }

    while (*current && is_delim(*current, delim)) {
        current++;
    }

    if (*current == '\0') {
        return NULL;
    }

    char *start = current;

    while (*current && !is_delim(*current, delim)) {
        current++;
    }

    if (*current != '\0') {
        *current = '\0';
        current++;
    }

    return start;
}


int my_strlen(const char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

char *my_strdup(const char *str) {
    int len =  my_strlen(str);
    char *res = malloc((len + 1) * sizeof(char));
    if (res == NULL) {
        return NULL;
    }
    int i = 0;
    while (str[i] != '\0') {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';

    return res;
}



char *my_readline(void) {
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    fputs(PROMPT, stdout);
    fflush(stdout);

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        
        if (length >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;  
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        
        buffer[length++] = (char)ch;
    }

    
    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }


    if (length >= capacity) {
        char *new_buffer = realloc(buffer, length + 1);
        if (!new_buffer) {
            free(buffer);
            return NULL;
        }
        buffer = new_buffer;
        capacity = length + 1;
    }
    buffer[length] = '\0';

    return buffer;
}
