#include "../../../utils/minishell.h"
#include "check_var.h"

char	*remove_quotation(char *string)
{
	int		i;
	int		len;
	int		count;
	char	*str2;

	i = 0;
	len = ft_strlen(string);
	count = ft_countchar(string, string[0]);
	str2 = malloc(sizeof(char) * (len - count + 1));
	count = 0;
	while (string[i])
	{
		if (string[i] != string[0])
		{
			str2[count] = string[i];
			count++;
		}
		i++;
	}
	str2[count] = '\0';
	return (str2);
}

void	update_value(char *split_line, t_env *pointer)
{
	char	*result;

	if (split_line[0] == '\'' || split_line[0] == '\"')
		result = remove_quotation(split_line);
	else
		result = ft_strdup(split_line);
	free(pointer->value);
	pointer->value = result;
}

void	free_all_temp(char **temp, char *temp_expand)
{
	free(temp_expand);
	free(temp[0]);
	free(temp[1]);
	free(temp);
}

void	check_to_put(char *split_line, t_env **new_env)
{
	t_init	ptr;

	ptr.flag = 0;
	ptr.list_reset = *new_env;
	ptr.temp_expand = expand_arg(*new_env, split_line, 0);
	ptr.temp = split_env(ptr.temp_expand);
    while (*new_env)
    {
        if (ft_strcmp((*new_env)->key, ptr.temp[0]) == 0)
		{
            update_value(ptr.temp[1], (*new_env));
            ptr.flag = 1;
            break;
        }
        (*new_env) = (*new_env)->next;
    }
	if (!ptr.flag)
	{
		(*new_env) = ptr.list_reset;
		put_env(new_env, ptr.temp_expand);
		free_all_temp(ptr.temp, ptr.temp_expand);
		return ;
	}
	(*new_env) = ptr.list_reset;
	free_all_temp(ptr.temp, ptr.temp_expand);
}
