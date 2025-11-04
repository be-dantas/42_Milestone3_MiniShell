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

void	put_exp(char **temp, t_env **new_env)
{
	char	*value;
	char	*tmp;
	char	*result;
	
	if (temp[1] == NULL)
	{
		put_env(new_env, temp[0]);
		return ;
	}
	if (temp[1] && (temp[1][0] == '\'' || temp[1][0] == '\"'))
	value = remove_quotation(temp[1]);
	else
	value = ft_strdup(temp[1]);
	tmp = ft_strjoin(temp[0], "=");
	result = ft_strjoin(tmp, value);
	free(value);
	free(tmp);
	put_env(new_env, result);
	free(result);
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
	t_init	ptr;

	ptr.flag = 0;
	ptr.list_reset = *new_env;
	ptr.temp = split_env(split_line);
	while (*new_env)
	{
		if (ft_strcmp((*new_env)->key, ptr.temp[0]) == 0)
		{
			update_value(ptr.temp[1], (*new_env));
			ptr.flag = 1;
			break ;
		}
		(*new_env) = (*new_env)->next;
	}
	if (!ptr.flag)
	{
		(*new_env) = ptr.list_reset;
		put_exp(ptr.temp, new_env);
		free_array(ptr.temp);
		return ;
	}
	(*new_env) = ptr.list_reset;
	free_array(ptr.temp);
}
