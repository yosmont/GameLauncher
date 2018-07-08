/*
** YOSMONT PROJECT, 2018
** yet another header
** File description:
** header
*/

#include <stdio.h>

#ifndef PROJECT_H_
	#define PROJECT_H_

typedef struct game_info_s {
	char *game_name;
	char *name;
	char *desc;
	char *bin_path;
	char *emu_bin;
	struct game_info_s *next;
} gameinfo_t;

char *gnl(FILE *fd);
int my_begincmp(char *begin, char *long_str);
char *my_strcat(char *dest, char *src);
void free_gameinfo(gameinfo_t *current);
gameinfo_t *get_list(char *progpath);
void exit_comment(int fd, char *str, int rtn);
gameinfo_t *display_basic(gameinfo_t *begin, char *path);
void add_a_game(char *path);

#endif /* !PROJECT_H_ */
