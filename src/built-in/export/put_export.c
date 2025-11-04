#include "../../../utils/minishell.h"

int	valid_arg_value(char *str)
{
	int	i;
	int	single_q;
	int	double_q;

	i = ft_chars_until(str, '=');
	single_q = 0;
	double_q = 0;
	if (i == 0)
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '\'' && double_q == 0)
			single_q = !single_q;
		else if (str[i] == '"' && single_q == 0)
			double_q = !double_q;
		i++;
	}
	if (single_q || double_q)
		return (0);
	return (1);
}

int	valid_arg_name(char *str)
{
	int	i;

	i = 0;
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
		if (valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
			i++;
		else
		{
			if (!valid_arg_name(split_line[i])
				&& valid_arg_value(split_line[i]))
				printf("export: `%s': not a valid identifier\n", split_line[i]);
			else if (!valid_arg_name(split_line[i]))
				printf("unexpected EOF while looking for matching `\"\'\n");
			return (0);
		}
	}
	return (1);
}

void	put_export(char **line_tokens, t_env *new_env)
{
	int	i;

	i = 1;
	(void)new_env;
	if (valid_arg(line_tokens) == 1)
	{
		while (line_tokens[i])
		{
			line_tokens[i] = expand_arg(new_env, line_tokens[i], 0);
			i++;
		}
		i = 1;
		while (line_tokens[i])
		{
			check_to_put(line_tokens[i], &new_env);
			i++;
		}
		free_array(line_tokens);
	}
}
