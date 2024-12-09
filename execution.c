#include "minishell.h"
//extern int g_signal;

static void	check_access(t_env_vars *vars, t_commands *temp)
{
	char		*path;
	int			index;

	index = -1;
	if (access(temp->cmd[0], X_OK) == 0)
	{
		temp->absolute_path = true;
		temp->right_command = 0;
		return ;
	}
	while (vars->true_paths[++index])
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
	}
	print_exit_error("command not found", temp->cmd[0], -1, NULL);
}

static void	execute_cmd(t_env_vars *vars, t_commands *temp)
{
	char		*command;

	temp->absolute_path = false;
	temp->right_command = -1;
	check_access(vars, temp);
	if (temp->right_command < 0)
		return ;
	if (temp->absolute_path == true)
		command = temp->cmd[0];
	else
		command = ft_strjoin(vars->true_paths[temp->right_command], \
		temp->cmd[0]);
	if (!command)
		print_exit_error("Malloc error", NULL, 1, NULL);
	execve(command, temp->cmd, vars->env);
	free(command);
}

static void	child(t_commands *cmd, t_env_vars *vars)
{
	if(cmd->infile < 0 || cmd->outfile < 0)
		print_exit_error("bad file redirection", NULL, 1, NULL);
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
	execute_cmd(vars, cmd);
	//if (cmd->cmd[0] == '/')  ---------> pour check path absolu /!\  ////bin/ls fonctionne -> marchera dans execve ?
	/*if (cmd->previous != NULL)
		dup2(cmd->exchange[1], cmd->previous->exchange[0]);
	if (cmd->infile > 0)
		dup2(cmd->infile, STDIN_FILENO);
	dup2(cmd->next->exchange[1], cmd->exchange[0]);
	if (cmd->outfile > 0)
		dup2(cmd->outfile, STDOUT_FILENO);
	if (cmd->infile > 0)
		close(cmd->infile);
	close(cmd->exchange[0]);
	//close(cmd->exchange[1]);
	if (ft_builtins(cmd, vars))
		exit(0);
	if (execute_cmd(vars, cmd))
		exit(1);*/
	exit (0);
}

static void	execute(t_commands **cmd, t_env_vars **vars)
{
	int			status;
	int			builtin_flag;
	t_commands	*temp;

	temp = (*cmd);
	ft_set_sig(3);
	if (!temp->next)
	{
		builtin_flag = ft_builtins((*cmd), *vars);
		if (builtin_flag > 0)
			return ;
	}
	while (temp != NULL)
	{
		temp->process = fork();
		if (temp->process < 0)
		{
			print_exit_error((*cmd)->cmd[0], "Fork error", -1, NULL);
			temp = temp->next;
			continue ;
		}
		if (temp->process == 0)
		{
			ft_set_sig(4);
			child(temp, *vars);
		}
		waitpid(temp->process, &status, 0);
		(*vars)->exit_code = status >> 8;
		if (g_signal == SIGINT)
			(*vars)->exit_code = 130;
		if (g_signal == SIGQUIT)
			(*vars)->exit_code = 131;
		g_signal = 0;
		if (temp->outfile > 0)
			close(temp->outfile);
		//close(temp->exchange[1]);
		temp = temp->next;
	}
	ft_set_sig(1);
}

void	execution(t_commands **cmd, t_env_vars **pointeur_vars)
{
	t_env_vars	*vars;
	int			index;

	index = 0;
	vars = *pointeur_vars;
	vars->paths = get_path_line((*pointeur_vars)->env, "PATH=", 0);
	if (!vars->paths)
		return (print_exit_error("PATH not set", NULL, -1, NULL));
	vars->split_path = ft_split(vars->paths, ':');
	if (!vars->split_path)
		print_exit_error("Malloc error", NULL, 1, NULL);
	while (vars->split_path[index])
		index++;
	vars->true_paths = malloc((index + 1) * sizeof(char *));
	if (!vars->true_paths)
		print_exit_error("Malloc error", NULL, 1, NULL);
	vars->true_paths[index] = NULL;
	index = 0;
	while (vars->split_path[index])
	{
		vars->true_paths[index] = ft_strjoin(vars->split_path[index], "/");
		if (!vars->true_paths[index])
			print_exit_error("Malloc error", NULL, 1, NULL);
		index++;
	}
	free_split(vars->split_path);
	execute(cmd, pointeur_vars);
}
