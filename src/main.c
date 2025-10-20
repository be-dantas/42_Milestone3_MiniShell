
#include "../utils/minishell.h"

int	main(int argc, char ** argv)
{
	char	*line;

	while (1)
	{
		line = read_input("minishell ~ ");
		if (line && line[0] != '\0')
			// FUNÇÕES DE PARSING E EXECUÇÃO AQUI
		if (line)
			free(line);
	}
	rl_clear_history();
	return (0);
}
