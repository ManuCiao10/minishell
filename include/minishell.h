/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 18:25:28 by eardingh         ###   ########.fr       */
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
# define PIPE 124
# define SPACE 32
# define DOLLAR 36


/* ****** STRUCTS ****** */

typedef struct s_cmd
{
	char			*buffer;
	char			**token;
}					t_cmd;

typedef struct s_env
{
	char			*cmd;
	char			*expand;
	struct s_env	*next;

}					t_env;

typedef struct s_shell
{
	char			*prompt;
	char			**argv;
	int				nb_cmd;
	int				done;
	int				size;
	t_cmd			*cmd;
	char			***cmd_store;
	t_env			*env;

}					t_shell;

/* ****** FUNCTIONS ****** */

/* ****** UTILS ****** */
void				ft_color(int color);

/* ****************************** FUNCTIONS ****************************** */

/* ****** MINISHELL ****** */
bool				init_shell(t_shell *shell, char **argv, char **env);

/* ****** PARSING ****** */
bool				valid_quotes(t_shell *shell);
char				*dollar_sign(t_shell *shell);

/* ****** UTILS ****** */
void				print_env(t_env *env);
int					strrlen(char **tab);

/* ****** INIT ****** */
bool				init_shell(t_shell *shell, char **argv, char **envp);

/* ****** ENVIRONEMENT ****** */
t_env				*ft_newenv(char **content);
bool				get_env(t_shell *shell, char **envp);

#endif
