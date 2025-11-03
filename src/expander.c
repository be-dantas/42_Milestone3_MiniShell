#include "../utils/minishell.h"

static char	*get_key(char *str)
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

static char	*join_and_free(char *s1, const char *s2)
{
    char *res;

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

char	*expand_arg(t_env *begin_list, char *str)
{
    int		i;
    int		in_single;
    int		in_double;
    char	*result;

    i = 0;
    in_single = 0;
    in_double = 0;
    result = ft_strdup("");
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
            in_single = !in_single;	
        else if (str[i] == '"' && !in_single)
            in_double = !in_double;
        else if (str[i] == '$' && !in_single && str[i + 1])
        {
            char *key = get_key(&str[i + 1]);
            char *value = expanded(begin_list, key);
            if (!value)
                value = "";
            result = join_and_free(result, value);
            i += ft_strlen(key);
            free(key);
        }
        else
        {
            char *literal = ft_substr(str, i, 1);
            result = join_and_free(result, literal);
            free(literal);
        }
        i++;
    }
    return (result);
}

char	*expanded(t_env *begin_list, char *key)
{
	while (begin_list)
	{
		if (ft_strncmp(key, begin_list->key, ft_strlen(begin_list->key) + 1) == 0)
			return (begin_list->value);
		begin_list = begin_list->next;
	}
	return (NULL);
}
