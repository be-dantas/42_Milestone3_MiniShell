#include "../../utils/minishell.h"

char	*remove_quotation(char *string)
{
	int		i;
	int		count;
	char	*str2;

	i = 0;
	count = ft_countchar(string, string[0]);
	str2 = malloc(sizeof(char) * (i - count + 1));
	count = 0;
	while (string[i])
	{
		if (string[i] != string[0])
		{
			str2[count] = string[i];
			count++;
		}
		i++;
	}
	str2[count] = '\0';
	return (str2);
}

char	*split_env_value(char *new_append1)
{
	int		len;
	char	result;

	len = ft_strlen(new_append1);
	if (new_append1[0] == '\'' || new_append1[0] == '\"')
		result = remove_quotation(new_append1);
	else
	{
		result = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(result, new_append1, len + 1);
	}
	return (result);
}

char	**split_env(char *string)
{
	char	**splited;
	char	**new_append;

	splited = malloc(sizeof(char *) * 3);
	new_append = ft_split(string, '=');
	if (!new_append[0])
		splited[0] = ft_strdup("");
	else
		splited[0] = ft_strdup(new_append[0]);
	if (!new_append[1])
		splited[1] = ft_strdup("");
	else
		splited[1] = split_env_value(new_append[1]);
	splited[2] = NULL;
	free_array(new_append);
	return (splited);
}
