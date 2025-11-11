#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_redirect
{
	int		fd_in;
	int		fd_out;
	int		prev_fd;
	int		fd[2];
	int		count_pipe;
	char	**s_pipe;
	pid_t	pid;
}	t_redirect;

typedef struct s_valid
{
	int quote1;
	int quote2;
	int last_pipe;
	int found_char;
}	t_valid;

#endif
