/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:33:04 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:46:33 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	bell(int index2, char **cmd, char **temp, char **final)
{
	index2 = 0;
	ft_strlcpy((*cmd), (*cmd) + 1, \
	ft_strlen((*cmd)));
	if (ft_strchr((*cmd), 6) != NULL)
	{
		(*temp) = ft_strdup(ft_strchr((*cmd), 6));
		if (!(*temp))
			print_exit_error("Malloc error", NULL, 1, NULL);
	}
	else
		return ;
	while ((*cmd)[index2] != 6)
		index2++;
	(*cmd)[index2] = '\0';
	cmd_without_quotes(&(*temp));
	(*final) = ft_strjoin((*cmd), (*temp));
	if (!(*final))
		print_exit_error("Malloc error", NULL, 1, NULL);
	free((*cmd));
	free((*temp));
	(*cmd) = (*final);
	return ;
}

void	delete_quotes(t_commands *cmd)
{
	int		index;
	char	*temp;
	char	*final;

	temp = NULL;
	final = NULL;
	while (cmd != NULL)
	{
		index = -1;
		while (cmd->cmd[++index])
		{
			if (cmd->cmd[index][0] == 7)
			{
				bell(0, &cmd->cmd[index], &temp, &final);
				continue ;
			}
			cmd_without_quotes(&cmd->cmd[index]);
		}
		cmd->cmd = clean_args(cmd->cmd, -1, -1, -1);
		cmd = cmd->next;
	}
}
