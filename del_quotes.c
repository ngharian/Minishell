/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:33:04 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:11:50 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double(char *splitted, char c)
{
	int	str_index;

	str_index = 0;
	while (splitted[str_index])
	{
		if (splitted[str_index] == c)
		{
			if (splitted[str_index + 1] == c)
				return (1);
			break ;
		}
		str_index++;
	}
	return (0);
}

static void	no_more_quotes(char *string, char *new_string)
{
	int		str_index;
	int		str_index2;
	char	type;

	str_index = -1;
	str_index2 = 0;
	while (string[++str_index])
	{
		if (string[str_index] == 39 || string[str_index] == '"')
		{
			type = string[str_index];
			while (string[++str_index] != type)
				new_string[str_index2++] = string[str_index];
			continue ;
		}
		if (string[str_index] == '\0')
			break ;
		new_string[str_index2++] = string[str_index];
	}
}

void	cmd_without_quotes(char **string)
{
	size_t	str_i;
	size_t	str_j;
	char	*new_string;

	str_i = 0;
	str_j = ft_strlen(*string);
	while (str_i < ft_strlen(*string))
	{
		if ((*string)[str_i] == 39 || (*string)[str_i] == '"')
		{
			str_i = skip_quotes((*string), str_i);
			str_j -= 2;
			continue ;
		}
		str_i++;
	}
	new_string = malloc((str_j + 1) * sizeof(char));
	if (!new_string)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	new_string[str_j] = '\0';
	no_more_quotes((*string), new_string);
	free(*string);
	*string = new_string;
}

void	delete_quotes(t_commands *cmd)
{
	int	index;

	while (cmd != NULL)
	{
		index = -1;
		while (cmd->cmd[++index])
		{
			if (cmd->cmd[index][0] == 7)
			{
				ft_strlcpy(cmd->cmd[index], cmd->cmd[index] + 1, \
				ft_strlen(cmd->cmd[index]));
				continue ;
			}
			cmd_without_quotes(&cmd->cmd[index]);
		}
		cmd = cmd->next;
	}
}
