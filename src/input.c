
#include "../utils/minishell.h"

char	*read_input(char *ppt)
{
	char	*line;

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

void	trate_input(char *line, char **env)
{
	// se ja for caminho
	// 	K_OK... acess...

	// se nao for
	// 	split line
	// 	split path
	// 	join linha path + comando
	// 	K_OK... acess...
}