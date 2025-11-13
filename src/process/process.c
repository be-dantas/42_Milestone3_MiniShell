#include "../../utils/minishell.h"
#include "process.h"

/*
static void	process_one_fork(char **line_tokens, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_external(line_tokens, env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}
*/

void	process_one_split(char *line, t_env *env, int fd_in, int fd_out)
{
	char	**line_tokens;
	char	*cmd;

	redirect_fd(line, STDIN_FILENO, STDOUT_FILENO, env);
	cmd = command(line);
	if (cmd == NULL)
		return ;
	line_tokens = tokens(cmd);
	if (is_builtin(line_tokens[0]))
		exec_line(line_tokens, env);
	// else
		// process_one_fork(line_tokens, env);
	free(cmd);
	free_array(line_tokens);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

static void	child_process(char **pipes, t_env *env, t_pipes p, int i)
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
	redirect_fd(pipes[i], STDIN_FILENO, STDOUT_FILENO, env);
	p.cmd = command(pipes[i]);
	if (p.cmd == NULL)
		return ;
	p.tokens_cmd = tokens(p.cmd);
	if (is_builtin(p.tokens_cmd[0]))
		exec_line(p.tokens_cmd, env);
	// else
	// 	exec_external(p.tokens_cmd, env);
	free(p.cmd);
	free_array(p.tokens_cmd);
	exit(EXIT_SUCCESS);
}

void	process_pipes(char **pipes, t_env *env)
{
	int		i;
	t_pipes	p;

	i = 0;
	p.prev_fd = -1;
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
}
