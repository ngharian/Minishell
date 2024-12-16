/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:59:19 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/16 13:13:47 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

int	ft_strrncmp(char *verif, char *base, int len)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = ft_strlen(verif) - 1;
	i = ft_strlen(base) - 1;
	if (!verif)
		return (-1);
	while (k <= len)
	{
		if (j - k == -1 && i - k == -1)
			return (0);
		if (verif[j] != base[i])
			return (verif[j] - base[i]);
		++k;
		j -= k;
		i -= k;
	}
	return (0);
}

int	ft_redirect(t_commands *cmd, int mode)
{
	if (cmd->infile < 0 || cmd->outfile < 0)
	{
		if (cmd->acces_file == 2)
			print_exit_error("No such file or directory", \
			cmd->error_file, -1, NULL);
		if (cmd->acces_file == 1)
			print_exit_error("Permission denied", cmd->error_file, -1, NULL);
		if (cmd->acces_file == 3)
			print_exit_error("ambiguous redirect", NULL, -1, NULL);
		if (mode == 1)
			exit(1);
		return (1);
	}
	if (cmd->infile > 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile > 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	return (0);
}

void	get_path(t_env_vars **p_vars, t_env_vars *vars, int index)
{
	vars = *p_vars;
	vars->paths = get_path_line((*p_vars)->env, "PATH=", 0);
	if (!vars->paths)
	{
		(*p_vars)->paths = NULL;
		return ;
	}
	vars->split_path = ft_split(vars->paths, ':');
	if (!vars->split_path)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	while (vars->split_path[index])
		index++;
	vars->true_paths = malloc((index + 1) * sizeof(char *));
	if (!vars->true_paths)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	vars->true_paths[index] = NULL;
	index = 0;
	while (vars->split_path[index])
	{
		vars->true_paths[index] = ft_strjoin(vars->split_path[index], "/");
		if (!vars->true_paths[index])
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		index++;
	}
	free_split(vars->split_path);
}

void	wait_process(t_commands **cmd, t_env_vars **vars)
{
	t_commands	*temp;
	int			status;

	status = 0;
	temp = (*cmd);
	while (temp != NULL)
	{
		waitpid(temp->process, &status, 0);
		if (ft_strrncmp((*cmd)->cmd[0], "minishell", 9) == 0)
			ft_set_sig(3);
		(*vars)->exit_code = status >> 8;
		if (g_signal == SIGINT)
			(*vars)->exit_code = 130;
		if (g_signal == SIGQUIT)
			(*vars)->exit_code = 131;
		g_signal = 0;
		temp = temp->next;
	}
}

void	check_access(t_env_vars *vars, t_commands *temp)
{
	char		*path;
	int			index;

	index = 0;
	if (vars->true_paths)
	{
		while (vars->true_paths[index])
		{
			path = ft_strjoin(vars->true_paths[index], temp->cmd[0]);
			if (!path)
				print_exit_error("Malloc error", NULL, 1, NULL);
			if (access(path, X_OK) == 0)
			{
				temp->right_command = index;
				free(path);
				return ;
			}
			free(path);
			++index;
		}
	}
	print_exit_error("command not found", temp->cmd[0], 127, NULL);
}
