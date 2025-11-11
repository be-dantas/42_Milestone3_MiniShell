#include "../../utils/minishell.h"

void	func_flag(char *line, int *i, int quote[2])
{
	while (line[*i])
	{
		if (line[*i] == '\'')
			quote[0] = !quote[0];
		else if (line[*i] == '\"')
			quote[1] = !quote[1];
		else if (line[*i] == '|' && !quote[0] && !quote[1])
			break ;
		(*i)++;
	}
}

size_t	count_pipe(char *line)
{
	int	i;
	int	count;
	int	quote[2];

	i = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (line[i])
	{
		func_flag(line, &i, quote);
		if (line[i] == '|' && !quote[0] && !quote[1])
			count++;
		if (line[i])
			i++;
	}
	return (count);
}

char	**split_pipe(char *line, int i, int j)
{
	int		start;
	int		i_pipe;
	char	**res;
	int		quote[2];

	i_pipe = count_pipe(line);
	res = malloc(sizeof(char *) * (i_pipe + 2));
	quote[0] = 0;
	quote[1] = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		start = i;
		func_flag(line, &i, quote);
		res[j++] = ft_substr(line, start, i - start);
		if (line[i] == '|')
			i++;
	}
	res[j] = NULL;
	return (res);
}
