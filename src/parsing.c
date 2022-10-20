#include "../include/minishell.h"

bool	ft_even(int nb)
{
	if (nb % 2 == 0)
		return (true);
	return (false);
}

char *get_valid_cmd(t_shell *data)
{
	int i = 0;
	while(data->prompt[i])
		printf("data->prompt[i] %c\n", data->prompt[i]);
	return(data->prompt);

}


// bool execute_cmd(t_shell *data)
// {
// 	if(access())
// }

// ls | cat | dio

bool valid_quotes(t_shell *data)
{
	int dflag;
	int sflag;
	int ind[2];
	int i;

	dflag = 0;
	sflag = 0;
	i = -1;
	while (data->prompt[++i])
	{
		if (data->prompt[i] == DBQUOTE)
		{
			dflag++;
			ind[0] = i;
		}
		else if (data->prompt[i] == SQUOTE)
		{
			sflag++;
			ind[1] = i;
		}
		// if(ft_even(dflag))
		// 	dflag =0;
		// if(ft_even(sflag))
		// 	sflag =0;
	}
	if(dflag && ((ft_even(dflag) && ind[0] < ind[1]) || (!ft_even(dflag) && ind[1] < ind[0])))
		printf("Open SQuotes: ind0[%d] -- ind1[%d] \n",ind[0], ind[1]);
	else if(sflag && ((ft_even(sflag) && ind[1] < ind[0]) || (!ft_even(sflag) && ind[0] < ind[1])))
		printf("Open DQuotes: ind0[%d] -- ind1[%d] \n",ind[0], ind[1]);
	return(true);
}

	bool char_valid(int c)
	{
		if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
			return (false);
		return (true);
	}

	char *dollar_sign(t_shell * data)
	{
		int i;
		t_env *temp;

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
