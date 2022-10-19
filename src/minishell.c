#include "../include/minishell.h"

int error_status;

t_shell *get_shell()
{
	static t_shell *shell = NULL;

	if(shell == NULL)
		shell = (t_shell *)malloc(sizeof(t_shell));
	return (shell);
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
	if(valid_quotes(shell->line))
		return 0;
	shell->cmd = ft_calloc(sizeof(t_shell), shell->nb_cmd);
	if(shell->cmd == NULL)
		ft_exit(shell, 0);
	//save nb_command;
	shell->cmd[0].buffer = trim_token(strtok_(shell->line, '|'), ' ');
	while(++i < shell->nb_cmd)
		shell->cmd[i].buffer = trim_token(strtok_(NULL, '|'), ' ');
	printf("%s", shell->cmd[0].buffer);
	
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
