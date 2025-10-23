#include "../utils/minishell.h"

void	exec_line(char *string, t_env *ptr)
{
	//if (string == "echo")
	//	;
	//if (string == "cd")
	//	;
	//if (string == "pwd")
	//	;
	//if (string == "export")
	//	;
	//if (string == "unset")
	//	;
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		print_env(ptr);
	//if (string == "exit")
	//	;
}
