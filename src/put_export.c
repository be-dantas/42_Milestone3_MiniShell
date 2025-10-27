#include "../utils/minishell.h"

int	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	valid_arg_value(char *str)
{
	int		i;
	int		count;
	char	x;
	int		len;

	i = 0;
	count = 0;
	x = str[0];
	len = ((int)ft_strlen(str) - 1);
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == '\"' || str[i] == '\'' || str[len] == '\"' || str[len] == '\'')
	{
		if (str[i] != str[len])
			return (0);
		while (str[i])
		{
			if (str[i] == x)
				count++;
			i++;
		}
		if (count % 2 != 0)
			return (0);
	}
	return (1);
}

int	valid_arg_name(char *str)
{
	int	i;
	
	i = 0;
	if (!have_equal(str))
		return (0);
	else
	{
		if (!ft_isalpha(str[0]))
			return(0);
		while (str[i] != '=')
		{
			if (ft_isalnum(str[i]))
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int valid_arg(char **split_line)
{
	int i;

	i = 1;
	while (split_line[i])
	{
		if (valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}








static int	count_args(char *str)
{
	int count = 0;
	int in_quotes = 0;
	char quote_char = 0;

	while (*str)
	{
		while (*str == ' ' && !in_quotes)
			str++;
		if (!*str)
			break;
		count++;
		while (*str && (in_quotes || *str != ' '))
		{
			if ((*str == '\'' || *str == '"'))
			{
				if (!in_quotes)
				{
					in_quotes = 1;
					quote_char = *str;
				}
				else if (*str == quote_char)
					in_quotes = 0;
			}
			str++;
		}
	}
	return (count);
}

char	**split_with_quotes(char *str)
{
	int		in_quotes = 0;
	char	quote_char = 0;
	int		arg_count = count_args(str);
	char	**result = malloc((arg_count + 1) * sizeof(char *));
	int		start = 0, end = 0, arg_i = 0;

	while (str[end])
	{
		while (str[start] == ' ')
			start++;
		if (!str[start])
			break;
		end = start;
		in_quotes = 0;
		while (str[end] && (in_quotes || str[end] != ' '))
		{
			if ((str[end] == '\'' || str[end] == '"'))
			{
				if (!in_quotes)
				{
					in_quotes = 1;
					quote_char = str[end];
				}
				else if (str[end] == quote_char)
					in_quotes = 0;
			}
			end++;
		}
		result[arg_i] = strndup(str + start, end - start);
		arg_i++;
		start = end;
	}
	result[arg_i] = NULL;
	return (result);
}


void	put_export(char *line, t_env *env)
{
	int		i;
	char	**split_line;

	i = 1;
	split_line = split_with_quotes(line);
	(void)env;
	if (valid_arg(split_line))
	{
		while (split_line[i])
		{
			check_to_put(split_line[i], &env);
			i++;
		}
	}
	else
		putstr_exit("ARG invalid", split_line, 1); //ainda nao limpa todo env criado, etc...
}
