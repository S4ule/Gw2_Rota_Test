
#include "rota.h"

int main(int ac, char **av)
{
	if (ac <= 2)
	{
		printf("Usage : [FILE] [TARGET_DMG] \n");
		return (1);
	}

	int fd; //file descriptor
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Can't open file\n");
		return (1);
	}

	t_spell *data; //spell list
	data = pars(fd); //pars the file descriptor with pars(fd) call
	if (data == NULL)
	{
		printf("Parssing fail, please take care of me ;(\n");
		close(fd);
		return (1);
	}
	close(fd);

	start(data, av[2]); //start
	free_chain_list(data);

	return (0);
}