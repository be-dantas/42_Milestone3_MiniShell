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

/*
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
} */

static int	valid_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

static int	valid_input(char *line, t_shell *sh)
{
	t_valid	v;

	v.quote1 = 0;
	v.quote2 = 0;
	v.last_pipe = 0;
	v.found_char = 0;
	if (valid_space(line) == 1)
		return (0);
	else if (!valid_pipe(line, &v, 0)   /// arrumar aqui ls -l | ""
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
	line = expand_arg(sh, input, 0);
	if (!valid_input(line, sh))
	{
		free(line);
		return ;
	}
	sh->fd_in = dup(STDIN_FILENO);
	sh->fd_out = dup(STDOUT_FILENO);
	sh->s_pipe = split_pipe(line, 0, 0);
	free(line);
	while (sh->s_pipe[count_pipe])
		count_pipe++;
	if (count_pipe == 1)
		process_one_split(sh);
	else
		process_pipes(sh);
}
