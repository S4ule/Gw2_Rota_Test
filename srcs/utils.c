
#include "rota.h"

void add_end(t_spell *add, t_spell *start)
{
	while (start->next != NULL)
		start = start->next;
	start->next = add;
}

void free_split(char **arg)
{
	int i = 0;

	while (arg && arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void free_chain_list(t_spell *start)
{
	t_spell *ptr;

	while (start != NULL)
	{
		ptr = start;
		start = start->next;
		free(ptr);
	}
}

int get_size_chain_list(t_spell *start)
{
	int i;

	i = 0;
	while (start != NULL)
	{
		i++;
		start = start->next;
	}
	return (i);
}
