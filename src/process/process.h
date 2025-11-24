#ifndef PROCESS_H
# define PROCESS_H

typedef struct s_pipes
{
	int		prev_fd;
	int		fd[2];
	pid_t	pid;
	char	*cmd;
	char	**tokens_cmd;
	pid_t	last_pid;
}	t_pipes;

#endif
