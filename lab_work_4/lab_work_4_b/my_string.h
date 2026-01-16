#ifndef MY_STRING_H
#define MY_STRING_H

int is_delim(char c, const char *delim);
char *my_strtok(char *str, const char *delim);
int my_strlen(char *str);
char *my_strdup(const char *str);
char *my_readline(void);

#endif
