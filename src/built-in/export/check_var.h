#include "../../../utils/minishell.h"

#ifndef CHECK_VAR_H
# define CHECK_VAR_H

typedef struct s_init
{
	int		flag;
	t_env	*list_reset;
	char	*temp_expand;
	char	**temp;
}	t_init;

void	free_all_temp(char **temp, char *temp_expand);

#endif
