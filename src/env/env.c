#include "../../include/minishell.h"

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

bool	get_env(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = ft_newenv(ft_split(envp[i], '='));
		if (shell->env == NULL && new)
		{
			shell->env = new;
			shell->size++;
		}
		else if (shell->env && new)
		{
			new->next = shell->env;
			shell->env = new;
			shell->size++;
		}
		i++;
	}
	return (true);
}
