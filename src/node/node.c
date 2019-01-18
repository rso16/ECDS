#include "node.h" 

node *createNode(uint8_t data)
{
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    return newNode;
}

void setNextNode(node *currentNode, node *nextNode)
{
    currentNode->next = nextNode;
}

void addHeadToList(nodeList *list, node* newHead)
{
    list->head = newHead;
}

void removeHeadFromList(nodeList *list)
{
    //check if head exist
    if(list->head != NULL)
    {
        //check if there is a next node
        if(list->head->next != NULL)
        {
            node *newHead = list->head->next;
            free(list->head);
            list->head = newHead;
        }
        else
        {
            free(list->head);
            list->head = NULL;
        }
	list->size--;
    }
    else
    {
        #if PRINTF == PRINTF_EN
            printf("ERROR No head\n");
        #endif
        return;
    }

}

void addNodeToList(nodeList *list, node *newNode)
{
    //check if head exist
    if(list->head != NULL)
    {
        //check if tail exist
        if(list->tail != NULL)
        {   
            node *temp = list->tail;
            temp->next = newNode;
            list->tail = newNode;
        }
        //tail doesn't exist
        else
        {
            list->tail = newNode;
            list->head->next = list->tail;
        }
	list->size++;
    }
    //head doesn't exist
    else
    {
        addHeadToList(list, newNode);
    }
}

void addNodeListToNodeListList(nodeListList *listList, nodeList *newNodeList)
{
    //check if head exist
    if(listList->head != NULL)
    {
        //check if tail exist
        if(listList->tail != NULL)
        {   
            nodeList *temp = listList->tail;
            temp->next = newNodeList;
            listList->tail = newNodeList;
        }
        //tail doesn't exist
        else
        {
            listList->tail = newNodeList;
            listList->head->next = listList->tail;
        }
	listList->size++;
    }
    //head doesn't exist
    else
    {
    	listList->head = newNodeList;
    }
}

void addDataToList(nodeList *list, uint8_t data)
{
   node *newNode = createNode(data);
   addNodeToList(list, newNode);
}

void addStrToList(nodeList *list, char *str)
{
	printf("str = %s\n", str);
	int index = 0;
	while(str[index] != '\0')
	{
		printf("c = %c , index = %i\n", str[index], index);
		addDataToList(list, str[index]);
		index++;
	}
	printf("\n");	
}

void printNode(node *currentNode)
{
    
   #if PRINTF == PRINTF_EN 
        if(currentNode != NULL)
        {
            printf("data = %d\n", currentNode->data);
        }
        else
        {
            printf("ERROR is NULL\n");
        }
   #endif
}

void printList(nodeList *list)
{
   #if PRINTF == PRINTF_EN 
        if(list->head != NULL)
        {
            node *currentNode = list->head;
            int counter = 0;
            while(currentNode != NULL)
            {
                printf("node %d = %d\n", counter, currentNode->data);
                counter++;
                currentNode = currentNode->next;
            }
        }
        else
        {
            printf("error no list\n ");
        }
   #endif
}

void printStrList(nodeList *list)
{
   #if PRINTF == PRINTF_EN 
        if(list->head != NULL)
        {
            node *currentNode = list->head;
            int counter = 0;
            while(currentNode != NULL)
            {
                printf("%c", currentNode->data);
                counter++;
                currentNode = currentNode->next;
            }
            printf("test\n");
        }
        else
        {
            printf("error no list\n ");
        }
   #endif
}


int listToStr(nodeList *list, char *str, int begin, int end)
{
	//check params
	//check if head exist
	if(list->head == NULL)
	{
 		return -1;
	}
	
	//check if end is after begin
	if(end <= begin)
	{
		return -2;
	}
	
	//check boundries
	if(end > list->size)
	{
		return -3;
	}
	
	//make temp node
	node *temp = list->head;		
	//go to begin location
	int index = 0;
	while(index < begin)
	{
		index++;
		temp = temp->next;
	}
		
	//prepare string for concatenation
	strcpy(str, "\0");
	printf("testing testing");	
	while(index < end)
	{	
		strcat(str,(char*) temp->data);
		printf("%c", temp->data);
		temp = temp->next;
		index++;
	}
	printf("str == %s", str);
	return 1;
}
