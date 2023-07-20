#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>

#define Change_lowercase     1
#define Change_UnSigned      2

#define Read_Buff_size  1024
#define Write_Buff_size 1024
#define Buff_flush      -1

#define use_getline    0
#define use_strtok     0

#define CMD_norms     0
#define CMD_ors       1
#define CMD_ands      2
#define CMD_chains    3

#define Hist_Fi    ".simple_shell_history"
#define Hist_Maxim     4096
extern char **environ;
/**
* struct liststr - list singly
* @numb: numb field
* @str: string
* @next: next node pointer
*/
typedef struct liststr
{
int numb;
char *str;
struct liststr *next;
} list_t;

/**
* struct passinfo - structure containing pseudo-args
* to get passed into a fun..
* allows uniform prototype for fun. pointer structure.
* @arg:  str produced from getline contains args.
* @argv: str array produced from `arg`.
* @path: str representing existing command's path.
* @argc: count of arg.
* @line_count: the count of lines (errors).
* @err_num: exit()s fault code.
* @linecount_flag: if enabled, count line of input.
* @fname: the filename of program.
* @env: a list representing enviroment local copy.
* @environ: adjusted custom copy of the environment from
* the linked list `env`.
* @history: node history.
* @alias: node alias.
* @env_changed: if enabled, indicates that `environ` got changed.
* @status: last carried out command return status.
* @cmd_buf: a pointer address to `cmd_buf`, if chaining.
* @cmd_buf_type: CMD_type: ||, &&, or ;.
* @readfd: file descriptor to read line input from.
* @histcount: count of history line numbs.
*/
typedef struct passinfo
{
int readfd;
int status;
int linecount_flag;
int cmd_buf_type;
int histcount;
int err_num;
int argc;
int env_changed;
unsigned int line_count;
char **cmd_buf;
char *fname;
char *arg;
char **environ;
char **argv;
char *path;
list_t *alias;
list_t *history;
list_t *env;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
* struct builtin - include builtin related fun. and str.
* @type: builtin instruction flag.
* @func: fun..
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

int isinteractivemode(info_t *);
int isdelimiter(char, char *);
int isalphabetic(int);
int stringtoint(char *);

int displayHistory(info_t *);
int Remove_alias(info_t *, char *);
int set_shellAlias(info_t *, char *);
int print_shellAlias(list_t *);
int shellAlias(info_t *);

size_t getList_leng(const list_t *);
char **LLtoStrings(list_t *);
size_t printLinkedL(const list_t *);
list_t *NodewithPrefix(list_t *, char *, char);
ssize_t getIndexofNode(list_t *, list_t *);

int My_Exit(info_t *);
int MyCD(info_t *);
int MyHelp(info_t *);

int Myenvironment(info_t *);
char *getenvironment(info_t *, const char *);
int setenvironment(info_t *);
int unsetenvironment(info_t *);
int populateenvironL(info_t *);

void errorprints(char *);
int errorprintchar(char);
int printfd(char, int);
int printfds(char *, int);

int errorstringtoint(char *);
void printerrormes(info_t *, char *);
int printintfd(int, int);
char *Turnnumb(long int, int, int);
void remcom(char *);

void clearnfstruct(info_t *);
void initializenfstruct(info_t *, char **);
void freenfstruct(info_t *, int);

char *StringCopy(char *, char *, int);
char *StringConcat(char *, char *, int);
char *StringCharac(char *, char);

ssize_t BufferInput(info_t *, char **, size_t *);
ssize_t GETin(info_t *);
ssize_t ReadBuffer(info_t *, char *, size_t *);
int GetNextli(info_t *, char **, size_t *);
void handleSigint(int);

char **GETEnvironment(info_t *);
int UnSetEnviron(info_t *, char *);
int SETEnviron(info_t *, char *, char *);

char *GETHisto(info_t *info);
int WHistofile(info_t *info);
int RHisto(info_t *info);
int PHistoL(info_t *info, char *buff, int linecount);
int RNHist(info_t *info);

list_t *Node_start(list_t **, const char *, int);
list_t *ANodeE(list_t **, const char *, int);
size_t PstringL(const list_t *);
int DNodeI(list_t **, unsigned int);
void FreeLL(list_t **);

int Freepointer(void **);

int executablecommand(info_t *, char *);
char *duplicateChar(char *, int, int);
char *FcommandP(info_t *, char *, char *);

char *Setmemory(char *, char, unsigned int);
void Fstring(char **);
void *memoryReallocate(void *, unsigned int, unsigned int);

#endif
