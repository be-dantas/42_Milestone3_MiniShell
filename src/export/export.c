#include "../utils/minishell.h"

void	export_arg(char *string, t_env *ptr)
{
	int	i;

	i = 6;
	if (string[i] == '\0')
		//printa export
	else if (string[i] == ' ')
	{
		while (string[i] == ' ')
			i++;
		if (string[i] == '\0')
			//printa export
		else
			put_export(string, ptr);
	}
}

int	have_1_equal(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if(string[i] == '=')
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	valid_arg(char **split_str)
{
	int	i;
	
	i = 0;
	while (split_str[i])
	{
		if (have_1_equal(split_str[i]) && ft_isalpha(split_str[i][0]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	put_export(char *string, t_env *ptr)
{
	int		i;
	char	**split_str;

	i = 1;
	split_str = ft_split(string, ' ');
	if (valid_arg(split_str))
	{
		while (split_str[i])
		{
			put_env(&ptr, split_str[i]);
			i++;
		}
	}
	else
		putstr_exit("ARG invalid", split_str, 1); //nao limpa todo env criado e etc...
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
//ARG=@@2    / FICA ARG2="@@2"
//ARG0=@'@2  / não aceita
//ARG=""2"   / não aceita
//ARG=''2'   / não aceita
