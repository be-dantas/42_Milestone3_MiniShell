#include "../../../utils/minishell.h"

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

void	check_to_put(char *split_line, t_env **new_env)
{
	int		flag;
	t_env	*list_reset;
	char	*temp_expand;
	char	**temp;

	flag = 0;
	list_reset = *new_env;
	temp_expand = expand_arg(*new_env, split_line); //devolve a string toda expandida, ex arg=my_$USER = arg=my_bedantas
	temp = split_env(temp_expand);
    while (*new_env)
    {
        if (ft_strncmp((*new_env)->key, temp[0], ft_strlen((*new_env)->key) + 1) == 0)
        {
            update_value(temp[1], (*new_env));
            flag = 1;
            break;
        }
        (*new_env) = (*new_env)->next;
    }
	if (!flag)
	{
		(*new_env) = list_reset;
		put_env(new_env, temp_expand);
		free(temp_expand);
		free(temp[0]);
		free(temp[1]);
		free(temp);
		return ;
	}
	(*new_env) = list_reset;
	free(temp_expand);
	free(temp[0]);
	free(temp[1]);
	free(temp);
}
