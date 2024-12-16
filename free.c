/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:54:58 by gdero             #+#    #+#             */
/*   Updated: 2024/12/16 15:10:29 by ngharian         ###   ########.fr       */
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

int	free_struct(t_commands **cmd, int error, t_env_vars **env)
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
	if ((*env)->true_paths)
		free_split((*env)->true_paths);
	(*env)->true_paths = NULL;
	(*env)->split_path = NULL;
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
	if (mode == -1 || mode == -4)
		clear_history();
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
		(*env)->exit_code = 2;
	if (mode == -4)
		exit(EXIT_FAILURE);
	return (1);
}

void	print_exit_error(char *message, char *name, \
int exit_code, char *builtin)
{
	write(2, "minishell: ", 12);
	if (builtin)
		write(2, builtin, ft_strlen(builtin));
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	if (exit_code >= 0)
		exit(exit_code);
}
