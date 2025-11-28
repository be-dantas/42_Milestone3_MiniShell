/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:31:20 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/28 14:46:33 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/minishell.h"

void	handle_sigint(int sig)
{
	g_heredoc_child = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_input(t_shell *sh)
{
	char	*line;

	line = readline("@minishell ~ ");
	if (line == NULL)
	{
		rl_clear_history();
		free_list(&sh->env);
		printf("exit\n");
		exit(sh->last_exit_status);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

static void	status_signal(t_shell *sh)
{
	if (g_heredoc_child == SIGINT || g_heredoc_child == SIGQUIT)
	{
		sh->last_exit_status = g_heredoc_child + 128;
		g_heredoc_child = -1;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	sh;

	if (argc > 1)
	{
		printf("minishell: unsupported arguments (\'%s\')\n", argv[1]);
		exit(2);
	}
	sh.env = clone_env(envp);
	sh.last_exit_status = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = read_input(&sh);
		status_signal(&sh);
		if (input[0] != '\0' && g_heredoc_child == -1)
			redirect_and_command(input, &sh);
		free(input);
	}
	rl_clear_history();
	free_list(&sh.env);
	return (0);
}
