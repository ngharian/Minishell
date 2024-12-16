/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:39:11 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/16 15:42:21 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_heredoc(int fd, char *line, int i, t_env_vars *env_vars)
{
	char	*readed;
	char	*eof_string;

	eof_string = find_eof(line, i + 1);
	signal(SIGINT, exit);
	if (!eof_string)
		print_exit_error("Malloc Error!\n", NULL, 1, NULL);
	while (1)
	{
		readed = readline("here_doc >");
		if (!readed)
		{
			write(2, "minishell: warning: ", 20);
			write(2, "here-document delimited by end-of-file (wanted `", 48);
			write(2, eof_string, ft_strlen(eof_string));
			write(2, "')\n", 3);
			exit (0);
		}
		if (ft_strcmp(readed, eof_string) == 0)
			exit(3);
		expander(&readed, env_vars);
		write(fd, readed, ft_strlen(readed));
		write(fd, "\n", 1);
		free(readed);
	}
}

int	ft_wait_single_process(pid_t pid, int fd, int i)
{
	int	status;

	status = -1;
	ft_set_sig(2);
	while (1 && pid)
	{
		if (waitpid(pid, &status, WNOHANG) < 0)
			print_exit_error("Error while using 'waitpid()'\n", NULL, 1, NULL);
		if (status >> 8 != -1)
		{
			if ((status >> 8) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
			if ((status >> 8) == SIGINT || status >> 8 == 0)
			{
				if ((status >> 8) == SIGINT)
					exit (2);
				close(fd);
				return (-6);
			}
			return (i);
		}
	}
	return (i);
}

t_here_doc	*find_last_heredoc(t_here_doc *here_doc)
{
	if (!here_doc)
		return (NULL);
	while (here_doc->next)
		here_doc = here_doc->next;
	return (here_doc);
}

static void	alloc_heredoc(t_here_doc **here_doc, int fd)
{
	t_here_doc	*new_element;
	t_here_doc	*last;

	new_element = malloc(sizeof(t_here_doc));
	if (!new_element)
		print_exit_error("Malloc Error!\n", NULL, 1, NULL);
	new_element->previous = NULL;
	new_element->fd = fd;
	new_element->next = NULL;
	if (*here_doc == NULL)
		*here_doc = new_element;
	else
	{
		last = find_last_heredoc(*here_doc);
		last->next = new_element;
		new_element->previous = last;
	}
}

int	ft_here_doc(t_here_doc **heredoc, char *readed_line, \
				int i, t_env_vars **env_vars)
{
	int		pipefd[2];
	pid_t	pid;
	int		ret;

	pid = 0;
	if (!(readed_line[i] == '<' && readed_line[i - 1] == '<'))
		return (i);
	if (pipe(pipefd) == -1)
		print_exit_error("Error while using 'pipe()'\n", NULL, 1, NULL);
	alloc_heredoc(heredoc, pipefd[0]);
	pid = fork();
	if (pid < 0)
		print_exit_error("Error while using 'fork()'\n", NULL, 1, NULL);
	if (pid == 0)
		fill_heredoc(pipefd[1], readed_line, i, *env_vars);
	close(pipefd[1]);
	ret = ft_wait_single_process(pid, pipefd[0], i);
	ft_set_sig(1);
	return (ret);
}
