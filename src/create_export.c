#include "../utils/minishell.h"

char    **sort_env(char **envp)
{
	int     i;
	int     j;
	char    *temp;

	i = 0;
	j = i + 1;
	while (envp[i])
	{
		while (envp[j] != (void *)0)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
				j = i + 1;
			}
			else
				j++;
		}
		i++;
	}
	return (envp);  //NÃO COLOCOU EM ORDEEEEEEEEEEEEEEEEEEEEEEEM
}
	
t_env	*creat_export(char **envp)
{
	t_env	*exp;

	exp = clone_env(sort_env(envp));
	return(exp);
}
