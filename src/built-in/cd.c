#include "../../utils/minishell.h"

static void	update_pwd(t_env **begin_list)
{
	t_env	*begin;
	char	*temp_1;
	char	*temp_2;

	temp_1 = NULL;
	temp_2 = NULL;
	begin = (*begin_list);
	while ((*begin_list) != NULL)
	{
		if (ft_strcmp((*begin_list)->key, "OLDPWD") == 0)
		{
			temp_2 = ft_strdup(expanded((*begin_list), "PWD"));
			free((*begin_list)->value);
			(*begin_list)->value = temp_2;
		}
		if (ft_strcmp((*begin_list)->key, "PWD") == 0)
		{
			temp_1 = getcwd(NULL, 0);
			free((*begin_list)->value);
			(*begin_list)->value = temp_1;
		}
		(*begin_list) = (*begin_list)->next;
	}
	(*begin_list) = begin;
}
//se a pessoa apagar OLDPWD ou PWD, deveriamos crio-los novamente?

static int	cd_utils(char **line, t_shell *sh)
{
	int	flag;

	flag = chdir(line[1]);
	if (flag == -1)
	{
		printf("cd: %s: No such file or directory\n", line[1]);
		sh->last_exit_status = 1;
		return (1);
	}
	update_pwd(&sh->env);
	return (0);
}

void	cd(char **line, t_shell *sh)
{
	int	flag;

	flag = 0;
	if (line[2] != NULL)
	{
		printf("cd: too many arguments\n");
		sh->last_exit_status = 1;
		return ;
	}
	if (line[1] == NULL || line[1][0] == '~')
	{
		chdir(expanded(sh->env, "HOME"));
		update_pwd(&sh->env);
	}
	else if (line[1])
	{
		if (cd_utils(line, sh) == 1)
			return ;
	}
	sh->last_exit_status = 0;
}
