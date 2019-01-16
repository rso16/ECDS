#ifndef NODE_H
#define NODE_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#define PRINTF_DI 0
#define PRINTF_EN 1
#define PRINTF PRINTF_EN

typedef struct Node
{
	uint8_t data;
    	struct Node *next;
}node;

typedef struct LongNodeList
{
	struct Node *head;
	struct Node *tail;
	long   size;
}longNodeList;

typedef struct NodeList
{
	struct Node *head;
	struct Node *tail;
	struct NodeList *next;
	uint8_t   size;
}nodeList;

typedef struct NodeListList
{
	struct NodeList *head;
	struct NodeList *tail;
	uint8_t	size;
}nodeListList;

node * createNode(uint8_t data);
void setNextNode(node *currentNode, node *nextNode);
void addHeadToList(nodeList *list, node* newHead);
void removeHeadFromList(nodeList *list);
void addNodeToList(nodeList *list, node *newNode);
void addDataToList(nodeList *list, uint8_t data);
void addNodeListToNodeListList(nodeListList * list, nodeList *nextNodeList);
void addStrToList(nodeList *list, char *str); 
void printNode(node *currentNode);
void printList(nodeList *list);
void printStrList(nodeList *list);
int listToStr(nodeList *list, char *str, int begin, int end);
#endif
