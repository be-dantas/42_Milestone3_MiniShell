#include "../../../utils/minishell.h"

static char	*remove_quotes(char *string, int i, int j)
{
	int		len;
	int		count1;
	int		count2;
	char	*str2;

	len = ft_strlen(string);
	count1 = ft_countchar(string, '\'');
	count2 = ft_countchar(string, '\"');
	if (count1 % 2 != 0 || count2 % 2 != 0)
		return (NULL);
	str2 = malloc(sizeof(char) * (len - (count1 + count2) + 1));
	while (string[i])
	{
		if (string[i] != '\'' && string[i] != '\"')
		{
			str2[j] = string[i];
			j++;
		}
		i++;
	}
	str2[j] = '\0';
	return (str2);
}

char	**tokens(char *line)
{
	char	**split_tokens;
	char	*temp;

	split_tokens = split_with_quotes(line);
	temp = remove_quotes(split_tokens[0], 0, 0);
	if (ft_countchar(split_tokens[0], ' ') != 0 || temp == NULL)
	{
		printf("Command not found\n");
		if (temp)
			free(temp);
		free_array(split_tokens);
		return (NULL);
	}
	free(split_tokens[0]);
	split_tokens[0] = temp;
	return (split_tokens);
}
