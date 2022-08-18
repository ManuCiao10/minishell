#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini		mini;
	static char	*input;
	int			i;

	i = 0;
	(void)env;
	while (ac && av)
	{
		input = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
		mini.split = ft_split_quotes(input, ' ');
		printf("[%s]", mini.split[0]);
		printf("[%s]", mini.split[1]);
		printf("[%s]", mini.split[2]);
		printf("[%s]", mini.split[3]);
		printf("[%s]", mini.split[4]);
		printf("[%s]", mini.split[5]);
		printf("[%s]", mini.split[6]);
		printf("[%s]", mini.split[7]);
		printf("[%s]", mini.split[8]);
		printf("[%s]", mini.split[9]);
		printf("[%s]", mini.split[10]);
		while(mini.split[i] != NULL)
		{
			if(strcmp(mini.split[i], '|'))
		}
	}
	return (0);
}

int	skip(const char *s, int i, char c)
{
	i++;
	while (s[i] != c)
		i++;
	return (i);
}

size_t	token_count(char *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		printf("I:%zu\n", i);
		if (s[i] != c && s[i])
		{
			printf("wordà\n");
			if (s[i] == '\'')
			{
				skip(s, i, '\'');
				printf("I if:%zu\n", i);
			}
			else if (s[i] == '\"')
			{
				skip(s, i, '\"');
				printf("I else:%zu\n", i);
			}
			nb++;
			while (s[i] != c && s[i])
				i++;
			printf("I:%zu\n", i);
		}
	}
	return (nb);
}
char const	*quote_alloc(char const *s, char **matrix, char c, char quote)
{
	int	len_ptr;

	len_ptr = 0;
	while (s[len_ptr + 1] != quote)
		len_ptr++;
	*matrix = ft_substr(s, 0, (len_ptr + 2));
	s = s + len_ptr;
	s++;
	s++;
	while (*s == c)
		s++;
	return (s);
}
void	ft_matrix_free(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (*(matrix + i))
	{
		free(*(matrix + i));
		i++;
	}
	free(matrix);
	return ;
}
int	is_not_quote(const char *s, char c, int i, char **matrix)
{
	int	len_ptr;

	len_ptr = 0;
	while (s[len_ptr] != c && s[len_ptr])
		len_ptr++;
	matrix[i] = ft_substr(s, 0, len_ptr);
	if (matrix[i] == NULL)
		ft_matrix_free(matrix);
	return (len_ptr);
}

void	letter_alloc(char **matrix, char const *s, char c, size_t nb_token)
{
	size_t	len_ptr;
	size_t	i;

	i = 0;
	while (i < nb_token)
	{
		if (*s == c)
		{
			while (*++s == c)
				;
		}
		if (*s != c && *s != '\'' && *s != '\"')
		{
			len_ptr = is_not_quote(s, c, i, matrix);
			s = s + len_ptr;
		}
		if (*s == '\'')
			s = quote_alloc(s, &matrix[i], c, '\'');
		else if (*s == '\"')
			s = quote_alloc(s, &matrix[i], c, '\"');
		i++;
	}
	matrix[i] = NULL;
}
char	**ft_split_quotes(char *str, char c)
{
	char	**res;
	int		count_word;

	res = NULL;
	count_word = 0;
	count_word = token_count(str, c);
	res = (char **)malloc(sizeof(char *) * (count_word + 1));
	if(!res)
		return NULL;
	letter_alloc(res, str, c, count_word);
	return (res);
}







/*
1. Take the input and dive it based on the Pipe [ | ] ✅ 
1.1 Only if is not in quotes and single quotes (check what is the result)
2. Consequently trim even the other's words with the quotes
3. Assign values command to the variables (Parsing)
4. executing
*/
