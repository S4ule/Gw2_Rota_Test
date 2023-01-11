
#include "rota.h"

t_spell *pars(int fd)
{
	int i;
	char **arg_line;
	char 	*line = NULL; //line buf
	t_spell *data; //the start of data spell list
	t_spell *tmp; //tmp spell list to iterate


	data = malloc(sizeof(t_spell) * 1);
	if (data == NULL)
		return (NULL);

	while (line == NULL || line[0] == '#' || line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_chain_list(data);
			return (NULL);
		}
	}

	i = 0;
	if (line[0] != '#' && line[0] != '\n')
	{
		arg_line = ft_split(line, ';');
		
		while (arg_line != NULL && arg_line[i] != NULL)
			i++;
		if (arg_line == NULL || i < 3)
		{
			free(line);
			free_chain_list(data);
			free_split(arg_line);
			return (NULL);
		}
		
		data->dm = ft_atoi(arg_line[0]);
		data->ct = ft_atoi(arg_line[1]);
		data->cd = ft_atoi(arg_line[2]);
		data->a_cd = 0;
		data->n = 1;
		data->next = NULL;
		free_split(arg_line);
	}

	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;

		if (line[0] == '#' || line[0] == '\n')
			continue ;

		i = 0;
		arg_line = ft_split(line, ';');
		
		while (arg_line != NULL && arg_line[i] != NULL)
			i++;
		if (arg_line == NULL || i < 3)
		{
			free(line);
			free_chain_list(data);
			free_split(arg_line);
			return (NULL);
		}

		tmp = malloc(sizeof(t_spell) * 1);
		if (tmp == NULL)
		{
			free(line);
			free_chain_list(data);
			free_split(arg_line);
			return (NULL);
		}

		tmp->dm = ft_atoi(arg_line[0]);
		tmp->ct = ft_atoi(arg_line[1]);
		tmp->cd = ft_atoi(arg_line[2]);
		tmp->a_cd = 0;
		tmp->n = get_size_chain_list(data) + 1;
		tmp->next = NULL;
		add_end(tmp, data);
		free_split(arg_line);
	}
	return (data);
}