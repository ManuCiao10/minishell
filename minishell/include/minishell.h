/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/08/18 15:33:29 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****** INCLUDES ****** */

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <string.h>
# include <ctype.h>

/* ****** STRUCTS ****** */

typedef struct mini {
  char **split;
  char **pipe;

}             t_mini;


/* ****** FUNCTIONS ****** */
char	**ft_split_quotes(char *str, char c);
#endif

