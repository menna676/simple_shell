#include "shell.h"
/**
* displayHistory - shows history list, shows each command on separate line
* starts at 0, perceded by line numbs.
* @info: Struct containing relevant information, to look after.
* Return: 0 always
*/
int displayHistory(info_t *info)
{
printLinkedL(info->history);
return (0);
}
/**
* Remove_alias - removes an alias from the shell's list of aliases
* @info: pointer to structure containing information about the shell
* @str: string representing the alias to get unset.
* Return: 1 if ot fails, 0 always (Success)
*/
int Remove_alias(info_t *info, char *str)
{
char *s, n;
int ret;
s = StringCharac(str, '=');
if (!s)
return (1);
n = *s;
*s = '\0';
ret = delete_node_at_index(&(info->alias),
getIndexofNode(info->alias, NodewithPrefix(info->alias, str, -1)));
*s = n;
return (ret);
}
/**
* set_shellAlias - set a shell alias to a given str.
* @info: pointer to structure containing information about the shell
* @str: string containing the alias to get set
* Return: 0 (Success), 1 if it fails
*/
int set_shellAlias(info_t *info, char *str)
{
char *s;
s = StringCharac(str, '=');
if (!s)
return (1);
if (!*++s)
return (Remove_alias(info, str));
Remove_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
* print_shellAlias - print the contents of a shell alias
* @Node: pointer to the node containing the alias string
* Return: 0 Success, 1 if it fails
*/
int print_shellAlias(list_t *Node)
{
char *s = NULL;
char *al = NULL;
if (Node)
{
s = StringCharac(Node->str, '=');
for (al = Node->str; al <= s; al++)
_putchar(*al);
_putchar('\'');
_puts(s + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
* shellAlias - imitatives builtin alias
* @info: pointer to a struct including information about the shell
* Return: 0 always
*/
int shellAlias(info_t *info)
{
int i = 0;
char *s = NULL;
list_t *Node = NULL;
if (info->argc == 1)
{
Node = info->alias;
while (Node)
{
print_shellAlias(Node);
Node = Node->next;
}
return (0);
}
i = 1;
while (info->argv[i])
{
s = StringCharac(info->argv[i], '=');
if (s)
set_shellAlias(info, info->argv[i]);
else
print_shellAlias(NodewithPrefix(info->alias, info->argv[i], '='));
i++;
}
return (0);
}
