#include "../../utils/minishell.h"

static void	func_flag(char *line, int *i, int quote[2])
{
	while (line[*i] && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'')
			quote[0] = !quote[0];
		else if (line[*i] == '\"')
			quote[1] = !quote[1];
		(*i)++;
	}
}

static int	open_write_fd(char *line, int i)
{
	int		start;
	char	*file;
	int		fd;
	int		append;

	append = 0;
	if (line[i + 1] == '>')
	{
		append = 1;
		i += 2;
	}
	else
		i++;
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '<' && line[i] != '>')
		i++;
	file = ft_substr(line, start, i - start);
	if (append == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	return (fd);
}

static int	open_read_fd(char *line, int i)
{
	int		start;
	char	*file;
	int		fd;

	i++;
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '<' && line[i] != '>')
		i++;
	file = ft_substr(line, start, i - start);
	fd = open(file, O_RDONLY, 0444);
	free(file);
	return (fd);
}

int	*parse_fd(char *line)
{
	int		i;
	int		quote[2];
	int		*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	quote[0] = 0;
	quote[1] = 0;
	i = 0;
	while (line[i])
	{
		func_flag(line, &i, quote);
		if (!quote[0] && !quote[1])
		{
			if (line[i] == '<')
			{
				if (fd[0] != STDIN_FILENO)
					close(fd[0]);
				fd[0] = open_read_fd(line, i);
			}
			else if (line[i] == '>')
			{
				if (fd[1] != STDOUT_FILENO)
					close(fd[1]);
				fd[1] = open_write_fd(line, i);
			}
		}
		if (line[i])
			i++;
	}
	return (fd);
}
