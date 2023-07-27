#include "shell.h"
/**
* Chaindel - checks if the existing character in buff is delimi command
* @info: structire  parameter
* @buff: buff character
* @s: existing pos in buf pointer
* Return: 1 whether the chain delimi, else 0
*/
int Chaindel(info_t *info, char *buff, size_t *s)
{
size_t j = *s;
if (buff[j] == '|' && buff[j + 1] == '|')
{
buff[j] = 0;
j++;
info->cmd_buf_type = CMD_ors;
}
else if (buff[j] == '&' && buff[j + 1] == '&')
{
buff[j] = 0;
j++;
info->cmd_buf_type = CMD_ands;
}
else if (buff[j] == ';')
{
buff[j] = 0;
info->cmd_buf_type = CMD_chains;
}
else
{
return (0);
}
*s = j;
return (1);
}
/**
* ChainStat - tests whether to continue chaining based on last command
* @info: structure parameter
* @buff: buff character
* @s: existing pos in buff address
* @i: begining pos in buffer
* @leng: Buffer leng
* Return: Void
*/
void ChainStat(info_t *info, char *buff, size_t *s, size_t i, size_t leng)
{
size_t j = *s;
if (info->cmd_buf_type == CMD_ands)
{
if (info->status)
{
buff[i] = 0;
j = leng;
}
}
else if (info->cmd_buf_type == CMD_ors)
{
if (!info->status)
{
buff[i] = 0;
j = leng;
}
}
*s = j;
}
/**
* ReplaceAL - Replace al in the tokenized str with corresponding val
* @info: structure parameter
* Return: 1 when replaced, else 0
*/
int ReplaceAL(info_t *info)
{
int i = 0;
list_t *Node = NULL;
char *s = NULL;
while (i < 10)
{
Node = NodewithPrefix(info->alias, info->argv[0], '=');
if (!Node)
return (0);
free(info->argv[0]);
s = StringCharac(Node->str, '=');
if (!s)
return (0);
s = DuplicateString(s + 1);
if (!s)
return (0);
info->argv[0] = s;
i++;
}
return (1);
}
/**
* ReplaceVAR - Replace var in tokenized str with corresponding val
* @info: structure parameter
* Return: 1 when replaced, else 0
*/
int ReplaceVAR(info_t *info)
{
int i = 0;
list_t *Node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!StringCompare(info->argv[i], "$?"))
{
ReplaceStr(&(info->argv[i]),
DuplicateString(Turnnumb(info->status, 10, 0)));
continue;
}
if (!StringCompare(info->argv[i], "$$"))
{
ReplaceStr(&(info->argv[i]),
DuplicateString(Turnnumb(getpid(), 10, 0)));
continue;
}
Node = NodewithPrefix(info->env, &info->argv[i][1], '=');
if (Node)
{
ReplaceStr(&(info->argv[i]),
DuplicateString(StringCharac(Node->str, '=') + 1));
continue;
}
ReplaceStr(&info->argv[i], DuplicateString(""));
i++;
}
return (0);
}
/**
* ReplaceStr - Replace  str with new str
* @old: old str address
* @new: address of new str
* Return: 1 when replaced, else 0
*/
int ReplaceStr(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
