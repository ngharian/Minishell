/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:25:19 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/16 13:13:02 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_signal;

void	ft_set_sig(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
		set_ctrl(1);
	}
	if (mode == 2)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, SIG_IGN);
	}
	ft_set_sig_bis(mode);
}

void	default_sigint(int sig)
{
	(void) sig;
	g_signal = SIGINT;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_process(int signal)
{
	(void) signal;
	g_signal = SIGINT;
	write(1, "\n", 1);
}
