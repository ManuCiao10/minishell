#include "../include/minishell.h"

int			error_status;

t_shell	*get_shell()
{
	static t_shell	*shell;

	shell = NULL;
	if (shell == NULL)
		shell = (t_shell *)malloc(sizeof(t_shell));
	return (shell);
}

void	ft_print_table(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	printf("while i < %d\n", shell->nb_cmd);
	while (i < shell->nb_cmd)
	{
		j = 0;
		ft_color(1);
		dprintf(2, "------------ TOKEN -----------------\n");
		ft_color(6);
		dprintf(2, "cmd %d = \t", i);
		while (shell->cmd[i].token[j])
		{
			ft_color(3);
			dprintf(2, "[\033[1;34m%s\033[1;33m]", shell->cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
	dprintf(2, "------------------------------------\n");
	ft_color(8);
}

void	init_shell(char *envp[])
{
	t_shell	*shell;

	shell = get_shell();
	shell->promt = NULL;
	shell->env_name = envp;
}

int	get_number_quotes(char *line, int quotes)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] == quotes)
			c++;
		i++;
	}
	return (c);
}

int	double_open(char *prompt)
{
	int	d;
	int	s;
	int	i;

	d = 0;
	s = 0;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == SQUOTE)
			s++;
		if (prompt[i] == DBQUOTE)
			d++;
	}
	if ((d % 2 != 0 && d) || (s % 2 != 0 && s))
	{
		printf("Quotes must be closed\n");
		return (1);
	}
	return (0);
}

void	*free_(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}

int	even_(int n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}



void	ft_exit(t_shell *data, int status)
{
	free_(data);
	exit(status);
}

bool	builtin(t_shell *data)
{
	char	*p;

	if (strncmp(data->promt, "exit ", 5) == 0)
		ft_exit(data, 0);
	else if (strncmp(data->promt, "cd", 2) == 0)
	{
		p = data->promt;
		p += 3;
		if (chdir(p) == -1)
			printf("cd: no such file or directory: %s\n", p);
	}
	else
		return (false);
	return (true);
}

bool	is_only(char *line, char c)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i])
	{
		if (line[i] != c)
			return (false);
		i++;
	}
	return (true);
}

static char	*buffer_end(char *str, char **s)
{
	*s = NULL;
	if (is_only(str, ' '))
		return (NULL);
	return (str);
}

char	*strtok_(char *str, char delim)
{
	static char	*s;
	char		*token;

	if (!s)
		s = str;
	token = s;
	while (s && *s == ' ')
		s++;
	while (s && *s != delim)
	{
		if (*s == '\0')
			return (buffer_end(token, &s));
		else if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (token);
			s++;
		}
		else
			s++;
	}
	if (s)
		*s++ = '\0';
	return (token);
}

char	*trim_token(char *token, char sep)
{
	int	i;

	i = 0;
	if (!token)
		return (token);
	i = ft_strlen(token) - 1;
	while (token[i] == sep)
	{
		token[i] = '\0';
		i--;
	}
	while (*token == sep)
		token++;
	return (token);
}

int	count_token(char *str, char sep)
{
	char	*tmp;
	int		i;
	char	*token;

	tmp = strdup(str);
	i = 0;
	token = trim_token(strtok_(tmp, sep), ' ');
	while (token)
	{
		i++;
		token = trim_token(strtok_(NULL, sep), ' ');
	}
	free_(tmp);
	return (i);
}

void	parse_token_bitch(t_shell *shell)
{
	int	i;
	int	t;
	int	count_;

	i = -1;
	t = 0;
	count_ = 0;
	while (++i < shell->nb_cmd)
	{
		count_ = count_token(shell->cmd[i].buffer, ' ');
		shell->cmd[i].token = ft_calloc(sizeof(char *), count_ + 2);
		if (!shell->cmd[i].token)
		{
			free_(shell->cmd[i].token);
			printf("Error Malloc");
			exit(0);
		}
		shell->cmd[i].token[t] = strtok_(shell->cmd[i].buffer, ' ');
		while (shell->cmd[i].token[t++])
			shell->cmd[i].token[t] = strtok_(NULL, ' ');
		// ft_print_table(shell);
		// printf("%s\n", shell->cmd[0].token[0]);
		// printf("%s\n",shell->cmd[0].token[1]);
	}
}

int	parsing_bitch(t_shell *shell)
{
	int	i;

	i = 0;
	if (valid_quotes(shell->promt))
		return (0);
	shell->nb_cmd = count_token(shell->promt, '|');
	shell->cmd = ft_calloc(sizeof(t_shell), shell->nb_cmd);
	if (shell->cmd == NULL)
		ft_exit(shell, 0);//ad free shit
	shell->cmd[0].buffer = trim_token(strtok_(shell->promt, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = trim_token(strtok_(NULL, '|'), ' ');
	printf("%s\n", shell->cmd[0].buffer);
	printf("%s\n",shell->cmd[1].buffer);
	parse_token_bitch(shell);
	//parese the toke --> assign the value of each command in shell->cmd[i].token[t]
	return (1);
}

// void	ft_signal(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(2, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		error_status = 130;
// 	}
// }

void	promt_bitch(char *envp[])
{
	t_shell	*shell;

	shell = get_shell();
	init_shell(envp);
	while (1)
	{
		// signal(SIGINT, ft_signal);
		shell->promt = readline("\033[0;36m\033[1m$minishell ▸ \033[0m");
		add_history(shell->promt);
		parsing_bitch(shell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	promt_bitch(envp);
	return (0);
}

/*
- unset and export functions
- signal 
*/