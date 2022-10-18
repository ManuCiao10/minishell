#include "../include/minishell.h"

t_data *get_data()
{
	static t_data *data = NULL;

	if(data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}


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

// int single_open(char *prompt)
// {
// 	int i = -1;
// 	while(prompt[++i])
// 	{
// 		if(prompt[i] == DBQUOTE)
// 		{
// 			while(prompt[++i])
// 			{
// 				if(prompt[i] == DBQUOTE)
// 				{
// 					while(prompt[++i])
// 					{
// 						if(prompt[i] == SQUOTE)
// 						{
// 							if(prompt[i + 1 ] == '\0')
// 							{
// 								printf("Single quotes must be closed\n");
// 								return 1;
// 							}
// 							while(prompt[++i])
// 							{
// 								if(!(prompt[i] == SQUOTE))
// 								{
// 									printf("Single quotes must be closed\n");
// 									return 1;
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}

// 		}

// 	}
// 	return 0;
// }

// int double_open(char *prompt)
// {
// 	int i = -1;
// 	while(prompt[++i])
// 	{
// 		if(prompt[i] == SQUOTE)
// 		{
// 			while(prompt[++i])
// 			{
// 				if(prompt[i] == SQUOTE)
// 				{
// 					while(prompt[++i])
// 					{
// 						if(prompt[i] == DBQUOTE)
// 						{
// 							if(prompt[i + 1 ] == '\0')
// 							{
// 								printf("Double quotes must be closed\n");
// 								return 1;
// 							}
// 							while(prompt[++i])
// 							{
// 								if(!(prompt[i] == DBQUOTE))
// 								{
// 									printf("Double quotes must be closed\n");
// 									return 1;
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}

// 		}

// 	}
// 	return 0;
// }

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
		printf("EIIIIIII MFQuotes must be closed\n");
		return 1;
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

//add index to save the position of the quote

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

// int sing_quote(char *prompt)
// {
// 	int s = get_number_quotes(prompt, SQUOTE);
// 	int d = get_number_quotes(prompt, DBQUOTE);
// 	if(s % 2 != 0 && s)
// 	{
// 		printf("Single quotes must be closed\n");
// 		return 1;
// 	}
// 	if(d % 2 != 0 && d)
// 	{
// 		printf("Double quotes must be closed\n");
// 		return 1;
// 	}
// 	return 0;
// }
int ft_even(int n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}

int valid_quotes(char *prompt)
{
    int dflag;
    int sflag;
    int ind[2];
    int i;

    dflag = 0;
    sflag = 0;
    i = -1;
    while (prompt[++i])
    {
        if (prompt[i] == DBQUOTE)
        {
            dflag++;
            ind[0] = i;
        }
        else if (prompt[i] == SQUOTE)
        {
            sflag++;
            ind[1] = i;
        }
    }
    if((dflag && ft_even(dflag) && ind[0] < ind[1]) || (!ft_even(dflag) && ind[1] < ind[0] && dflag))
        printf("Open SQuotes: ind0[%d] -- ind1[%d] \n",ind[0], ind[1]);
    else if(( sflag && ft_even(sflag) && ind[1] < ind[0]) || (!ft_even(sflag) && ind[0] < ind[1] && sflag))
        printf("Open DQuotes: ind0[%d] -- ind1[%d] \n",ind[0], ind[1]);
    return(1);
}




void builtin(char *prompt)
{
	if(strncmp(prompt, "exit ", 5) == 0)
		exit(0);
	if(strncmp(prompt, "cd", 2) == 0)
	{
		char *p = prompt;
		p += 3;
		if(chdir(p) == -1)
			printf("cd: no such file or directory: %s\n", p);
	}
	if(strncmp(prompt, "pwd", 3) == 0)
	{
		char *p = getcwd(NULL, 0);
		printf("%s\n", p);
		free(p);
	}
	if(strncmp(prompt, "echo", 4) == 0)
	{
		char *p = prompt;
		p += 5;
		printf("%s\n", p);
	}
	
	
}

void parsing_bitch(t_data *data)
{
	builtin(data->line);
	// if(double_open(data->line))
	// 	return;
	
	// if(single_open(data->line))
	// 	return;
	cmd_quote_s(data);
	cmd_quote_d(data);
	if(valid_quotes(data->line))
		return;
	
	
}




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
