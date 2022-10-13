#include "../include/minishell.h"

t_data *get_data()
{
	static t_data *data = NULL;

	if(data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

int array_len(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}

char	**init_env(char **env)
{
	int	i;
	char	**new_env;
	i = -1;
	if (env == NULL)
		return (NULL);
	new_env = (char **)ft_calloc(array_len(env) + 1, sizeof(char *));
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	return (new_env);
}

void init_data(char *envp[])
{
	t_data	*data;

	data = get_data();
	data->line = NULL;
	data->env = init_env(envp);
	// data->cmd = malloc
}




// add double and single quotes
// void no_build_in(t_data *data)
// {
// 	//add pipe in quotes
// 	int i = 0;
// 	int dflag = 0;
// 	char **cmd = malloc(sizeof(char *) * 3);
// 	int init = 0;
// 	int pos = 0;
// 	int sflag = 0;
// 	int last = ft_strlen(data->line);
// 	while (data->line[i])
// 	{
// 		if(data->line[i] == DBQUOTE)
// 			dflag++;
// 		if(data->line[i] == SQUOTE)
// 			sflag++;
// 		if(is_even(dflag) && data->line[i] == PIPE)
// 		{
// 			//''word'' or ""word"" 
// 			cmd[pos] = ft_substr(data->line, init, i - init);
// 			printf("cmd = %s\n", cmd[pos]);
// 			pos += 1;
// 			init = i + 1;
// 		}
// 		i++;
// 		if (i == last)
// 		{
// 			cmd[pos] = ft_substr(data->line, init, i - init);
// 			printf("cmd_last = %s\n", cmd[pos]);
// 		}
// 		// printf("i = %d\n", i);
// 	}
// }

int invalid_quotes(t_data *data)
{
	int dflag = 0;
	int sflag = 0;
	int i = -1;

	while(data->line[++i])
	{
		if(data->line[i] == DBQUOTE)
			dflag++;
		if(data->line[i] == SQUOTE)
			sflag++;
	}
	if ((dflag % 2) != 0 && dflag)
	{
		printf("\t%d\n", dflag);
		printf("Quotes must be closed\n");
		return (0);
	}
	else if ((sflag % 2) != 0 && sflag)
	{
		printf("\t%d\n", sflag);
		printf("Quotes must be closed\n");
		return (0);
	}
	return (1);
										
}




void parsing_bitch(t_data *data)
{
	//$dollar sign

	if(invalid_quotes(data))
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
		parsing_bitch(data);
		add_history(data->line);
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
- parsing/tokenize
- unset and export functions
- add_history (to Print the history use: cat ~/.bash_history)
- signal 
*/
