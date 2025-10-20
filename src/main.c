
#include "../utils/minishell.h"

int	main(int argc, char ** argv)
{
	char	*line;

	line = read_input();







	free(line);
    rl_clear_history();
    return (0);
}
