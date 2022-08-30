#include "../include/minishell.h"

void	print_token(t_data *data )
{
	int i = 0;
	while (data->cmd[i].buffer)
    {
        printf("%s\n", data->cmd[i].buffer);
        i++;
    }
}

int		count_token(char *buffer)
{
	char *copy = ft_strdup(buffer);
	int i = 0;
	copy = ft_strtok(copy, SPACE);
	while (copy)
	{
		copy = ft_strtok(NULL, SPACE);
		i++;
	}
	return i;
}