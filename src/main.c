#include "../utils/minishell.h"

static void	handle(int sig)
{
	if (sig == 2)
		printf("\nminishell ~ ");
}
//Oif str[i] == " - flag = 1                if str[i] == > ou >> e flag != 1      redirecione if str[i] == " && flag == 1    flag = 0
static char	*read_input(char *ppt, t_env *new_env)
{
	char		*line;

	line = readline(ppt);
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		free_list(&new_env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

static void	exec_line(char **line_tokens, t_env *new_env)
{
	if (ft_strncmp(line_tokens[0], "echo", 5) == 0)
		echo(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "cd", 3) == 0)
		;
	else if (ft_strncmp(line_tokens[0], "pwd", 4) == 0)
		;
	else if (ft_strncmp(line_tokens[0], "export", 7) == 0)
		export_arg(line_tokens, new_env);
	else if (ft_strncmp(line_tokens[0], "unset", 6) == 0)
		unset_env(&new_env, line_tokens);
	else if (ft_strncmp(line_tokens[0], "env", 4) == 0)
		print_env(new_env);
	else if (ft_strncmp(line_tokens[0], "exit", 5) == 0)
		read_input("exit", new_env);
	else
		printf("Command not found\n"); //VOCÊ VAI REMOVER NO FUTURO E SUBSTUIR PELA FUNÇÃO QUE FAZ O EXECVE
}

char *remove_word(const char *str, const char *word)
{
    char *result;
    char *pos;
    size_t len_word = ft_strlen(word);
    size_t len_before, len_after;
    const char *after;

    pos = strstr(str, word);
    if (!pos)
        return ft_strdup(str); // palavra não encontrada

    len_before = pos - str;
    after = pos + len_word;
    while (*after == ' ') // pula espaços depois da palavra
        after++;
    len_after = ft_strlen(after);

    // +2 para espaço e '\0'
    result = calloc(len_before + len_after + 2, 1);
    if (!result)
        return NULL;

    // copia o que vem antes
    ft_strlcat(result, str, len_before + 1);

    // se precisar, adiciona espaço entre as partes
    if (len_before > 0 && *after != '\0' && result[len_before - 1] != ' ')
        ft_strlcat(result, " ", len_before + len_after + 2);

    // adiciona o que vem depois da palavra
    ft_strlcat(result, after, len_before + len_after + 2);

    return result;
}

char	*line_check(char *line)
{
	int	i;
	int flag;
	char **split1;
	char *palavra1;
	char *palavra2;
	char *fd_name_temp;
	char *fd_name;
	//char *palavra3;
	int fd;
	char *result;
	char	*final;

	final = NULL;
	result = NULL;
	fd = 0;
	//palavra1 = NULL;
	//palavra2 = NULL;
	//palavra3 = NULL;
	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' && flag == 0)
		{
			flag = 1;
			i++;
		}
		if (line[i] == '\"' && flag == 1)
		{
			flag = 0;
			i++;
		}
		if ((line[i] == '>' && line[i + 1] != '>') && flag == 0)
		{
			split1 = ft_split(line, '>');
			palavra1 = split1[0];
			fd_name_temp = split1[1]; //palavra1 ""arquivo.txt palavra2""
			fd_name = ft_split(fd_name_temp, ' ')[0];
			palavra2 = remove_word(fd_name_temp, fd_name);
			result = ft_strjoin(palavra1, palavra2);
			final = ft_strjoin(final, result);
			fd = open(fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			free(fd_name_temp);
			free(fd_name);
			i++;
			//funcao que cria o arquivo e SOBRESCREVE
			//trocar o valor do fd para o do arquivo criado
		}
		if ((line[i] == '>' && line[i + 1] == '>') && flag == 0)
		{
			fd_name_temp = ft_split(line, '>')[1];
			fd_name = ft_split(fd_name_temp, ' ')[0];
			fd = open(fd_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			free(fd_name_temp);
			free(fd_name);
			i++;
			//funcao que cria o arquivo e CONCATENA
			//troca o valor do fd para o arquivo criado
		}
		printf("%s\n", final);
		//printf("to aqui?\n");
		i++;
	}
	//line = jajaja ">jajaja" ">ajaja" ">ajaj" asjajaj
	return (final);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**line_tokens;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = clone_env(envp);
	line_tokens = NULL;
	if (signal(SIGQUIT, SIG_IGN) || signal(SIGINT, handle))
		add_history(NULL);
	while (1)
	{
		line = read_input("minishell ~ ", new_env);
		if (line[0] != '\0')
		{
			line = line_check(line);
			line_tokens = tokens(new_env, line);
		}
		if (line_tokens)
			exec_line(line_tokens, new_env);
		if (*line)
			free(line);
		if (line_tokens)
			free_array(line_tokens);
	}
	rl_clear_history();
	return (0);
}
