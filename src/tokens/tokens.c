#include "../../utils/minishell.h"

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
	str2 = malloc(sizeof(char) * (len - (count1 + count2 ) + 1));
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

char	**tokens(t_env *new_env, char *line)
{
	char	*expand;
	char	**split_tokens;
	char	*temp;

	expand = expand_arg(new_env, line, 0);
	split_tokens = split_with_quotes(expand);
	temp = remove_quotes(split_tokens[0], 0 , 0);
	printf("%s\n", split_tokens[0]);
	printf("%s\n", temp);
	if (ft_countchar(split_tokens[0], ' ') != 0 || temp == NULL)
	{
		printf("Command not found\n");
		free(expand);
		if (temp)
			free(temp);
		free_array(split_tokens);
		return (NULL);
	}
	free(split_tokens[0]);
	split_tokens[0] = temp;
	free(expand);
	return (split_tokens);
}
