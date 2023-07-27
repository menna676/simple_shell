#include "shell.h"
/**
* ANode_start - insert node to beginning of a linked L
* @head: the first node poinrer of the linked list
* @str: pointer to the string to be stored in the node
* @numb: the index of the Node used by Histo
* Return: numb of nodes in the Linked list (Size)
*/
list_t *ANode_start(list_t **head, const char *str, int numb)
{
list_t *N_head;
if (!head)
return (NULL);
N_head = malloc(sizeof(list_t));
if (!N_head)
return (NULL);
Setmemory((void *)N_head, 0, sizeof(list_t));
N_head->numb = numb;
if (str)
{
N_head->str = DuplicateString(str);
if (!N_head->str)
{
free(N_head);
return (NULL);
}
}
N_head->next = *head;
*head = N_head;
return (N_head);
}
/**
* ANodeE - Insert  node to ending of a linked list
* @head: the first node pointer of the linked list
* @str: pointer to the string to be stored in the node
* @numb: the index of the Node used by Histo
* Return: numb of nodes in Linked list (Size)
*/
list_t *ANodeE(list_t **head, const char *str, int numb)
{
list_t *new_Node, *Node;
if (!head)
return (NULL);
Node = *head;
new_Node = malloc(sizeof(list_t));
if (!new_Node)
return (NULL);
Setmemory((void *)new_Node, 0, sizeof(list_t));
new_Node->numb = numb;
if (str)
{
new_Node->str = DuplicateString(str);
if (!new_Node->str)
{
free(new_Node);
return (NULL);
}
}
if (Node)
{
do {
Node = Node->next;
} while (Node->next);
Node->next = new_Node;
}
else
*head = new_Node;
return (new_Node);
}
/**
* PstringL - just print string elems of LL
* @head : head node pointer of the linked list
* Return: the numb of nodes in the linked list (Size)
*/
size_t PstringL(const list_t *head)
{
size_t i = 0;
for (; head; head = head->next)
{
PrintString(head->str ? head->str : "(nil)");
PrintString("\n");
i++;
}
return (i);
}
/**
* DNodeI - At specific index removes the node
* @head: head node pointer of linked list
* @index: Node index to get removed
* Return: 1 (Success), 0 otherwise
*/
int DNodeI(list_t **head, unsigned int index)
{
list_t *Node, *prev_Node;
unsigned int i = 0;
if (!head || !*head)
return (0);
if (!index)
{
Node = *head;
*head = (*head)->next;
free(Node->str);
free(Node);
return (1);
}
Node = *head;
while (Node)
{
if (i == index)
{
prev_Node->next = Node->next;
free(Node->str);
free(Node);
return (1);
}
i++;
prev_Node = Node;
Node = Node->next;
}
return (0);
}
/**
* FreeLL - sets the node Frees in LL
* @head_ptr: the first node pointer
* Return: void
*/
void FreeLL(list_t **head_ptr)
{
list_t *Node, *next_Node, *head;
if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
Node = head;
for (; Node; Node = next_Node)
{
next_Node = Node->next;
free(Node->str);
free(Node);
}
*head_ptr = NULL;
}
