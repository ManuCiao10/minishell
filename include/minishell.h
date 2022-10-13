/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/12 16:48:59 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/* ****** INCLUDES ****** */

#include "libft/libft.h"
#include <ctype.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DBQUOTE 34
#define SQUOTE 39
#define PIPE 124

/* ****** TOKENS ****** */

/* ****** STRUCTS ****** */

typedef struct s_data
{
	char *line;
	char **env;

} t_data;

/* ****** FUNCTIONS ****** */

#endif
