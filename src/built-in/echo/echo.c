#include "../../../utils/minishell.h"

int	check_flag(char **token)
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

char    *ft_join_all(char **string, unsigned int start)
{
    char    *result;
    char    *temp;

    temp = NULL;
    result = ft_strdup("");
    if (!result)
        return (NULL);
    while (string[start] != NULL)
    {
        temp = ft_strjoin(result, string[start]);
        free(result);
        result = temp;
        if (string[start + 1])
        {
            temp = ft_strjoin(result, " ");
            free(result);
            result = temp;
        }
        start++;
    }
    return (result);
}

char    *echo(char **token, t_env *begin_list)
{
	char    *result;
	(void)begin_list;
	int	flag;

	flag = check_flag(token); //if flag == 1 não printa \n
	if (flag)
	{
		result = ft_join_all(token, 2); //concatena do item 2 pra cima ou seja echo, -n, descartado
		printf("%s", result);
	}
	else
	{
		result = ft_join_all(token, 1);
		printf("%s\n", result);
	}
	return (result);
}
