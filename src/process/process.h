#ifndef PROCESS_H
# define PROCESS_H

typedef struct s_pipes
{
	int		prev_fd;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	pid_t	pid;
	char	*cmd;
	char	**tokens_cmd;
}	t_pipes;

#endif
