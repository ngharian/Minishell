/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:36 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 12:52:11 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_node(t_commands **cmd)
{
	t_commands	*new_node;
	t_commands	*current;

	new_node = (t_commands *) malloc (sizeof(t_commands));
	if (!new_node)
		return (1);
	new_node->infile = 0;
	new_node->outfile = 0;
	new_node->last_cmd = 1;
	new_node->next = NULL;
	new_node->previous = NULL;
	if (*cmd == NULL)
		*cmd = new_node;
	else
	{
		current = *cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
		new_node->previous->last_cmd = 0;
	}
	return (0);
}

/*static void	previous_struct(t_commands *cmd)
{
	t_commands	*temp;

	cmd->previous = NULL;
	if (!cmd->next)
	{
		cmd->last_cmd = 1;
		return ;
	}
	while (cmd->next != NULL)
	{
		temp = cmd;
		cmd->last_cmd = 0;
		cmd = cmd->next;
		cmd->previous = temp;
	}
	cmd->last_cmd = 1;
	cmd->previous = temp;
}
*/
int	fill_cmd_struct(t_commands **cmd, char **splitted, t_here_doc **heredoc)
{
	int			index;
	t_commands	*temp;
	char		*trimmed;

	index = -1;
	while (splitted[++index])
	{
		if (pipe_node(cmd))
			print_exit_error("Malloc error!\n", NULL, 1);
	}
	index = -1;
	in_the_pipes(cmd);
	temp = (*cmd);
	while (temp && ++index >= 0)
	{
		temp->acces_file = 0;
		temp->error_file = NULL;
		checking_in_and_out(temp, splitted[index], heredoc);
		trimmed = ft_strtrim(splitted[index], " ");
		if (split_mini(trimmed, &temp->cmd, ' '))
			print_exit_error("Malloc error!\n", NULL, 1);
		free(trimmed);
		temp = temp->next;
	}
	free_split(splitted);
	if (delete_quotes(*cmd))
		return (free_struct(cmd, 2));
	return (0);
}
