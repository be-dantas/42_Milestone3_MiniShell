#include "../utils/minishell.h"

// rever free_array, pois queremos trabalhar com gc

void	exec_access_perror(char *s, char **array, int x)
{
	perror(s);
	free_array(array);
	exit(x);
}

void	exec_access_putstr(char *s, char **array, int x)
{
	ft_putstr_fd(s, 2);
	free_array(array);
	exit(x);
}