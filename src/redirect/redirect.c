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
		read_input("exit", new_env);
	else
		printf("Command not found\n"); //VOCÊ VAI REMOVER NO FUTURO E SUBSTUIR PELA FUNÇÃO QUE FAZ O EXECVE
}

void	redirect_and_command(char *line, t_env *new_env)
{
	t_rd	rd;

	rd.fd_in = dup(STDIN_FILENO);
	rd.fd_out = dup(STDOUT_FILENO);
	rd.fd_temp = parse_fd(line);
	rd.fd[0] = rd.fd_temp[0];
	rd.fd[1] = rd.fd_temp[1];
	free(rd.fd_temp);
	dup2(rd.fd[0], STDIN_FILENO);
	dup2(rd.fd[1], STDOUT_FILENO);
	rd.cmd = command(line, 0, 0, ft_strdup(""));
	rd.line_tokens = tokens(new_env, rd.cmd);
	exec_line(rd.line_tokens, new_env);
	dup2(rd.fd_in, STDIN_FILENO);
	dup2(rd.fd_out, STDOUT_FILENO);
	close(rd.fd_in);
	close(rd.fd_out);
	close(rd.fd[0]);
	close(rd.fd[1]);
	free(rd.cmd);
	free_array(rd.line_tokens);
}
