#include "../utils/minishell.h"



int	valid_arg_value(char *str)
{
	int	i;

	i = 0;
	if (str[i] == "\"" || str[i] == "\'")
	{
		if (str[i] != str[ft_strlen(str) - 1])
			return (0);
	}

	return (1);
}



// int	aspas(char *str, int len)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	if(str[i] != "\"" || str[i] != "\'")
// 	{
// 		while(str[i])
// 		{
// 			if(str[i] == "\"" || str[i] == "\'")
// 				count++;
// 			i++;
// 		}
// 		if(count % 2 != 0)
// 			return (0);
// 	}
// 	return (1);
// }









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