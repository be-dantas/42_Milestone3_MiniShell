#include "../utils/minishell.h"

void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}

char	*read_input(char *ppt, t_env *new_env)
{
	char		*line;

	line = readline(ppt);
	if (line == NULL)
	{
		free_list(&new_env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

void	exec_line(char **line_tokens, t_env *new_env)
{
	// if (ft_strncmp(line_tokens[0], "echo", 4) == 0)
	// 	echo(line_tokens, new_env);
	//if (string == "cd")
	//	;
	//if (string == "pwd")
	//	;
	if (ft_strncmp(line_tokens[0], "export", 6) == 0)
		export_arg(line_tokens, new_env);
	if (ft_strncmp(line_tokens[0], "unset", 5) == 0)
		// unset_env(&new_env, line_tokens);
	if (ft_strncmp(line_tokens[0], "env", 3) == 0)
		print_env(new_env);
	//if (string == "exit")
	//	;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**line_tokens;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		line = read_input("minishell ~ ", new_env);
		line_tokens = split_with_quotes(line);
		
		// int x = 0;
		// while(line_tokens[x])
		// {
		// 	printf("%s\n", line_tokens[x]);
		// 	x++;
		// }

		if (line_tokens && line_tokens[0] && line_tokens[0][0] != '\0')
			exec_line(line_tokens, new_env);
		if (line)
			free(line);
		if (line_tokens)
			free_array(line_tokens);
	}
	rl_clear_history();
	return (0);
}
