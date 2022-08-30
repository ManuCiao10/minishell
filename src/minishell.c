#include "../include/minishell.h"

/*
	SAVE BEFORE:-->"DIO" stai 'dio'
	SAVE + 1:-->DIO" stai 'dio'
	SAVE AFTER:-->" stai 'dio'
	RETURN "DIO"
*/

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char		*ret;

	if (!save)
		save = buffer;
	ret = save;
	while (save && *save != sep)
	{
		if (*save == '\0')
		{
			save = NULL;
			return (ret);
		}
		else if (*save == DQUOTE || *save == QUOTE)
		{
			save = strchr(save + 1, *save);
			if (!save)
				return (ret);
			save++;
		}
		else
			save++;
	}
	if (save)
		*save++ = 0;
	return (ret);
}

void	parsing(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_count = ft_token_count(data, '|');
	data->cmd = ft_calloc(sizeof(char *), data->cmd_count);
	data->cmd[0].buffer = ft_strtok(data->buffer, '|');
	while (data->cmd[i].buffer)
	{
		i++;
		data->cmd[i].buffer = ft_strtok(NULL, '|');
	}
}

int	ft_token_count(t_data *data, char sep)
{
	char	*tmp;
	char	*token;
	int		i;

	i = 0;
	tmp = ft_strdup(data->buffer);
	token = ft_strtok(tmp, sep);
	while (token)
	{
		i++;
		token = ft_strtok(NULL, sep);
	}
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)env;
	(void)av;
	while (ac < 2)
	{
		data.prompt = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		parsing(&data);
		//dollar_sign(&mini);
		print_token(&data);
		// get_path(mini);
	}
	printf("Usage: ./minishell\n");
	return (0);
}
