
#ifndef MINISHELL_H
# define MINISHELL_H

#include "collector.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct  s_collect
{
    struct s_collect    *next;
    void                *data;
}   t_collect;

t_collect	*create_item(void *data);
t_collect	*last_item(t_collect *begin_list);
t_collect	*init_collect(void);
void		close_collect(t_collect *init);
void		*put_item(t_collect **begin_list, void *data);

#endif
