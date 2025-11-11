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

static void	redirect_fd(char *line, int fd_in, int fd_out)
{
	int	fd[2];
	int	*fd_temp;

	fd_temp = parse_fd(line, fd_in, fd_out);
	fd[0] = fd_temp[0];
	fd[1] = fd_temp[1];
	free(fd_temp);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

static void	process_one_split(char *line, t_env *env)
{
	char	**line_tokens;
	char	*cmd;

	redirect_fd(line, STDIN_FILENO, STDOUT_FILENO);
	cmd = command(line, 0, 0, ft_strdup(""));
	line_tokens = tokens(cmd, env);
	exec_line(line_tokens, env);
	free(cmd);
	free_array(line_tokens);
}

static t_redirect	init_redirect_vars(char *line)
{
	t_redirect	rd;

	rd.s_pipe = split_pipe(line, 0, 0);
	rd.count_pipe = 0;
	while (rd.s_pipe[rd.count_pipe])
		rd.count_pipe++;
	rd.fd_in = dup(STDIN_FILENO);
	rd.fd_out = dup(STDOUT_FILENO);
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
	if (rd.count_pipe == 1)
		process_one_split(line, env);
	else
		//funcao para linhas com pipe
	dup2(rd.fd_in, STDIN_FILENO);
	dup2(rd.fd_out, STDOUT_FILENO);
	close(rd.fd_in);
	close(rd.fd_out);
	free_array(rd.s_pipe);
}
