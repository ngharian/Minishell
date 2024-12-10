/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:38 by gdero             #+#    #+#             */
/*   Updated: 2024/12/10 15:19:05 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_the_pipes(t_commands **cmd)
{
	t_commands	*temp;
	int			texchange[2];

	temp = (*cmd);
	if (temp->next != NULL && temp->previous == NULL)
	{
		if (pipe(temp->exchange) < 0)
			print_exit_error("Error while using pipe()\n", NULL, 1, NULL);
		temp->outfile = temp->exchange[1];
		texchange[0] = temp->exchange[0];
	}
	while (temp->next != NULL)
	{
		if (temp->next != NULL && temp->previous != NULL)
		{
			temp->infile = texchange[0];
			if (pipe(temp->exchange) < 0)
				print_exit_error("Error while using pipe()\n", NULL, 1, NULL);
			temp->outfile = temp->exchange[1];
			texchange[0] = temp->exchange[0];
		}
		temp = temp->next;
	}
	if (temp->next == NULL && temp->previous != NULL)
		temp->infile = texchange[0];
}

static void	infile_case(t_commands *cmd, t_file *file, t_here_doc **heredoc)
{
	t_here_doc	*temp;

	if (cmd->infile > 2)
		close(cmd->infile);
	if (access((*file).trimmed, R_OK) == -1 || \
	access((*file).trimmed, F_OK) == -1)
	{
		cmd->error_file = ft_strdup((*file).trimmed);
		if (!cmd->error_file)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		if (cmd->outfile > 2)
			close(cmd->outfile);
		cmd->acces_file = 2;
		if (access((*file).trimmed, F_OK) > -1)
			cmd->acces_file = 1;
	}
	if ((*file).mode == 0 && (*file).type == '<')
		cmd->infile = open((*file).trimmed, O_RDONLY);
	else if ((*file).mode == 1 && (*file).type == '<')
	{
		cmd->infile = (*heredoc)->fd;
		temp = (*heredoc);
		(*heredoc) = (*heredoc)->next;
		free(temp);
	}
}

static void	open_files(t_commands *cmd, t_file *file, t_here_doc **hd, char *s)
{
	s = (*file).trimmed;
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (free((*file).trimmed));
	if ((*file).type == '>')
	{
		if (cmd->outfile > 2)
		{
			close(cmd->outfile);
			cmd->outfile = 0;
		}
		if (access(s, W_OK) == -1)
		{
			cmd->error_file = ft_strdup((*file).trimmed);
			if (!cmd->error_file)
				print_exit_error("Malloc error!\n", NULL, 1, NULL);
			cmd->acces_file = 1;
		}
		if ((*file).mode == 0)
			cmd->outfile = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*file).mode == 1)
			cmd->outfile = open(s, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	infile_case(cmd, file, hd);
	free(s);
}

void	checking_in_and_out(t_commands *cmd, char *splitted, t_here_doc **hd)
{
	int		str_index;
	t_file	file;

	str_index = -1;
	while (splitted[++str_index])
	{
		if (splitted[str_index] == 39 || splitted[str_index] == '"')
			str_index = skip_quotes(splitted, str_index);
		if (splitted[str_index] == '\0')
			return ;
		else if (splitted[str_index] == '>' || splitted[str_index] == '<')
		{
			get_file_name_trimmed(&file, &str_index, &splitted);
			if(file.trimmed[0] == 0)
			{
				cmd->infile = -1;
				cmd->acces_file = 3;
				free(file.trimmed);
			}
			else
				open_files(cmd, &file, hd, NULL);
			if (splitted[str_index] == '\0')
				break ;
		}
	}
}
