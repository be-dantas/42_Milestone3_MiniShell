#include "../../utils/minishell.h"
#include "redirect.h"

static int	check_pipe_error(char *line, int i)
{
	int	j;

	j = i + 1;
	if (line[i + 1] == '|')
		return (1);
	while (line[j] && line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|')
		return (1);
	return (0);
}

static int	valid_pipe(char *line, t_valid *v, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (0);
	while (line[i])
	{
		if (line[i] == '\'' && !v->quote1)
			v->quote2 = !v->quote2;
		else if (line[i] == '\"' && !v->quote2)
			v->quote1 = !v->quote1;
		else if (line[i] == '|' && !v->quote1 && !v->quote2)
		{
			if (check_pipe_error(line, i))
				return (0);
			v->last_pipe = 1;
		}
		else if (line[i] != ' ')
			v->last_pipe = 0;
		if (line[i] != ' ')
			v->found_char = 1;
		i++;
	}
	if (v->quote2 || v->quote1 || v->last_pipe || !v->found_char)
		return (0);
	return (1);
}

static int	valid_red_utils(char *line, char c, int *i)
{
	int	count;
	int	j;

	count = 0;
	while (line[*i + count] == c)
		count++;
	if (count > 2)
		return (0);
	if ((c == '>' && line[*i + count] == '<')
		|| (c == '<' && line[*i + count] == '>'))
		return (0);
	j = *i + count;
	while (line[j] && line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|' || line[j] == '>' || line[j] == '<')
		return (0);
	*i += count - 1;
	return (1);
}

static int	valid_red(char *line, t_valid *v, char c)
{
	int	i;

	i = 0;
	v->quote1 = 0;
	v->quote2 = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !v->quote1)
			v->quote2 = !v->quote2;
		else if (line[i] == '"' && !v->quote2)
			v->quote1 = !v->quote1;
		else if (line[i] == c && !v->quote1 && !v->quote2)
		{
			if (!valid_red_utils(line, c, &i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	valid_input(char *line)
{
	t_valid	v;

	v.quote1 = 0;
	v.quote2 = 0;
	v.last_pipe = 0;
	v.found_char = 0;
	if (!valid_pipe(line, &v, 0)
		|| !valid_red(line, &v, '>') || !valid_red(line, &v, '<'))
		return (0);
	return (1);
}
