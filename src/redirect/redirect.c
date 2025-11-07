#include "../../utils/minishell.h"

// static void	exec_line(char **line_tokens, t_env *new_env)
// {
// 	if (ft_strncmp(line_tokens[0], "echo", 5) == 0)
// 		echo(line_tokens, new_env);
// 	else if (ft_strncmp(line_tokens[0], "cd", 3) == 0)
// 		;
// 	else if (ft_strncmp(line_tokens[0], "pwd", 4) == 0)
// 		;
// 	else if (ft_strncmp(line_tokens[0], "export", 7) == 0)
// 		export_arg(line_tokens, new_env);
// 	else if (ft_strncmp(line_tokens[0], "unset", 6) == 0)
// 		unset_env(&new_env, line_tokens);
// 	else if (ft_strncmp(line_tokens[0], "env", 4) == 0)
// 		print_env(new_env);
// 	else if (ft_strncmp(line_tokens[0], "exit", 5) == 0)
// 		read_input("exit", new_env);
// 	else
// 		printf("Command not found\n"); //VOCÊ VAI REMOVER NO FUTURO E SUBSTUIR PELA FUNÇÃO QUE FAZ O EXECVE
// }

int	*func_flag(char *line, int *end)
{
	int	*flag[2];

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
	return (flag);
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
		flag = func_flag(line, &i);
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
	command = ft_strdup("");
	while (line[end])
	{
		while (line[end] && (flag[0] == 1 || flag[1] == 1))
			flag = func_flag(line, &end);
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
				;
			else
				palavra = ft_substr(line, start, end - start);
				command = ft_strjoin(command, palavra);
		}
		if (palavra)
			free(palavra);
		end++;
		start = end;
	}
	return (command);
}
