#include "shell.h"
/**
* Freepointer - set pointer free and the value of it NULL
* @ptr: a pointer to the pointer to be freed
* Return: 1 if the pointer was freed, 0 when it fails
*/
int Freepointer(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
