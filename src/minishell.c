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

int even(int n)
{
	if(n % 2 == 0)
		return (1);
	return (0);
}

int odds(int n)
{
	if(n % 2 != 0)
		return (1);
	return (0);
}


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
	if(odds(dflag))
	{
		if(!(even(sflag) && sflag))
			return dflag;
	}
	if(odds(sflag))
	{
		if(!(even(dflag) && dflag))
			return sflag;
	}
	return 0;
}


void check_quotes(t_data *data)
{
	int n = invalid_quotes(data);
	if(n != 0)
	{
		printf("\t%d\n", n);
		printf("Quotes must be closed\n");
		return ;
	}
}

void parsing_bitch(t_data *data)
{
	// char *dollar; 
	check_quotes(data);

	// dollar = dollar_sign(data);
	// printf("%s", dollar);

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



//if the pipe the only one elemt in the quotes do to NOT take it
// "ls|cat" --> TAKE IT

/*
- unset and export functions
- signal 
*/
