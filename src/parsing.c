#include "../include/minishell.h"

void	print_token(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	ft_color(RED);
	printf("---------- COMAND TABLE ----------\n");
	while (i < data->cmd_count)
	{
		j = 0;
		ft_color(CYAN);
		while (data->cmd[i].token[j])
		{
			ft_color(YELLOW);
			printf("[%s]", data->cmd[i].token[j]);
			j++;
		}
		printf("\n");
		i++;
	}
	ft_color(RED);
	printf("---------------END----------------\n");
	ft_color(WHITE);
}

int	ft_array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i + 2);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		if (array[i])
			free (array[i]);
	}
	free(array);
}

void	exit_err(t_data *data, char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_array(data->env);
	exit(1);
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}