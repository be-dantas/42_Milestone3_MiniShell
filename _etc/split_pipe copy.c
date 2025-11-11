#include "../../utils/minishell.h"
#include "redirect.h"

static void	func_flag(char *line, int *i, int quote[2])
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

static size_t	count_pipe(char *line)
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

char	**split_pipe(char *line)
{
	t_split_pipe	sp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	sp.i_pipe = count_pipe(line);
	sp.res = malloc(sizeof(char *) * (sp.i_pipe + 2));
	sp.quote[0] = 0;
	sp.quote[1] = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		sp.start = i;
		func_flag(line, &i, sp.quote);
		if (line[i] == '|' && !sp.quote[0] && !sp.quote[1])
			sp.res[j++] = ft_substr(line, sp.start, i - sp.start + 1);
		if (line[i])
			i++;
	}
	if (i > sp.start)
		sp.res[j++] = ft_substr(line, sp.start, i - sp.start);
	sp.res[j] = NULL;
	return (sp.res);
}
