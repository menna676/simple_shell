#include "shell.h"
/**
* getList_leng - sets leng. of list
* @head: first node pointer
* Return: number of nodes at the array of strings
*/
size_t getList_leng(const list_t *head)
{
size_t i = 0;
while (head)
{
head = head->next;
i++;
}
return (i);
}
/**
* LLtoStrings - returns array of strs of the linked list's string values
* @head: first node pointer of the linked list
* Return: number of nodes at the array of strings
*/
char **LLtoStrings(list_t *head)
{
list_t *Node = head;
size_t i = getList_leng(head), j;
char **strings;
char *str;
if (!head || !i)
return (NULL);
strings = malloc(sizeof(char *) * (i + 1));
if (!strings)
return (NULL);
i = 0;
while (Node)
{
str = malloc(_strlen(Node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strings[j]);
free(strings);
return (NULL);
}
str = _strcpy(str, Node->str);
strings[i] = str;
Node = Node->next;
i++;
}
strings[i] = NULL;
return (strings);
}
/**
* printLinkedL - output all linked list_t elemens
* @head: the linked list first node pointer
* Return: the number of nodes at the array of strings
*/
size_t printLinkedL(const list_t *head)
{
size_t i;
for (i = 0; head; head = head->next, i++)
{
_puts(Turnnumb(head->numb, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
}
return (i);
}
/**
* NodewithPrefix - returns the node that str begin with the given prefix
* @Node: the linked list head node pointer
* @pref: the prefix to be matched
* @n: next char after the pref to get matched
* Return: a pointer to the matched node or NULL if no match is found
*/
list_t *NodewithPrefix(list_t *Node, char *pref, char n)
{
char *s = NULL;
for (; Node; Node = Node->next)
{
s = starts_with(Node->str, pref);
if (s && ((n == -1) || (*s == n)))
return (Node);
}
return (NULL);
}
/**
* getIndexofNode - get a Node index in a linked list
* @head: the linked list head node pointer
* @Node: Node to get the index of pointer
* Return: the node index or -1 if the node is not found
*/
ssize_t getIndexofNode(list_t *head, list_t *Node)
{
size_t i;
for (i = 0; head; head = head->next, i++)
{
if (head == Node)
return (i);
}
return (-1);
}
