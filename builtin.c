#include "shell.h"
/**
* My_Exit - get out from shell
* @info: pointer to struct includes information about the shell
* Return: when info->argv[0] != "exit" exit with a given exit status (0)
*/
int My_Exit(info_t *info)
{
int exit_status;
if (info->argv[1])
{
exit_status = errorstringtoint(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
printerrormes(info, "Invalid number: ");
errorprints(info->argv[1]);
errorprintchar('\n');
return (1);
}
info->err_num = errorstringtoint(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
* MyCD - converts existing dir of process
* @info: pointer to struct includes information about the shell
* Return: 0 always
*/
int MyCD(info_t *info)
{
char *p, *dirc, buffer[1024];
int chdir_ret;
p = getcwd(buffer, 1024);
if (!p)
PrintString(" TODO: >>getcwd failed emsg here<<\n");
if (!info->argv[1])
{
dirc = getenvironment(info, "HOME=");
if (!dirc)
chdir_ret = /* TODO: what is this supposed to be? */
chdir((dirc = getenvironment(info, "PWD=")) ? dirc : "/");
else
chdir_ret = chdir(dirc);
}
else if (StringCompare(info->argv[1], "-") == 0)
{
if (!getenvironment(info, "OLDPWD="))
{
PrintString(p);
WriteCharacter('\n');
return (1);
}
PrintString(getenvironment(info, "OLDPWD="));
WriteCharacter('\n');
chdir_ret = /* TODO: what is this supposed to be? */
chdir((dirc = getenvironment(info, "OLDPWD=")) ? dirc : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
printerrormes(info, "can not cd to ");
errorprints(info->argv[1]), errorprintchar('\n');
}
else
{
SETEnviron(info, "OLDPWD", getenvironment(info, "PWD="));
SETEnviron(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* MyHelp - converts existing dir of process
* @info: pointer to struct includes information about the shell
* Return: 0 always
*/
int MyHelp(info_t *info)
{
char **arg_array;
arg_array = info->argv;
PrintString("help function is called. function not implemented yet.\n");
if (0)
PrintString(*arg_array); /* Temporary work avoid unused var warning */
return (0);
}
