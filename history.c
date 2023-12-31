#include "shell.h"
/**
* GETHisto - Get the path to file history
* @info: pointer to the info structure
* Return: pointer to a str including a path to the file history
*/
char *GETHisto(info_t *info)
{
char *buff, *dir;
dir = getenvironment(info, "HOME=");
if (!dir)
return (NULL);
buff = malloc(sizeof(char) * (StringLength(dir) + StringLength(Hist_Fi) + 2));
if (!buff)
return (NULL);
buff[0] = 0;
Stringcop(buff, dir);
Stringcon(buff, "/");
Stringcon(buff, Hist_Fi);
return (buff);
}
/**
* WHistofile - writes the history to file
* @info: pointer to the info structure
* Return: 1 (Success), otherwise -1
*/
int WHistofile(info_t *info)
{
ssize_t fid;
char *fname = GETHisto(info);
list_t *Node = NULL;
if (!fname)
return (-1);
fid = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(fname);
if (fid == -1)
return (-1);
Node = info->history;
while (Node)
{
printfds(Node->str, fid);
printfd('\n', fid);
Node = Node->next;
}
printfd(Buff_flush, fid);
close(fid);
return (1);
}
/**
* RHisto - Read the file history
* @info: pointer to the info structure
* Return: the number of history (Success), else 0
*/
int RHisto(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fid, rdlen, fsize = 0;
struct stat st;
char *buff = NULL, *fname = GETHisto(info);
if (!fname)
return (0);
fid = open(fname, O_RDONLY);
free(fname);
if (fid == -1)
return (0);
if (!fstat(fid, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buff = malloc(sizeof(char) * (fsize + 1));
if (!buff)
return (0);
rdlen = read(fid, buff, fsize);
buff[fsize] = 0;
if (rdlen <= 0)
return (free(buff), 0);
close(fid);
for (i = 0; i < fsize; i++)
if (buff[i] == '\n')
{
buff[i] = 0;
PHistoL(info, buff + last, linecount++);
last = i + 1;
}
if (last != i)
PHistoL(info, buff + last, linecount++);
free(buff);
info->histcount = linecount;
while (info->histcount-- >= Hist_Maxim)
DNodeI(&(info->history), 0);
RNHist(info);
return (info->histcount);
}
/**
* PHistoL - adds an entry to the history LL.
* @info: pointer to the info structure
* @buff: pointer to the buffer containing the history entry
* @linecount: line number of the history entry
* Return: 0 always
*/
int PHistoL(info_t *info, char *buff, int linecount)
{
list_t *Node = NULL;
if (info->history)
Node = info->history;
ANodeE(&Node, buff, linecount);
if (!info->history)
info->history = Node;
return (0);
}
/**
* RNHist - Renumb history entries in LL
* @info: pointer to the info structure
* Return: new number of history entries
*/
int RNHist(info_t *info)
{
list_t *Node = info->history;
int i = 0;
while (Node)
{
Node->numb = i++;
Node = Node->next;
}
return (info->histcount = i);
}
