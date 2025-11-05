#include "../../../utils/minishell.h"

static void	swap_key_value(t_env *exp, t_env *cmp)
{
	char	*temp;

	temp = exp->key;
	exp->key = cmp->key;
	cmp->key = temp;
	temp = exp->value;
	exp->value = cmp->value;
	cmp->value = temp;
}

static t_env	*sort_list(t_env *head)
{
	t_env	*cmp;
	t_env	*exp;

	if (!head)
		return (NULL);
	exp = head;
	while (exp)
	{
		cmp = exp->next;
		while (cmp)
		{
			if (ft_strcmp(exp->key, cmp->key) > 0)
				swap_key_value(exp, cmp);
			cmp = cmp->next;
		}
		exp = exp->next;
	}
	return (head);
}

static void	creat_print_export(t_env *new_env)
{
	t_env	*exp;

	exp = sort_list(new_env);
	while (exp)
	{
		if (exp->value == NULL)
		{
			printf("declare -x ");
			printf("%s\n", exp->key);
		}
		else
		{
			printf("declare -x ");
			printf("%s", exp->key);
			printf("=\"");
			printf("%s", exp->value);
			printf("\"\n");
		}
		exp = exp->next;
	}
	free_list(&exp);
}

void	export_arg(char **line_tokens, t_env *new_env)
{
	int	i;

	i = 1;
	if (!line_tokens[1])
		creat_print_export(new_env);
	else if (valid_arg(line_tokens) == 1)
	{
		while (line_tokens[i])
		{
			check_to_put(line_tokens[i], &new_env);
			i++;
		}
	}
}
