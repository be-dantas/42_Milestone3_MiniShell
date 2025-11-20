#include "../../utils/minishell.h"
#include "process.h"

static void	process_one_fork(char **line_tokens, t_shell *sh,
		int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_external(line_tokens, sh->env, fd_in, fd_out);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->last_exit_status = 128 + WTERMSIG(status);
}

void	process_one_split(char **line, t_shell *sh)
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**line_tokens;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	redirect_fd(line[0], STDIN_FILENO, STDOUT_FILENO, sh->env);
	cmd = command(line[0]);
	free_array(line);
	if (cmd == NULL)
	{
		dup2_close_in_out(fd_in, fd_out);
		return ;
	}
	line_tokens = tokens(cmd);
	free(cmd);
	if (is_builtin(line_tokens[0]))
		exec_line(line_tokens, sh);
	else
		process_one_fork(line_tokens, sh, fd_in, fd_out);
	free_array(line_tokens);
	dup2_close_in_out(fd_in, fd_out);
}
