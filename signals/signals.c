/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 06:04:28 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/31 21:29:28 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	readline_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		return ;
}

void	heredoc_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_global = SIGINT;
		close(0);
	}
}

t_bool	set_readline_signals(t_vars *v)
{
	struct sigaction	act;

	act.sa_handler = &readline_handler;
	act.sa_flags = SA_RESTART;
	if (sigemptyset(&act.sa_mask) == -1)
		return(ft_leave(v, EXIT_FAILURE, "sigemptyset", __PERROR), __FALSE);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (ft_leave(v, EXIT_FAILURE, "sigaction", __PERROR), __FALSE);
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (ft_leave(v, EXIT_FAILURE, "sigaction", __PERROR), __FALSE);
	return (__TRUE);
}

void	ignore_signals(void)
{
	struct sigaction	act;

	act.sa_handler = &ignore_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	heredoc_signals(void)
{
	struct sigaction	act;

	act.sa_handler = &heredoc_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
