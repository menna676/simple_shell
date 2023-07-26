#include "shell.h"
/**
* StringLength - return leng of  str
* @p: str leng to get checked
* Return: str int leng
*/
int StringLength(char *p)
{
int i = 0;
if (!p)
return (0);
while (*p++)
i++;
return (i);
}
/**
* StringCompare - excutes lexicographic compare between two strs.
* @p1: first str
* @p2: second str
* Return: zero if s1 == s2, positive if s1 > s2, negative if s1 < s2
*/
int StringCompare(char *p1, char *p2)
{
for (; *p1 && *p2; p1++, p2++)
{
if (*p1 != *p2)
return (*p1 - *p2);
}
if (*p1 == *p2)
return (0);
else
return (*p1 < *p2 ? -1 : 1);
}
/**
* Beginstr - check wether str begins with a given substring
* @haystack: str to get searched
* @needle: substr to get found
* Return: Null or nxt character of haystack address or NULL
*/
char *Beginstr(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
* Stringcon - Concatenate two strs
* @dest: buff destination
* @src: buff source
* Return: dest buff pointer
*/
char *Stringcon(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
