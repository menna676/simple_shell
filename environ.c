#include "shell.h"
/**
* Myenvironment - print existing shell environ variables
* @info: pointer to a struct including information about the shell
* Return: 0 always
*/
int Myenvironment(info_t *info)
{
print_list_str(info->env);
return (0);
}
/**
* getenvironment - get value of a shell environment var
* @info: pointer to a struct including information about the shell
* @name: name of the environment variable
* Return: value of the environment variable
*/
char *getenvironment(info_t *info, const char *name)
{
list_t *Node = info->env;
char *s;
for (; Node; Node = Node->next)
{
s = starts_with(Node->str, name);
if (s && *s)
return (s);
}
return (NULL);
}
/**
* setenvironment - Initialize new environ var or adjust an existing one
* @info: pointer to a struct including information about the shell
* Return: 0 always
*/
int setenvironment(info_t *info)
{
if (info->argc != 3)
{
errorprints("Incorrect numb of arguments\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* unsetenvironment - Delete a shell environ var
* @info: pointer to a struct including information about the shell
* Return: Always 0
*/
int unsetenvironment(info_t *info)
{
int i = 1;
if (info->argc == 1)
{
errorprints("Too few arguments.\n");
return (1);
}
while (i <= info->argc)
{
_unsetenv(info, info->argv[i]);
i++;
}
return (0);
}
/**
* populateenvironL - populates linked list of shell environment variables
* @info: pointer to a struct including information about the shell
* Return: 0 always
*/
int populateenvironL(info_t *info)
{
list_t *NODE = NULL;
size_t x = 0;
while (environ[x])
{
add_node_end(&NODE, environ[x], 0);
x++;
}
info->env = NODE;
return (0);
}
