#include "shell.h"
/**
* GETEnvironment - returns a copy of the environment variables
* @info: pointer to the info structure
* Return: 0 always
*/
char **GETEnvironment(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
* UnSetEnviron - deletes environ var
* @info: pointer to the info structure
* @vari: the name of the environment variable to delete
* Return: 1 On success, else 0
*/
int UnSetEnviron(info_t *info, char *vari)
{
list_t *Node = info->env;
size_t i;
char *s;
if (!Node || !vari)
return (0);
for (i = 0; Node; i++)
{
s = starts_with(Node->str, vari);
if (s && *s == '=')
{
info->env_changed = DNodeI(&(info->env), i);
i = 0;
Node = info->env;
continue;
}
Node = Node->next;
}
return (info->env_changed);
}
/**
* SETEnviron - creates or modifies an env var
* @info: pointer to the info structure
* @vari: the name of the environment variable
* @val: the value of the environment variable
* Return: 0 always
*/
int SETEnviron(info_t *info, char *vari, char *val)
{
char *buff = NULL;
list_t *Node;
char *s;
if (!vari || !val)
return (0);
buff = malloc(_strlen(vari) + _strlen(val) + 2);
if (!buff)
return (1);
_strcpy(buff, vari);
_strcat(buff, "=");
_strcat(buff, val);
Node = info->env;
for (; Node; Node = Node->next)
{
s = starts_with(Node->str, vari);
if (s && *s == '=')
{
free(Node->str);
Node->str = buff;
info->env_changed = 1;
return (0);
}
}
ANodeE(&(info->env), buff, 0);
free(buff);
info->env_changed = 1;
return (0);
}
