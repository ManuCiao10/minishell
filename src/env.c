#include "../include/minishell.h"

t_env	*ft_newenv(char **content)
{
	t_env	*n_element;

	n_element = malloc(sizeof(t_env));
	if (!n_element)
		return (NULL);
	n_element->cmd = content[0];
	n_element->expand = content[1];
	n_element->next = NULL;
	return (n_element);
}

bool	get_env(t_shell *data, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = ft_newenv(ft_split(envp[i], '='));
		if (data->env == NULL && new)
		{
			data->env = new;
			data->size++;
		}
		else if (data->env && new)
		{
			new->next = data->env;
			data->env = new;
			data->size++;
		}
		i++;
	}
	return (true);
}
