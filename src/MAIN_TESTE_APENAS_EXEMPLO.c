#include "../utils/minishell.h"

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
}
