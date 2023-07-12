#include "shell.h"
/**
* isinteractivemode - checks if the shell is running in interactive mode
* @info: pointer to info_t structure
* Return: 1 if running in interactive mode, else 0
*/
int isinteractivemode(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
* isdelimiter - check whether char is delimi
* @n: character to be checked
* @delim: delimiter string
* Return: 1 if @n is a delimiter, 0 otherwise
*/
int isdelimiter(char n, char *delim)
{
while (*delim)
if (*delim++ == n)
return (1);
return (0);
}
/**
* isalphabetic - check whether the char is alphabetic
* @n: char to be checked
* Return: 1 if n is alphabetic, 0 otherwise
*/
int isalphabetic(int n)
{
if ((n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z'))
return (1);
else
return (0);
}
/**
* stringtoint - converts a string to an integer
* @p: The string to be converted
* Return: 0 if no nums are found in string, the converted number otherwise
*/
int stringtoint(char *p)
{
int i = 0, sign = 1, f = 0, output;
unsigned int result = 0;
while (p[i] != '\0' && f != 2)
{
if (p[i] == '-')
sign *= -1;
if (p[i] >= '0' && p[i] <= '9')
{
f = 1;
result *= 10;
result += (p[i] - '0');
}
else if (f == 1)
{
f = 2;
}
i++;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
