#include "../include/minishell.h"

t_data *get_data()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

void init_data(t_data *data)
{
	data->line = NULL;
	data->env = NULL;
	data->cmd = 0;
}

int main(int argc, char **argv)
{
	t_data *data;

	(void)argc;
	(void)argv;
	data = get_data();
	init_data(data);
	while(1)
	{
		data->line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		if (!data->line)
			break;
	}


	return 0;
}