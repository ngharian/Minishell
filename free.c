#include "minishell.h"

void	free_split(char **split)
{
	int	index;

	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
	return ;
}

int	free_struct(t_commands **cmd, int error)
{
	t_commands	*temp;

	if (*cmd == NULL)
		return (error);
	while (*cmd != NULL)
	{
		temp = *cmd;
		free_split((*cmd)->cmd);
		*cmd = (*cmd)->next;
		free(temp);
	}
	*cmd = NULL;
	return (error);
}

int exit_parsing(int mode) // !!! rajouter exit codes !!!
{
	if (mode == -1)
	{
		write(1, "Exit...\n", 8);
		exit(EXIT_SUCCESS);
	}
	if (mode == -4)
		exit(EXIT_FAILURE);
	return (1);
}

void	print_exit_error(char *message, int exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}