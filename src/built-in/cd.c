#include "../../utils/minishell.h"

void	update_pwd(t_env **begin_list)
{
	t_env	*list_reset;
	t_env	*ptr;
	char	*pwd;
	char	*temp;
	
	temp = NULL;
	pwd = NULL;
	list_reset = *begin_list;
	ptr = NULL;
	while (list_reset)
	{
		if (list_reset->key && ft_strcmp(list_reset->key, "OLDPWD") == 0)
		{
			temp=list_reset->value;
			list_reset->value = expanded(list_reset, "PWD");
			free(temp);
			list_reset = (*begin_list);
			break ;
		}
		list_reset = list_reset->next;
	}
	while (list_reset)
	{
		if (list_reset->key && ft_strcmp(list_reset->key, "PWD") == 0)
		{
			pwd = getcwd(NULL, 0);
			list_reset->value = ft_strdup(pwd);
			list_reset = (*begin_list);
			break ;
		}
		list_reset = list_reset->next;
	}
	(*begin_list) = list_reset;
	if (pwd)
		free(pwd);
}

void	cd(char **line, t_env **begin_list)
{
	int		flag;

	flag = 0;
	if (line[1] == NULL || line[1][0] == '~')
	{
		chdir(expanded(*begin_list, "HOME"));
		return ;
	}
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
