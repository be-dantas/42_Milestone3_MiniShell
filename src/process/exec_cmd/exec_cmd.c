/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:32:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/28 16:29:33 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../utils/minishell.h"

void	cmd_bar(char **tokens, t_shell *sh)
{
	char	**envp;
	char	*temp1;
	char	*temp2;

	if (access(tokens[0], F_OK) != 0)
	{
		free(sh->s_pipe);
		dup2_close_in_out(sh->fd_in, sh->fd_out);
		exec_access_putstr("No such file or directory\n", tokens, 127, sh->env);
	}
	if (access(tokens[0], X_OK) != 0)
	{
		free(sh->s_pipe);
		dup2_close_in_out(sh->fd_in, sh->fd_out);
		exec_access_putstr("Permission denied\n", tokens, 126, sh->env);
	}
	temp1 = ft_strdup("");
	temp2 = ft_strdup("");
	envp = env_list_to_array(sh->env, 0, temp1, temp2);
	execve(tokens[0], tokens, envp);
	free_array(envp);
	free(sh->s_pipe);
	dup2_close_in_out(sh->fd_in, sh->fd_out);
	exec_access_perror("Error execve", tokens, 126, sh->env);
}

static char	**path_split_func(char **tokens, t_shell *sh)
{
	char	**path_split;

	path_split = path(sh->env);
	if (path_split == NULL)
	{
		dup2_close_in_out(sh->fd_in, sh->fd_out);
		exec_access_putstr("No such file or directory\n", tokens, 121, sh->env);
		return (NULL);
	}
	else
		return (path_split);
}

static void	valid_exec(char **tokens, t_shell *sh, char *exec, char **path_split)
{
	if (exec == (char *)-1)
	{
		free(sh->s_pipe);
		free_array(path_split);
		dup2_close_in_out(sh->fd_in, sh->fd_out);
		exec_access_putstr("Permission denied\n", tokens, 126, sh->env);
	}
	else if (!exec)
	{
		free(sh->s_pipe);
		free_array(path_split);
		dup2_close_in_out(sh->fd_in, sh->fd_out);
		exec_access_putstr("Command not found\n", tokens, 127, sh->env);
	}
}

void	cmd_not_bar(char **tokens, t_shell *sh)
{
	char	**path_split;
	char	*exec;
	char	**envp;
	char	*temp1;
	char	*temp2;

	path_split = path_split_func(tokens, sh);
	if (path_split == NULL)
		return ;
	exec = command_valid(tokens, path_split);
	valid_exec(tokens, sh, exec, path_split);
	temp1 = ft_strdup("");
	temp2 = ft_strdup("");
	envp = env_list_to_array(sh->env, 0, temp1, temp2);
	execve(exec, tokens, envp);
	free_array(path_split);
	free(exec);
	free_array(envp);
	free(sh->s_pipe);
	dup2_close_in_out(sh->fd_in, sh->fd_out);
	exec_access_perror("Error execve", tokens, 126, sh->env);
}
