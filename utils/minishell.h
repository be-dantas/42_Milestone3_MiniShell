#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/redirect/redirect.h"
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

typedef struct s_shell
{
	t_env	*env;
	int		last_exit_status;
}	t_shell;

//export
void		update_value(char *split_line, t_env *pointer);
void		check_to_put(char *split_line, t_env **env);
void		export_arg(char **line_tokens, t_shell *sh);
int			valid_arg(char **split_line, t_shell *sh);

void		cd(char **line, t_shell *sh);
void		echo(char **token, t_shell *sh);
void		print_env(t_env *ptr);
char		**split_env(char *line);
void		put_env(t_env **list, char *line);
t_env		*clone_env(char **envp);
t_env		*get_value_by_name(t_env **new_env, char *str);
void		pwd(t_shell *sh);
void		unset_env(t_shell *sh, char **cmd);

/****************************** EXPANDER ******************************/

char		*join_and_free(char *s1, const char *s2);
char		*expanded(t_env *begin_list, char *key);
char		*get_key(char *str);
char		*expand_arg(t_env *new_env, char *line, int i);

/****************************** PROCESS *******************************/

//exec
void		exec_access_perror(char *s, char **array, int x, t_env *env);
void		exec_access_putstr(char *s, char **array, int x, t_env *env);
char		**path(t_env *env);
char		*command_valid(char **tokens, char **path_split);
void		cmd_bar(char **tokens, t_env *env, int fd_in, int fd_out);
void		cmd_not_bar(char **tokens, t_env *env, int fd_in, int fd_out);
char		**env_list_to_array(t_env *env, int i, char *tmp1, char *tmp2);

//tokens
char		**split_with_quotes(char *line);
char		**tokens(char *line);

char		*command(char *line);
void		process_one_split(char **line, t_shell *sh);
void		process_pipes(char **pipes, t_shell *sh);
void		dup2_close_in_out(int fd_in, int fd_out);
int			is_builtin(char *cmd);
void		redirect_fd(char *line, int fd_in, int fd_out, t_env *begin_list);
void		exec_external(char **tokens, t_env *env, int fd_in, int fd_out);
void		exec_line(char **line_tokens, t_shell *sh);

/****************************** REDIRECT ******************************/

void		if_write(char *line, int fd_out, t_fd *fd);
void		if_read(char *line, int fd_in, t_fd *fd, t_env *begin_list);
int			*parse_fd(char *line, int fd_in, int fd_out, t_env *begin_list);
int			red_heredoc(t_env *begin_list, char *line);
char		**split_pipe(char *line, int i, int j);
int			valid_input(char *line);

/**********************************************************************/

//free.c
void		free_array(char **array);
void		free_list(t_env **begin_list);

//main.c
char		*read_input(t_shell *sh);

//valid_input.c
typedef struct s_valid
{
	int	quote1;
	int	quote2;
	int	last_pipe;
	int	found_char;
}	t_valid;

int			valid_input(char *line);

#endif
