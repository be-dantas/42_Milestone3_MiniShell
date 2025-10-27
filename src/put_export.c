#include "../utils/minishell.h"

int	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	valid_arg_name(char *str)
{
	int	i;
	
	i = 0;
	if (!have_equal(str[i]))
		return (0);
	else
	{
		if (!ft_isalpha(str[0]))
			return(0);
		while (str[i] != '=')
		{
			if (ft_isalnum(str[i]))
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int valid_arg(char **split_line)
{
	int i;

	i = 1;
	while (split_line[i])
	{
		if (valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	put_export(char *line, t_env *env)
{
	int		i;
	char	**split_line;

	i = 1;
	split_line = ft_split(line, ' ');
	if (valid_arg(split_line))
	{




	}
	else
		putstr_exit("ARG invalid", split_line, 1); //ainda nao limpa todo env criado, etc...
}

