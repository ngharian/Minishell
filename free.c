/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:54:58 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 14:33:40 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	free_struct(t_commands **cmd, int error)// completer a la fin
{
	t_commands	*temp;

	if (*cmd == NULL)
		return (error);
	while (*cmd != NULL)
	{
		temp = *cmd;
		if (temp->infile > 2)
			close(temp->infile);
		if (temp->outfile > 2)
			close(temp->outfile);
		free_split((*cmd)->cmd);
		if ((*cmd)->error_file != NULL)
			free((*cmd)->error_file);
		*cmd = (*cmd)->next;
		free(temp);
	}
	*cmd = NULL;
	return (error);
}

int	free_env(t_env_vars *vars, int error)
{
	free_split(vars->env);
	free_split(vars->exp);
	free(vars);
	vars = NULL;
	return (error);
}

int	exit_parsing(int mode, t_env_vars **env)
{
	if (mode == -1)
	{
		write(1, "Exit...\n", 8);
		if ((*env)->exit_code == 258)
			exit(2);
		if ((*env)->exit_code != 0)
			exit((*env)->exit_code);
		exit(0);
	}
	if (mode == -2 || mode == -3)
		(*env)->exit_code = 258;
	if (mode == -4)
		exit(EXIT_FAILURE);
	return (1);
}

void	print_exit_error(char *message, char *name, int exit_code)
{
	write(2, "Minishell :", 11);
	if (name)
		write(2, name, ft_strlen(name));
	if (message)
		write(2, message, ft_strlen(message));
	if (exit_code >= 0)
		exit(exit_code);
}

/*-1 = ctrl+d (->quitter)
-2 = quottes unclosed (->continuer) 258
-3 = parsing erreur (->continue) 258
-4 = malloc error (->quitter)
-5 = empty_line -> (continue) sans exit code
//-6 = ctrl+c (-> continuer + exit code = 1)*/