/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:36 by gdero             #+#    #+#             */
/*   Updated: 2024/12/03 13:07:01 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_node(t_commands **cmd, char *splitted, t_here_doc **heredoc)
{
	t_commands	*new_node;
	t_commands	*current;

	new_node = (t_commands *) malloc (sizeof(t_commands));
	if (!new_node)
		return (1);
	new_node->infile = 0;
	new_node->outfile = 0;
	if (checking_in_and_out(new_node, splitted, heredoc))
		return (1);
	printf("ici");
	printf("infile: %d outfile: %d\n", new_node->infile, new_node->outfile);
	if (split_mini(splitted, &new_node->cmd, ' '))
		return (2);
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
	int	index;

	index = 0;
	while (splitted[index])
	{
		if (pipe_node(cmd, splitted[index], heredoc))
			return (free_struct(cmd, 1));
		
		index++;
	}
	//previous_struct(*cmd);
	if (delete_quotes(*cmd))
		return (free_struct(cmd, 2));
	return (0);
}
