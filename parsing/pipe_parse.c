#include "../minishell.h"

//verifies qu'un pipe ne soit pas au debut de la commande, et
//qu'il a bien des arguments autres que seulement des symboles
static int	error_pipe(char *str, int i)
{
	if (i == 0)
		return (1);
	--i;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		--i;
	if (i < 0 || str[i] == '<' || str[i] == '>' || str[i] == '|')
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		return (1);
	}
	return (0);
}

//verifies si un pipe finit la ligne
static int	finish_line(char *line, int i)
{
	++i;
	while (line[i] == 32 || (line[i] > 8 && line[i] < 14))
		++i;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	pipe_case(char **line, int i)
{
	if (error_pipe(*line, i))
		return (-3);
	if (finish_line(*line, i))
		return (finish_pipe(line, i));
	return (i + 1);
}
