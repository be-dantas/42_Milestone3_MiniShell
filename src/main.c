#include "../utils/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_input(t_env *new_env)
{
	char	*line;

	line = readline("@minishell ~ ");
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		rl_clear_history();
		free_list(&new_env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

static void	redirect_and_command(char *input, t_env **env)
{
	char	*line;
	char	**s_pipe;
	int		count_pipe;

	count_pipe = 0;
	line = expand_arg(*env, input, 0);
	if (!valid_input(line))
	{
		free(line);
		write(2, "Syntax error\n", 13);
		return ;
	}
	s_pipe = split_pipe(line, 0, 0);
	free(line);
	while (s_pipe[count_pipe])
		count_pipe++;
	if (count_pipe == 1)
		process_one_split(s_pipe, env);
	else
		process_pipes(s_pipe, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = read_input(new_env);
		if (input[0] != '\0')
			redirect_and_command(input, &new_env);
		free(input);
	}
	rl_clear_history();
	free_list(&new_env);
	return (0);
}
