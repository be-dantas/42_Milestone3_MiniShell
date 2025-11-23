#include "../../../utils/minishell.h"
#include "../redirect.h"

static void	free_all(char *str1, char *str2, char *str3)
{
	free(str1);
	free(str2);
	free(str3);
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

static t_here	init_heredoc(char *line)
{
	t_here	here;

	here.to_free = ft_split(strstr(line, "<<"), ' ');
	here.eof = NULL;
	here.str = NULL;
	here.result = ft_strdup("");
	return (here);
}

char	*heredoc(t_env *begin_list, char *line)
{
	t_here	h;

	h = init_heredoc(line);
	if (ft_strlen(h.to_free[0]) > 2)
		h.eof = ft_strdup(h.to_free[0] + 2);
	else
		h.eof = ft_strdup(h.to_free[1]);
	h.temp1 = remove_quotes(h.eof, 0, 0);
	while (1)
	{
		h.str = readline("heredoc > ");
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
