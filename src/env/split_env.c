#include "../../utils/minishell.h"

char	**find_and_split(char *string, size_t i, size_t j, char **str3)
{
	char	*str1;
	char	*str2;

	while (string[i] != '=')
	{
		i++;
		j++;
	}
	while (string[j] != '\0')
		j++;
	str1 = malloc(sizeof(*str1) * (i + 1));
	str2 = malloc(sizeof(*str2) * (j - i + 1));
	ft_strlcpy(str1, string, i + 1);
	ft_strlcpy(str2, string + i + 1, j - i + 1);
	str3[0] = str1;
	str3[1] = str2;
	str3[2] = NULL;
	return (str3);
}

char	**split_env(char *string)
{
	char	**splited;
	size_t	i;
	size_t	j;
	char	**str3;

	str3 = malloc(sizeof(char *) * 3);
	i = 0;
	j = 0;
	splited = find_and_split(string, i, j, str3);
	return (splited);
}
