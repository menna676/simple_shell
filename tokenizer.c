#include "shell.h"
/**
* **splitstr - Split str to words using  delimi
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
p = malloc((1 + numbword) * sizeof(char *));
if (!p)
return (NULL);
for (i = 0, j = 0; j < numword; j++)
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
free(s[k]);
free(s);
return (NULL);
}
for (w = 0; w < k; w++)
s[j][w] = str[i++];
p[j][w] = 0;
}
p[j] = NULL;
return (p);
}
/**
 * * split_string - splits a string into words using a delimiter
 * * @str: the input string to be split
 * * @d: the delimiter character
 * * Return: a pointer to an array of strings, or NULL on failure
 * */
char **split_string(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;
	if (str == NULL || str[0] == 0)
		return NULL;
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	}
	if (numwords == 0)
		return NULL;
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return NULL;
	j = 0;
	for (i = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return NULL;
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return s;
}
