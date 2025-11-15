#include "../../utils/minishell.h"
#include "process.h"

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

void	process_one_split(char *line, t_env **env, int fd_in, int fd_out)
{
	char	**line_tokens;
	char	*cmd;

	redirect_fd(line, STDIN_FILENO, STDOUT_FILENO, *env);
	cmd = command(line);
	if (cmd == NULL)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
		return ;
	}
	line_tokens = tokens(cmd);
	if (is_builtin(line_tokens[0]))
		exec_line(line_tokens, env);
	else
		process_one_fork(line_tokens, *env);
	free(cmd);
	free_array(line_tokens);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}
