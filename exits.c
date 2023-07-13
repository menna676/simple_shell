#include "shell.h"
/**
**StringCopy - copies c characters of a str from source to destination
* @dest: dest stri to copy to
* @src: source stri to copy from
* @c: numb of chars to copy
* Return: a pointer to the destination string
*/
char *StringCopy(char *dest, char *src, int c)
{
int i;
char *p = dest;
for (i = 0; src[i] != '\0' && i < c - 1; i++)
{
dest[i] = src[i];
}
if (i < c)
{
int j;
for (j = i; j < c; j++)
{
dest[j] = '\0';
}
}
return (p);
}
/**
**StringConcat - Concatenate two strs up to a maximum number of bytes
* @dest: des stri to concatenate to
* @src: source stri to concatenate from
* @c: maximum numb of bytes to concatenate
* Return: a pointer to the destination string
*/
char *StringConcat(char *dest, char *src, int c)
{
int i = 0;
int j;
char *p = dest;
while (dest[i] != '\0')
{
i++;
}
for (j = 0; src[j] != '\0' && j < c; j++)
{
dest[i] = src[j];
i++;
}
if (j < c)
{
dest[i] = '\0';
}
return (p);
}
/**
**StringCharac - finds the first occurrence of a char in a stri
* @p: stri to be searched
* @n: char to be found
* Return: pointer to first occurrence of the character in the string,
*/
char *StringCharac(char *p, char n)
{
while (*p++ != '\0')
{
if (*p == n)
return (p);
}
return (NULL);
}
