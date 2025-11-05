#include "../../../utils/minishell.h"
#include "echo.h"

char    *join_all(char **string, unsigned int start);
char    *split_to_line(char **token);

char	*check_line(char *line, t_env *begin_list)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '>' && line[i + 1] != '>') && flag == 0)
			flag = 1;
		else if ((line[i] == '>' && line[i + 1] == '>') && flag == 0)
			flag = 2;
		if (line[i] == '$')
			line = expanded(begin_list, line);
		i++;
	}
	if (flag == 2)
		;//concatenar
	if (flag == 1)
		;//sobrescrever
	if (flag == 0)
		return (line);//simplesmente escrever
	return (NULL);
}

char	*echo(char **token, t_env *begin_list)
{
	char	*result;
	char	*line;

	line = split_to_line(token);
	result = check_line(line, begin_list);

	printf("%s", line);
	return (result);
}

char	*split_to_line(char **token)
{
	char	*result;
	char	*temp;

	temp = NULL;
	result = NULL;
	if (token[1][0] == '-' && token[1][1] == 'n')
	{
		if (token[1][2] != '\0')
		{
			printf("Command not found\n");
			return (NULL);
		}
		//chamo a função de concatenar split a partir do token[2]
		result = join_all(token, 2);
	}
	else
	{
		result = join_all(token, 1);
		temp = result;
		free(result);
		ft_strjoin(temp, "\n");
	}	//chamo a função de concatenar split a partir do token[1]
	return (result);
}

char	*join_all(char **string, unsigned int start)
{
	char	*result;
	char	*temp;

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
/*
int main()
{
	char **token = malloc(sizeof(char *) * 7);
	t_env	*ptr;

	ptr = NULL;
	//token = NULL;
	token[0] = "echo";
	token[1] = "palavra0";
	token[2] = "palavra1";
	token[3] = ">palavra2.txt";
	token[4] = "palavra3";
	token[5] = "palavra4";
	token[6] = NULL;
	echo(token, ptr);
	free(token);
	
	return (0);
}
*/














/*****************************************************************************************/



// int	print_without_n(char **result, t_env *begin_list, int i, int j)
// {
// 	char *expanded;

// 	expanded = NULL;
// 	if (!result[i])
// 	{
// 		printf("");
// 		return (0);
// 	}
// 	while (result[i] != NULL)
// 	{
// 		j = 0;
// 		while (result[i][j] != '\0')
// 		{
// 			if (result[i][j] == '$')
// 			{
// 				expanded = expand_arg(begin_list, result[i], 0);
// 				free(result[i]);
// 				result[i] = expanded;
// 				break ;
// 			}
// 			j++;
// 		}
// 		printf("%s", result[i]);
// 		if (result[i + 1] != NULL)
// 			printf(" ");
// 		i++;
// 	}
// 	return (1);
// }

// int	print_with_n(char **result, t_env *begin_list, int i, int j)
// {
// 	char *expanded;

// 	expanded = NULL;
// 	if (!result[i])
// 	{
// 		printf("");
// 		return (0);
// 	}
// 	while (result[i] != NULL)
// 	{
// 		j = 0;
// 		while (result[i][j] != '\0')
// 		{
// 			if (result[i][j] == '$')
// 			{
// 				expanded = expand_arg(begin_list, result[i], 0);
// 				free(result[i]);
// 				result[i] = expanded;
// 				break ;
// 			}
// 			j++;
// 		}
// 		printf("%s", result[i]);
// 		if (result[i + 1] != NULL)
// 			printf(" ");
// 		i++;
// 	}
// 	printf("\n");
// 	return (1);
// }

// void	free_split(char **string)
// {
// 	int i;

// 	i = 0;
// 	while (string[i] != NULL)
// 	{
// 		free(string[i]);
// 		i++;
// 	}
// 	free(string);
// }

// char	*echo(char *line, t_env *begin_list)
// {
// 	char	**result;

// 	result = ft_split(line, ' ');
// 	if (!result[1])
// 	{
// 		printf("\n");
// 		free_split(result);
// 		return (NULL);
// 	}
// 	if (ft_strcmp(result[1], "-n") == 0)
// 	{
// 		if (print_without_n(result, begin_list, 2, 0) == 0)
// 		{
// 			free_split(result);
// 			return (NULL);
// 		}
// 	}
// 	else
// 	{
// 		if (print_with_n(result, begin_list, 1, 0) == 0)
// 		{
// 			free_split(result);
// 			return (NULL);
// 		}
// 	}
// 	free_split(result);
// 	return (line);
// }
