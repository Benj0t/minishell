#include "token.h"
#include "stdio.h"
#include "minishell.h"

int main(int argc, char const *argv[])
{
	char	*str;
	t_token	tok;
	t_command	*command;

	str = ft_strdup("cat <lol.c>> out;echo $yop \"$yop\" '$yop'");
	while (str)
	{
		tok = next_token(&str);
		printf("-%s- %d\n", tok.name, (int)tok.type);
	}
	str = ft_strdup(">");
	command = NULL;
	parser_token(&str, command);
	return 0;
}

//cat <lol.c>> out;echo $yop \"$yop\" '$yop'
//separator =
