#include "../../utils/minishell.h"

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

int	*fd(char *line) //retornar fd da linha, leitura e escrita
{
	int		i;
	int		flag[2];
	int		fd[2];

	i = 0;
	while (line[i] != '\0')
	{
		flag = flag(line, &i, flag);
		if (line[i] == '<' && flag[0] == 0 && flag[1] == 0)
		{
			if (line[i + 1] == '<')
				//função para << ;
			else
				fd[0] = open(NOME_ARQUIVO, O_RDONLY, 0444);;
		}
		else if (line[i] == '>' && flag[0] == 0 && flag[1] == 0)
		{
			if (line[i + 1] == '>')
				fd[1] = open(NOME_ARQUIVO, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd[1] = open(NOME_ARQUIVO, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		i++;


			//split1 = ft_split(line, '>');
			//palavra1 = split1[0];
			//fd_name_temp = split1[1]; //palavra1 ""arquivo.txt palavra2""
			//fd_name = ft_split(fd_name_temp, ' ')[0];
			//palavra2 = remove_word(fd_name_temp, fd_name);
			//result = ft_strjoin(palavra1, palavra2);
			//final = ft_strjoin(final, result);
			//fd = open(fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			//dup2(fd, STDOUT_FILENO);
			//close(fd);
			//free(fd_name_temp);
			//free(fd_name);

		//fd = open(fd_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (fd);
}


int	*flag(char *line, int end, int *flag)
{
	while (line[end] && line[end] != '<' && line[end] != '>')
	{
		if (line[end] == '\'')
		{
			if (flag[0] == 1)
				flag[0] = 0;
			else
				flag[0] = 1;
		}
		else if (line[i] == '\"')
		{
			if (flag[1] == 1)
				flag[1] = 0;
			else
				flag[1] = 1;
		}
		(*end)++;
	}
	if (line[end] == '<' || line[end] == '>')
		(*end)++;
	return (flag);
}

//echo teste > file.txt >> file1.txt teste2
char	*command(char *line)
{
	int		start;
	int		end;
	int		flag[2];
	char	*palavra;
	char	*command;

	start = 0;
	end = 0;
	Command = ft_strdup("");
	while (line[end])
	{
		while (line[end] && (flag[0] == 1 || flag[1] == 1))
			flag = flag(line, &end, flag);
		if (!command)
		{
			palavra = ft_substr(line, start, (end - start));
			command = ft_strdup(palavra);
		}
		else
		{
			while (!ft_isalnum(line[end])) //?
				end++;
			while (ft_isalnum(line[end])) //?
				end++;
			while (line[end] == ' ')
				end++;
			if (line[end] == '<' && line[end] == '>')
				break ;
			palavra = ft_substr(line, start, end - start);
			command = ft_strjoin(command, palavra);
		}
		if (palavra)
			free(palavra);
		end++;
		start = end;
	}
	//flag[0] == 0;
	//flag[0] == 0;
	return (Command);
}
