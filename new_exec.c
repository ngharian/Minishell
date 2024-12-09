/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:48:13 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/09 12:49:12 by ngharian         ###   ########.fr       */
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

/*int    throw_single_child(t_commands **cmd, t_env_vars **env, int ret)
{
		int	in;
		int	out;
		
		in = dup(0);
		out = dup(1);
		ret = ft_redirect();
		if (ret = -1)
			return(1);
		ret = ft_builtins();
		if (ret == 0)
		{
			
		}
		ft_restor_in_out(in, out, (*cmd)->infile, (*cmd)->outfile);
}*/

void	throw_multiple_child(t_commands **cmd, t_env_vars **env, t_commands *temp)
{
	temp = (*cmd);
	ft_set_sig(3);
	while (temp != NULL)
	{
		temp->process = fork();
		if (temp->process < 0)
		{
			perror("minishell: %s: FORK_ERROR\n", (*cmd)->cmd[0]);
			return (1);
		}
		if (temp->process == 0)
		{
			ft_set_sig(4);
			if (child(temp, *env))
			{
				kill(temp->process, SIGQUIT);
				return (1);
			}
		}
		//waitpid(temp->process, &status, 0);
		//(*vars)->exit_code = status >> 8;
		//if (g_signal == SIGINT)
			//(*vars)->exit_code = 130;
		//if (g_signal == SIGQUIT)
		//	(*vars)->exit_code = 131;
		//g_signal = 0;
		//if (temp->outfile > 0)
		//	close(temp->outfile);
		//close(temp->exchange[1]);
		temp = temp->next;
	}
	ft_set_sig(1);
	return (0);
}

int ft_execution(t_commands **cmd, t_env_vars **vars)
{
	get_path(vars, NULL, 0);
	if ((*cmd)->next != NULL || (*cmd)->previous != NULL)
	{
		throw_multiple_child(cmd, vars, NULL);
		wait_process();
	}
	//else
		//(*vars)->exit_code = throw_single_child(cmd, vars, ret);
	//wait_process();
}