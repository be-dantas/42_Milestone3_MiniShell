#include "../utils/minishell.h"

static void	handle_quote_state(char c, int *in_quotes, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = c;
		}
		else if (c == *quote_char)
			*in_quotes = 0;
	}
}

static int	count_args(char *str)
{
	int		count;
	int		in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = 0;
	while (*str)
	{
		while (*str == ' ' && !in_quotes)
			str++;
		if (!*str)
			break ;
		count++;
		while (*str && (in_quotes || *str != ' '))
		{
			handle_quote_state(*str, &in_quotes, &quote_char);
			str++;
		}
	}
	return (count);
}

static int	find_arg_end(char *str, int start)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = start;
	in_quotes = 0;
	while (str[i] && (in_quotes || str[i] != ' '))
	{
		handle_quote_state(str[i], &in_quotes, &quote_char);
		i++;
	}
	return (i);
}

char	**split_with_quotes(char *str)
{
	int		start;
	int		end;
	int		i;
	int		count;
	char	**res;

	count = count_args(str);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	start = 0;
	i = 0;
	while (str[start])
	{
		while (str[start] == ' ')
			start++;
		if (!str[start])
			break ;
		end = find_arg_end(str, start);
		res[i] = ft_strndup(str + start, end - start);
		i++;
		start = end;
	}
	res[i] = NULL;
	return (res);
}
