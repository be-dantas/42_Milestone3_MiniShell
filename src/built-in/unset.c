#include "../../utils/minishell.h"

void	unset_env(t_env **env, char **cmd)
{
	t_env	*curr;
	t_env	*prev;

	if (cmd[1] == NULL)
		return ;
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, cmd[1], ft_strlen(cmd[1]) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
