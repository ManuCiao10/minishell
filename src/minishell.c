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
	data->cmd = 0;
}




int	main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	(void)argc;
	(void)argv;
	data = get_data();
	init_data(envp);
	while(1)
	{
		data->line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		printf("line: %s", data->line);
	}


	return 0;
}