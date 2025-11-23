#include "../../utils/minishell.h"
#include "redirect.h"

static pid_t g_heredoc_child = -1;

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

static void parent_sigint(int sig)
{
    (void)sig;
    if (g_heredoc_child > 0)
        kill(g_heredoc_child, SIGKILL);  // mata na hora
    write(1, "\n", 1);
}

static void handle(int sig)
{
    (void)sig;

    /* limpa a linha que estava sendo digitada */
    //rl_replace_line("", 0);

    /* avisa readline que agora estamos em nova linha e pede re-display */
   // rl_on_new_line();
    //rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
    /* força readline() a retornar imediatamente */
    //rl_done = 1;
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
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handle);
	//if (signal(SIGINT, SIG_DFL))
	//	free_list(&begin_list);
	while (1)
	{
		h.str = readline("heredoc > ");
		// if (signal_flag == 1)
		// {
    	// 	printf("banana\n");
    	// 	exit(130) ;
		// }
		if (h.str == NULL)
		{
			printf("Warning: Expecting delimiter (required '%s')\n", h.temp1);
			break ;
		}
		if (ft_strcmp(h.str, h.temp1) == 0)
		 	break ;
		h.tmp1 = ft_strjoin(h.result, h.str);
		h.tmp2 = ft_strjoin(h.tmp1, "\n");
		free(h.result);
		h.result = ft_strdup(h.tmp2);
		free_all(h.tmp1, h.tmp2, h.str);
		//free(h.str);
		h.str = NULL;
	}
	free_list(&begin_list);
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

int red_heredoc(t_env *begin_list, char *line)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        return (-1);

    pid = fork();
    if (pid == -1)
        return (-1);

    if (pid == 0)
    {
        // filho
        signal(SIGINT, handle);     // filho trata SIGINT
        signal(SIGQUIT, SIG_IGN);
        pid_zero(begin_list, line, fd);
    }
    else
    {
        // pai
        g_heredoc_child = pid;

        signal(SIGINT, parent_sigint);  // pai mata o filho no CTRL+C

        close(fd[1]);

        waitpid(pid, NULL, 0);

        g_heredoc_child = -1;  // filho já morreu

        signal(SIGINT, SIG_DFL); // restaura comportamento padrão

        return fd[0];
    }
	return fd[0];
}

// #include "../../utils/minishell.h"
// #include "redirect.h"

// int signal_flag = 0;

// static t_here init_heredoc(char *line)
// {
//     t_here here;
//     here.to_free = ft_split(strstr(line, "<<"), ' ');
//     here.eof = NULL;
//     here.str = NULL;
//     here.result = ft_strdup("");
//     return (here);
// }

// static char *remove_quotes(char *string, int i, int j)
// {
//     int len;
//     int count1;
//     int count2;
//     char *str2;
    
//     len = ft_strlen(string);
//     count1 = ft_countchar(string, '\'');
//     count2 = ft_countchar(string, '\"');
//     if (count1 % 2 != 0 || count2 % 2 != 0)
//         return (NULL);
//     str2 = malloc(sizeof(char) * (len - (count1 + count2) + 1));
//     while (string[i])
//     {
//         if (string[i] != '\'' && string[i] != '\"')
//         {
//             str2[j] = string[i];
//             j++;
//         }
//         i++;
//     }
//     str2[j] = '\0';
//     return (str2);
// }

// static void expand_and_free(t_here *h, t_env *begin_list)
// {
//     int len;
//     int flag_quotes;
//     char *result_final;
    
//     len = ft_strlen(h->eof);
//     flag_quotes = 0;
//     if (len >= 2 && ((h->eof[0] == '\'' && h->eof[len - 1] == '\'')
//         || (h->eof[0] == '\"' && h->eof[len - 1] == '\"')))
//         flag_quotes = 1;
//     if (flag_quotes == 1)
//     {
//         result_final = expand_arg(begin_list, h->result, 0);
//         free(h->result);
//         h->result = ft_strdup(result_final);
//         free(result_final);
//     }
//     else
//         (void)result_final;
//     free(h->str);
//     free_array(h->to_free);
//     free(h->eof);
// }

// static void free_all(char *str1, char *str2, char *str3)
// {
//     free(str1);
//     free(str2);
//     free(str3);
// }

// static void handle(int sig)
// {
//     (void)sig;
//     signal_flag = 1;
    
//     // Limpa a linha atual
//     rl_replace_line("", 0);
//     rl_done = 1;  // Força readline a retornar
// }

// static char *heredoc(t_env *begin_list, char *line)
// {
//     t_here h;
    
//     h = init_heredoc(line);
//     if (ft_strlen(h.to_free[0]) > 2)
//         h.eof = ft_strdup(h.to_free[0] + 2);
//     else
//         h.eof = ft_strdup(h.to_free[1]);
//     h.temp1 = remove_quotes(h.eof, 0, 0);
    
//     signal(SIGQUIT, SIG_IGN);
//     signal(SIGINT, handle);
    
//     while (1)
//     {
//         h.str = readline("heredoc > ");
        
//         // Verifica se foi interrompido por Ctrl+C
//         if (signal_flag == 1)
//         {
//             if (h.str)
//                 free(h.str);
//             free(h.result);
//             h.result = NULL;
//             break;
//         }
        
//         // EOF (Ctrl+D)
//         if (h.str == NULL)
//         {
//             printf("Warning: Expecting delimiter (required '%s')\n", h.temp1);
//             break;
//         }
        
//         // Encontrou o delimitador
//         if (ft_strcmp(h.str, h.temp1) == 0)
//         {
//             free(h.str);
//             break;
//         }
        
//         h.tmp1 = ft_strjoin(h.result, h.str);
//         h.tmp2 = ft_strjoin(h.tmp1, "\n");
//         free(h.result);
//         h.result = ft_strdup(h.tmp2);
//         free_all(h.tmp1, h.tmp2, h.str);
//         h.str = NULL;
//     }
    
//     free_list(&begin_list);
//     free(h.temp1);
    
//     if (h.result)
//         expand_and_free(&h, begin_list);
    
//     return (h.result);
// }

// static void pid_zero(t_env *begin_list, char *line, int fd[2])
// {
//     char *result;
//     int tty;
    
//     tty = open("/dev/tty", O_RDWR);
//     dup2(tty, STDIN_FILENO);
//     dup2(tty, STDOUT_FILENO);
//     close(tty);
//     close(fd[0]);
    
//     result = heredoc(begin_list, line);
    
//     if (result && signal_flag == 0)
//     {
//         write(fd[1], result, ft_strlen(result));
//         free(result);
//         close(fd[1]);
//         free_list(&begin_list);
//         exit(EXIT_SUCCESS);
//     }
    
//     if (result)
//         free(result);
//     close(fd[1]);
//     free_list(&begin_list);
//     exit(130); // Exit code para SIGINT
// }

// int red_heredoc(t_env *begin_list, char *line)
// {
//     int fd[2];
//     pid_t pid;
//     int status;
    
//     if (pipe(fd) == -1)
//         return (-1);
    
//     pid = fork();
    
//     if (pid == -1)
//         return (-1);
    
//     if (pid == 0)
//         pid_zero(begin_list, line, fd);
    
//     // Processo pai
//     close(fd[1]);
//     waitpid(pid, &status, 0);
    
//     // Se filho foi interrompido por sinal
//     if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
//     {
//         close(fd[0]);
//         return (-1);
//     }
    
//     return (fd[0]);
// }