#include "../include/minishell.h"

char	*ft_end_buffer(char *ret, char **save)
{
	*save = NULL;
	if (ft_is_only(ret, ' '))
		return (NULL);
	return (ret);
}

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char		*ret;

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

char	*ft_trim_token(char *buffer, char sep)
{
	int		i;
	
	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == sep)
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == sep)
		buffer++;
	return (buffer);
}

void	make_token(t_data *data)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < data->cmd_count)
	{
		count = ft_token_count(data->cmd[c].buffer, ' ');
		data->cmd[c].token = ft_calloc(sizeof(char *), count + 2);
		t = 0;
		data->cmd[c].token[t] = ft_strtok(data->cmd[c].buffer, ' ');
		while (data->cmd[c].token[t])
		{
			t++;
			data->cmd[c].token[t] = ft_strtok(NULL, ' ');
		}
	}
	c = -1;
	// while (++c < data->cmd_count)
	// 	ft_clean_token(data, data->cmd[c].token);
}

void	parsing(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_count = ft_token_count(data->buffer, '|');
	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count + 1);
	if (data->cmd == NULL)
		exit_err(data, "Malloc error\n", 2);
	data->cmd[0].buffer = ft_trim_token(ft_strtok(data->buffer, '|'), ' ');
	while (++i < data->cmd_count)
		data->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	make_token(data);
}
int	ft_token_count(char *buffer, char sep)
{
	char	*tmp;
	char	*token;
	int		i;

	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_strtok(tmp, sep);
	while (token)
	{
		i++;
		token = ft_strtok(NULL, sep);
	}
	free(tmp);
	return (i);
}

void	init_env(t_data *data, char **env)
{
	int	i;

	data->prompt = NULL;
	data->buffer = NULL;
	data->cmd_count = 0;
	data->cmd = NULL;
	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (!data->env)
		exit_err(data, "Error: malloc failed", 2);
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			exit_err(data, "Error: malloc failed", 2);
		i++;
	}
}

void	free_table(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->cmd_count)
		free(data->cmd[i].token);
	free(data->cmd);
	free(data->buffer);
}

void execute_bultin(t_data *data, int i)
{
	if (ft_strncmp(data->cmd[i].token[0], "echo", 4) == 0)
		printf("echo %s", data->cmd[i].token[0]);
		// ft_echo(data->cmd[i].token[0]);
}

void	make_child_process(t_data *data, int nb)
{
	//pid
	//fork
	//enter child process
	//ft_find_redirect(data, nb);
	//if builtin
	execute_bultin(data, nb);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	int i;
	init_env(&data, env);
	while (ac < 2)
	{
		i = -1;
		data.buffer = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		if (ft_is_only(data.buffer, ' ')) // Newline on empty buffer
			free(data.buffer);
		else
		{
			parsing(&data);
			print_token(&data);
			while(++i < data.cmd_count)
				make_child_process(&data, i);
			free_table(&data);
		}
	}
	exit_err(&data, "Usage: ./minishell\n", 0);
	return (0);
}
