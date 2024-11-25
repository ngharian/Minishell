/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:12:28 by gdero             #+#    #+#             */
/*   Updated: 2024/11/25 14:49:55 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_exit(t_commands *cmd, t_env_vars *vars) // exit 123 coucou n'exit pas --> PAS FINI
{
	int	index;
	/*if (cmd->previous != NULL || cmd->next != NULL) //rentre la dedans quand exit seul ???
			return (7);*/
	if (cmd->cmd[1])
	{
		index = -1;
		while (cmd->cmd[1][++index])
		{
			if (!ft_isdigit(cmd->cmd[1][index]))
			{
				printf("exit\nminishell: exit: numeric argument required\n");
				exit(255);
			}
		}
		if (cmd->cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n"); //!!! echo $? = 1
			vars->exit_code = 1;
			return (7);			
		}
	}
	if (cmd->cmd[1]) //!!! overflow
		vars->exit_code = ft_atoi(cmd->cmd[1]);
	printf("exit\n");
	exit((unsigned char)vars->exit_code);
}
