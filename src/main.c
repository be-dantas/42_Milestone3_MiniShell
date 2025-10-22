
#include "../utils/minishell.h"

//sigint = 2 - sigout = 3
void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}

char	*read_input(char *ppt)
{
	char		*line;

	line = readline(ppt);
	if (line == NULL)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

int	main(int argc, char ** argv, char **env)
{
	char	*line;

	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		line = read_input("minishell ~ ");
		if (line && line[0] != '\0')
			// exec_line(line, env);
		if (*line)
			free(line);
	}
	rl_clear_history();
	return (0);
}
