#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_redirect
{
	char	**s_pipe;
	int		count_pipe;
	int		fd_in;
	int		fd_out;
}	t_redirect;

typedef struct s_valid
{
	int quote1;
	int quote2;
	int last_pipe;
	int found_char;
}	t_valid;

typedef struct s_pipes
{
	int		fd[2];
	pid_t	pid;
	int		prev_fd;
	char	*cmd;
	char	**tokens_cmd;
}	t_pipes;

#endif
