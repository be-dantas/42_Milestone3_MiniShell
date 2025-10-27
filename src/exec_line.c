#include "../utils/minishell.h"

void	exec_line(char *line, t_env *new_env)
{
	//if (string == "echo")
	//	;
	//if (string == "cd")
	//	;
	//if (string == "pwd")
	//	;
	if (ft_strncmp(line, "export", 6) == 0)
		export_arg(line, new_env);
	//if (string == "unset")
	//	;
	if (ft_strncmp(line, "env", ft_strlen(line)) == 0)
		print_env(new_env);
	//if (string == "exit")
	//	;
}
