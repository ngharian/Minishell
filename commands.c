/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:36 by gdero             #+#    #+#             */
/*   Updated: 2024/12/16 14:30:58 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_node(t_commands **cmd)
{
	t_commands	*new_node;
	t_commands	*current;

	new_node = (t_commands *) malloc (sizeof(t_commands));
	if (!new_node)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
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
}

void	fill_cmd_struct(t_commands **cmd, char **splitted, t_here_doc **heredoc)
{
	int			index;
	t_commands	*temp;
	char		*trimmed;

	index = -1;
	while (splitted[++index])
		pipe_node(cmd);
	index = -1;
	in_the_pipes(cmd);
	temp = (*cmd);
	while (temp && ++index >= 0)
	{
		temp->acces_file = 0;
		temp->error_file = NULL;
		checking_in_and_out(temp, splitted[index], heredoc, 0);
		trimmed = ft_strtrim(splitted[index], " ");
		if (!trimmed)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		if (split_mini(trimmed, &temp->cmd, ' '))
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		free(trimmed);
		temp = temp->next;
	}
	free_split(splitted);
	delete_quotes(*cmd);
}
