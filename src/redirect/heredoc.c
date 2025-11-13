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

static void	heredoc(t_env *begin_list, char *line)
{
	t_here	h;

	h = (init_heredoc(line));
	if (ft_strlen(h.to_free[0]) > 2)
		h.eof = ft_strdup(h.to_free[0] + 2);
	else
		h.eof = ft_strdup(h.to_free[1]);
	while (1)
	{
		h.str = readline("heredoc > ");
		if (ft_strcmp(h.str, h.eof) == 0)
			break ;
		h.result = ft_strjoin(h.result, h.str);
		h.result = ft_strjoin(h.result, "\n");
	}
	if ((h.eof[0] == '\'' && h.eof[ft_strlen(h.eof) - 1] == '\'')
			|| (h.eof[0] == '\"' && h.eof[ft_strlen(h.eof) - 1] == '\"'))
		printf("%s", h.result);
	else
	{
		h.result2 = expand_arg(begin_list, h.result, 0);
		if (h.result2 == NULL)
			printf("%s", h.result);
		else
			printf("%s", h.result2);
	}
}

int	red_heredoc(t_env *begin_list, char *line)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		// Filho: escreve no pipe
		// colocar aqui a tratativa para receber sinais e tratar eles no heredoc
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		heredoc(begin_list, line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Pai: lê do pipe
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return (fd[0]);
	}
}
