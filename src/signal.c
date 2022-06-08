/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.r>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:38:57 by fserwyn           #+#    #+#             */
/*   Updated: 2021/11/17 21:57:47 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	heredoc_sig(int sig)
{
	g_status = 247;
	rl_event_hook = kill_readline;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)sig;
}

void	sig_int(pid_t	pid)
{
	if (pid != -1)
	{
		write(2, "\n", 1);
		g_status = 130 << 8;
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_control(int sig)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	if (sig == SIGINT)
		sig_int(pid);
	if (sig == SIGQUIT)
	{
		if (pid != -1)
		{
			write(2, "Quit: 3\n", 8);
			g_status = 131 << 8;
		}
		else
			(void)sig;
	}
}

void	signal_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_control);
	signal(SIGQUIT, signal_control);
}
