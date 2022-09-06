/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:13:01 by hsaadi            #+#    #+#             */
/*   Updated: 2022/09/06 09:31:15 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****** INCLUDES ****** */

# include "libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define DBQUOTE 34
# define SQUOTE 39

/* ****** TOKENS ****** */

typedef struct s_cmd
{
	char *buffer; //indivividual buffer
	char **token; //tokenized buffer
	char *path;   //for execve path
	int		infile;
	int		outfile;

}			t_cmd;

/* ****** STRUCTS ****** */

typedef struct s_data
{
	char	**env;
	char *buffer;  //buffer for readline
	char *prompt;  //prompt message for readline
	int cmd_count; //count of commands
	t_cmd *cmd;    //array of cmdmi

}			t_data;

/* ****** FUNCTIONS ****** */
void		print_token(t_data *data);
char		*ft_strtok(char *buffer, char sep);
int			ft_token_count(char *buffer, char sep);
void		parsing(t_data *data);
int			ft_array_size(char **array);
void		exit_err(t_data *data, char *str, int s);
void		print_env(t_data *data);
int			ft_is_only(char *str, char c);
void		ft_color(int color);
char		*ft_remove_char(char *token, char sep);
char		*ft_strjoin_2(char *s1, char const *s2, int f);

#endif
