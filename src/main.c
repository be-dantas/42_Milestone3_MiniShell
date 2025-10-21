
#include "../utils/minishell.h"

int	main(int argc, char ** argv, char **env)
{
	char	*line;

	while (1)
	{
		line = read_input("minishell ~ ");
		if (line && line[0] != '\0')
			// exec_line(line, env);
		if (line)
			free(line);
	}
	rl_clear_history();
	return (0);
}
