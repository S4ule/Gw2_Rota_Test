
#include "rota.h"

static void cast(t_spell *start, int i, unsigned int *time)
{
	t_spell *tmp;

	tmp = start;
	while (tmp != NULL)
	{
		if (tmp->a_cd > 0)
		{
			if (tmp->a_cd - i < 0)
				tmp->a_cd = 0;
			else
				tmp->a_cd -= i;
		}
		tmp = tmp->next;
	}
	(*time) += i;
}

static unsigned int solve(t_spell *data, unsigned int target_dmg)
{
	//prety simple
	unsigned int time = 0;
	unsigned int total_dm = 0;
	unsigned int wait_time = 0;
	int lost_time = 0;


	t_spell *tmp; //tmp spell list to iterate

	//solve
	while (total_dm < target_dmg)
	{
		tmp = data; //set tmp at the start of data
		while (tmp != NULL) //iterate in data
		{
			if (tmp->a_cd == 0) //look if the speel if off cd
			{
				if (wait_time != 0) //if wait_time != 0 print the time waited and set it to 0
				{
					printf("Wait :  %d\n", wait_time);
					lost_time += wait_time;
					wait_time = 0;
				}

				printf("Spell : %d\n", tmp->n); //print the number of the spell put
				cast(data, tmp->ct, &time); // call cast to do the cast of the spell
				
				tmp->a_cd = tmp->cd; //set the a_cd of the spell at cd
				
				total_dm += tmp->dm; //add the dommage of the spell to total_dm
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL) //see if you have noting to cast
		{
			cast(data, 1, &time); //cast noting
			wait_time++;
		}
	}
	printf("Damage : %d\n", total_dm);
	printf("Lost time : %d \n", lost_time);

	return (time);
}

void start(t_spell *data, char *target_dmg_arg)
{
	unsigned int target_dmg;
	unsigned int time;

	target_dmg = ft_atoi(target_dmg_arg); //get target_dmg
	time = solve(data, target_dmg);
	printf("Time : %d\n", time);
//	printf("%d", time);
	return ;
}

