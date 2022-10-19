#include "../include/minishell.h"

int error_status;

t_shell *get_shell()
{
	static t_shell *shell = NULL;

	if(shell == NULL)
		shell = (t_shell *)malloc(sizeof(t_shell));
	return (shell);
}

void	ft_color(int color)
{
	if (color == 1)
		printf("\033[1;31m");
	else if (color == 2)
		printf("\033[1;32m");
	else if (color == 3)
		printf("\033[1;33m");
	else if (color == 4)
		printf("\033[1;34m");
	else if (color == 5)
		printf("\033[1;35m");
	else if (color == 6)
		printf("\033[1;36m");
	else if (color == 7)
		printf("\033[1;37m");
	else if (color == 8)
		printf("\033[0;0m");
}

int	ft_pipe_count(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (shell->line[i])
	{
		if (shell->line[i] == '|')
		{
			if (shell->line[i + 1] == '|')
			{
				shell->line[i] = '\0';
				shell->nb_cmd = count;
				printf("pipe count return %d\n", count);
				return (0);
			}
			i++;
			while(shell->line[i] == ' ')
				i++;
			if (shell->line[i] == '|')
			{
				shell->nb_cmd = 0;
				printf("syntax error near unexpected token `|'\n");
				return (1);
			}
			count++;
		}
		i++;
	}
	shell->nb_cmd = count;
	printf("pipe count return %d\n", count);
	return (0);
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

void init_data(char *envp[])
{
	t_shell	*shell;

	shell = get_shell();
	shell->line = NULL;
	shell->env_name = envp;
	// data->cmd = malloc
}


int get_number_quotes(char *line, int quotes)
{
	int i = 0;
	int c = 0;
	while(line[i])
	{
		if(line[i] == quotes)
			c++;
		i++;
	}
	return (c);
}


int double_open(char *prompt)
{
	int d = 0;
	int s = 0;
	int i = -1;
	while(prompt[++i])
	{
		if(prompt[i] == SQUOTE)
			s++;
		if(prompt[i] == DBQUOTE)
			d++;
	}
	if((d % 2 != 0 && d) || (s % 2 != 0 && s))
	{
		printf("Quotes must be closed\n");
		return 1;
	}
	return 0;
}





void *free_(void *ptr)
{
	if(ptr != NULL)
		free(ptr);
	return (NULL);
}




int ft_even(int n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}

bool valid_quotes(char *buf)
{
	int	i;
	int	d;
	int	s;

	i = -1;
	d = 0;
	s = 0;
	while (buf[++i]){
		if (buf[i] == '\"')
			d++;
		if (buf[i] == '\'')
			s++;
	}
	if ((d && (d % 2) != 0) || (s && (s % 2)) != 0){
		printf("Error: Quote not closed\n");
		return (true);
	}
	return (false);
}


void ft_exit(t_shell *data, int status)
{
	free_(data);
	exit(status);

}

bool builtin(t_shell *data)
{
	if(strncmp(data->line, "exit ", 5) == 0)
		ft_exit(data, 0);
	else if(strncmp(data->line, "cd", 2) == 0)
	{
		char *p = data->line;
		p += 3;
		if(chdir(p) == -1)
			printf("cd: no such file or directory: %s\n", p);
	}
	// else if(strncmp(data->line, "pwd", 3) == 0)
	// {
	// 	char *p = getcwd(NULL, 0);
	// 	printf("%s\n", p);
	// 	free_(p);
	// }
	// else if(strncmp(data->line, "echo", 4) == 0)
	// {
	// 	char *p = data->line;
	// 	p += 5;
	// 	printf("%s\n", p);
	// }
	else
		return false;
	return true;
	
	
}

bool is_only(char *line, char c)
{
	int i = 0;
	if(!line)
		return false;
	while(line[i])
	{
		if(line[i] != c)
			return false;
		i++;
	}
	return true;
}

static char *buffer_end(char *str, char **s)
{
	*s = NULL;
	if(is_only(str, ' '))
		return NULL;
	return str;
	
}

char *strtok_(char *str, char delim)
{
	static char *s;
	char *token;
	
	if(!s)
		s = str;
	token = s;
	while(s && *s == ' ')
		s++;
	while(s && *s != delim)
	{
		if(*s == '\0')
		    return buffer_end(token, &s);
		else if(*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if(!s)
				return (token);
			s++;
		}
		else
			s++;
	}
	if(s)
		*s++ = '\0';
	return (s);
}


char *trim_token(char *token, char sep)
{
	int i = 0;
	if(!token)
		return token;
	i = ft_strlen(token) - 1;
	while(token[i] == sep)
	{
		token[i] = '\0';
		i--;
	}
	while(*token == sep)
		token++;
	return token;
}

int parsing_bitch(t_shell *shell)
{
	int i = 0;
	// builtin(data);
	if(valid_quotes(shell->line) || ft_pipe_count(shell))
		return 0;
	shell->cmd = ft_calloc(sizeof(t_shell), shell->nb_cmd);
	if(shell->cmd == NULL)
		ft_exit(shell, 0);
	//save nb_command;
	shell->cmd[0].buffer = trim_token(strtok_(shell->line, '|'), ' ');
	while(++i < shell->nb_cmd)
		shell->cmd[i].buffer = trim_token(strtok_(NULL, '|'), ' ');
	ft_print_table(shell);
	
	return 1;
	
}

void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		error_status = 130;
	}
}

void promt_bitch(char *envp[])
{
	t_shell *shell;

	shell = get_shell();
	init_data(envp);
	while(1)
	{
		// signal(SIGINT, ft_signal);
		shell->line = readline("\033[0;36m\033[1m$minishell ▸ \033[0m");
		add_history(shell->line);
		parsing_bitch(shell);
		
	}

}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	promt_bitch(envp);
	return 0;
}





/*
- unset and export functions
- signal 
*/
