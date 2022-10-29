#include "../../include/minishell.h"

void	msg_exit(char *error)
{
	write(2, "Exit: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
