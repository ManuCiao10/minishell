
#include "../../include/minishell.h"

int		open_quotes(char *line)
{
	int	i;
	int	status;
	i = 0;
	status = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			continue ;
		else if (status == 0 && line[i] == '\"')
			status = 1;
		else if (status == 0 && line[i] == '\'')
			status = 2;
		else if (status == 1 && line[i] == '\"')
			status = 0;
		else if (status == 2 && line[i] == '\'')
			status = 0;
		i++;
	}
	return (status);
}

