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
	free_array(array); //gc
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
} //nao vai precisar depois do gc
