#include "shell.h"
/**
* BufferInput - reads input from standard input, buffers chained commands
* @info: pointer to the info structure
* @buff: buf address to store the input
* @leng: length address variable
* Return: the number of bytes read from standard input
*/
ssize_t BufferInput(info_t *info, char **buff, size_t *leng)
{
ssize_t b = 0;
size_t leng_s = 0;
if (!*leng) /* fill buffer when nothing left in it */
{
free(*buff);
*buff = NULL;
signal(SIGINT, handleSigint);
#if use_getline
b = getline(buff, &leng_s, stdin);
#else
b = GetNextli(info, buff, &leng_s);
#endif
if (b > 0)
{
if ((*buff)[b - 1] == '\n')
{
(*buff)[b - 1] = '\0';
b--;
}
info->linecount_flag = 1;
remcom(*buff);
PHistoL(info, *buff, info->histcount++);
/* check if *buf contains a command chain ";". If so, buff the commands */
if (StringCharac(*buff, ';'))
{
*leng = b;
info->cmd_buf = buff;
}
}
}
return (b);
}
/**
* GETin - reads input from standard input and parses chained commands
* @info: pointer to the info structure
* Return: the number of bytes read from standard input
*/
ssize_t GETin(info_t *info)
{
static char *buff;
static size_t i, j, leng;
ssize_t b = 0;
char **buff_s = &(info->arg), *s;
WriteCharacter(Buff_flush);
b = BufferInput(info, &buff, &leng);
if (b == -1)
return (-1);
if (leng) /* comments still in buff */
{
j = i;
s = buff + i;
ChainStat(info, buff, &j, i, leng);
while (j < leng)
{
if (Chaindel(info, buff, &j))
break;
j++;
}
i = j + 1;
if (i >= leng) /* Buff End ? */
{
i = leng = 0;
info->cmd_buf_type = CMD_norms;
}
*buff_s = s;
return (StringLength(s)); /* Returns curr command leng*/
}
*buff_s = buff;
return (b); /* Returns buff leng BufferInput() */
}
/**
* ReadBuffer - reads data from a file descriptor into a buffer
* @info: pointer to the info structure
* @buff: buff to store the data
* @i: size of the buffer
* Return: the number of bytes read from standard input
*/
ssize_t ReadBuffer(info_t *info, char *buff, size_t *i)
{
ssize_t b = 0;
if (*i)
return (0);
b = read(info->readfd, buff, Read_Buff_size);
if (b >= 0)
*i = b;
return (b);
}
/**
* GetNextli - reads next line inp. from a file descriptor
* @info: pointer to the info structure
* @ptr: pointer to buff address, NULL or preassigned
* @size: If it isn't NULL, preassigned buff size
* Return: p
*/
int GetNextli(info_t *info, char **ptr, size_t *size)
{
static char buff[Read_Buff_size];
static size_t i, leng;
size_t k;
ssize_t b = 0, p = 0;
char *s = NULL, *new_s = NULL, *n;
s = *ptr;
if (s && size)
p = *size;
if (i == leng)
i = leng = 0;
b = ReadBuffer(info, buff, &leng);
if (b == -1 || (b == 0 && leng == 0))
return (-1);
n = StringCharac(buff + i, '\n');
k = n ? 1 + (unsigned int)(n - buff) : leng;
new_s = memoryReallocate(s, p, p ? p + k : k + 1);
if (!new_s)
return (s ? free(s), -1 : -1);
if (p)
StringConcat(new_s, buff + i, k - i);
else
StringCopy(new_s, buff + i, k - i + 1);
p += k - i;
i = k;
s = new_s;
if (size)
*size = p;
*ptr = s;
return (p);
}
/**
* handleSigint - handles the SIGINT signal (Ctrl+C)
* @sig_numb: signal numb
* Return: void
*/
void handleSigint(__attribute__((unused)) int sig_numb)
{
PrintString("\n"); /* print newline */
PrintString("$ "); /* print prompt */
WriteCharacter(Buff_flush); /* flush buffer */
}
