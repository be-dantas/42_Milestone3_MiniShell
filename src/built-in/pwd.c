#include "../../utils/minishell.h"

static t_env	*get_value_by_name(t_env **new_env)
{
	t_env	*list_reset;
	t_env	*value;

	list_reset = *new_env;
	while (*new_env)
	{
		if (ft_strcmp((*new_env)->key, "PWD") == 0)
		{
			value = (*new_env);
			(*new_env) = list_reset;
			return (value);
		}
		(*new_env) = (*new_env)->next;
	}
	(*new_env) = list_reset;
	return (NULL);
}

void	pwd(t_env *new_env, char **line_tokens)
{
	t_env	*pointer;
	char	*pwd;
	char	*join_pwd;

	if (line_tokens[1][0] != '\0')
	{
		printf("Command not found\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
	pointer = get_value_by_name(&new_env);
	if (pointer)
		update_value(pwd, pointer);
	else
	{
		join_pwd = ft_strjoin("PWD=", pwd);
		put_env(&new_env, join_pwd);
		free(join_pwd);
	}
	free(pwd);
}
