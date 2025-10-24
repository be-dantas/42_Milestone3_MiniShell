#include "../utils/minishell.h"

void	exec_line(char *string, t_env *ptr)
{
	//if (string == "echo")
	//	;
	//if (string == "cd")
	//	;
	//if (string == "pwd")
	//	;
	if (ft_strncmp(string, "export", 6) == 0)
		export_arg(string, ptr);
	//if (string == "unset")
	//	;
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		print_env(ptr);
	//if (string == "exit")
	//	;
}
