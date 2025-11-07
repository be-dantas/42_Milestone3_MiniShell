#include "../../utils/minishell.h"

static void	func_flag(char *line, int *i, int quote[2])
{
	while (line[*i] && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'')
			quote[0] = !quote[0];
		else if (line[*i] == '\"')
			quote[1] = !quote[1];
		(*i)++;
	}
}

static int	open_write_fd(char *line, int i)
{
	int		start;
	char	*file;
	int		fd;

	// pula '>' e possíveis espaços
	if (line[i + 1] == '>')
		i += 2;
	else
		i++;
	while (line[i] == ' ')
		i++;

	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '<' && line[i] != '>')
		i++;

	file = ft_substr(line, start, i - start);
	if (line[start - 2] == '>')
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	return (fd);
}

static int	open_read_fd(char *line, int i)
{
	int		start;
	char	*file;
	int		fd;

	i++; // pula '<'
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '<' && line[i] != '>')
		i++;

	file = ft_substr(line, start, i - start);
	fd = open(file, O_RDONLY, 0444);
	free(file);
	return (fd);
}

int	*parse_fd(char *line)
{
	int		i;
	int		quote[2];
	int		*fd;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	fd[0] = dup(STDIN_FILENO);  // entrada padrão
	fd[1] = dup(STDOUT_FILENO); // saída padrão
	quote[0] = 0;
	quote[1] = 0;
	i = 0;
	while (line[i])
	{
		func_flag(line, &i, quote);
		if (!quote[0] && !quote[1])
		{
			if (line[i] == '<')
				fd[0] = open_read_fd(line, i);
			else if (line[i] == '>')
				fd[1] = open_write_fd(line, i);
		}
		if (line[i])
			i++;
	}
	return (fd);
}


/*
void	func_flag(char *line, int *end, int flag[2])
{
	while (line[*end] && line[*end] != '<' && line[*end] != '>')
	{
		if (line[*end] == '\'')
		{
			if (flag[0] == 1)
				flag[0] = 0;
			else
				flag[0] = 1;
		}
		else if (line[*end] == '\"')
		{
			if (flag[1] == 1)
				flag[1] = 0;
			else
				flag[1] = 1;
		}
		(*end)++;
	}
	if (line[*end] == '<' || line[*end] == '>')
		(*end)++;
}

int	fd_write(char *line, int i)
{
	int		count;
	int		restart;
	int		fd_1;
	char	*file;

	count = 0;
	restart = i;
	while(line[i] == ' ' && line[i])
		i++;
	while(ft_isalnum(line[i]) && line[i])
	{
		count++;
		i++;
	}
	file = ft_substr(line, i - count, count + 1);
	if (line[restart + 1] == '>')
		fd_1 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else 
		fd_1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	return (fd_1);
}

int	fd_read(char *line, int i)
{
	int		count;
	int		fd_0;
	char	*file;

	count = 0;
	while (line[i] == ' ' && i >= 0)
		i--;
	while (ft_isalnum(line[i]) && i >= 0)
	{
		count++;
		i--;
	}
	i++;
	file = ft_substr(line, i, count + 1);
	fd_0 = open(file, O_RDONLY, 0444);
	free(file);
	return (fd_0);
}

int	*fd(char *line)
{
	int	i;
	int	flag[2];
	int	fd[2];

	i = 0;
	flag[0] = dup(STDIN_FILENO);
	flag[1] = dup(STDOUT_FILENO);
	while (line[i] != '\0')
	{
		func_flag(line, &end, flag);
		if (line[i] == '<' && flag[0] == 0 && flag[1] == 0)
		{
			if (line[i + 1] == '<')
				//função para << ;
			else
				fd[0] = fd_read(line, i);
		}
		else if (line[i] == '>' && flag[0] == 0 && flag[1] == 0)
			fd[1] = fd_write(line, &i);
		i++;
	}
	return (fd);
}*/
