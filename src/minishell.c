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

char	*ft_get_variable(t_data *data, char *buffer)
{
	int		i;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (data->env[i][ft_strlen(buffer)] == '=')
				return (data->env[i] + (ft_strlen(buffer) + 1));
		}
	}
	buffer[0] = '\0';
	return (buffer);
}

// char	*strjoin_2(char const *s1, char const *s2)
// {
// 	// if(!s2)
// 	// 	return (ft_strjoin(s2, ""));
// 	if (!s1)
// 		s1 = ft_strdup("");
// 	return (ft_strjoin(s1, s2));
	
// }

void	swap_tmp(char **tmp, char **tmp2)
{
	char	*tmp3;
	tmp3 = *tmp;
	*tmp = *tmp2;
	*tmp2 = tmp3;
}

char	*ft_expand_variable(t_data *data, char *token)
{
	(void)data;
	char *ret;
	char *tmp;
	char *tmp2;
	char *final = NULL;
	while(*token)
	{
		if (*token == '$')
		{
			token++;
			ret = ft_substr(token, 0, strcspn(token, "$"));
			tmp = ft_get_variable(data, ret);
			if(!final)
				final = ft_strjoin("", tmp);
			else
			{
				tmp2 = final;
				tmp2 = ft_strjoin(tmp2, tmp);
				free(final);
				final = tmp2;
			}
			free(ret);	
		}
		token++;
	}
	return (final);
}

void	ft_clean_token(t_data *data, char **token)
{
	int t;

	t = 0;
	while (token[t])
	{
		if (token[t][0] == '\'' && token[t][ft_strlen(token[t]) - 1] == '\'')
			ft_remove_char(token[t], '\'');
		else if (token[t][0] == '\"' && token[t][ft_strlen(token[t]) - 1] == '\"')
		{
			ft_remove_char(token[t], '\"');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(data, token[t]);
		}
		else
		{
			token[t] = ft_trim_token(token[t], ' ');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(data, token[t]);
		}
		t++;
	}
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
	while (++c < data->cmd_count)
		ft_clean_token(data, data->cmd[c].token);
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

void	ft_echo(char **arg)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (ft_is_only(arg[i], ' '))
			i++;
		else
		{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

void execute_bultin(t_data *data, int i)
{
	if (ft_strncmp(data->cmd[i].token[0], "echo", 4) == 0)
		ft_echo(data->cmd[i].token);
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
