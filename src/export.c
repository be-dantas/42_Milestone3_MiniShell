#include "../utils/minishell.h"

void	print_export(t_env *exp)
{
	t_env	*temp;

	temp = exp;
	while (temp->next != NULL)
	{
		printf("declare -x ");
		printf("%s", temp->key);
		printf("=\"");
		printf("%s", temp->value);
		printf("\"\n");
		temp = temp->next;
	}
}

void	export_arg(char *line, t_env *exp)
{
	int	i;

	i = 6;
	if (line[i] == '\0')
		print_export(exp);
	else if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			print_export(exp);
		else
			put_export(line, exp);
	}
}
