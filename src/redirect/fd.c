#include "../../utils/minishell.h"
#include "redirect.h"

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

static t_fd	init_parse_fd(int fd_in, int fd_out)
{
	t_fd	fd;

	fd.i = 0;
	fd.tmp = 0;
	fd.fd = malloc(sizeof(int) * 2);
	if (!fd.fd)
	{
		fd.fd = NULL;
		return (fd);
	}
	fd.fd[0] = fd_in;
	fd.fd[1] = fd_out;
	fd.quote[0] = 0;
	fd.quote[1] = 0;
	return (fd);
}

int	*parse_fd(char *line, int fd_in, int fd_out, t_env *begin_list)
{
	t_fd	fd;

	fd = init_parse_fd(fd_in, fd_out);
	while (line[fd.i])
	{
		func_flag(line, &fd.i, fd.quote);
		if (!fd.quote[0] && !fd.quote[1])
		{
			if (line[fd.i] == '<')
				char_read(line, fd_in, &fd, begin_list);
			else if (line[fd.i] == '>')
			{
				fd.tmp = open_write_fd(line, fd.i);
				if (fd.tmp != -1)
				{
					if (fd.fd[1] != fd_out)
						close(fd.fd[1]);
					fd.fd[1] = fd.tmp;
				}
			}
		}
		if (line[fd.i])
			fd.i++;
	}
	return (fd.fd);
}
