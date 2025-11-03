#include "../../utils/minishell.h"

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
			result = join_and_free(result,
					expand_variable(begin_list, str, &i));
		else
			result = join_and_free(result, expand_literal(str, &i));
		i++;
	}
	return (result);
}

// char	*expand_arg(t_env *begin_list, char *str)
// {
// 	int		i;
// 	int		in_single;
// 	int		in_double;
// 	char	*result;

// 	i = 0;
// 	in_single = 0;
// 	in_double = 0;
// 	result = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && !in_double)
// 			in_single = !in_single;	
// 		else if (str[i] == '"' && !in_single)
// 			in_double = !in_double;
// 		else if (str[i] == '$' && !in_single && str[i + 1])
// 		{
// 			char *key = get_key(&str[i + 1]);
// 			char *value = expanded(begin_list, key);
// 			if (!value)
// 				value = "";
// 			result = join_and_free(result, value);
// 			i += ft_strlen(key);
// 			free(key);
// 		}
// 		else
// 		{
// 			char *literal = ft_substr(str, i, 1);
// 			result = join_and_free(result, literal);
// 			free(literal);
// 		}
// 		i++;
// 	}
// 	return (result);
// }