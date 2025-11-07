#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_rd
{
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		*fd_temp;
	char	*cmd;
	char	**line_tokens;
} t_rd;

#endif
