/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:12:28 by gdero             #+#    #+#             */
/*   Updated: 2024/11/05 19:37:53 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_exit(t_commands *cmd)
{
	if (cmd->previous != NULL || cmd->next != NULL)
		return (7);
	else
	{
		free_struct(&cmd, 0);
		exit(0);//kill le child, pas le parent
	}
}
