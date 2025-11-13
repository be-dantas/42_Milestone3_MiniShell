#include "../../utils/minishell.h"
#include "redirect.h"

//#include "../../../libft/libft.h"
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <signal.h>
//#include <string.h>
//#include <stdio.h>
//#include <stdio.h>

static void	heredoc(t_env *begin_list, char *line)
{
	//procurar a palavra que vai dar stop no heredoc
	//o primeiro passo será percorrer a lista de here enviada
	//dentro dos valores das listas eu procuro individualmente o caractere '<'
	//verifico agora se o próximo item é '<' novamente
	//caso seja, verifico se o próximo item é '\0' caso seja, sei que o próximo item é o stop
	//caso não seja, dou um split no ponto atual e pego o valor [1] dele
	//coloco o valor disso dentro de uma variável e dou free em todos os itens
	//após, verifico se o valor [1] está com aspas simples, caso esteja, não expande nada
	//caso contrário, expande tudo
	//CASO seja encontrado aspas no EOF, todas as variáveis não serão expandidas
	char	*eof;
	char	*to_free1;
	char	*to_free2;
	char	**to_free_s1;
	char	**to_free_s2;
	char	*str;
	char	*result;

	result = ft_strdup("");
	str = NULL;
	to_free_s1 = NULL;
	to_free_s2 = NULL;
	to_free1 = NULL;
	to_free2 = NULL;
	eof = strstr(line, "<<");
	to_free_s1 = ft_split(eof, ' ');
	to_free1 = to_free_s1[0];
	to_free_s2 = ft_split(to_free1, '<');
	to_free2 = to_free_s2[0];
	eof = ft_strdup(to_free2);
	//printf("%s", eof);
	free(to_free1);
	free(to_free2);
	while (1)
	{
		str = readline("heredoc > ");
		if (ft_strcmp(str, eof) == 0)
			break ;
		result = ft_strjoin(result, str);
		result = ft_strjoin(result, "\n");
	}
	if ((eof[0] == '\'' && eof[ft_strlen(eof)] == '\'')
			|| (eof[0] == '\"' && eof[ft_strlen(eof)] == '\"'))
		printf("%s", result);
	else
		eof = expanded(begin_list, eof);
}

int	red_heredoc(t_env *begin_list, char *line)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		// Filho: escreve no pipe
		// colocar aqui a tratativa para receber sinais e tratar eles no heredoc
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		heredoc(begin_list, line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Pai: lê do pipe
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return (fd[0]);
	}
}

/*
int main()
{
	char *str = heredoc("COMANDO_1 <<'HERE' PALAVRAS_APÓS");
	free(str);
	return (0);
}*/