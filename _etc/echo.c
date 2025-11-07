#include "../../../utils/minishell.h"
#include "echo.h"

char    *join_all(char **string, unsigned int start);
char    *split_to_line(char **token);

char	*get_file_name(char *line)
{
	char	*file_name;
	char	**to_free1;
	char	*to_free2;
										//palavra, palavra1.txt palavra2 palavra3 ....
	to_free1 = NULL;
	to_free2 = NULL;
	file_name = NULL;
	to_free1 = ft_split(line, '>'); // nessa parte
	to_free2 = ft_split(to_free1[1], ' ')[0]; //palavra.txt, palavra2, palavra3, ... 
	file_name = ft_strdup(to_free2);
	free_array(to_free1);
	free(to_free2);
	return (file_name);
}

char	*concatenate_file(char *line)
{
	int		fd;
	char	*file_name;

	file_name = get_file_name(line);
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	char **to_free1 = ft_split(line, '>');//teste>teste teste - split no ">"
	char *string_antes_do_sinal = ft_strdup(to_free1[0]);//valor splitado = teste teste sdfasdasdasd [0], ajskdhkajshd kajshd kaksjd hkakajshd [1]
	char *new_string_antes_do_sinal = ft_strjoin(string_antes_do_sinal, " ");
	char **to_free2 = ft_split(to_free1[1], ' ');//valor  = split do primeiro = ajskdhkajshd,[0] kajshd[1] kaksjd[2] hkakajshd[3]
	char *result = ft_strjoin(new_string_antes_do_sinal, join_all(to_free2, 1));//join_all(split so primeiro 1)
	write(fd, result, ft_strlen(result));
	free(file_name);
	return (NULL);
}

char	*overwrite_file(char *line)
{
	int		fd;
	char	*file_name;

	file_name = get_file_name(line);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char **to_free1 = ft_split(line, '>');//teste>teste teste - split no ">"
	char *string_antes_do_sinal = ft_strdup(to_free1[0]);//valor splitado = teste teste sdfasdasdasd [0], ajskdhkajshd kajshd kaksjd hkakajshd [1]
	char *new_string_antes_do_sinal = ft_strjoin(string_antes_do_sinal, " ");
	char **to_free2 = ft_split(to_free1[1], ' ');//valor  = split do primeiro = ajskdhkajshd,[0] kajshd[1] kaksjd[2] hkakajshd[3]
	char *result = ft_strjoin(new_string_antes_do_sinal, join_all(to_free2, 1));//join_all(split so primeiro 1)
	write(fd, result, ft_strlen(result));
	free(file_name);
	return (NULL);
}

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
		return (concatenate_file(line));
	if (flag == 1)
		return (overwrite_file(line));
	if (flag == 0)
		return (line);
	return (NULL);
}

char	*echo(char **token, t_env *begin_list)
{
	char	*result;
	char	*line;

	line = split_to_line(token);
	//printf("%s = line\n", line);
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
		result = join_all(token, 2);
	}
	else
		result = ft_strjoin(join_all(token, 1), "\n");
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
