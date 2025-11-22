#include "../../utils/minishell.h"
#include "redirect.h"

static t_here	init_heredoc(char *line)
{
	t_here	here;

	here.to_free = ft_split(strstr(line, "<<"), ' ');
	here.eof = NULL;
	here.str = NULL;
	here.result = ft_strdup("");
	return (here);
}

static char	*remove_quotes(char *string, int i, int j)
{
	int		len;
	int		count1;
	int		count2;
	char	*str2;

	len = ft_strlen(string);
	count1 = ft_countchar(string, '\'');
	count2 = ft_countchar(string, '\"');
	if (count1 % 2 != 0 || count2 % 2 != 0)
		return (NULL);
	str2 = malloc(sizeof(char) * (len - (count1 + count2) + 1));
	while (string[i])
	{
		if (string[i] != '\'' && string[i] != '\"')
		{
			str2[j] = string[i];
			j++;
		}
		i++;
	}
	str2[j] = '\0';
	return (str2);
}

static void	expand_and_free(t_here	*h, t_env *begin_list)
{
	int		len;
	int		flag_quotes;
	char	*result_final;

	len = ft_strlen(h->eof);
	flag_quotes = 0;
	if (len >= 2 && ((h->eof[0] == '\'' && h->eof[len - 1] == '\'')
			|| (h->eof[0] == '\"' && h->eof[len - 1] == '\"')))
		flag_quotes = 1;
	if (flag_quotes == 1)
	{
		result_final = expand_arg(begin_list, h->result, 0);
		free(h->result);
		h->result = ft_strdup(result_final);
		free(result_final);
	}
	else
		(void)result_final;
	free(h->str);
	free_array(h->to_free);
	free(h->eof);
}

static void	free_all(char *str1, char *str2, char *str3)
{
	free(str1);
	free(str2);
	free(str3);
}

static void	handle(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}

static char	*heredoc(t_env *begin_list, char *line)
{
	t_here	h;

	h = init_heredoc(line);
	if (ft_strlen(h.to_free[0]) > 2)
		h.eof = ft_strdup(h.to_free[0] + 2);
	else
		h.eof = ft_strdup(h.to_free[1]);
	h.temp1 = remove_quotes(h.eof, 0, 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle);
	while (1)
	{
		h.str = readline("heredoc > ");
		if (h.str == NULL)
			printf("Warning: Expecting delimiter (required '%s')\n", h.temp1);
		if (ft_strcmp(h.str, h.temp1) == 0)
		 	break ;
		h.tmp1 = ft_strjoin(h.result, h.str);
		h.tmp2 = ft_strjoin(h.tmp1, "\n");
		free(h.result);
		h.result = ft_strdup(h.tmp2);
		free_all(h.tmp1, h.tmp2, h.str);
		h.str = NULL;
	}
	free(h.temp1);
	expand_and_free(&h, begin_list);
	return (h.result);
}

static void	pid_zero(t_env *begin_list, char *line, int fd[2])
{
	char	*result;
	int		tty;

	tty = open("/dev/tty", O_RDWR);
	dup2(tty, STDIN_FILENO);
	dup2(tty, STDOUT_FILENO);
	close(tty);
	close(fd[0]);
	result = heredoc(begin_list, line);
	if (result)
	{
		write(fd[1], result, ft_strlen(result));
		free(result);
	}
	close(fd[1]);
	free_list(&begin_list);
	exit(EXIT_SUCCESS);
}

int	red_heredoc(t_env *begin_list, char *line)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return (-1);
	if (pid == 0)
		pid_zero(begin_list, line, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
