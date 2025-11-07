void	func_flag(char *line, int *end, int flag[2])
{
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
}

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
			func_flag(line, &end, flag);
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
