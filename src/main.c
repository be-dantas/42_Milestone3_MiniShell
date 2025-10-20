
#include "../utils/minishell.h"

int	main(int argc, char ** argv, char **env)
{
	char	*line;

	while (1)
	{
		line = read_input("minishell ~ ");
		if (line && line[0] != '\0')
		{
			trate_input(line, env);
			
		}
		if (line)
			free(line);
	}
	rl_clear_history();
	return (0);
}
