#include "../../utils/minishell.h"
#include "process.h"

static void	child_process(char **pipes, t_env **env, t_pipes p, int i)
{
	if (p.prev_fd != -1)
	{
		dup2(p.prev_fd, STDIN_FILENO);
		close(p.prev_fd);
	}
	if (pipes[i + 1])
	{
		dup2(p.fd[1], STDOUT_FILENO);
		close(p.fd[0]);
		close(p.fd[1]);
	}
	redirect_fd(pipes[i], STDIN_FILENO, STDOUT_FILENO, *env);
	p.cmd = command(pipes[i]);
	if (p.cmd == NULL)
	{
		free_array(pipes);
		dup2_close_in_out(p.fd_in, p.fd_out);
		exit(EXIT_FAILURE);
	}
	p.tokens_cmd = tokens(p.cmd);
	if (is_builtin(p.tokens_cmd[0]))
		exec_line(p.tokens_cmd, env);
	else
		exec_external(p.tokens_cmd, *env, p.fd_in, p.fd_out);
	free(p.cmd);
	free_array(p.tokens_cmd);
	free_array(pipes);
	dup2_close_in_out(p.fd_in, p.fd_out);
	exit(EXIT_SUCCESS);
}

void	process_pipes(char **pipes, t_env **env)
{
	int		i;
	t_pipes	p;

	i = 0;
	p.prev_fd = -1;
	p.fd_in = dup(STDIN_FILENO);
	p.fd_out = dup(STDOUT_FILENO);
	while (pipes[i])
	{
		if (pipes[i + 1])
			pipe(p.fd);
		p.pid = fork();
		if (p.pid == 0)
			child_process(pipes, env, p, i);
		if (p.prev_fd != -1)
			close(p.prev_fd);
		if (pipes[i + 1])
		{
			close(p.fd[1]);
			p.prev_fd = p.fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	free_array(pipes);
	dup2_close_in_out(p.fd_in, p.fd_out);
}
