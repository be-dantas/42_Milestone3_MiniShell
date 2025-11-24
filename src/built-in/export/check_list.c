#include "../../../utils/minishell.h"

char	*remove_quotes_start(char *string)
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

static void	put_exp(char **temp, t_env **new_env)
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
		value = remove_quotes_start(temp[1]);
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
		result = remove_quotes_start(split_line);
	else
		result = ft_strdup(split_line);
	free(pointer->value);
	pointer->value = result;
}

void	check_to_put(char *split_line, t_env **env)
{
	int		flag;
	char	**temp;
	t_env	*current;

	flag = 0;
	temp = split_env(split_line);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, temp[0]) == 0)
		{
			update_value(temp[1], current);
			flag = 1;
			break ;
		}
		current = current->next;
	}
	if (!flag)
		put_exp(temp, env);
	free_array(temp);
}
