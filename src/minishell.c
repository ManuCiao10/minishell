#include "../include/minishell.h"

int			error_status;

void 		print_struct(t_shell *shell)
{
	int i = 0;

	while(i < shell->nb_cmd)
	{
		printf("cmd[%d] = %s\n", i, shell->cmd[i].command);
		printf("option[%d] = %s\n", i, shell->cmd[i].option);
		i++;
	}



}
char	*strtok_(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = strdup(str);
	while (*stock != '\0')
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

int count_token(char **str)
{
	int i = 0;

	while(str[i])
		i++;
	return i;
}

void	save_shit(t_shell *shell)
{
	int		i;
	char **string = ft_split(shell->prompt, '|');

	i = 0;
	shell->nb_cmd = count_token(string);
	shell->cmd = malloc(sizeof(t_cmd) * shell->nb_cmd);
	while (i < shell->nb_cmd)
	{
		shell->cmd[i].command = strtok_(string[i], ' ');
		// printf("cmd: %s\n", shell->cmd[i].command);
		while (shell->cmd[i].command)
		{
			shell->cmd[i].option = strtok_(NULL, ' ');
			// printf("options: %s\n", shell->cmd[i].option);
			break ;
		}
		i++;
	}
}

bool	get_valid_cmd(t_shell *shell)
{

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
