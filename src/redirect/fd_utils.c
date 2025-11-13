#include "../../utils/minishell.h"
#include "redirect.h"

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

void	char_read(char *line, int fd_in, t_fd *fd, t_env *begin_list)
{
	int	tmp;

	tmp = 0;
	if (line[fd->i] == '<' && line[fd->i + 1] != '<')
	{
		tmp = open_read_fd(line, fd->i);
		if (tmp != -1)
		{
			if (fd->fd[0] != fd_in)
				close(fd->fd[0]);
			fd->fd[0] = tmp;
		}
	}
	else if (line[fd->i] == '<' && line[fd->i + 1] == '<')
	{
		tmp = red_heredoc(begin_list, line);
		if (tmp != -1)
		{
			if (fd->fd[0] != fd_in)
				close(fd->fd[0]);
			fd->fd[0] = tmp;
		}
	}
}
