/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trate_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:31:20 by bedantas          #+#    #+#             */
/*   Updated: 2025/11/27 18:01:39 by bedantas         ###   ########.fr       */
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

char	*trate_input(char *input, t_shell *sh)
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
	line = expand_arg(sh->env, rmv_quotes, 0);
	free(rmv_quotes);
	return (line);
}
