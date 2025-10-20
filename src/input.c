/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:16:16 by bedantas          #+#    #+#             */
/*   Updated: 2025/10/20 17:25:50 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/minishell.h"

char	*read_input(void)
{
	char	*prompt;
	char	*line;

	prompt = "minishell ~ ";
	line = readline(prompt);
	if (line == NULL)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}
