/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:41:55 by bedantas          #+#    #+#             */
/*   Updated: 2025/10/20 17:28:46 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/minishell.h"

int	main(int argc, char ** argv)
{
	char	*line;

	line = read_input();







	free(line);
    rl_clear_history();
    return (0);
}
