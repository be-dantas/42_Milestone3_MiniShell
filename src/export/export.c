#include "../utils/minishell.h"

char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			else
				j++;
		}
		i++;
	}
	return (envp);
}

void	creat_print_export(char **envp)
{
	t_env	*exp;

	exp = clone_env(sort_env(envp));
	while (exp)
	{
		printf("declare -x ");
		printf("%s", exp->key);
		printf("=\"");
		printf("%s", exp->value);
		printf("\"\n");
		exp = exp->next;
	}
	free_list(&exp);
}

void	export_arg(char *line, t_env *new_env, char **envp)
{
	int	i;

	i = 6;
	if (line[i] == '\0')
		creat_print_export(envp);
	else if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			creat_print_export(envp);
		else
			put_export(line, new_env);
	}
}
