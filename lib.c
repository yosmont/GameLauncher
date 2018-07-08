/*
** YOSMONT PROJECT, 2018
** game launcher
** File description:
** lib function
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include "project.h"

void exit_comment(int fd, char *str, int rtn)
{
	write(fd, str, strlen(str));
	exit(rtn);
}

char *my_strcat(char *dest, char *src)
{
	int len = strlen(dest);
	int tmp = 0;
	char *res = malloc(sizeof(char) * (len + strlen(src) + 1));

	for (int i = 0; i < len; i++)
		res[i] = dest[i];
	free(dest);
	while (src[tmp] != '\0') {
		res[len] = src[tmp];
		len++;
		tmp++;
	}
	res[len] = '\0';
	dest = strdup(res);
	free(res);
	return (dest);
}

int my_begincmp(char *begin, char *long_str)
{
	int tmp = 0;

	for (tmp = 0; begin[tmp] == long_str[tmp]; tmp++);
	if (begin[tmp] == '\0')
		return (0);
	else
		return (begin[tmp] - long_str[tmp]);
}
