#include "../../utils/minishell.h"

static void	unsetting(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
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

void	unset_env(t_env **env, char **cmd)
{
	if (!cmd[1])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	unsetting(env, cmd[1]);
}
