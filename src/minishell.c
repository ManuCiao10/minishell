#include "../include/minishell.h"

//assign value to the struct -->malloc struct

char	*strtok_(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
			// printf("ptr = %s\n", ptr);
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	// printf("Final_ptr = %s\n", ptr);
	return (ptr);
}


void	save_shit(char **string)
{
	int		i;
	char	*token;

	i = 0;
	while (string[i])
	{
		token = strtok_(string[i], ' ');
		printf("cmd: %s\n", token);
		while (token != NULL)
		{
			token = strtok_(NULL, ' ');
			printf("options: %s\n", token);
			break ;
		}
		i++;
	}
}

bool	get_valid_cmd(t_shell *shell)
{
	char	**buff;

	buff = ft_split(shell->prompt, '|');
	save_shit(buff);
	// print_shit(shell);
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
