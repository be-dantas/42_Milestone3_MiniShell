#include "../../utils/minishell.h"

char	*remove_quotes(char *string)
{
	int		i;
	int		len;
	int		count;
	char	*str2;

	i = 0;
	len = ft_strlen(string);
	count = ft_countchar(string, string[0]);
	str2 = malloc(sizeof(char) * (len - count + 1));
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

char	**tokens(char *line)
{
	char	*expand;
	char	**split_tokens;

	expand = expand_arg(line);
	split_tokens = split_with_quotes(expand);
	if (ft_countchar(split_tokens[0], ' ') != 0)
	{
		printf("Command not found");
		free(expand);
		free_array(split_tokens);
		return (NULL);
	}
	remove_quotes(split_tokens[0]);
	free(expand);
	return (split_tokens);
}
