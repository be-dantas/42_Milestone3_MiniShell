#include "../../../utils/minishell.h"

int	print_without_n(char **result, t_env *begin_list, int i, int j)
{
		if (!result[i])
		{
			printf("");
			return (0);
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
	return (1);
}

int	print_with_n(char **result, t_env *begin_list, int i, int j)
{
		if (!result[i])
		{
			printf("");
			return (0);
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
	return (1);
}

void	free_split(char **string)
{
	int i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

char	*echo(char *line, t_env *begin_list)
{
	char	**result;

	result = ft_split(line, ' ');
	if (!result[1])
	{
		printf("\n");
		free_split(result);
		return (NULL);
	}
	if (ft_strcmp(result[1], "-n") == 0)
	{
		if (print_without_n(result, begin_list, 2, 0) == 0)
		{
			return (NULL);
			free_split(result);
		}
	}
	else
	{
		if (print_with_n(result, begin_list, 1, 0) == 0)
		{
			return (NULL);
			free_split(result);
		}
	}
	free_split(result);
	return (line);
}
