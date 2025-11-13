#include "../../utils/minishell.h"

static void	update_quotes(char c, int flag[2])
{
	if (c == '\'' && flag[1] == 0)
		flag[0] = !flag[0];
	else if (c == '"' && flag[0] == 0)
		flag[1] = !flag[1];
}

static int	skip_redirection(char *line, int i, int flag[2])
{
	while (line[i] == '>' || line[i] == '<')
		i++;
	while (line[i] == ' ')
		i++;
	while (line[i] && !(line[i] == ' ' && flag[0] == 0 && flag[1] == 0)
		&& line[i] != '<' && line[i] != '>')
	{
		update_quotes(line[i], flag);
		i++;
	}
	while (line[i] == ' ')
		i++;
	return (i);
}

//command(str, 0, 0, ft_strdup(""));
char	*command(char *line, int i, int len, char *result)
{
	int	flag[2];

	flag[0] = 0;
	flag[1] = 0;
	while (line[i])
	{
		update_quotes(line[i], flag);
		if ((line[i] == '>' || line[i] == '<') && flag[0] == 0 && flag[1] == 0)
		{
			i = skip_redirection(line, i, flag);
			continue ;
		}
		if (line[i] == ' ' && (result[0] == '\0'
				|| result[ft_strlen(result) - 1] == ' '))
		{
			i++;
			continue ;
		}
		result = ft_strjoin_char(result, line[i]);
		i++;
	}
	len = ft_strlen(result);
	while (len > 0 && result[len - 1] == ' ')
		result[--len] = '\0';
	if (!result || result[0] == '\0')
	{
		free(result);
		return (NULL);
	}
	return (result);
}
