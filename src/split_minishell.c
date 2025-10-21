
#include "../utils/minishell.h"

char	*malloc_array(char *line, int i, int count)
{
	char	**array;
	int		x;

	x = 0;
	array = malloc((count + 1) * sizeof(char));
	if (!array)
		return (0);
	array[count] = '\0';
	while (count > 0)
	{
		array[x] = line[i];
		x++;
		i++;
		count--;
	}
	return (array);
}

char	*new_array_aspas(char *line, int i, char x)
{
	int		count;
	char	*new_array;

	count = 0;
	while (line[i] != x && line[i] != '\0')
	{
		count++;
		i++;
	}
	if (line[i - 1] != x && line[i] == '\0')
		return (0);
	i = i - count;
	new_array = malloc_array(line, i, count);
	if (!new_array)
		return (0);
	return (new_array);
}

char	*new_array_red(char *line, int i)
{
	int		count;
	char	*new_array;

	count = 1;
	if (line[i] == '<' && line[i + 1] == '<')
	{
		count = 2;
		new_array = malloc_array(line, i, count);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		count = 2;
		new_array = malloc_array(line, i, count);
	}
	else
		new_array = malloc_array(line, i, count);
	if (!new_array)
		return (0);
	return (new_array);
}

char	**split_minishell(char *line)
{
	int		i;
	char	*array;
	char	**final_array;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			array = new_array_aspas(line, i, '"');
		else if (line[i] == '\'')
			array = new_array_aspas(line, i, '\'');
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			array = new_array_red(line, i);
		else
			//nova funçao


		i++;
	}
}