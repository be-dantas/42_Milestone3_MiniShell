#include "../../utils/minishell.h"

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
