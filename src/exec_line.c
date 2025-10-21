
#include "../utils/minishell.h"

// funções para pegar cada comando da linha;

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

void	exec_line(char *cmd, char **env)
{

}
