#include "../../utils/minishell.h"
#include "redirect.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

void	redirect_fd(char *line, int fd_in, int fd_out)
{
	int	fd[2];
	int	*fd_temp;

	printf("10\n");
	fd_temp = parse_fd(line, fd_in, fd_out);
	fd[0] = fd_temp[0];
	fd[1] = fd_temp[1];
	free(fd_temp);
	if (fd[0] != fd_in)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != fd_out)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

// void	exec_external(char **tokens, t_env *env)
// {
// 	char *path = find_in_path(tokens[0], env);

// 	if (!path)
// 	{
// 		write(2, "Command not found\n", 18);
// 		exit(127);
// 	}
// 	execve(path, tokens, env_to_array(env));
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

void	exec_line(char **line_tokens, t_env *new_env)
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
} // vai mudar tudo pq não deve receber o comando splitado no começo
