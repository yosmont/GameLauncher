/*
** YOSMONT PROJECT, 2018
** game launcher
** File description:
** gnl with getline
*/

#include <stdio.h>
#include <stdlib.h>
#include "project.h"

char *gnl(FILE *fd)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (fd == NULL)
		exit_comment(2, "Error: missing file\n", 84);
	read = getline(&line, &len, fd);
	if (read == -1) {
		free(line);
		return (NULL);
	}
	return (line);
}
