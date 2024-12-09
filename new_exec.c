/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:48:13 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/09 14:40:21 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_path(t_env_vars **p_vars, t_env_vars *vars, int index)
{
	vars = *p_vars;
	vars->paths = get_path_line((*p_vars)->env, "PATH=", 0);
	if (!vars->paths)
		return (1);
	vars->split_path = ft_split(vars->paths, ':');
	if (!vars->split_path)
		return (1);
	while (vars->split_path[index])
		index++;
	vars->true_paths = malloc((index + 1) * sizeof(char *));
	if (!vars->true_paths)
		return (1);
	vars->true_paths[index] = NULL;
	index = 0;
	while (vars->split_path[index])
	{
		vars->true_paths[index] = ft_strjoin(vars->split_path[index], "/");
		if (!vars->true_paths[index])
		{
			free_split(vars->true_paths);
			return (1);
		}
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

void	multiple_commands(t_commands **cmd, t_env_vars **env, t_commands *temp)
{
	temp = (*cmd);
	//ft_set_sig(3);
	while (temp != NULL)
	{
		temp->process = fork();
		if (temp->process < 0)
		{
			print_exit_error((*cmd)->cmd[0], ": FORK_ERROR\n", -1);
			if((*cmd)->outfile > 0)
				close((*cmd)->outfile);
			(*cmd)->outfile = 0;
			temp = temp->next;
			continue;
		}
		if (temp->process == 0)
		{
			ft_set_sig(4);
			child(temp, *env);
		}
		//waitpid(temp->process, &status, 0);
		//(*vars)->exit_code = status >> 8;
		//if (g_signal == SIGINT)
			//(*vars)->exit_code = 130;
		//if (g_signal == SIGQUIT)
		//	(*vars)->exit_code = 131;
		//g_signal = 0;
		temp = temp->next;
	}
	wait_process(cmd, env);
	//ft_set_sig(1);
	return (0);
}

int	ft_redirect(t_commands *cmd, int mode)
{
	if(cmd->infile < 0 || cmd->outfile < 0)
	{
		if (cmd->acces_file == 1)
			print_exit_error(cmd->error_file, ": No such file or directory\n", -1);
		if (cmd->acces_file == 2)
			print_exit_error(cmd->error_file, ": Permission denied\n", -1);
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

int    single_command(t_commands **cmd, t_env_vars **env, int ret)
{
		ret = ft_redirect(*cmd, 0);
		if (ret = 1)
		{
			(*env)->exit_code = 1;
			return(1);
		}
		ret = ft_builtins(cmd, env);
		if (ret == 0)
			multiple_commands(cmd, env, NULL);
		else
			(*env)->exit_code = ret;
}

int ft_execution(t_commands **cmd, t_env_vars **vars)
{
	int	save_stdin;
	int	save_stdout;
	
	save_stdin = dup(0);
	save_stdout = dup(1);
	get_path(vars, NULL, 0);
	ft_set_sig(3);
	if ((*cmd)->next != NULL || (*cmd)->previous != NULL)
		multiple_commands(cmd, vars, NULL);
	else
		single_command(cmd, vars, 0);
	dup2(save_stdin ,STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	ft_set_sig(1);
}