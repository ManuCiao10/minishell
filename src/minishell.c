#include "../include/minishell.h"

int		error_status;

// bool	ft_is_only(char *buffer, char c)
// {
// 	int i;

// 	i = 0;
// 	if (!buffer)
// 		return (false);
// 	while (buffer[i] != '\0')
// 	{
// 		if (buffer[i] != c)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }
// static char	*ft_end_buffer(char *ret, char **save)
// {
// 	*save = NULL;
// 	if (ft_is_only(ret, ' '))
// 		return (NULL);
// 	return (ret);
// }

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

void	handling_cmd(void);

//trim_quotes
//execution cmd

bool	get_valid_cmd(t_shell *shell)
{
	save_shit(shell);
	handling_cmd(shell);
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
