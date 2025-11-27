/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:33:26 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/27 18:41:47 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/minishell.h"

void	exit_status(t_shell *sh, int status)
{
	sh->old_exit_status = sh->last_exit_status;
	sh->last_exit_status = status;
}

void	exit_process(char **tokens, t_shell *sh, char *cmd)
{
	(void)cmd;
	if (sh->s_pipe)
		free_array(sh->s_pipe);
	if (cmd)
		free(cmd);
	close(sh->fd_in);
	close(sh->fd_out);
	free_list(&sh->env);
	free_array(tokens);
	rl_clear_history();
	exit_status(sh, 0);
	exit(EXIT_SUCCESS);
}
