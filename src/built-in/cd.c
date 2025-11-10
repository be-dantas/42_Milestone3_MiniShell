#include "../../utils/minishell.h"

void	update_pwd(t_env **begin_list)
{
	t_env	*list_reset;
	t_env	*ptr;

	list_reset = *begin_list;
	ptr = NULL;
	while (*begin_list)
	{
		if (ft_strcmp((*begin_list)->key, "OLDPWD") == 0)
		{
			(*begin_list)->value = expanded(*begin_list, "PWD");
			(*begin_list) = list_reset;
			break ;
		}
		(*begin_list) = (*begin_list)->next;
	}
	while (*begin_list)
	{
		if (ft_strcmp((*begin_list)->key, "PWD") == 0)
		{
			(*begin_list)->value = getcwd(NULL, 0);
			(*begin_list) = list_reset;
			break ;
		}
		(*begin_list) = (*begin_list)->next;
	}
}

void	cd(char **line, t_env **begin_list)
{
	int		flag;

	flag = 0;
	if (line[1] == NULL || line[1][0] == '~')
		chdir(expanded(*begin_list, "HOME"));
	if (line[2] != NULL)
		printf("cd: too many arguments\n");
	if (line[1])
	{
		flag = chdir(line[1]);
		if (flag == -1)
		{
			printf("cd: %s: No such file or directory\n", line[1]);
			return ;
		}
		update_pwd(begin_list);
	}
}
