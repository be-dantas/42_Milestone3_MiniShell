#include "../../utils/minishell.h"

static int	check_flag(char **token)
{
	int	i;

	i = 0;
	if (token[1][i] == '-' && token[1][i + 1] == 'n')
	{
		i++;
		while (token[1][i] != '\0')
		{
			if (token[1][i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

char    *echo(char **token, t_env *begin_list)
{
	char    *result;
	(void)begin_list;
	int	flag;

	if (token[1] == NULL)
	{
		printf("\n");
		return (NULL);
	}
	flag = check_flag(token);
	if (flag)
	{
		result = ft_join_all(token, 2);
		ft_printf("%s", result);
	}
	else
	{
		result = ft_join_all(token, 1);
		ft_printf("%s\n", result);
	}
	return (result);
}
