#include "../../utils/minishell.h"

void	exit_process(char **tokens, t_shell *sh, char *cmd)
{
	rl_clear_history();
	free_list(&sh->env);
	close(sh->fd_in);
	close(sh->fd_out);
	free_array(tokens);
	free_array(sh->s_pipe);
	free(cmd);
	sh->last_exit_status = 0;
	exit(EXIT_SUCCESS);
}
