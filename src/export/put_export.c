#include "../../utils/minishell.h"

// ajustar validação de value
// ajustar printagem do env
// ajustar printagem do export

// int	valid_arg_value(char *str)
// {
// 	int		i;
// 	int		count;
// 	char	x;
// 	int		len;

// 	i = ft_chars_until(str, "=") + 1;
// 	if (valid_arg_name(str) && !str[i])
// 		return (1);
// 	len = ((int)ft_strlen(str) - 1);
// 	if (str[i] == '\"' || str[i] == '\'' || str[len] == '\"' || str[len] == '\'')
// 	{
// 		x = str[i];
// 		if (str[i] != str[len])
// 			return (0);
// 		while (str[i])
// 		{
// 			if (str[i] == x)
// 				count++;
// 			i++;
// 		}
// 		if (count % 2 != 0)
// 			return (0);
// 	}
// 	return (1);
// }

int	valid_arg_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) || str[0] != '_')
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
