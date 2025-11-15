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
	int	quote1;
	int	quote2;
	int	last_pipe;
	int	found_char;
}	t_valid;

typedef struct s_fd
{
	int	i;
	int	tmp;
	int	quote[2];
	int	*fd;
}	t_fd;

typedef struct s_here
{
	char	*eof;
	char	**to_free;
	char	*str;
	char	*result;
}	t_here;

#endif
