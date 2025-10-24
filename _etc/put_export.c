#include "../utils/minishell.h"

int	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	valid_arg_name(char *str)
{
	int	i;
	
	i = 0;
	if (have_equal(str[i]))
	{
		if(!ft_isalpha(str[0]))
			return(0);
		while(str[i] != '=')
		{
			if(!ft_isalnum(str[i]))
				return (0);
			i++;
		}
		if(str[i] == '=' && str[i + 1] == '=' && str[i + 2])
			return (0);
	}
	return (1);
}

int	aspas(char *str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if(str[i] != "\"" || str[i] != "\'")
	{
		while(str[i])
		{
			if(str[i] == "\"" || str[i] == "\'")
				count++;
			i++;
		}
		if(count % 2 != 0)
			return (0);
	}
	return (1);
}

int	valid_arg_value(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	len--;
	if(str[i] == "\"" && str[len] != "\"" || str[i] == "\'" && str[len] != "\'"
		|| str[i] != "\"" && str[len] == "\"" || str[i] != "\'" && str[len] == "\'")
		return (0);
	if(!aspas(str, len))
		return (0);
	return (1);
}

int valid_arg(char **split_line)
{
	int i;

	i = 1;
	while (split_line[i])
	{
		if(valid_arg_name(split_line[i]) && valid_arg_value(split_line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	put_export(char *line, t_env *exp)
{
	int		i;
	char	**split_line;

	i = 1;
	split_line = ft_split(line, ' ');
	if(valid_arg(split_line))
	{




	}
	else
		putstr_exit("ARG invalid", split_line, 1); //ainda nao limpa todo env criado, etc...
}






//DIFERENÇAS ENTRE ENV E EXPORT:


//ENV:
//ACEITA ARGS COM "" MAS NAO ARMAZENA ", EXEMPLOS:
//ARG="2"  / FICA ARG=2;
//ARG='2'  / FICA ARG=2;
//ARG='"2' / FICA ARG="2;
//ARG="'2" / FICA ARG='2;
//ARG=""2" / não aceita
//ARG=''2' / não aceita

//EXPORT:
//MESMO CONTEÚDO DO ENV PORÉM ESCRITO "declare -x " NA FRENTE E EM ORDEM ALFABÉTICA;
//ACEITA ARGS COM "" E ARMAZENA ", EXEMPLOs:
//ARG="2"    / FICA ARG="2";
//ARG='2'    / FICA ARG="2";
//ARG=2      / FICA ARG="2";
//ARG='"2'   / FICA ARG2="\"2"
//ARG="$2"   / FICA ARG2="\$2"
//ARG=$2     / FICA ARG2=""
//ARG=$$$2   / FICA ARG2="949485"
//ARG="$$$2" / FICA ARG2="949485"
//ARG="@@2"  / FICA ARG2="@@2"
//ARG=@@2    / FICA ARG2="@@2"
//ARG="@@2"  / FICA ARG2="@@2"
//ARG0=@'@2  / não aceita
//ARG=""2"   / não aceita
//ARG=''2'   / não aceita
