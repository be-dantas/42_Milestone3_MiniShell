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
			{
				if_read(line, fd_in, &fd, begin_list);
				if (line[fd.i])
					continue ;
			}
			else if (line[fd.i] == '>')
			{
				if_write(line, fd_out, &fd);
				if (line[fd.i])
					continue ;
			}
		}
		if (line[fd.i])
			fd.i++;
	}
	return (fd.fd);
}
