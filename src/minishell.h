/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 18:12:47 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****** INCLUDES ****** */

# include "libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define DBQUOTE 34
# define SQUOTE 39

/* ****** TOKENS ****** */
typedef struct s_env
{
	char			*cmd;
	char			*expand;

	struct s_env	*next;

}					t_env;

typedef struct s_built
{
	char			*cmd;
	char			**options;

	struct s_env	*next;

}					t_built;

/* ****** STRUCTS ****** */
typedef struct s_data
{
	char			*prompt;
	char			**argv;
	int				done;
	int				size;

	char			***cmd;
	t_env			*env;

}					t_shell;

/* ****** FUNCTIONS ****** */

/* ****** MINISHELL ****** */
bool				init_shell(t_shell *data, char **argv, char **env);

/* ****** PARSING ****** */
bool				valid_quotes(t_shell *data);
char				*dollar_sign(t_shell *data);

/* ****** UTILS ****** */
void				print_env(t_env *env);

/* ****** ENVIRONEMENT ****** */
t_env				*ft_newenv(char **content);
bool				get_env(t_shell *data, char **envp);

#endif
