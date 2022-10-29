#include "../../include/minishell.h"

int			error_status;

int	invalid_quotes(char *buf)
{
	char	*tmp;

	tmp = buf;
	while (*tmp)
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			if (ft_strchr(tmp + 1, *tmp) == NULL)
			{
				printf("Error Quote not closed\n");
				return (1);
			}
			else
				tmp = ft_strchr(tmp + 1, *tmp);
		}
		tmp++;
	}
	return (0);
}

bool	only(char *buffer, char c)
{
	int	i;

	i = 0;
	if (!buffer)
		return (false);
	while (buffer[i] != '\0')
	{
		if (buffer[i] != c)
			return (false);
		i++;
	}
	return (true);
}

static char	*check_empty(char *tmp, char **save)
{
	*save = NULL;
	if (only(tmp, ' '))
		return (NULL);
	return (tmp);
}

t_link	*new_list(char *command)
{
	t_link	*cmd;

	cmd = malloc(sizeof(t_link));
	if (!cmd)
		return (NULL);
	cmd->token = command;
	cmd->next = NULL;
	return (cmd);
}

char	*strtok_(char *buffer, char sep)
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
			return (check_empty(ret, &save));
		else if (*save == '\'' || *save == '\"')
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

int	count_token(char *prompt, char del)
{
	char	*string;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(prompt);
	string = strtok_(tmp, del);
	while (string)
	{
		string = strtok_(NULL, del);
		i++;
	}
	return (i);
}

// void	ft_print_table(t_shell *shell)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < shell->nb_cmd)
// 	{
// 		j = 0;
// 		while (j < shell->cmd[i].nb_token)
// 		{
// 			printf("cmd[%d][%d]=> [%s]\n", i, j, shell->cmd[i].token[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	parse_token(t_shell *shell)
// {
// 	int	t;
// 	int	c;

// 	c = -1;
// 	while (++c < shell->nb_cmd)
// 	{
// 		shell->cmd[c].nb_token = count_token(shell->cmd[c].command, ' ');
// 		shell->cmd[c].token = ft_calloc(sizeof(char *), shell->cmd[c].nb_token
// 				+ 1);
// 		if (!shell->cmd[c].token)
// 			exit(1);
// 		t = 0;
// 		shell->cmd[c].token[t] = strtok_(shell->cmd[c].command, ' ');
// 		while (shell->cmd[c].token[t++])
// 			shell->cmd[c].token[t] = strtok_(NULL, ' ');
// 		shell->cmd[c].save = shell->cmd[c].token;
// 	}
// }

// void	save_shit(t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	shell->nb_cmd = count_token(shell->prompt, '|');
// 	shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);
// 	shell->cmd[0].command = strtok_(shell->prompt, '|');
// 	while (++i < shell->nb_cmd)
// 		shell->cmd[i].command = strtok_(NULL, '|');
// 	parse_token(shell);
// }

/*

---"ls -e" | cat | wc----

cmd[0]->command[0] = "ls -e"
cmd[1]->command[0] = "cat"
cmd[2]->command[0] = "wc"

---ls -e | cat | wc----

cmd[0]->command[0] = "ls"
cmd[0]->command[1] = "-e"
cmd[1]->command[0] = "cat"
cmd[2]->command[0] = "wc"

*/

void	print_link(t_link *link)
{
	while (link)
	{
		printf("link->token => [%s]\n", link->token);
		link = link->next;
	}
}

int	num_node(t_link *link)
{
	t_link	*token;
	int		i;

	token = link;
	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

bool	save_link(t_shell *shell)
{
	t_link	*link;
	int		i;

	link = NULL;
	i = 0;
	shell->nb_cmd = count_token(shell->prompt, '|');
	while (i < shell->nb_cmd)
	{
		link = new_list((strtok_(shell->prompt, '|')));
		if (shell->link == NULL && link)
			shell->link = link;
		else if (shell->link && link)
		{
			link->next = shell->link;
			shell->link = link;
		}
		i++;
	}
	print_link(link);
	return (true);
}

bool	get_valid_cmd(t_shell *shell)
{
	if (invalid_quotes(shell->prompt))
		return (false);
	save_link(shell);
	// save_shit(shell);
	// ft_print_table(shell);
	// execution(shell);
	return (true);
}

bool	parsing(t_shell *shell)
{
	get_valid_cmd(shell);
	return (true);
}

void	prompting(t_shell *shell)
{
	while (!shell->done)
	{
		shell->prompt = readline("\033[0;36m\033[1m$minishell ▸ \033[0m");
		add_history(shell->prompt);
		parsing(shell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	if (argc == 1)
	{
		if (!init_shell(&shell, argv, envp))
			return (false);
		prompting(&shell);
	}
	return (0);
}

//add trim space
//try to divide by space
//fix momory leaks and improve loop function