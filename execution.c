/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:48:13 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/17 17:19:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_env_vars *vars, t_commands *temp)
{
	char		*command;

	command = NULL;
	if (temp->cmd[0][0] == '\0')
		exit(0);
	if (access(temp->cmd[0], X_OK) == 0)
		command = temp->cmd[0];
	else if (access(temp->cmd[0], F_OK) == 0 \
			&& (access(temp->cmd[0], R_OK) != 0))
		print_exit_error("Permission denied", temp->cmd[0], 126, NULL);
	else
	{
		check_access(vars, temp);
		command = ft_strjoin(vars->true_paths[temp->right_command], \
		temp->cmd[0]);
	}
	if (!command)
		print_exit_error("Malloc error", temp->cmd[0], 1, NULL);
	if (execve(command, temp->cmd, vars->env) == -1)
		print_exit_error("Execve error", temp->cmd[0], 1, NULL);
	free(command);
}

static void	child(t_commands *cmd, t_env_vars *env)
{
	int	ret;

	ft_redirect(cmd, 1);
	ret = ft_builtins(cmd, env);
	if (ret != -1)
		exit(ret);
	execute_cmd(env, cmd);
}

static void	multiple_commands(t_commands **cmd, \
			t_env_vars **env, t_commands *temp)
{
	temp = (*cmd);
	while (temp != NULL)
	{
		if (ft_strrncmp((*cmd)->cmd[0], "minishell", 9) == 0)
			ft_set_sig(5);
		temp->process = fork();
		if (temp->process < 0)
		{
			print_exit_error((*cmd)->cmd[0], "FORK_ERROR\n", -1, NULL);
			if ((*cmd)->outfile > 0)
				close((*cmd)->outfile);
			(*cmd)->outfile = 0;
			temp = temp->next;
			continue ;
		}
		if (temp->process == 0)
		{
			ft_set_sig(4);
			child(temp, *env);
		}
		if (temp->outfile > 2)
			close(temp->outfile);
		temp = temp->next;
	}
	wait_process(cmd, env);
}

static void	single_command(t_commands **cmd, t_env_vars **env, int ret)
{
	ret = ft_redirect(*cmd, 0);
	if (ret == 1)
	{
		(*env)->exit_code = 1;
		return ;
	}
	ret = ft_builtins(*cmd, *env);
	if (ret == -1)
		multiple_commands(cmd, env, NULL);
	else
		(*env)->exit_code = ret;
}

void	ft_execution(t_commands **cmd, t_env_vars **vars)
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
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	ft_set_sig(1);
}
