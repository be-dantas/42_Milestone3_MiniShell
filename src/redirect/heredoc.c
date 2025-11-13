#include "../../utils/minishell.h"
#include "redirect.h"

static t_here init_heredoc(char *line)
{
	t_here	here;

	here.result = ft_strdup("");
	here.str = NULL;
	here.to_free = NULL;
	here.eof = strstr(line, "<<");
	here.to_free = ft_split(here.eof, ' ');
	return (here);
}

static char	*heredoc(t_env *begin_list, char *line)
{
	t_here	h;

	h = (init_heredoc(line));
	if (ft_strlen(h.to_free[0]) > 2)
		h.eof = ft_strdup(h.to_free[0] + 2);
	else
		h.eof = ft_strdup(h.to_free[1]);
	while (1)
	{
		write(1, "heredoc > ", 10);
		h.str = readline(NULL);
		if (ft_strcmp(h.str, h.eof) == 0)
			break ;
		h.result = ft_strjoin(h.result, h.str);
		h.result = ft_strjoin(h.result, "\n");
	}
	if ((h.eof[0] == '\'' && h.eof[ft_strlen(h.eof) - 1] == '\'')
			|| (h.eof[0] == '\"' && h.eof[ft_strlen(h.eof) - 1] == '\"'))
		return (h.result);
	else
	{
		h.result2 = expand_arg(begin_list, h.result, 0);
		if (h.result2 == NULL)
			return (h.result);
		else
			return(h.result2);
	}
	return (h.result);
}

int	red_heredoc(t_env *begin_list, char *line)
{
	int		fd[2];
	pid_t	pid;
	char	*result;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		// colocar aqui a tratativa para receber sinais e tratar eles no heredoc
		close(fd[0]);
		result = heredoc(begin_list, line);
		if (result)
			write(fd[1], result, ft_strlen(result));
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return (fd[0]);
	}
}
