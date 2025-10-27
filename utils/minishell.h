#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//collection.c
typedef struct  s_collect
{
	struct s_collect	*next;
	void				*data;
}	t_collect;

t_collect	*create_item(void *data);
t_collect	*last_item(t_collect *begin_list);
t_collect	*init_collect(void);
void		close_collect(t_collect *init);
void		*put_item(t_collect **begin_list, void *data);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//env
t_env		*create_env(char **string);
t_env		*last_env(t_env *begin_list);
void		*put_env(t_env **begin_list, char *string);
t_env		*clone_env(char **string);
void		print_env(t_env *ptr);
char		**find_and_split(char *string);
char		**split_env(char *string);

//export
void		print_export(t_env *exp);
void		export_arg(char *line, t_env *exp);

//error.c
void		putstr_exit(char *s, char **array, int x);
void		free_array(char **array);

//exec_line.c
void		exec_line(char *string, t_env *new_env);

//main.c
char		*read_input(char *ppt);
void		handle(int sig);

#endif
