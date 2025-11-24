#include "../../../utils/minishell.h"

static int	count_quotes(char *line)
{
	int	i;
	int	quote1;
	int	quote2;
	int	count;

	i = 0;
	quote1 = 0;
	quote2 = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !quote1)
		{
			quote2 = !quote2;
			count++;
		}
		else if (line[i] == '\"' && !quote2)
		{
			quote1 = !quote1;
			count++;
		}
		i++;
	}
	return (i - count);
}

char	*remove_quotes_str(char *line, int quote1, int quote2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (count_quotes(line) + 1));
	while (line[i])
	{
		if (line[i] == '\'' && !quote1)
			quote2 = !quote2;
		else if (line[i] == '\"' && !quote2)
			quote1 = !quote1;
		if ((line[i] == '\'' && !quote1) || (line[i] == '\"' && !quote2))
			;
		else
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
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
	value = remove_quotes_str(temp[1], 0, 0);
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

	result = remove_quotes_str(split_line, 0, 0);
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
