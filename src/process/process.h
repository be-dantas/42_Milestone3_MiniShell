#ifndef PROCESS_H
# define PROCESS_H

typedef struct s_pipes
{
	int		fd[2];
	pid_t	pid;
	int		prev_fd;
	char	*cmd;
	char	**tokens_cmd;
}	t_pipes;

#endif
