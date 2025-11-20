#include "../../utils/minishell.h"
#include "process.h"

static void	dup2_close_in_out(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

static void	process_one_fork(char **line_tokens, t_env *env, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_external(line_tokens, env);
		dup2_close_in_out(fd_in, fd_out);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

void	process_one_split(char **line, t_env **env)
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**line_tokens;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	redirect_fd(line[0], STDIN_FILENO, STDOUT_FILENO, *env);
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
		exec_line(line_tokens, env);
	else
		process_one_fork(line_tokens, *env, fd_in, fd_out);
	free_array(line_tokens);
	dup2_close_in_out(fd_in, fd_out);
}
