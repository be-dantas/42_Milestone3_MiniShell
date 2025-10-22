#include "../utils/minishell.h"
/*
int main()
{
	t_collect	*gc;
	char		*array;
	char		*array2;

	gc = init_collect();
	array = put_item(&gc, "teste");
	array2 = put_item(&gc, "teste2");
	close_collect(gc);
	return (0);
}*/
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell$ ");
}

int main(void)
{
    char *input;
	char *teste_arg_terminal;

	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	teste_arg_terminal = getenv("PATH");
	printf("%s", teste_arg_terminal);
    while (1)
    {
        input = readline("minishell$ ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);
        printf("Você digitou: %s\n", input);
        free(input);
    }
    return (0);
}

