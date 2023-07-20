#include "shell.h"
/**
* Setmemory - Fill  memory space with steady byte
* @p: memory space pointer to fill
* @r: byte to fill up memory space p with
* @c: number of bytes to fill
* Return: pointer to filled memory space p
*/
char *Setmemory(char *p, char r, unsigned int c)
{
unsigned int i = 0;
while (i < c)
{
p[i] = r;
i++;
}
return (p);
}
/**
* Fstring - Sets an array of strs free
* @ss: the array of strs to free
*/
void Fstring(char **ss)
{
char **e = ss;
if (!ss)
return;
while (*ss)
free(*ss++);
free(e);
}
/**
* memoryReallocate - reassign memory block
* @ptr: a pointer to the prev memory block assigned
* @old_size: the size of the prev memory block in bytes
* @new_size: the size of the new memory block in bytes
* Return: a pointer to the reallocated memory block
*/
void *memoryReallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *s;
if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
s = malloc(new_size);
if (!s)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
s[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (s);
}
