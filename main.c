#include "shell.h"
/**
* main - Entrance point for the shell program
* @ac: the number of command-line arguments
* @av: an array of pointers to the arguments
* Return: 0 (Success), 1 when it fails
*/
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT};
int fid = 2;
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fid)
: "r" (fid));
if (ac == 2)
{
fid = open(av[1], O_RDONLY);
if (fid == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
errorprints(av[0]);
errorprints(": 0: Can't open ");
errorprints(av[1]);
errorprintchar('\n');
errorprintchar(Buff_flush);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fid;
}
populateenvironL(info);
RHisto(info);
shell(info, av);
return (EXIT_SUCCESS);
}
