#include "../../utils/minishell.h"

static int	check_flag(char **token)
{
	int	i;

	i = 0;
	if (!token[1])
		return (0);
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

static char	*result_echo(char **token, t_shell *sh)
{
	char	*result;
	int		flag;

	result = NULL;
	flag = check_flag(token);
	if (ft_strncmp(token[1], "$?", 3) == 0)
		printf("%d\n", sh->last_exit_status);
	else if (flag && token[2] != NULL)
	{
		result = ft_join_all(&token[2], 2);
		ft_printf("%s", result);
	}
	else if (flag)
	{
		result = ft_join_all(token, 2);
		ft_printf("%s", result);
	}
	else if (!flag)
	{
		result = ft_join_all(token, 1);
		ft_printf("%s\n", result);
	}
	return (result);
}

void	echo(char **token, t_shell *sh)
{
	char	*result;

	sh->last_exit_status = 0;
	if (token[1] == NULL)
	{
		printf("\n");
		return (NULL);
	}
	result = result_echo(token, sh);
	if (result != NULL)
		free(result);
}
