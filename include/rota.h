
#ifndef ROTA_H
# define ROTA_H

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

typedef struct s_spell
{
	int		dm; //domage
	int		ct; //cast time
	int 	a_cd; //actual cd
	int		cd; //cd
	int		n; //number of the spell
	struct s_spell *next; //the next spell
}	t_spell;

/*
	utils.c
*/

void add_end(t_spell *add, t_spell *start);
void free_split(char **arg);
void free_chain_list(t_spell *start);
int get_size_chain_list(t_spell *start);

/*
	pars.c
*/

t_spell *pars(int fd);

/*
	rota.c
*/

void start(t_spell *data, char *target_dmg_arg);

#endif
