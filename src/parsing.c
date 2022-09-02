#include "../include/minishell.h"

void	print_token(t_data *data)
{
	int i = 0;
	while (data->cmd[i].buffer)
    {
        printf("%s\n", data->cmd[i].buffer);
        i++;
    }
}

int	ft_array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i + 2);
}