#include "../utils/minishell.h"

static void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_input(char *ppt, t_env *new_env)
{
	char	*line;

	line = readline(ppt);
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		free(ppt);
		rl_clear_history();
		free_list(&new_env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*new_env;
	char	*user;

	(void)argc;
	(void)argv;
	user = ft_strjoin(getenv("USER"), "@minishell ~ ");
	new_env = clone_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = read_input(user, new_env);
		if (input[0] != '\0')
			redirect_and_command(input, &new_env);
		free(input);
	}
	free(user);
	rl_clear_history();
	free_list(&new_env);
	return (0);
}
