/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:25:19 by ngharian          #+#    #+#             */
/*   Updated: 2024/11/23 14:01:35 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	default_sigint(int sig)
{
	(void) sig;
	g_signal = SIGINT;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_ctrl_d(int mode)
{	
	struct termios term;

	tcgetattr(0, &term);
	if (mode == 1)
	{
		term.c_cc[VEOF] = 4;
		term.c_lflag &= ~(ECHOCTL);
	}
	else if (mode == 2)
	{
		term.c_cc[VEOF] = _POSIX_VDISABLE;
		term.c_lflag |= (/*ICANON | */ ECHOCTL);
	}
	else if (mode == 3)
	{
		term.c_cc[VEOF] = 4;
		term.c_lflag |= (/*ICANON | */ ECHOCTL);
	}
	tcsetattr(0, TCSANOW, &term);
}
void	ft_set_sig(int mode)
{
	if (mode == 1)//comportement par defaut
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
		set_ctrl_d(1);
	}
	if (mode == 2) //processus non bloquants(here_doc, pipe_join)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, SIG_IGN);
		//modifier ctrl+d? -> differents pour here_doc et pipe_join (voir bash)
	}
	if (mode == 3)//processus bloquant
	{
		signal(SIGINT, sigint_block);
		signal(SIGQUIT, sigint_block);
		set_ctrl_d(2);
	}
	if (mode == 4)//comportement par defaut
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, exit);
		set_ctrl_d(3);
	}
}

//variable SHLVL important ou pas dans gestion signale ? (si on lance un minishell dans un minishell)

void	sigint_block(int sig)
{
	(void) sig;
	g_signal = sig;
	if (sig == SIGQUIT)
		write(1, "QUIT: 3", 7);
	write(1, "\n", 1);
}

void	sigint_process(int signal)
{
	(void) signal;
	g_signal = SIGINT;
	write(1, "\n", 1);
}
