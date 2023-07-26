#include "shell.h"
/**
* **splitstr - Split str to words with delimi
* @str: input str to get split
* @t: delimi str
* Return: NULL when it fails or array if strs pointer
*/
char **splitstr(char *str, char *t)
{
int i, j, k, w, numbword = 0;
char **p;
if (str == NULL || str[0] == 0)
return (NULL);
if (!t)
t = " ";
for (i = 0; str[i] != '\0'; i++)
if (!isdelimiter(str[i], t) && (isdelimiter(str[i + 1], t) || !str[i + 1]))
numbword++;
if (numbword == 0)
return (NULL);
p = malloc((1 + numbword) *sizeof(char *));
if (!p)
return (NULL);
for (i = 0, j = 0; j < numbword; j++)
{
while (isdelimiter(str[i], t))
i++;
k = 0;
while (!isdelimiter(str[i + k], t) && str[i + k])
k++;
p[j] = malloc((k + 1) * sizeof(char));
if (!p[j])
{
for (k = 0; k < j; k++)
free(p[k]);
free(p);
return (NULL);
}
for (w = 0; w < k; w++)
p[j][w] = str[i++];
p[j][w] = 0;
}
p[j] = NULL;
return (p);
}
/**
* **splitstr2 - Split str to words with delimi
* @str: stri input to be split
* @t: char delimi
* Return: a pointer to an array of strings, or NULL on failure
*/
char **splitstr2(char *str, char t)
{
int i, j, k, w, numbword = 0;
char **p;
if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != t && str[i + 1] == t) ||
(str[i] != t && !str[i + 1]) || str[i + 1] == t)
numbword++;
if (numbword == 0)
return (NULL);
p = malloc((1 + numbword) *sizeof(char *));
if (!p)
return (NULL);
for (i = 0, j = 0; j < numbword; j++)
{
while (str[i] == t && str[i] != t)
i++;
k = 0;
while (str[i + k] != t && str[i + k] && str[i + k] != t)
k++;
p[j] = malloc((k + 1) * sizeof(char));
if (!p[j])
{
for (k = 0; k < j; k++)
free(p[k]);
free(p);
return (NULL);
}
for (w = 0; w < k; w++)
p[j][w] = str[i++];
p[j][w] = 0;
}
p[j] = NULL;
return (p);
}
