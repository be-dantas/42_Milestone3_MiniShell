//sigint = 2 - sigout = 3
#include "../utils/minishell.h"

void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}
