#include "shell.h"
/**
* shell - main loop for the shell
* @info: a pointer to the info structure containing shell info
* @av: arg vector of main
* Return: 1 On error code or on error, 0 (Success)
*/
int shell(info_t *info, char **av)
{
ssize_t b = 0;
int builtin_ret = 0;
while (b != -1 && builtin_ret != -2)
{
clearnfstruct(info);
if (isinteractivemode(info))
PrintString("$ ");
errorprintchar(Buff_flush);
b = GETin(info);
if (b != -1)
{
initializenfstruct(info, av);
builtin_ret = Fbuiltin(info);
if (builtin_ret == -1)
Fcommand(info);
}
else if (isinteractivemode(info))
WriteCharacter('\n');
freenfstruct(info, 0);
}
WHistofile(info);
freenfstruct(info, 1);
if (!isinteractivemode(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* Fbuiltin - searchs for builtin cmd
* @info: pointer to the info structure containing shell information
* Return: -1 when the builtin command is not found,
* 0 when the builtin command is executed successfully,
* 1 when the builtin command is found but not successful,
* 2 when the builtin command signals exit()
*/
int Fbuiltin(info_t *info)
{
int i = 0, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", shell_exit},
{"env", shell_env},
{"help", shell_help},
{"history", shell_history},
{"setenv", shellSETEnviron},
{"unsetenv", shellUnSetEnviron},
{"cd", shell_cd},
{"alias", shell_alias},
{NULL, NULL}
};
while (builtintbl[i].type)
{
if (StringCompare(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
i++;
}
return (built_in_ret);
}
/**
* Fcommand - finds a command in the PATH environment variable
* @info: a pointer to the info structure containing shell information
* Return: void
*/
void Fcommand(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!isdelimiter(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = FcommandP(info, getenvironment(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
Forkthread(info);
}
else
{
if ((isinteractivemode(info) || getenvironment(info, "PATH=")
|| info->argv[0][0] == '/') && executablecommand(info, info->argv[0]))
{
Forkthread(info);
}
else if (*(info->arg) != '\n')
{
info->status = 127;
printerrormes(info, "command not found\n");
}
}
}
/**
* Forkthread - forks a child process to perform a command
* @info: a pointer to the info structure containing shell information
* Return: void
*/
void Forkthread(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: print error func */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, GETEnvironment(info)) == -1)
{
freenfstruct(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: print error func */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
printerrormes(info, "Permission denied\n");
}
}
}
