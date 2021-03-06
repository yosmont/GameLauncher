/*
** YOSMONT PROJECT, 2018
** game launcher
** File description:
** list function
*/

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "project.h"

static char *get_value(char *line)
{
	int len = 0;
	int begin = 0;
        char *name;

        for (len = 0; line[len] != '"'; len++);
	len += 1;
	begin = len;
	for (; line[len] != '"'; len++);
        name = malloc(sizeof(char) * (len + 1));
        for (int i = begin; line[i] != '"'; i++)
                name[i - begin] = line[i];
        name[len - begin] = '\0';
	return (name);
}

static gameinfo_t *get_gameinfo(gameinfo_t *tmp, char *path, struct dirent *file)
{
	FILE *fd;
	char *line = NULL;
	int len = strlen(file->d_name);
	char *filepath = my_strcat(strdup(path), file->d_name);

	tmp = malloc(sizeof(gameinfo_t));
	tmp->game_name = strndup(file->d_name, (len - 4));
	tmp->name = NULL;
	tmp->desc = NULL;
	tmp->bin_path = NULL;
	tmp->emu_bin = NULL;
	tmp->next = NULL;
	fd = fopen(filepath, "r");
	line = gnl(fd);
	while (line) {
		if (my_begincmp("NAME", line) == 0)
			tmp->name = get_value(line);
		else if (my_begincmp("DESC", line) == 0)
			tmp->desc = get_value(line);
		else if (my_begincmp("BIN_PATH", line) == 0)
			tmp->bin_path = get_value(line);
		else if (my_begincmp("EMU_BIN", line) == 0)
			tmp->emu_bin = get_value(line);
		free(line);
		line = NULL;
		line = gnl(fd);
	}
	free(filepath);
	fclose(fd);
	return (tmp);
}

gameinfo_t *get_list(char *progpath)
{
	gameinfo_t *begin = NULL;
	gameinfo_t *tmp;
	char *path = my_strcat(strdup(progpath), "game_config/\0");
	DIR *dir = opendir(path);
	if (dir == NULL) {
		mkdir(progpath, 0777);
		mkdir(path, 0777);
		mkdir(my_strcat(strdup(progpath), "game/\0"), 0777);
	}
	dir = opendir(path);
	struct dirent *file = readdir(dir);

	while (file) {
		if (file->d_name[0] != '.' && begin != NULL &&
		    !strcmp(&file->d_name[strlen(file->d_name) - 4], ".gcf")) {
			tmp = begin;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = get_gameinfo(tmp->next, path,
						 file);
		} else if (file->d_name[0] != '.' &&
			   !strcmp(&file->d_name[strlen(file->d_name) - 4],
				  ".gcf")) {
			begin = get_gameinfo(begin, path, file);
		}
		file = readdir(dir);
	}
	closedir(dir);
	free(path);
	return (begin);
}

void free_gameinfo(gameinfo_t *current)
{
	gameinfo_t *tmp = NULL;

	while (current) {
		tmp = current->next;
		if (current->game_name)
			free(current->game_name);
		if (current->name)
			free(current->name);
		if (current->desc)
			free(current->desc);
		if (current->bin_path)
			free(current->bin_path);
		if (current->emu_bin)
			free(current->emu_bin);
		free(current);
		current = tmp;
	}
}
