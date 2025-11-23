#include "../../../utils/minishell.h"
#include "../redirect.h"

static pid_t	g_heredoc_child = -1;

static void	parent_sigint(int sig)
{
	(void)sig;
	write(1, "^C\n", 2);
	if (g_heredoc_child > 0)
		kill(g_heredoc_child, SIGKILL);
	write(1, "\n", 1);
}

static void	restore_terminal(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHO;
	t.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static void	pid_zero(t_shell *sh, int i, int fd[2])
{
	char	*result;
	int		tty;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	tty = open("/dev/tty", O_RDWR);
	dup2(tty, STDIN_FILENO);
	dup2(tty, STDOUT_FILENO);
	close(tty);
	close(fd[0]);
	result = heredoc(sh, i);
	if (result)
	{
		write(fd[1], result, ft_strlen(result));
		free(result);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	red_heredoc(t_shell *sh, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		pid_zero(sh, i, fd);
	else
	{
		g_heredoc_child = pid;
		signal(SIGINT, parent_sigint);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		restore_terminal();
		g_heredoc_child = -1;
		signal(SIGINT, handle_sigint);
	}
	return (fd[0]);
}
