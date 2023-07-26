#include "shell.h"
/**
* executablecommand - define whether the file is executable cmd
* @info: a pointer to the info structure
* @path: the path to the file path to get checked
* Return: 1 if the file is an executable command, 0 when it fails
*/
int executablecommand(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
if (st.st_mode & S_IXUSR)
return (1);
}
return (0);
}
/**
* duplicateChar - transcript a substring of a string
* @pathstr: the string to duplicate from
* @start: the beginning index of the substring
* @stop: the ending index of the substring (exclusive)
* Return: Pointer to a new buf containing the copied substring
*/
char *duplicateChar(char *pathstr, int start, int stop)
{
static char buff[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buff[k++] = pathstr[i];
buff[k] = 0;
return (buff);
}
/**
* FcommandP - locates the full path of a command in str
* @info: a pointer to the info structure
* @pathstr: path str to search in
* @cmd: command to be found
* Return: pointer to new buf containing full path of command if found
* otherwise NULL
*/
char *FcommandP(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if (StringLength(cmd) > 2 && Beginstr(cmd, "./"))
{
if (executablecommand(info, cmd))
return (cmd);
}
do {
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicateChar(pathstr, curr_pos, i);
if (!*path)
Stringcon(path, cmd);
else
{
Stringcon(path, "/");
Stringcon(path, cmd);
}
if (executablecommand(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
} while (1);
return (NULL);
}
