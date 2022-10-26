#include "../include/minishell.h"

int		error_status;

char	*strtok_(char *str, char sepa)
{
	static char	*stock;
	char		*ptr;
	int			i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = strdup(str);
	// if (stock == (void *)0)
	// 	return (ptr);
	while (*stock && stock != (void *)0)
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}

void	save_shit(t_shell *shell)
{
	int		i;
	char	**string;

	i = 0;
	string = ft_split(shell->prompt, '|');
	shell->nb_cmd = count_token(string);
	shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);
	while (i < shell->nb_cmd)
	{
		shell->cmd[i].command = strtok_(string[i], ' ');
		while (shell->cmd[i].command)
		{
			shell->cmd[i].option = strtok_(NULL, ' ');
			break ;
		}
		i++;
	}
}
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

//https://linuxhint.com/bash_echo/
void	ft_echo(char *string)
{
	
	//maybe split some command for pipe etc...
	//handle dollar sign
	//handle \ and quotes
	//handle options -n
	printf("string from echo: -->[%s]\n", string);
}

bool	check_bulitin(t_shell *shell)
{
	int	i;
	char *string = shell->prompt;

	i = 0;
	if (strncmp(string, "echo ", 5) == 0)
	{
		ft_echo(string + 5);//delete the initial echo\0
		return (true);
	}
	// else if (strcmp(shell->cmd[i].command, "cd") == 0)
	// 	ft_cd(shell->cmd[i].option);
	// else if (strcmp(shell->cmd[i].command, "pwd") == 0)
	// 	ft_pwd();
	// else if (strcmp(shell->cmd[i].command, "export") == 0)
	// 	ft_export(shell->cmd[i].option);
	// else if (strcmp(shell->cmd[i].command, "unset") == 0)
	// 	ft_unset(shell->cmd[i].option);
	// else if (strcmp(shell->cmd[i].command, "env") == 0)
	// 	ft_env();
	// else if (strcmp(shell->cmd[i].command, "exit") == 0)
	// 	ft_exit(shell->cmd[i].option);

	return (false);
}

void	handling_cmd(t_shell *shell)
{
	if (!check_bulitin(shell))
	{
		printf("Execution command\n");
		run_parent(shell);

		// ft_exec(shell->cmd[i].command, shell->cmd[i].option);
	}
}

char	*strtok_(char *str, char sepa)
{
	static char	*stock;
	char		*ptr;
	int			i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = strdup(str);
	// if (stock == (void *)0)
	// 	return (ptr);
	while (*stock && stock != (void *)0)
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}

void	save_shit(t_shell *shell)
{
	int		i;
	char	**string;

	i = 0;
	string = ft_split(shell->prompt, '|');
	shell->nb_cmd = count_token(string);
	shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);
	while (i < shell->nb_cmd)
	{
		shell->cmd[i].command = strtok_(string[i], ' ');
		while (shell->cmd[i].command)
		{
			shell->cmd[i].option = strtok_(NULL, ' ');
			break ;
		}
		i++;
	}
}


bool	get_valid_cmd(t_shell *shell)
{
	if (invalid_quotes(shell->prompt))
		return (false);
	handling_cmd(shell);
	save_shit(shell);
	print_struct(shell);
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
