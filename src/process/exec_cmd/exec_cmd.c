#include "../../../utils/minishell.h"

static void	exec_access_perror(char *s, char **array, int x)
{
	perror(s);
	free_array(array);
	exit(x);
}

static void	exec_access_putstr(char *s, char **array, int x)
{
	ft_putstr_fd(s, 2);
	free_array(array);
	exit(x);
}

void	cmd_bar(char **tokens, t_env *env)
{
	char	**envp;

	if (access(tokens[0], F_OK) != 0)
		exec_access_putstr("Command not found\n", tokens, 127);
	if (access(tokens[0], X_OK) != 0)
		exec_access_putstr("Permission denied\n", tokens, 126);
	envp = env_list_to_array(env, 0, ft_strdup(""), ft_strdup(""));
	execve(tokens[0], tokens, envp);
	free_array(envp);
	exec_access_perror("Error execve", tokens, 126);
}

static void	free_all(char **path_split, char *exec, char **envp)
{
	free_array(path_split);
	free(exec);
	free_array(envp);
}

void	cmd_not_bar(char **tokens, t_env *env)
{
	char	**path_split;
	char	*exec;
	char	**envp;

	path_split = path(env);
	if (!path_split)
	{
		free_array(tokens);
		exit(EXIT_FAILURE);
	}
	exec = command_valid(tokens, path_split);
	if (exec == (char *)-1)
	{
		free_array(path_split);
		exec_access_putstr("Permission denied\n", tokens, 126);
	}
	else if (!exec)
	{
		free_array(path_split);
		exec_access_putstr("Command not found\n", tokens, 127);
	}
	envp = env_list_to_array(env, 0, ft_strdup(""), ft_strdup(""));
	execve(exec, tokens, envp);
	free_all(path_split, exec, envp);
	exec_access_perror("Error execve", tokens, 126);
}
