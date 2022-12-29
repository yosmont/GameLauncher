/*
** YOSMONT PROJECT, 2018
** game launcher
** File description:
** display
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "project.h"

static void print_boxline(int len, char *str)
{
  //int len_two = (str)? ((strlen(str) % 2) == 1)?
  //	((strlen(str) / 2) + 1) : (strlen(str) / 2) : 0;
  int len_two = (str)? strlen(str) / 2 : 0;
	if (str) {
		printf("┌");
		for (int i = 0; i < ((len / 2) - len_two); i++)
			printf("─");
		printf(str);
		if (((len % 2) == 1 && (strlen(str) % 2) == 0) ||
		    ((len % 2) == 0 && (strlen(str) % 2) == 1))
			printf("─");
		for (int i = 0; i < ((len / 2) - len_two); i++)
                        printf("─");
		printf("┐\n");
	} else {
		printf("└");
		for (int i = 0; i < len; i++)
			printf("─");
		printf("┘\n");
	}
}

static void display_desc(gameinfo_t *current, char *path)
{
	int len = strlen((current->name)? current->name : current->game_name);
	char *line = NULL;
	char *tmp = NULL;
	char *tmp_two = NULL;
	char *oldpwd = NULL;
	char *pwd = NULL;
	int check = 2;

	print_boxline(len, "GAME");
	printf("│%s│\n",
	       (current->name)? current->name : current->game_name);
	print_boxline(len, NULL);
	if (current->desc)
		printf("description: %s\n", current->desc);
	printf("__________\n");
	printf("binary name: %s\n", current->bin_path);
	if (current->emu_bin)
		printf("launch with this emulator: %s\n", current->emu_bin);
	while (check == 2) {
		if (line)
			free(line);
		write(1, "\ndo you want to launch it? [y|n] \0", 34);
		line = gnl(stdin);
		if (line[0] == 'y' || line[0] == 'Y')
			check = 1;
		else if (line[0] == 'n' || line[0] == 'N')
			check = 0;
	}
	free(line);
	line = NULL;
	if (check == 1) {
		oldpwd = malloc(sizeof(char) * 200);
		oldpwd = getcwd(oldpwd, 200);
		tmp = my_strcat(my_strcat(strdup("game/"), current->game_name),
					  "/");
		pwd = my_strcat(strdup(path), tmp);
		chdir(pwd);
		free(pwd);
		line = strdup(current->bin_path);
		free(tmp);
		if (current->emu_bin) {
			tmp_two = my_strcat(strdup(" "), line);
			tmp = my_strcat(strdup(current->emu_bin), tmp_two);
			free(tmp_two);
			free(line);
			line = tmp;
		}
		printf("\n**********LOG**********\n");
		system(line);
		printf("**********END**********\n\n");
		chdir(oldpwd);
		free(line);
		free(oldpwd);
	} else
		printf("\n");
}

int nblen(int nb)
{
	int len = 0;

	for (len = 0; nb > 0; len++)
		nb = nb / 10;
	return (len);
}

int lib_box_len(gameinfo_t *begin)
{
	gameinfo_t *current = begin;
	int len = 0;
	char *name;

	for (int i = 1; current; i++) {
		name = (current->name)? current->name : current->game_name;
		len = (((int)strlen(name) + nblen(i) + 2) > len)?
			((int)strlen(name) + nblen(i) + 2) : len;
		current = current->next;
	}
	return (len);
}

gameinfo_t *display_basic(gameinfo_t *begin, char *path)
{
	gameinfo_t *current = begin;
	char *command = NULL;
	int nb = 0;
	int box_len = 0;
	char *name;

	while (1) {
		current = begin;
		box_len = lib_box_len(begin);
		print_boxline(box_len, "LIBRARY");
		for (int i = 1; current; i++) {
			name = (current->name)?
				current->name : current->game_name;
			printf("│%d. %s", i, name);
			for (int j = (strlen(name) + nblen(i) + 2);
			     j < box_len; j++)
				printf(" ");
			printf("│\n");
			current = current->next;
		}
		print_boxline(box_len, NULL);
		current = begin;
		write(1, "\n[which one? (or other command)]> \0", 35);
		command = gnl(stdin);
		if (strstr(command, "exit") != NULL) {
			free(command);
			write(1, "exit asked\n\0", 13);
			return (begin);
		}
		if (strstr(command, "add") != NULL) {
                        free(command);
			add_a_game(path);
			free_gameinfo(begin);
			begin = NULL;
			begin = get_list(path);
	                continue;
		}
		nb = atoi(command) - 1;
		for (int i = 0; i < nb && current; i++)
			current = current->next;
		if (current == NULL) {
			write(1, "\nnot found\n", 11);
			free(command);
		} else {
			display_desc(current, path);
			free(command);
		}
	}
}
