/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:59:19 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/10 16:37:58 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect(t_commands *cmd, int mode)
{
	if(cmd->infile < 0 || cmd->outfile < 0)
	{
		if (cmd->acces_file == 2)
			print_exit_error("No such file or directory", cmd->error_file, -1, NULL);
		if (cmd->acces_file == 1)
			print_exit_error("Permission denied", cmd->error_file, -1, NULL);
        if (cmd->acces_file == 3)
            print_exit_error("ambiguous redirect", NULL, -1, NULL);
		if	(mode == 1)
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

void get_path(t_env_vars **p_vars, t_env_vars *vars, int index)
{
	vars = *p_vars;
	vars->paths = get_path_line((*p_vars)->env, "PATH=", 0);
	if (!vars->paths)
	{
        (*p_vars)->paths = NULL;
		//free(vars->true_paths);
        //vars->true_paths = NULL;
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
	while(temp != NULL)
	{
		waitpid(temp->process, &status, 0);
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
    if(vars->true_paths)
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