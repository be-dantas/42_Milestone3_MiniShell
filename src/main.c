#include "../utils/minishell.h"

static void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}

static char	*read_input(char *ppt, t_env *new_env)
{
	char		*line;

	line = readline(ppt);
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		free_list(&new_env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

static void	exec_line(char **line_tokens, t_env *new_env)
{
	if (ft_strncmp(line_tokens[0], "echo", 5) == 0)
		;	// 	echo(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "cd", 3) == 0)
		;
	else if (ft_strncmp(line_tokens[0], "pwd", 4) == 0)
		;
	else if (ft_strncmp(line_tokens[0], "export", 7) == 0)
		export_arg(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "unset", 6) == 0)
		unset_env(&new_env, line_tokens);
	else if (ft_strncmp(line_tokens[0], "env", 4) == 0)
		print_env(new_env);
	else if (ft_strncmp(line_tokens[0], "exit", 5) == 0)
		read_input("exit", new_env);
	else
		printf("Command not found\n"); //VOCÊ VAI REMOVER NO FUTURO E SUBSTUIR PELA FUNÇÃO QUE FAZ O EXECVE
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**line_tokens;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	line_tokens = NULL;
	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		line = read_input("minishell ~ ", new_env);
		if (line[0] != '\0')
			line_tokens = tokens(new_env, line);		
		if (line_tokens)
			exec_line(line_tokens, new_env);
		if (*line)
			free(line);
		if (line_tokens)
			free_array(line_tokens);
	}
	rl_clear_history();
	return (0);
}
