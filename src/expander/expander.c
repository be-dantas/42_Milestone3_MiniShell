#include "../../utils/minishell.h"

static char	*expand_variable(t_env *begin_list, char *str, int *i)
{
	char	*key;
	char	*value;

	key = get_key(&str[*i + 1]);
	value = expanded(begin_list, key);
	if (!value)
		value = "";
	*i += ft_strlen(key) + 1;
	free(key);
	return (ft_strdup(value));
}

static char	*expand_literal(char *str, int *i)
{
	char	*literal;

	literal = ft_substr(str, *i, 1);
	return (literal);
}

char	*expand_arg(t_env *begin_list, char *str, int i)
{
	int		in_single;
	int		in_double;
	char	*result;
	char	*temp;

	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		if (str[i] == '$' && !in_single && str[i + 1])
			temp = expand_variable(begin_list, str, &i);
		else
		{
			temp = expand_literal(str, &i);
			i++;
		}
		result = join_and_free(result, temp);
		free(temp);
	}
	return (result);
}
