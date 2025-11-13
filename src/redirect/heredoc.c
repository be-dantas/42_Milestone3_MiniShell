#include "../../utils/minishell.h"
#include "redirect.h"

void	heredoc(t_env *begin_list, char *line)
{
	(void)begin_list;
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
	if (ft_strlen(to_free_s1[0]) > 2)
	{
		to_free1 = to_free_s1[0];
		to_free_s2 = ft_split(to_free1, '<');
		to_free2 = to_free_s2[0];
		eof = ft_strdup(to_free2);
	}
	else
	{
		eof = ft_strdup(to_free_s1[1]);
	}
	while (1)
	{
		str = readline("heredoc > ");
		if (ft_strcmp(str, eof) == 0)
			break ;
		result = ft_strjoin(result, str);
		result = ft_strjoin(result, "\n");
	}
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'')
			|| (eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
		printf("%s", result);
	else
	{
		char *result2;
		result2 = expand_arg(begin_list, result, 0);
		if (result2 == NULL)
			printf("%s", result);
		else
			printf("%s", result2);
	}
}
