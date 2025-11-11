#include "../../utils/minishell.h"
#include "redirect.h"

static void	exec_line(char **line_tokens, t_env *new_env)
{
	if (ft_strncmp(line_tokens[0], "echo", 5) == 0)
		echo(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "cd", 3) == 0)
		;
	else if (ft_strncmp(line_tokens[0], "pwd", 4) == 0)
		pwd(new_env);
	else if (ft_strncmp(line_tokens[0], "export", 7) == 0)
		export_arg(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "unset", 6) == 0)
		unset_env(&new_env, line_tokens);
	else if (ft_strncmp(line_tokens[0], "env", 4) == 0)
		print_env(new_env);
	else if (ft_strncmp(line_tokens[0], "exit", 5) == 0)
		read_input("exit", new_env, line_tokens);
	else
		printf("Command not found\n"); //VOCÊ VAI REMOVER NO FUTURO E SUBSTUIR PELA FUNÇÃO QUE FAZ O EXECVE
} // vai mudar tudo pq não deve receber o comando splitado no começo

/*
static void	redirect_fd(char *line, int fd_in, int fd_out, int count_pipe)
{
	int	fd[2];
	int	*fd_temp;

	fd_temp = parse_fd(line, fd_in, fd_out, count_pipe);
	fd[0] = fd_temp[0];
	fd[1] = fd_temp[1];
	free(fd_temp);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	redirect_and_command(char *line, t_env *new_env)
{
	int		fd_in;
	int		fd_out;
	int		count_pipe;
	char	*cmd;
	char	**s_pipe;
	char	**line_tokens;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	s_pipe = split_pipe(line);
	count_pipe = 0;
	while (s_pipe[count_pipe])
		count_pipe++;
	while(count >= 0)
	{
		redirect_fd(line, fd_in, fd_out, count_pipe);
		cmd = command(line, 0, 0, ft_strdup(""));
		line_tokens = split_with_quotes(cmd);
		exec_line(line_tokens, new_env);
		free(cmd);
		free_array(line_tokens);
		i++;
		count_pipe--;
	}
	free_array(s_pipe);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	// close(fd_in); //
	// close(fd_out); // free? close?
}
*/

// static void	parent_process(t_redirect *rd, int i)
// {
// 	if (i > 0)
// 		close(rd->prev_fd);
// 	if (i < rd->count_pipe - 1)
// 		close(rd->fd[1]);
// 	if (i < rd->count_pipe - 1)
// 		rd->prev_fd = rd->fd[0];
// 	waitpid(rd->pid, NULL, 0);
// }

// static void	redirect_fd(char *line)
// {
// 	int	*fd_temp;
// 	int	fd[2];

// 	fd_temp = parse_fd(line);
// 	if (!fd_temp)
// 		return ;
// 	fd[0] = fd_temp[0];
// 	fd[1] = fd_temp[1];
// 	free(fd_temp);
// 	if (fd[0] != STDIN_FILENO)
// 	{
// 		if (dup2(fd[0], STDIN_FILENO) == -1)
// 			perror("dup2 input");
// 		close(fd[0]);
// 	}
// 	if (fd[1] != STDOUT_FILENO)
// 	{
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 			perror("dup2 output");
// 		close(fd[1]);
// 	}
// }

// static void	child_process(t_redirect *rd, t_env *env, int i)
// {
// 	char	*cmd;
// 	char	**args;

// 	if (i > 0)
// 		dup2(rd->prev_fd, STDIN_FILENO);
// 	if (i < rd->count_pipe - 1)
// 		dup2(rd->fd[1], STDOUT_FILENO);
// 	if (i < rd->count_pipe - 1)
// 	{
// 		close(rd->fd[0]);
// 		close(rd->fd[1]);
// 	}
// 	if (i > 0)
// 		close(rd->prev_fd);
// 	redirect_fd(rd->s_pipe[i]);
// 	cmd = command(rd->s_pipe[i], 0, 0, ft_strdup(""));
// 	args = split_with_quotes(cmd);
// 	exec_line(args, env);
// 	free(cmd);
// 	free_array(args);
// 	exit(0);
// }

static t_redirect	init_redirect_vars(char *line)
{
	t_redirect	rd;

	rd.fd_in = dup(STDIN_FILENO);
	rd.fd_out = dup(STDOUT_FILENO);
	// rd.prev_fd = rd.fd_in;
	rd.s_pipe = split_pipe(line, 0, 0);
	rd.count_pipe = 0;
	while (rd.s_pipe[rd.count_pipe])
		rd.count_pipe++;
	return (rd);
}

void	redirect_and_command(char *line, t_env *env)
{
	int			i;
	t_redirect	rd;

	i = 0;
	if (!valid_input(line))
	{
		printf("Syntax error\n");
		return ;
	}
	rd = init_redirect_vars(line);
	// while (i < rd.count_pipe)
	// {
	// 	if (i < rd.count_pipe - 1 && pipe(rd.fd) == -1)
	// 		perror("pipe");
	// 	rd.pid = fork();
	// 	if (rd.pid == 0)
	// 		child_process(&rd, env, i);
	// 	else if (rd.pid > 0)
	// 		parent_process(&rd, i);
	// 	else
	// 		perror("fork");
	// 	i++;
	// }
	// dup2(rd.fd_in, STDIN_FILENO);
	// dup2(rd.fd_out, STDOUT_FILENO);
	// close(rd.fd_in);
	// close(rd.fd_out);
	// free_array(rd.s_pipe);
}
