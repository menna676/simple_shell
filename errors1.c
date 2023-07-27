#include "shell.h"
/**
* errorstringtoint - turn str to integer`
* @p: str to get turned
* Return: 0 if there aren't numeric chars in str else return changed numbs
* -1 (error).
*/
int errorstringtoint(char *p)
{
int i = 0;
unsigned long int res = 0;
if (*p == '+')
p++;/* TODO: Identify reason behind return val of 255 in the main func */
while (p[i] != '\0')
{
if (p[i] >= '0' && p[i] <= '9')
{
res *= 10;
res += (p[i] - '0');
if (res > INT_MAX)
return (-1);
}
else
{
return (-1);
}
i++;
}
return (res);
}
/**
* printerrormes - print error mesg to stderr
* @info: pointer to a struct including information about the shell
* @errorstring: str including particular err. type
* Return: 0 if there aren't numeric chars in str else return changed numbs
* return -1 on error.
*/
void printerrormes(info_t *info, char *errorstring)
{
errorprints(info->fname);
errorprints(": ");
printintfd(info->line_count, STDERR_FILENO);
errorprints(": ");
errorprints(info->argv[0]);
errorprints(": ");
errorprints(errorstring);
}
/**
* printintfd - prints an integer to the given file descriptor
* @input: the integer to print
* @fid: the file descriptor to write to
* Return: number of characters printed
*/
int printintfd(int input, int fid)
{
int (*_WriteCharacter)(char) = WriteCharacter;
int i, con = 0;
unsigned int abs_value, current;
if (fid == STDERR_FILENO)
_WriteCharacter = errorprintchar;
if (input < 0)
{
abs_value = -input;
_WriteCharacter('-');
con++;
}
else
abs_value = input;
current = abs_value;
i = 1000000000;
while (i > 1)
{
if (abs_value / i)
{
_WriteCharacter('0' + current / i);
con++;
}
current %= i;
i /= 10;
}
_WriteCharacter('0' + current);
con++;
return (con);
}
/**
* Turnnumb - changes integer to string representation using specified base
* @numb: the integer to convert
* @base: the base to use for the conversion
* @fs: flags to modify the conversion behavior
* Return: pointer to the resulting string
*/
char *Turnnumb(long int numb, int base, int fs)
{
static char *digits;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long c = numb;
if (!(fs & Change_UnSigned) && numb < 0)
{
c = -numb;
sign = '-';
}
digits = fs & Change_lowercase ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
while (c != 0)
{
*--ptr = digits[c % base];
c /= base;
}
if (sign)
*--ptr = sign;
return (ptr);
}
/**
* remcom - exchange the first example of '#' in the string with '\0'
* @buff: pointer to str to adjust
* Return: 0 always
*/
void remcom(char *buff)
{
int i = 0;
while (buff[i] != '\0')
{
if (buff[i] == '#' && (i == 0 || buff[i - 1] == ' '))
{
buff[i] = '\0';
break;
}
i++;
}
}
