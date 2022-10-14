#include "../include/minishell.h"

t_data *get_data()
{
	static t_data *data = NULL;

	if(data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

// int array_len(char **array)
// {
// 	int i;

// 	i = 0;
// 	while(array[i])
// 		i++;
// 	return (i);
// }

// char	**init_env(char **env)
// {
// 	int	i;
// 	char	**new_env;
// 	i = -1;
// 	if (env == NULL)
// 		return (NULL);
// 	new_env = (char **)ft_calloc(array_len(env) + 1, sizeof(char *));
// 	while (env[++i])
// 		new_env[i] = ft_strdup(env[i]);
// 	return (new_env);
// }

// char **init_env(char **envp)
// {
// 	int i = -1;
// 	char **env = NULL;
// 	while(envp[++i])
// 	{
// 		env = ft_split(envp[i], '=');
// 		printf("%s", env[0]);
// 	}
// 	return (env);
// }

void init_data(char *envp[])
{
	t_data	*data;

	data = get_data();
	data->line = NULL;
	data->env_name = envp;
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

int single_open(char *prompt)
{
	int i = -1;
	while(prompt[++i])
	{
		if(prompt[i] == DBQUOTE)
		{
			while(prompt[++i])
			{
				if(prompt[i] == DBQUOTE)
				{
					while(prompt[++i])
					{
						if(prompt[i] == SQUOTE)
						{
							if(prompt[i + 1 ] == '\0')
							{
								printf("Single quotes must be closed\n");
								return 1;
							}
							while(prompt[++i])
							{
								if(!(prompt[i] == SQUOTE))
								{
									printf("Single quotes must be closed\n");
									return 1;
								}
							}
						}
					}
				}
			}

		}

	}
	return 0;
}

int double_open(char *prompt)
{
	int i = -1;
	while(prompt[++i])
	{
		if(prompt[i] == SQUOTE)
		{
			while(prompt[++i])
			{
				if(prompt[i] == SQUOTE)
				{
					while(prompt[++i])
					{
						if(prompt[i] == DBQUOTE)
						{
							if(prompt[i + 1 ] == '\0')
							{
								printf("Double quotes must be closed\n");
								return 1;
							}
							while(prompt[++i])
							{
								if(!(prompt[i] == DBQUOTE))
								{
									printf("Double quotes must be closed\n");
									return 1;
								}
							}
						}
					}
				}
			}

		}

	}
	return 0;
}

void cmd_quote_s(t_data *data)
{
	//check if the string is in quotes
	int i = -1;
	char *p = data->line;
	p++;
	p[ft_strlen(p)-1] = 0;

	while(data->line[++i])
	{
		if(data->line[i] == DBQUOTE)
		{
			while(data->line[i])
			{
				
				if(data->line[i] == DBQUOTE)
				{
					// if(data->line[i + 1] == DBQUOTE)
					// {
					// 	check_dioporco(data->line, i, DBQUOTE);
					// 	return ;
					// }
					
					printf("%s: command non found\n", p);
					return ;
				}
			}
		}
	}
}

// void check_dioporco(char *line, int pos, int quotes)
// {
// 	int i = pos + 1;
// 	while(line[i])
// 	{

		
// 	}
// }

void cmd_quote_d(t_data *data)
{
	//check if the string is in quotes
	int i = -1;

	while(data->line[++i])
	{
		if(data->line[i] == SQUOTE)
		{
			while(data->line[i])
			{
				if(data->line[i] == SQUOTE)
				{
					// if(data->line[i + 1] == SQUOTE)
					// {
					// 	check_dioporco(data->line, i, SQUOTE);
					// 	return ;
					// }
					char *p = data->line;
					p++;
					p[ft_strlen(p)-1] = 0;
					printf("%s: command non found\n", p);
					return ;
				}
			}
		}
	}
	
}

int sing_quote(char *prompt)
{
	int s = get_number_quotes(prompt, SQUOTE);
	int d = get_number_quotes(prompt, DBQUOTE);
	if(s % 2 != 0)
	{
		printf("Single quotes must be closed\n");
		return 1;
	}
	if(d % 2 != 0)
	{
		printf("Double quotes must be closed\n");
		return 1;
	}
	return 0;
}

void parsing_bitch(t_data *data)
{
	//check bulit-in
	if(double_open(data->line) == 1)
		return;
	if(single_open(data->line) == 1)
		return ;
	if(sing_quote(data->line) == 1)
		return;
	cmd_quote_s(data);
	cmd_quote_d(data);
}


//add return 0 - 1 to handler all the function

void promt_bitch(char *envp[])
{
	t_data *data;

	data = get_data();
	init_data(envp);
	while(1)
	{
		data->line = readline("\033[0;36m\033[1m$minishell ▸ \033[0m");
		add_history(data->line);
		parsing_bitch(data);
		
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
