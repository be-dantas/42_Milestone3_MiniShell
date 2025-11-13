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
# include <sys/wait.h>

/****************************** BUILT-IN ******************************/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//export
void		update_value(char *split_line, t_env *pointer);
void		check_to_put(char *split_line, t_env **new_env);
void		export_arg(char **line_tokens, t_env *new_env);
int			valid_arg(char **split_line);

void		cd(char **line, t_env **begin_list);
void		echo(char **token);
void		print_env(t_env *ptr);
char		**split_env(char *line);
void		put_env(t_env **list, char *line);
t_env		*clone_env(char **envp);
void		pwd(char **line_tokens, t_env *new_env);
void		unset_env(t_env **env, char **cmd);

/****************************** EXPANDER ******************************/

char		*join_and_free(char *s1, const char *s2);
char		*expanded(t_env *begin_list, char *key);
char		*get_key(char *str);
char		*expand_arg(t_env *new_env, char *line, int i);

/****************************** PROCESS *******************************/

//tokens
char		**split_with_quotes(char *line);
char		**tokens(char *line);

char		*command(char *line);
int			is_builtin(char *cmd);
void		redirect_fd(char *line, int fd_in, int fd_out);
// void		exec_external(char **tokens, t_env *env);
void		exec_line(char **line_tokens, t_env *new_env);
void		process_one_split(char *line, t_env *env, int fd_in, int fd_out);
void		process_pipes(char **pipes, t_env *env);

/****************************** REDIRECT ******************************/

int			*parse_fd(char *line, int fd_in, int fd_out);				 //+25 linhas
void		heredoc(t_env *begin_list, char *line);
void		redirect_and_command(char *line, t_env *new_env);
char		**split_pipe(char *line, int i, int j);
int			valid_input(char *line);

/**********************************************************************/

//free.c
void		free_array(char **array);
void		free_list(t_env **begin_list);

//main.c
char		*read_input(char *ppt, t_env *new_env);

#endif
