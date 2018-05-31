#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//typedef unsigned int uint64_t;

typedef struct {
	char name[20];
	float price;
	double quantity;
}menu;

typedef struct Node {
  menu data;
  struct Node* next;
}t_node;

menu initMenu(t_node* head);
char* getFileName();
void loadFile(t_node** head);
void saveFile(t_node* head);
void printMenu(menu data);
unsigned int nodesCounter(t_node* head);
void printNode(t_node** head);
void deleteNode(t_node** head);
void addNode(t_node** head, menu data, int mode);
void deleteNodeAtPoss(t_node** head, int poss);
void getstr(char* str, int maxLen);
int strCmpIgnoreCase(char* str1, char* str2);
void makeOrder(t_node** head);

#endif

