#include "../include/minishell.h"

bool	ft_even(int nb)
{
	if (nb % 2 == 0)
		return (true);
	return (false);
}

// bool execute_cmd(t_shell *data)
// {
// 	if(access())
// }

// ls | cat | dio



bool	char_valid(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (false);
	return (true);
}

char	*dollar_sign(t_shell *data)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = data->env;
	while (data->prompt[i])
	{
		if (data->prompt[i] == 36)
		{
			while (temp)
			{
				if (!ft_strncmp(&data->prompt[i + 1], temp->cmd,
						strlen(temp->cmd)))
				{
					if (char_valid(*(&data->prompt[i + strlen(temp->cmd) + 1])))
						// print_rest()
						//TODO print the rest of the string after the character.
						// TODO Handle this shit buddy $? $#
						return (temp->expand);
				}
				temp = temp->next;
			}
		}
		i++;
	}
	return (NULL);
}
