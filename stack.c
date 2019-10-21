#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init(stack *s) {
    *s = NULL;
    printf("stack initialised\n");
}

void push(stack *s, values val) {
    node *temp = (node *)malloc(sizeof(node));
    temp->val.num = val.num;
    temp->val.row = val.row;
    temp->val.col = val.col;
    temp->next = *s;
    *s = temp;
    printf("(%d, %d, %d) is pushed into stack\n", (*s)->val.row, (*s)->val.col, (*s)->val.num);
}

values pop(stack *s) {
    node *temp = *s;
    values newval;
    newval.row = (*s)->val.row;
    printf("HEY \n");
    newval.col = (*s)->val.col;
    newval.num = (*s)->val.num;
    *s = (*s)->next;
    free(temp);
    printf("(%d, %d, %d) is poped from stack\n", newval.row, newval.col, newval.num);
    return newval;
}

int isempty(stack *s) {
    return *s == NULL;
}

int isfull(stack *s) {
    return 0;
}