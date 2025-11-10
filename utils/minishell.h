#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>

/****************************** BUILT-IN ******************************/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//echo.c
char		*echo(char **token, t_env *begin_list);

//export
void		check_to_put(char *split_line, t_env **new_env);
void		export_arg(char **line_tokens, t_env *new_env);
int			valid_arg(char **split_line);
void		update_value(char *split_line, t_env *pointer);

//env.c
void		print_env(t_env *ptr);
char		**split_env(char *line);
void		put_env(t_env **list, char *line);
t_env		*clone_env(char **envp);

//unset.c
void		unset_env(t_env **env, char **cmd);

//pwd.c
void		pwd(t_env *new_env);

/****************************** EXPANDER ******************************/

char		*join_and_free(char *s1, const char *s2);
char		*expanded(t_env *begin_list, char *key);
char		*get_key(char *str);
char		*expand_arg(t_env *new_env, char *line, int i);

/****************************** REDIRECT ******************************/

char		*command(char *line, int i, int len, char *result);
int			*parse_fd(char *line);
void		redirect_and_command(char *line, t_env *new_env);

/******************************* TOKENS *******************************/

char		**split_with_quotes(char *line);
char		**tokens(t_env *new_env, char *line);

/**********************************************************************/

//free.c
void		free_array(char **array);
void		free_list(t_env **begin_list);

//main.c
char		*read_input(char *ppt, t_env *new_env);

#endif
