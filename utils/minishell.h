#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/****************************** BUILT-IN ******************************/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//export
char		*remove_quotation(char *string);
void		update_value(char *split_line, t_env *pointer);
void		put_exp(char **temp, t_env **new_env);
void		check_to_put(char *split_line, t_env **new_env);

void		swap_key_value(t_env *exp, t_env *cmp);
t_env		*sort_list(t_env *head);
void		creat_print_export(t_env *new_env);
void		export_arg(char *line, t_env *new_env);

int			valid_arg_value(char *str);
int			valid_arg_name(char *str);
int			valid_arg(char **split_line);
void		put_export(char *line, t_env *new_env);

char		**split_with_quotes(char *line);

//env.c
void		print_env(t_env *ptr);
char		**split_env(char *line);
t_env		*create_env(char *line);
void		put_env(t_env **list, char *line);
t_env		*clone_env(char **envp);

//unset.c
void		unsetting(t_env **env, char *key);
void		unset_env(t_env **env, char *cmd);

/****************************** EXPANDER ******************************/

char		*expand_arg(t_env *begin_list, char *str, int i);
char		*join_and_free(char *s1, const char *s2);
char		*expanded(t_env *begin_list, char *key);
char		*get_key(char *str);
char		*expand_variable(t_env *begin_list, char *str, int *i);
char		*expand_literal(char *str, int *i);

/**********************************************************************/

//error_free.c
void		free_array(char **array);
void		free_list(t_env **begin_list);

//main.c
void		handle(int sig);
char		*read_input(char *ppt, t_env *new_env);
void		exec_line(char *line, t_env *new_env);
int			main(int argc, char **argv, char **envp);

#endif
