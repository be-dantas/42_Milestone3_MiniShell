/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:33:26 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/28 12:38:56 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../utils/minishell.h"

void	exit_status(t_shell *sh, int status)
{
	if (g_heredoc_child == 0 || g_heredoc_child == -1)
		sh->old_exit_status = sh->last_exit_status;
	else
		sh->old_exit_status = g_heredoc_child + 128;
	sh->last_exit_status = status;
}

static void	exit_args(char **tokens, t_shell *sh, int i, int is_num)
{
	char	*token;
	int		status;

	token = remove_quotes_str(tokens[1], 0, 0);
	while (token[i])
	{
		if (!isdigit(token[i]) && !((token[0] == '+' || token[0] == '-')))
			is_num = -1;
		i++;
	}
	if (is_num == -1)
	{
		printf("exit: %s: numeric argument required\n", tokens[1]);
		exit_status(sh, 2);
	}
	else
	{
		status = ft_atoi(token);
		status %= 256;
		if (status < 0)
			status += 256;
		exit_status(sh, status);
	}
	free(token);
}

void	exit_process(char **tokens, t_shell *sh, char *cmd)
{
	(void)cmd;
	if (tokens[1] && tokens[2])
	{
		printf("exit: too many arguments\n");
		exit_status(sh, 1);
		return ;
	}
	if (tokens[1])
		exit_args(tokens, sh, 0, 0);
	else
		exit_status(sh, 0);
	if (sh->s_pipe)
		free_array(sh->s_pipe);
	if (cmd)
		free(cmd);
	close(sh->fd_in);
	close(sh->fd_out);
	free_list(&sh->env);
	free_array(tokens);
	rl_clear_history();
	exit(sh->last_exit_status);
}
