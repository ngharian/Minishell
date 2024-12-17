/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:39:37 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/17 17:47:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	set_ctrl(int mode)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (mode == 1)
	{
		term.c_cc[VEOF] = 4;
		term.c_lflag &= ~(ECHOCTL);
	}
	else if (mode == 2)
	{
		term.c_cc[VEOF] = _POSIX_VDISABLE;
		term.c_lflag |= (ECHOCTL);
	}
	else if (mode == 3)
	{
		term.c_cc[VEOF] = 4;
		term.c_lflag |= (ECHOCTL);
	}
	tcsetattr(0, TCSANOW, &term);
}

void	sigint_block(int sig)
{
	(void) sig;
	g_signal = sig;
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)", 18);
	write(1, "\n", 1);
}

void	ft_set_sig_bis(int mode)
{
	if (mode == 3)
	{
		signal(SIGINT, sigint_block);
		signal(SIGQUIT, sigint_block);
		set_ctrl(2);
	}
	if (mode == 4)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, exit);
		set_ctrl(3);
	}
	if (mode == 5)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		set_ctrl(2);
	}
}
