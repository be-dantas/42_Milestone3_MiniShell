#ifndef REDIRECT_H
# define REDIRECT_H

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
	char	*temp1;
	char	*tmp1;
	char	*tmp2;
}	t_here;

#endif
