#include "../../utils/minishell.h"

void	check_to_put(char *split_line, t_env **new_env)
{
	int		i;
	int		flag;
	t_env	*list_reset;
	char	*temp_expand;
	char	**temp;

	i = 0;
	flag = 0;
	list_reset = *new_env;
	temp_expand = expand_arg(*new_env, split_line);
	temp = split_env(split_line);
    while (*new_env)
    {
        if (ft_strncmp((*new_env)->key, temp[0], ft_strlen((*new_env)->key) + 1) == 0)
        {
            if (temp_expand != NULL)
            {
                char *eq = ft_strchr(temp_expand, '=');
                char *val_dup;

                if (eq && *(eq + 1))
                    val_dup = ft_strdup(eq + 1);
                else
                    val_dup = ft_strdup("");
                free(temp[1]);
                temp[1] = val_dup;
            }
            update_value(temp[1], (*new_env));
            flag = 1;
            break;
        }
        (*new_env) = (*new_env)->next;
    }
	if (!flag)
	{
		if (temp_expand != NULL)
		{
			(*new_env) = list_reset;
			put_env(new_env, temp_expand);
            free(temp[0]);
            free(temp[1]);
            free(temp);
			free(temp_expand);
			return ;
		}
		(*new_env) = list_reset;
		put_env(new_env, split_line);
	}
	(*new_env) = list_reset;
	if (temp_expand != NULL)
        free(temp_expand);
	free(temp[0]);
	free(temp[1]);
	free(temp);
}

void	update_value(char *split_line, t_env *pointer)
{
	char	*result;

	if (split_line[0] == '\'' || split_line[0] == '\"')
		result = find_and_split(split_line);
	else
	{
		result = (char *)malloc(sizeof(char) * (ft_strlen(split_line) + 1));
		ft_strlcpy(result, split_line, (ft_strlen(split_line) + 1));
	}
	free(pointer->value);
	pointer->value = result;
}
