#include "shell.h"
/**
* clearnfstruct - Initializes the info structure.
* @info: pointer to the info structure to be cleared
*/
void clearnfstruct(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* initializenfstruct - Initializes the info structure
* @info: pointer to the info structure to be initialized
* @av: the vec of the arg
*/
void initializenfstruct(info_t *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
i = 0;
while (info->argv && info->argv[i])
i++;
info->argc = i;
replace_alias(info);
replace_vars(info);
}
}
/**
* freenfstruct - sets the domains of the info structure free
* @info: pointer to the info structure to be released
* @all: true if all domains should be released
*/
void freenfstruct(info_t *info, int all)
{
Fstring(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
FreeLL(&(info->env));
if (info->history)
FreeLL(&(info->history));
if (info->alias)
FreeLL(&(info->alias));
Fstring(info->environ);
info->environ = NULL;
Freepointer((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(Buff_flush);
}
}
