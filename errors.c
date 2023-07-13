#include "shell.h"
/**
* errorprints - Print error message to stdout
* @str: error message to print
* Return: Nothing
*/
void errorprints(char *str)
{
if (!str)
return;
for (int i = 0; str[i] != '\0'; i++)
{
errorprintchar(str[i]);
}
}
/**
* errorprintchar - write the char n to stderr
* @n: char to get printed
* Return: 1 (Success), errno is set properly on error and -1 is returned
*/
int errorprintchar(char n)
{
static int i;
static char buff[Write_Buff_size];
if (n == Buff_flush || i >= Write_Buff_size)
{
write(2, buff, i);
i = 0;
}
if (n != Buff_flush)
buff[i++] = n;
return (1);
}
/**
* printfd - write char n to the given file descriptor
* @n: char to be printed
* @fid: write to file descriptor
* Return: 1 (Success), errno is set properly on error and -1 is returned
*/
int printfd(char n, int fid)
{
static int i;
static char buff[Write_Buff_size];
if (n == Buff_flush || i >= Write_Buff_size)
{
write(fid, buff, i);
i = 0;
}
if (n != Buff_flush)
buff[i++] = n;
return (1);
}
/**
* printfds - print str to the given file descriptor
* @str:  string to get changed
* @fid: the file descriptor to write to
* Return: the number of characters printed
*/
int printfds(char *str, int fid)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += printfd(*str++, fid);
}
return (i);
}
