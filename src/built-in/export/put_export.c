#include "../../../utils/minishell.h"

int	valid_arg_value(char *str)
 {
 	int		i;
 	int		count;
 	int		len;

	printf("entrei value\n");
 	i = ft_chars_until(str, '=') + 1;
 	len = ft_strlen(str) - 1;
	count = 0;
 	if (str[i] == '\"' || str[i] == '\'' || str[len] == '\"' || str[len] == '\'')
 	{
 		if (str[i] != str[len])
 			return (0);
 		while (str[i])
 		{
 			if (str[i] == str[0])
 				count++;
 			i++;
 		}
 		if (count % 2 != 0)
 			return (0);
 	}
 	return (1);
}

int	valid_arg_name(char *str)
{
	int	i;

	i = 0;
	printf("entrei name\n");
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] != '=' && str[i] != ' ' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	valid_arg(char **split_line)
{
	int	i;

	i = 1;
	while (split_line[i])
	{
		printf("entrei aqui\n");
		if (valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
			i++;
		else
		{
			if (!valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
				printf("export: `%s': not a valid identifier\n", split_line[i]);
			else if (!valid_arg_name(split_line[i]))
				printf("unexpected EOF while looking for matching `\"\'\n");
			return (0);
		}
	}
	return (1);
}

void	put_export(char *line, t_env *new_env)
{
	int		i;
	char	**split_line;

	i = 1;
	split_line = split_with_quotes(line);
	(void)new_env;
	if (valid_arg(split_line) == 1)
	{
		while (split_line[i])
		{
			check_to_put(split_line[i], &new_env);
			i++;
		}
		free_array(split_line);
	}
}
