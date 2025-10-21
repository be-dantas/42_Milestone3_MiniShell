
#include "../utils/minishell.h"

// funções para executar 1 cmd de cada vez tirada da linha;
// adaptar para gc

void	cmd_not_bar(char **cmd_split, char **env)
{
	char	*exec;
	char	**path_split;

	path_split = path(env);
	if (!path_split)
	{
		free_array(cmd_split);
		exit(EXIT_FAILURE);
	}
	exec = command_valid(cmd_split, path_split);
	if (exec == (char *)-1)
	{
		free_array(path_split);
		exec_access_putstr("Permission denied\n", cmd_split, 126);
	}
	else if (!exec)
	{
		free_array(path_split);
		exec_access_putstr("Command not found\n", cmd_split, 127);
	}
	execve(exec, cmd_split, env);
	free_array(path_split);
	free(exec);
	exec_access_perror("Error execve", cmd_split, 126);
}

void	cmd_bar(char **cmd_split, char **env)
{
	if (access(cmd_split[0], F_OK) != 0)
		exec_access_putstr("Command not found\n", cmd_split, 127);
	if (access(cmd_split[0], X_OK) != 0)
		exec_access_putstr("Permission denied\n", cmd_split, 126);
	execve(cmd_split[0], cmd_split, env);
	exec_access_perror("Error execve", cmd_split, 126);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
		exit(EXIT_FAILURE);
	if (bar(cmd_split[0]))
		cmd_bar(cmd_split, env);
	else
		cmd_not_bar(cmd_split, env);
}
