#include "minishell.h"

int	check_access(t_env_vars *vars, t_commands *temp)
{
	char		*path;
	int			index;

	index = -1;
	if (access(temp->cmd[0], X_OK) == 0)
	{
		temp->absolute_path = true;
		temp->right_command = 0;
		return (0);
	}
	while (vars->true_paths[++index])
	{
		path = ft_strjoin(vars->true_paths[index], temp->cmd[0]);
		if (!path)
			return (1);
		if (access(path, X_OK) == 0)
		{
			temp->right_command = index;
			free(path);
			return (0);
		}
		free(path);
	}
	printf("minishell: %s: command not found\n", temp->cmd[0]);
	return (0);
}

int	execute_cmd(t_env_vars *vars, t_commands *temp)
{
	char		*command;

	temp->absolute_path = false;
	temp->right_command = -1;
	if (check_access(vars, temp))
		return (1);
	if (temp->right_command < 0)
		return (1);
	if (temp->absolute_path == true)
		command = temp->cmd[0];
	else
		command = ft_strjoin(vars->true_paths[temp->right_command], \
		temp->cmd[0]);
	if (!command)
		return (1);
	execve(command, temp->cmd, vars->env);
	free(command);
	return (0);
}

static int	child(t_commands *cmd, t_env_vars *vars)
{
	if (cmd->last_cmd == 1)
	{
		if (cmd->infile > 0)
			dup2(cmd->infile, STDIN_FILENO);
		if (cmd->outfile > 0)
			dup2(cmd->outfile, STDOUT_FILENO);
		else
			dup2(cmd->exchange[0], STDOUT_FILENO);
		if (cmd->infile > 0)
			close(cmd->infile);
		close(cmd->exchange[0]);
		//close(cmd->exchange[1]);
		execute_cmd(vars, cmd);
	}
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

int	execute(t_commands **cmd, t_env_vars **vars)
{
	int			status;
	int			builtin_flag;
	t_commands	*temp;

	temp = (*cmd);
	ft_set_sig(3);
	if (!temp->next)
	{
		builtin_flag = ft_builtins((*cmd), *vars);
		if (builtin_flag < 0) //faire un truc ici -> NECESSAIRE
			return (1);
		if (builtin_flag > 0)
			return (0);
	}
	while (temp != NULL)
	{
		temp->process = fork();
		if (temp->process < 0)
		{
			printf("FORK_ERROR\n");
			return (1);
		}
		if (temp->process == 0)
		{
			ft_set_sig(4);
			if (child(temp, *vars))
			{
				kill(temp->process, SIGQUIT);
				return (1);
			}
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
	return (0);
}

int	in_the_pipes(t_commands **cmd)
{
	int			exchange[2];
	t_commands	*temp;

	temp = (*cmd);
	if (temp->next != NULL && temp->previous == NULL)
	{
		if (pipe(exchange) < 0)
			print_exit_error("Error while using pipe()\n", 1);
		temp->outfile = exchange[1];
	}
	while (temp->next != NULL)
	{
		if (temp->next != NULL && temp->previous != NULL)
		{
			temp->infile = exchange[0];
			if (pipe(exchange) < 0)
				print_exit_error("Error while using pipe()\n", 1);
			temp->outfile = exchange[1];
		}
		temp = temp->next;
	}
	if(temp->next == NULL && temp->previous != NULL)
		temp->infile = exchange[0];
}

int	execution(t_commands **cmd, t_env_vars **pointeur_vars)
{
	int		index;
	t_env_vars	*vars;

	vars = *pointeur_vars;
	index = 0;
	vars->paths = getenv("PATH="); //on pourrait utiliser notre env pour trouver ca en fait
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
	if (in_the_pipes(cmd))
		return (1);
	if (execute(cmd, pointeur_vars))
		return (1);
	return (0);
}
