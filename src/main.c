#include "../utils/minishell.h"

static void	handle(int sig)
{
	if (sig == 2)
		printf("\n%s@minishell ~ ", getenv("USER"));
}

char	*read_input(char *ppt, t_env *new_env)
{
	char		*line;

	line = readline(ppt);
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		free_list(&new_env);
		free(ppt);
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

	user = ft_strjoin(getenv("USER"), "@minishell ~ ");
	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		input = read_input(user, new_env);
		if (input[0] != '\0')
			redirect_and_command(input, new_env);
		free(input);
	}
	free(user);
	rl_clear_history();
	return (0);
}
