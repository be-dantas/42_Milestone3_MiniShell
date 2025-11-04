#include "../../utils/minishell.h"

char	*join_and_free(char *s1, const char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*expanded(t_env *begin_list, char *key)
{
	while (begin_list)
	{
		if (ft_strncmp(key, begin_list->key,
				ft_strlen(begin_list->key) + 1) == 0)
			return (begin_list->value);
		begin_list = begin_list->next;
	}
	return (NULL);
}

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, i + 1);
	return (key);
}

int	arg_in_line(char *key, char **split)
{
	int		i;
	char	*key_split;

	i = 0;
	while (split[i])
	{
		key_split = get_key(split[i]);
		if (ft_strequal(key, key_split))
		{
			free(key_split);
			return (1);
		}
		free(key_split);
		i++;
	}
	return (0);
}
