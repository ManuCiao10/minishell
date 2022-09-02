#include "../include/minishell.h"

/*
	SAVE BEFORE:-->"DIO" stai 'dio'
	SAVE + 1:-->DIO" stai 'dio'
	SAVE AFTER:-->" stai 'dio'
	RETURN "DIO"
*/

int		ft_is_only_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_end_buffer(char *ret, char **save)
{
	*save = NULL;
	if (ft_is_only_space(ret))
		return (NULL);
	return (ret);
}

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char *ret;
	
	if (!save)
		save = buffer;
	ret = save;
	while (save && *save == ' ')
		save++; 
	while (save && *save != sep)
	{
		if (*save == '\0')
			return (ft_end_buffer(ret, &save));
		else if (*save == DBQUOTE || *save == SQUOTE)
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
		*save++ = '\0';
	return (ret);
}

void	ft_make_cmd_table(t_data *data)
{
	int i;

	i = 0;
	data->cmd_count = ft_token_count(data->buffer, '|');
	printf("%d\n", data->cmd_count);
	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count);
	data->cmd[0].buffer = ft_strtok(data->buffer, '|');
	while (++i < data->cmd_count)
	{
		data->cmd[i].buffer = ft_strtok(NULL, '|');
	}
}

void 	parsing(t_data *data)
{
	int i = -1;
	
	ft_make_cmd_table(data);
	while (++i < data->cmd_count)
		printf("%s\n", data->cmd[i].buffer);
}
int	ft_token_count(char *buffer, char sep)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_strtok(tmp, sep);
	while(token)
	{
		i++;
		token = ft_strtok(NULL, sep);
	}
	free(tmp);
	return (i);
}

void	exit_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void init_env(t_data *data, char **env)
{
	data->prompt = NULL;
	data->buffer = NULL;
	data->cmd_count = 0;
	data->cmd = NULL;
	int i;
	
	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(env));
	if(!data->env)
		exit_err("Error: malloc failed");
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if(!data->env[i])
			exit_err("Error: malloc failed");
		i++;
	}
	
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)env;
	(void)av;
	init_env(&data, env);
	while (ac < 2)
	{
		data.buffer = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		parsing(&data);
		// get_path(mini);
		free (data.buffer);
		free(data.cmd);

	}
	exit_err("Usage: ./minishell\n");
	return (0);
}
