#include "../utils/minishell.h"

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

void	exec_line(char *line, t_env *new_env)
{
	//if (string == "echo")
	//	;
	//if (string == "cd")
	//	;
	//if (string == "pwd")
	//	;
	if (ft_strncmp(line, "export", 6) == 0)
		export_arg(line, new_env);
	//if (string == "unset")
	//	;
	if (ft_strncmp(line, "env", ft_strlen(line)) == 0)
		print_env(new_env);
	//if (string == "exit")
	//	;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		line = read_input("minishell ~ ");
		if (line && line[0] != '\0')
			exec_line(line, new_env);
		if (*line)
			free(line);
		if (line == NULL)
			break ;
	}
	free_list(&new_env);
	rl_clear_history();
	return (0);
}
