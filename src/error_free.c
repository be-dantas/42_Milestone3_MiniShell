#include "../utils/minishell.h"

// void	perror_exit(char *s, char **array, int x)
// {
// 	perror(s);
// 	free_array(array); //gc
// 	exit(x);
// }

void	putstr_exit(char *s, char **array, int x)
{
	ft_putstr_fd(s, 2);
	free_array(array);
	exit(x);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(t_env **begin_list)
{
	t_env	*to_free;

	to_free = NULL;
	while (*begin_list)
	{
		free(((*begin_list)->key));
		free(((*begin_list)->value));
		to_free = (*begin_list);
		(*begin_list) = (*begin_list)->next;
		free(to_free);
	}
	free(*begin_list);
}
