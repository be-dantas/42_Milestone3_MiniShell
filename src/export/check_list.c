#include "../utils/minishell.h"

void	check_to_put(char *split_line, t_env **new_env)
{
	char	**temp;
	t_env	*list_reset;
	t_env	*ptr;

	ptr = NULL;
	list_reset = *new_env;
	temp = split_env(split_line);
	while (*new_env)
	{
		if (ft_strncmp((*new_env)->key, temp[0], ft_strlen((*new_env)->key)) == 0)
		{
			//(*new_env)->value = temp[1];
			update_value(temp[1], (*new_env));
			free(temp[0]);
			free(temp[1]);
			free(temp);
			return ;
		}
		(*new_env) = (*new_env)->next;
	}
	(*new_env) = list_reset;
	put_env(new_env, split_line);
	free(temp[0]);
	free(temp[1]);
	free(temp);
}

void	update_value(char *split_line, t_env *pointer)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * ft_strlen(split_line) + 1);
	ft_strlcpy(result, split_line, ft_strlen(split_line) + 1);
	free(pointer->value);
	pointer->value = result;
}
