#include "shell.h"
/**
* Stringcop - reduplicate str
* @dest: buff dest
* @src: buff source
* Return: dest buff pointer
*/
char *Stringcop(char *dest, char *src)
{
int i;
if (dest == src || src == 0)
return (dest);
for (i = 0; src[i]; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}
/**
* DuplicateString - transcripts str
* @str: str to get transcripted
* Return: transcripted str pointer
*/
char *DuplicateString(const char *str)
{
int size = 0;
char *ret;
if (str == NULL)
return (NULL);
while (*str++)
size++;
ret = malloc(sizeof(char) * (size + 1));
if (!ret)
return (NULL);
for (size++; size--;)
ret[size] = *--str;
return (ret);
}
/**
* PrintString - print str to stdout
* @str: str to print
* Return: Nothing
*/
void PrintString(char *str)
{
if (!str)
return;
for (int i = 0; str[i] != '\0'; i++)
{
WriteCharacter(str[i]);
}
}
/**
* WriteCharacter - prints char n to stdout
* @n: char to get printed
* Return: (Success) 1, errno is set properly and -1 is returned on error
*/
int WriteCharacter(char n)
{
static int i;
static char buff[Write_Buff_size];
if (n == Buff_flush || i >= Write_Buff_size)
{
write(1, buff, i);
i = 0;
}
if (n != Buff_flush)
buff[i++] = n;
return (1);
}
