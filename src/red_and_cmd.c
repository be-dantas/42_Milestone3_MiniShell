/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_and_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:31:20 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/28 15:38:34 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/minishell.h"

static char	*remove_quotes_start(char *input)
{
	int		i;
	int		len;
	int		len2;
	char	*result;

	i = 0;
	len = ft_strlen(input);
	if (!((input[0] == '\'' && input[len - 1] == '\'')
			|| (input[0] == '\"' && input[len - 1] == '\"')))
		return (NULL);
	len2 = len - 2;
	result = malloc(sizeof(char) * (len2 + 1));
	while (i < len2)
	{
		result[i] = input[i + 1];
		i++;
	}
	result[len2] = '\0';
	return (result);
}

static char	*trate_input(char *input, t_shell *sh)
{
	char	*rmv_quotes;
	char	*line;

	rmv_quotes = remove_quotes_start(input);
	if (!rmv_quotes)
		rmv_quotes = ft_strdup(input);
	if (rmv_quotes[0] == '\0')
	{
		ft_putstr_fd("Command not found\n", 2);
		sh->last_exit_status = 127;
		free(rmv_quotes);
		return (NULL);
	}
	line = expand_arg(sh, rmv_quotes, 0);
	free(rmv_quotes);
	return (line);
}

static int	valid_input(char *line, t_shell *sh)
{
	t_valid	v;

	v.quote1 = 0;
	v.quote2 = 0;
	v.last_pipe = 0;
	v.found_char = 0;
	if (!valid_pipe(line, &v, 0)
		|| !valid_red(line, '>') || !valid_red(line, '<'))
	{
		printf("Syntax error\n");
		sh->last_exit_status = 2;
		return (0);
	}
	else if (!valid_quotes(line))
	{
		printf("unexpected EOF while looking for matching `\"\'\n");
		sh->last_exit_status = 2;
		return (0);
	}
	return (1);
}

void	redirect_and_command(char *input, t_shell *sh)
{
	char	*line;
	int		count_pipe;

	count_pipe = 0;
	line = trate_input(input, sh);
	if (line == NULL)
		return ;
	if (!valid_input(line, sh))
	{
		free(line);
		return ;
	}
	sh->s_pipe = split_pipe(line, 0, 0);
	free(line);
	while (sh->s_pipe[count_pipe])
		count_pipe++;
	if (count_pipe == 1)
		process_one_split(sh);
	else
		process_pipes(sh);
}
