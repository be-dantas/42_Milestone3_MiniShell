#include "../../utils/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

// Usada em vários pontos — serve só pra identificar 
// se o comando deve ser tratado “internamente” (pelo próprio shell).

void	exec_external(char **tokens, t_env *env)
{
	char *path = find_in_path(tokens[0], env);

	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", tokens[0]);
		exit(127);
	}
	execve(path, tokens, env_to_array(env));
	perror("execve");
	exit(EXIT_FAILURE);
}

// Procura o binário no $PATH
// Se não achar → erro
// Se achar → chama execve
// Só é usada em filhos criados por fork()

static void	redirect_fd(char *line, int fd_in, int fd_out)
{
	int	*fd_temp;
	int	fd[2];

	fd_temp = parse_fd(line, fd_in, fd_out);
	fd[0] = fd_temp[0];
	fd[1] = fd_temp[1];
	free(fd_temp);

	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

// parse_fd() analisa a linha e abre arquivos (open) conforme os redirecionamentos
// dup2() substitui stdin/stdout
// Fechamos os descritores antigos para evitar vazamentos

static void	process_one_split(char *line, t_env *env)
{
	char	**tokens;
	char	*cmd;
	int		saved_in;
	int		saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);

	redirect_fd(line, STDIN_FILENO, STDOUT_FILENO);

	cmd = command(line, 0, 0, ft_strdup(""));
	tokens = tokens(cmd, env);

	if (is_builtin(tokens[0]))
	{
		// ✅ builtin: executa no processo pai (sem fork)
		exec_line(tokens, env);
	}
	else
	{
		// 🧠 comando externo: precisa de fork + execve
		pid_t pid = fork();
		if (pid == 0)
		{
			exec_external(tokens, env);
			exit(EXIT_FAILURE);
		}
		waitpid(pid, NULL, 0);
	}

	free(cmd);
	free_array(tokens);

	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

// Salva os fds atuais (stdin/stdout)
// Aplica redirecionamentos
// Se for builtin → roda direto no pai
// Se for comando externo → cria um fork e chama exec_external
// Depois restaura os fds (pra não “sujar” o shell)

static void	process_pipes(char **pipes, t_env *env)
{
	int	prev_fd = -1;
	int	fd[2];
	int	i = 0;
	pid_t	pid;

	while (pipes[i])
	{
		if (pipes[i + 1])
			pipe(fd);

		pid = fork();
		if (pid == 0)
		{
			// Configura entrada (se não for o primeiro comando)
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			// Configura saída (se não for o último comando)
			if (pipes[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}

			// Parse e exec
			char *cmd = command(pipes[i], 0, 0, ft_strdup(""));
			char **tokens_cmd = tokens(cmd, env);
			redirect_fd(pipes[i], STDIN_FILENO, STDOUT_FILENO);

			if (is_builtin(tokens_cmd[0]))
				exec_line(tokens_cmd, env);  // builtin executa aqui no filho
			else
				exec_external(tokens_cmd, env);

			free(cmd);
			free_array(tokens_cmd);
			exit(EXIT_SUCCESS);
		}

		if (prev_fd != -1)
			close(prev_fd);
		if (pipes[i + 1])
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}

	while (wait(NULL) > 0)
		;
}

// Cria um pipe() entre cada comando
// Para cada comando:
// Cria um fork()
// Redireciona entrada/saída conforme o pipe
// Se for builtin → executa direto dentro do filho
// Se for externo → executa com execve
// Fecha os fds no pai e espera todos os filhos
// Mantém o comportamento do bash (env | wc -l, cd | echo, etc.)

void	redirect_and_command(char *line, t_env *env)
{
	t_redirect	rd;

	if (!valid_input(line))
	{
		printf("Syntax error\n");
		return ;
	}
	rd = init_redirect_vars(line);

	if (rd.count_pipe == 1)
		process_one_split(line, env);
	else
		process_pipes(rd.s_pipe, env);

	// restaura fds originais
	dup2(rd.fd_in, STDIN_FILENO);
	dup2(rd.fd_out, STDOUT_FILENO);
	close(rd.fd_in);
	close(rd.fd_out);
	free_array(rd.s_pipe);
}

// Checa se há pipes
// Se não tiver → executa no pai (process_one_split)
// Se tiver → executa a pipeline (process_pipes)
// Garante que stdin e stdout são restaurados no final
