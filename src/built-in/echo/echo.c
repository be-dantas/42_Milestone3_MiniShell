#include "../../../utils/minishell.h"

char	*echo(char *line, t_env *begin_list)
{
	char	**result;
	(void)	begin_list;
	int		i;
	int		j;

	j = 0;
	i = 0;
	result = ft_split(line, ' ');
	if (!result[1])
	{
		printf("\n");
		return (NULL);
	}
	if (ft_strcmp(result[1], "-n") == 0)
	{
		i = 2;
		if (!result[i])
		{
			printf("");
			return (NULL);
		}
		while (result[i] != NULL)
		{
			j = 0;
			while (result[i][j] != '\0')
			{
				if (result[i][j] == '$')
				{
					result[i] = expand_arg(begin_list, result[i], 0);
					break ;
				}
				j++;
			}
			printf("%s", result[i]);
			if (result[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		if (!result[i])
		{
			printf("");
			return (NULL);
		}
		while (result[i] != NULL)
		{
			j = 0;
			while (result[i][j] != '\0')
			{
				if (result[i][j] == '$')
				{
					result[i] = expand_arg(begin_list, result[i], 0);
					break ;
				}
				j++;
			}
			printf("%s", result[i]);
			if (result[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (result[1]);
}
