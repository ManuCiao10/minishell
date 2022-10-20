/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 08:41:19 by eardingh         ###   ########.fr       */
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
#include <stdbool.h>

#define DBQUOTE 34
#define SQUOTE 39
#define PIPE 124
#define SPACE 32
#define DOLLAR 36

/* ****** TOKENS ****** */

/* ****** STRUCTS ****** */

typedef struct s_cmd
{
	char *buffer;
	char **token;
} t_cmd;


typedef struct s_shell
{
	char *promt;
	char **env_name;
	int nb_cmd;
	t_cmd *cmd;

} t_shell;

/* ****** FUNCTIONS ****** */

/* ****** UTILS ****** */
void	ft_color(int color);

#endif
