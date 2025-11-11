#include "../utils/minishell.h"

static void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}

char	*read_input(char *ppt, t_env *new_env, char **line_tokens)
{
	char	*line;

	line = readline(ppt);
	if (*line_tokens && line_tokens[1][0] != '\0')
		return ("Command not found\n");
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
		line = read_input("minishell ~ ", new_env, NULL);
		if (line[0] != '\0')
			redirect_and_command(line, new_env);
		free(line);
	}
	rl_clear_history();
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	char	**line_tokens;
// 	t_env	*new_env;

// 	int fd[2] = {0, 0};
// 	int	*parsed_fd;
// 	int fd_in = dup(STDIN_FILENO);
// 	int fd_out = dup(STDOUT_FILENO);
// 	char *comando;

// 	(void)argc;
// 	(void)argv;
// 	new_env = clone_env(envp);
// 	line_tokens = NULL;
// 	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
// 		add_history(NULL);
// 	while (1)
// 	{
// 		line = read_input("minishell ~ ", new_env);
// 		if (line[0] != '\0')
// 		{
// 			parsed_fd = parse_fd(line);
// 			fd[0] = parsed_fd[0];
// 			fd[1] = parsed_fd[1];
// 			free(parsed_fd); 
// 			comando = command(line, 0, 0, ft_strdup(""));
// 			dup2(fd[0], STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 			line_tokens = tokens(new_env, comando);
// 			exec_line(line_tokens, new_env);
// 			dup2(fd_in, STDIN_FILENO);
// 			dup2(fd_out, STDOUT_FILENO);
// 		}
// 		if (*line)
// 			free(line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }
