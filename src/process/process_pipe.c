#include "../../utils/minishell.h"
#include "process.h"

static void	child_utils(char **pipes, t_shell *sh, t_pipes *p, int i)
{
	if (p->prev_fd != -1)
	{
		dup2(p->prev_fd, STDIN_FILENO);
		close(p->prev_fd);
	}
	if (pipes[i + 1])
	{
		dup2(p->fd[1], STDOUT_FILENO);
		close(p->fd[0]);
		close(p->fd[1]);
	}
	redirect_fd(pipes[i], STDIN_FILENO, STDOUT_FILENO, sh->env);
	p->cmd = command(pipes[i]);
	if (p->cmd == NULL)
	{
		free_array(pipes);
		dup2_close_in_out(p->fd_in, p->fd_out);
		exit(EXIT_FAILURE);
	}
	p->tokens_cmd = tokens(p->cmd);
}

static void	child_process(char **pipes, t_shell *sh, t_pipes p, int i)
{
	child_utils(pipes, sh, &p, i);
	if (is_builtin(p.tokens_cmd[0]))
		exec_line(p.tokens_cmd, sh);
	else
		exec_external(p.tokens_cmd, sh->env, p.fd_in, p.fd_out);
	free(p.cmd);
	free_array(p.tokens_cmd);
	free_array(pipes);
	free_list(&sh->env);
	dup2_close_in_out(p.fd_in, p.fd_out);
	exit(EXIT_SUCCESS);
}

static void	pipes_utils(char **pipes, t_pipes p, t_shell *sh)
{
	int	status;

	waitpid(p.last_pid, &status, 0);
	if (WIFEXITED(status))
		sh->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->last_exit_status = 128 + WTERMSIG(status);
	while (wait(NULL) > 0)
		;
	free_array(pipes);
	dup2_close_in_out(p.fd_in, p.fd_out);
}

void	process_pipes(char **pipes, t_shell *sh)
{
	t_pipes	p;
	int		i;

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
			child_process(pipes, sh, p, i);
		p.last_pid = p.pid;
		if (p.prev_fd != -1)
			close(p.prev_fd);
		if (pipes[i + 1])
		{
			close(p.fd[1]);
			p.prev_fd = p.fd[0];
		}
		i++;
	}
	pipes_utils(pipes, p, sh);
}
