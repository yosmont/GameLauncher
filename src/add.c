/*
** YOSMONT PROJECT, 2018
** game launcher
** File description:
** add
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

void add_a_game(char *path)
{
	char *line = NULL;
	char *name = NULL;
	char *content = strdup("");
	char *add = NULL;
	int check = 0;
	int fd;

	printf("game directory name: ");
	add = gnl(stdin);
	add[strlen(add) - 1] = '\0';
	add = my_strcat(add, ".gcf");
	line = my_strcat(strdup(path), "game_config/");
	name = my_strcat(line, add);
	free(add);
	while (check != 1) {
		printf("do you want to set a game name? [y|n] ");
		line = gnl(stdin);
		if (line[0] == 'y' || line[0] == 'Y') {
			free(line);
			printf("game name: ");
			line = gnl(stdin);
			line[strlen(line) - 1] = '\0';
			add = my_strcat(my_strcat(strdup("NAME=\""),
						  line), "\"\n");
			content = my_strcat(content, add);
			free(add);
			check = 1;
		} else if (line[0] == 'n' || line[0] == 'N')
			check = 1;
		free(line);
	}
	check = 0;
	while (check != 1) {
                printf("do you want to set a description? [y|n] ");
	        line = gnl(stdin);
                if (line[0] == 'y' || line[0] == 'Y') {
			free(line);
                        printf("description: ");
                        line = gnl(stdin);
			line[strlen(line) - 1] = '\0';
                        add = my_strcat(my_strcat(strdup("DESC=\""),
						  line), "\"\n");
			content = my_strcat(content, add);
			free(add);
                        check =	1;
                } else if (line[0] == 'n' || line[0] == 'N')
                        check = 1;
		free(line);
        }
	printf("binary path: ");
	line = gnl(stdin);
	line[strlen(line) - 1] = '\0';
	add = my_strcat(my_strcat(strdup("BIN_PATH=\""),
				  line), "\"\n");
	content = my_strcat(content, add);
	free(add);
	free(line);
	check = 0;
        while (check != 1) {
                printf("do you want to set a emulator? [y|n] ");
	        line = gnl(stdin);
		line[strlen(line) - 1] = '\0';
                if (line[0] == 'y' || line[0] == 'Y') {
			free(line);
			printf("emulator binary: ");
                        line = gnl(stdin);
			line[strlen(line) - 1] = '\0';
                        add = my_strcat(my_strcat(strdup("EMU_BIN=\""),
                                                  line), "\"\n");
                        content = my_strcat(content, add);
                        free(add);
                        check = 1;
	        } else if (line[0] == 'n' || line[0] == 'N')
	                check = 1;
		free(line);
	}
	fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0777);
	write(fd, content, strlen(content));
	free(content);
	free(name);
}
