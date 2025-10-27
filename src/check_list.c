#include "../utils/minishell.h"

void	check_to_put(char *string, t_env **begin_list)
{
	char	**temp;
	t_env	*list_reset;
	t_env	*ptr;

	ptr = NULL;
	list_reset = *begin_list;
	temp = split_env(string);
	while (*begin_list)
	{
		if (ft_strncmp((*begin_list)->key, temp[0], ft_strlen((*begin_list)->key)) == 0)
		{
			(*begin_list)->value = temp[1];
			free(temp[0]);
			free(temp[1]);
			free(temp);
			return ;
		}
		(*begin_list) = (*begin_list)->next;
	}
	(*begin_list) = list_reset;
	put_env(begin_list, string);
	free(temp[0]);
	free(temp[1]);
	free(temp);
}
