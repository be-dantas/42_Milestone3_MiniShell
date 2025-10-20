
#include "../utils/minishell.h"

char	*read_input(void)
{
	char	*prompt;
	char	*line;

	prompt = "minishell ~ ";
	line = readline(prompt);
	if (line == NULL)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}
