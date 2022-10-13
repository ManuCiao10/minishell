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

int pari(int n)
{
	if(n % 2 == 0)
		return (1);
	return (0);
}

int dispari(int n)
{
	if(n % 2 != 0)
		return (1);
	return (0);
}

// int err_(int n)
// {
// 	if(n == 1)
// 	{
// 		printf("\t%d\n", n);
// 		printf("Quotes must be closed\n");
// 	}
// 	break;
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
	if(dispari(dflag))
	{
		if(pari(sflag) && sflag)
			printf("dougle quotes GOOD\n");
		else
			return dflag;
	}
	if(dispari(sflag))
	{
		if(pari(dflag) && dflag)
			printf("single quotes GOOD\n");
		else
			return sflag;
	}
	return 0;
}



void parsing_bitch(t_data *data)
{
	// char *dollar; 
	int n = invalid_quotes(data);
	if(n != 0)
	{
		printf("\t%d\n", n);
		printf("Quotes must be closed\n");
		return ;

	}
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


// fix single and double quotes

/*
- add dollar sign
- unset and export functions
- signal 
*/
