#ifndef MY_FUNC_H
#define MY_FUNC_H

typedef struct Node {
    char value;
    struct Node* next;
} Node;


int add_el(Node **head, char ch);


int check(char chr);


void sortWord(Node* wordStart);


void processAllWords(Node* head);


void printList(Node* head);

int run();

#endif
