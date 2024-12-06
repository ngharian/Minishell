/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:35:47 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/04 13:36:57 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_string(char **splitted, char *trimmed, int mode, char c)
{
	int	index;
	int	trim_index;

	index = 0;
	trim_index = 1;
	while ((*splitted)[index] != c)
		index++;
	if (mode == 1)
		trim_index++;
	while ((*splitted)[index + trim_index] == ' ')
		trim_index++;
	trim_index += ft_strlen(trimmed);
	while ((*splitted)[index + trim_index])
	{
		(*splitted)[index] = (*splitted)[index + trim_index];
		index++;
	}
	(*splitted)[index] = '\0';
}

static void	update_trim_string(char *trimmed)
{
	int	str_index;

	str_index = 0;
	while (trimmed[str_index])
	{
		if (trimmed[str_index] == 39 || trimmed[str_index] == '"')
		{
			str_index = skip_quotes(trimmed, str_index);
			continue ;
		}
		if (trimmed[str_index] == ' ' || trimmed[str_index] == '\0')
			break ;
		str_index++;
	}
	ft_strlcpy(trimmed, trimmed, str_index + 1);
}

void	get_file_name_trimmed(t_file *file, int *str_index, char **splitted)
{
	(*file).type = (*splitted)[*str_index];
	(*file).mode = 0;
	if ((*splitted)[*str_index] == (*splitted)[(*str_index) + 1])
		(*file).mode = 1;
	(*file).trimmed = ft_strchr(*splitted, (*file).type);
	if ((*file).type == '>')
		(*file).trimmed = ft_strtrim((*file).trimmed, "> ");
	else
		(*file).trimmed = ft_strtrim((*file).trimmed, "< ");
	if (!(*file).trimmed)
		print_exit_error("Malloc failure!\n", 1);
	update_trim_string((*file).trimmed);
	update_string(splitted, (*file).trimmed, (*file).mode, (*file).type);
	if (cmd_without_quotes(&file->trimmed))
		print_exit_error("(a changer) Del_quotes_error\n", 1);
	//trimmed = ft_strtrim(trimmed, "\"'");
}