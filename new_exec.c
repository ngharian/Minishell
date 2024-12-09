/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:48:13 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/09 13:43:29 by ngharian         ###   ########.fr       */
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
	ft_set_sig(3);
	while (temp != NULL)
	{
		temp->process = fork();
		if (temp->process < 0)
		{
			print_exit_error((*cmd)->cmd[0], ": FORK_ERROR\n", -1);
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
	ft_set_sig(1);
	return (0);
}

int ft_execution(t_commands **cmd, t_env_vars **vars)
{
	get_path(vars, NULL, 0);
	if ((*cmd)->next != NULL || (*cmd)->previous != NULL)
		multiple_child(cmd, vars, NULL);
	//else
		//(*vars)->exit_code = throw_single_child(cmd, vars, ret);
	//wait_process();
}