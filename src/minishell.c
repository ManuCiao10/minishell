#include "../include/minishell.h"

int		error_status;


// int		quotes(char *line, int index)
// {
// 	int	i;
// 	int	open;

// 	i = 0;
// 	open = 0;
// 	while (line[i] && i != index)
// 	{
// 		if (i > 0 && line[i - 1] == '\\')
// 			;
// 		else if (open == 0 && line[i] == '\"')
// 			open = 1;
// 		else if (open == 0 && line[i] == '\'')
// 			open = 2;
// 		else if (open == 1 && line[i] == '\"')
// 			open = 0;
// 		else if (open == 2 && line[i] == '\'')
// 			open = 0;
// 		i++;
// 	}
// 	return (open);
// }

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
		// run_parent(shell);
		// ft_exec(shell->cmd[i].command, shell->cmd[i].option);
	}
}

char	*strtok_(char *str, char sepa)
{
	static char	*stock;
	char		*save = NULL;

	if (str != NULL)
		stock = strdup(str); //copy the string
	save = stock;
	while(*stock != sepa)
	{
		if (*stock == '\0')  //end of the string
			return (NULL);
		else if(*stock == SQUOTE || *stock == DBQUOTE)
		{
			printf("quote found\n");
			save = strchr(stock + 1, *stock);
			printf("save: %s\n", save);
			if (save == NULL)
				return (NULL);
		}
		stock++;
	}
	*stock = '\0';
	stock++;
	return (save);
}


int	count_token(char *prompt, char del)
{
	char *string;
	char *tmp;
	int i = 0;

	tmp = ft_strdup(prompt);
	string = strtok_(tmp, del);
	while(string)
	{
		string = strtok_(NULL, del);
		i++;
	}
	return (i);
}

void	save_shit(t_shell *shell)
{
	int		i;

	i = 0;
	shell->nb_cmd = count_token(shell->prompt, '|');
	printf("nb_cmd: %d\n", shell->nb_cmd);
	shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);
	
	// shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);

	// shell->cmd[0].command = strtok_(shell->prompt, '|');
	// while(i < shell->nb_cmd)
	// {
	// 	shell->cmd[i].command = strtok_(NULL, '|');
	// 	i++;
	// }
	
}


//count number command
//count numebr of token for each command

bool	get_valid_cmd(t_shell *shell)
{
	if (invalid_quotes(shell->prompt))
		return (false);
	// handling_cmd(shell);
	save_shit(shell);
	// print_struct(shell);
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
