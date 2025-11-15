#include "../../utils/minishell.h"
#include "redirect.h"

static t_redirect	init_redirect_vars(char *line)
{
	t_redirect	rd;

	rd.s_pipe = split_pipe(line, 0, 0);
	free(line);
	rd.count_pipe = 0;
	while (rd.s_pipe[rd.count_pipe])
		rd.count_pipe++;
	rd.fd_in = dup(STDIN_FILENO);
	rd.fd_out = dup(STDOUT_FILENO);
	close(rd.fd_in);
	close(rd.fd_out);
	return (rd);
}

void	redirect_and_command(char *input, t_env **env)
{
	char		*line;
	t_redirect	rd;

	line = expand_arg(*env, input, 0);
	if (!valid_input(line))
	{
		free(line);
		write(2, "Syntax error\n", 13);
		return ;
	}
	rd = init_redirect_vars(line);
	if (rd.count_pipe == 1)
		process_one_split(rd.s_pipe, env, rd.fd_in, rd.fd_out);
	else
		process_pipes(rd.s_pipe, env);
	dup2(rd.fd_in, STDIN_FILENO);
	dup2(rd.fd_out, STDOUT_FILENO);
	close(rd.fd_in);
	close(rd.fd_out);
}
