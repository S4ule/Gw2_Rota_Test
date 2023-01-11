
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
	t_spell *b_spell; ////utiliser pour chercher si le spell tmp vas fair du gachi
	bool find;
	int t_jump = 0;

	//solve
	while (total_dm < target_dmg)
	{
		tmp = data; //set tmp at the start of data
		b_spell = data; ////set b_spell a la data de départ

		while (tmp != NULL) //iterate in data
		{
			b_spell = data;
			if (tmp->a_cd == 0) //look if the spell is off cd
			{
				find = false;
				while(b_spell != tmp)
				{

					if(b_spell->a_cd != 0)
					{
						if ((float)b_spell->dm / (float)(b_spell->a_cd + b_spell->ct) > (float)(tmp->dm + b_spell->dm) / (float)(tmp->ct + b_spell->ct))
						{
							find = true;
							break ;
						}
					}
					b_spell = b_spell->next;
				}
				if(find == true)
				{
					printf(" B_damage : %d B_casting_time : %d A_casting_time : %d B_actual_CD : %d A_damage : %d \n",b_spell->dm, b_spell->ct, tmp->ct, b_spell->a_cd, tmp->dm);
					printf("saut__________\n");
					printf("%d \n", tmp->n);
					t_jump++;
				}
				break;
			}
			tmp = tmp->next;
		}
		if (find == true || tmp == NULL) //see if you have noting to cast
		{
			cast(data, 1, &time); //cast noting
			wait_time++;
		}
		else
		{
			if (wait_time != 0) //if wait_time != 0 print the time waited and set it to 0
			{
				printf("Wait :  %d\n", wait_time);
				lost_time += wait_time;
				wait_time = 0;
			}
			printf("Spell : %d\n", tmp->n);
			cast(data, tmp->ct, &time);	
			tmp->a_cd = tmp->cd;
			total_dm += tmp->dm;
		}
	}
	printf("Damage : %d\n", total_dm);
	printf("Lost time : %d \n", lost_time);
	printf("Total jump : %d \n", t_jump);
	return (time);
}

void start(t_spell *data, char *target_dmg_arg)
{
	unsigned int target_dmg;
	unsigned int time;

	target_dmg = ft_atoi(target_dmg_arg); //get target_dmg
	time = solve(data, target_dmg);
	printf("Time : %d\n", time);
	//printf("%d", time);
	return ;
}

