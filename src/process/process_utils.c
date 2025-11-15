#include "../../utils/minishell.h"
#include "process.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	redirect_fd(char *line, int fd_in, int fd_out, t_env *begin_list)
{
	int	fd[2];
	int	*fd_temp;

	fd_temp = parse_fd(line, fd_in, fd_out, begin_list);
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

void	exec_external(char **tokens, t_env *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tokens[0][i])
	{
		if (tokens[0][i] == '/')
			flag = 1;
		i++;
	}
	if (flag == 1)
		cmd_bar(tokens, env);
	else
		cmd_not_bar(tokens, env);
}

void	exec_line(char **line_tokens, t_env **new_env)
{
	if (ft_strncmp(line_tokens[0], "echo", 5) == 0)
		echo(line_tokens);
	else if (ft_strncmp(line_tokens[0], "cd", 3) == 0)
		cd(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "pwd", 4) == 0)
		pwd(line_tokens, *new_env);
	else if (ft_strncmp(line_tokens[0], "export", 7) == 0)
		export_arg(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "unset", 6) == 0)
		unset_env(new_env, line_tokens);
	else if (ft_strncmp(line_tokens[0], "env", 4) == 0)
	{
		if (line_tokens[1] == NULL)
			print_env(*new_env);
		else
			printf("env: ‘%s’: No such file or directory\n", line_tokens[1]);
	}
	else if (ft_strncmp(line_tokens[0], "exit", 5) == 0)
		read_input("exit", *new_env);
}
