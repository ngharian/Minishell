/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:33:04 by gdero             #+#    #+#             */
/*   Updated: 2024/12/16 19:31:27 by gdero            ###   ########.fr       */
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

static int	count_clean_str(char *str)
{
	int	i;
	int	cond;
	int	counter;

	cond = 0;
	i = 0;
	counter = 0;
	while (str[i])
	{
		++counter;
		if (str[i] == 6 || str[i] == 7)
		{
			cond = 1;
			--counter;
		}
		++i;
	}
	if (cond == 0)
		return (-1);
	return (counter);
}

static char	**clean_args(char **split, int i, int index, int j)
{
	int		counter;
	char	*new_str;

	while (split[++i])
	{
		j = -1;
		index = -1;
		counter = count_clean_str(split[i]);
		if (counter == -1)
			continue ;
		new_str = malloc(sizeof(char) * (counter + 1));
		if (!new_str)
			print_exit_error("Malloc error", NULL, 1, NULL);
		while (split[i][++j])
		{
			if (split[i][j] == 7 || split[i][j] == 6)
				continue ;
			new_str[++index] = split[i][j];
		}
		new_str[++index] = '\0';
		free(split[i]);
		split[i] = new_str;
	}
	return (split);
}

void	delete_quotes(t_commands *cmd)
{
	int		index;
	int		index2;
	char	*temp;
	char	*final;

	while (cmd != NULL)
	{
		index = -1;
		while (cmd->cmd[++index])
		{
			if (cmd->cmd[index][0] == 7)
			{
				index2 = 0;
				ft_strlcpy(cmd->cmd[index], cmd->cmd[index] + 1, \
				ft_strlen(cmd->cmd[index]));
				if (ft_strchr(cmd->cmd[index], 6) != NULL)
				{
					temp = ft_strdup(ft_strchr(cmd->cmd[index], 6));
					if (!temp)
						print_exit_error("Malloc error", NULL, 1, NULL);
				}
				else
					continue ;
				while (cmd->cmd[index][index2] != 6)
					index2++;
				cmd->cmd[index][index2] = '\0';
				cmd_without_quotes(&temp);
				final = ft_strjoin(cmd->cmd[index], temp);
				if (!final)
					print_exit_error("Malloc error", NULL, 1, NULL);
				free(cmd->cmd[index]);
				free(temp);
				cmd->cmd[index] = final;
				continue ;
			}
			cmd_without_quotes(&cmd->cmd[index]);
		}
		cmd->cmd = clean_args(cmd->cmd, -1, -1, -1);
		cmd = cmd->next;
	}
}
