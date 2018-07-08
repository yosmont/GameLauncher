/*
** YOSMONT PROJECT, 2018
** yet another main
** File description:
** main
*/

#include <stdlib.h>
#include <string.h>
#include "project.h"

void help(void)
{
	printf("USAGE:\n\tgame_launcher [PATH]\n"
	       "\nDESC:\n\tgame launcher is a tools for select and launch the "
	       "game you want (steam library-like)\n"
	       "\t\t- game config file (.gcf) are in the \"game_config\" "
	       "directory and are made of:\n"
	       "\t\t\t- NAME: the name of the game | (not mandatory)\n"
	       "\t\t\t- DESC: a description of this game | (not mandatory)\n"
	       "\t\t\t- BIN_PATH: the path of the game binary (from his "
	       "directory | (mandatory)\n"
	       "\t\t\t- EMU_BIN: the emulator binary (command) you want to use"
	       " (like wine). If you don't need a emulator, just ignore this "
	       "var | (not mandatory)\n"
	       "\t\t- game file are in the \"game\" directory, the game "
	       "directory need to have the same name as his game config file "
	       "(without the \".gcf\")\n"
	       "\tAll this file have to be in \"~/game_launcher/\" directory"
	       " or in the directory PATH\n"
	       "\tYou can create a .gcf file with a add command\n");
}

int main(int ac, char **av)
{
	gameinfo_t *list;
	char *path = (ac > 1)? strdup(av[1]) :
		my_strcat(strdup(getenv("HOME")), "/game_launcher/");

	if (ac > 1 && av[1][0] == '-' && av[1][1] == 'h')
		help();
	else {
		list = get_list(path);
		list = display_basic(list, path);
		free_gameinfo(list);
	}
	free(path);
	return (0);
}
