#include "../../../utils/minishell.h"

char	**path(t_env *env)
{
	t_env	*value_path;
	char	*value;
	char	**path_split;

	value_path = get_value_by_name(&env, "PATH");
	value = ft_strdup(value_path->value);
	path_split = ft_split(value, ':');
	if (!path_split)
		return (NULL);
	free(value);
	return (path_split);
}

char	*command_valid(char **tokens, char **path_split)
{
	int		i;
	char	*temp_path;
	char	*exec;

	i = 0;
	while (path_split[i])
	{
		temp_path = ft_strjoin(path_split[i], "/");
		exec = ft_strjoin(temp_path, tokens[0]);
		free(temp_path);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		else if (access(exec, F_OK) == 0 && access(exec, X_OK) != 0)
		{
			free(exec);
			return ((char *)-1);
		}
		free(exec);
		i++;
	}
	return (NULL);
}
