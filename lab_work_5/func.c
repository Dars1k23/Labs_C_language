#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node{
    char value;
    struct Node* next;
}Node;

int add_el(Node **head, char ch){
    Node* new_node = malloc(sizeof(Node));
    new_node->value = ch;
    new_node->next = NULL;
    
    if(*head == NULL){
        *head = new_node;
    }
    else{
        Node* last = *head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new_node;
    }
    return 0;
}


int check(char chr){
    
    char vowels[] = "AEIOUYaeiouy";
    char consonants[] = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
    
    for (int i = 0; vowels[i] != '\0'; i++){
        if (chr == vowels[i]){
            return 0;
        }
    }
    
    for (int j = 0; consonants[j] != '\0'; j++){
        if (chr == consonants[j]){
            return 1;
        }
    }
    
    return 2;
}


void sortWord(Node* wordStart){
    char vowels[100], consonants[100], others[100];
    int vCount = 0, cCount = 0, oCount = 0;
    
    
    Node* p = wordStart;
    while (p != NULL && p->value != ' '){
        int res = check(p->value);
        
        if (res == 0){
            vowels[vCount++] = p->value;
        } else if (res == 1){
            consonants[cCount++] = p->value;
        } else {
            others[oCount++] = p->value;
        }
        p = p->next;
    }
    
   
    p = wordStart;
    for (int i = 0; i < vCount; i++){
        p->value = vowels[i];
        p = p->next;
    }
    for (int i = 0; i < cCount; i++){
        p->value = consonants[i];
        p = p->next;
    }
    for (int i = 0; i < oCount; i++){
        p->value = others[i];
        p = p->next;
    }
}


void processAllWords(Node* head){
    Node* p = head;
    
    while (p != NULL){
       
        while (p != NULL && p->value == ' '){
            p = p->next;
        }
        
        if (p == NULL) break;
        
      
        sortWord(p);
        
        
        while (p != NULL && p->value != ' '){
            p = p->next;
        }
    }
}


void printList(Node* head){
    Node* p = head;
    while (p != NULL){
        putchar(p->value);
        p = p->next;
    }
}

int run(){
    int ch;
    Node* head = NULL;
    
    while ((ch = getchar()) != '\n' && ch != EOF){
        if (add_el(&head, (char)ch) != 0){
            printf("Ошибка памяти!\n");
            break;
        }
    }
    
    processAllWords(head);
    printList(head);
    putchar('\n');
    
   
    while(head != NULL){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    
    return 0;
}
