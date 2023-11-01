/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 06:04:28 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/01 21:07:13 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	readline_handler(int signal);
void	heredoc_handler(int signal);
void	main_simple_handler(int signal);
void	launch_handler(int signal);

t_bool	set_readline_signals(t_vars *v)
{
	struct sigaction	act;

	act.sa_handler = &readline_handler;
	act.sa_flags = SA_RESTART;
	if (sigemptyset(&act.sa_mask) == -1)
		return (ft_leave(v, EXIT_FAILURE, "sigemptyset", __PERROR), __FALSE);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (ft_leave(v, EXIT_FAILURE, "sigaction", __PERROR), __FALSE);
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (ft_leave(v, EXIT_FAILURE, "sigaction", __PERROR), __FALSE);
	return (__TRUE);
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

void	launch_signals(void)
{
	struct sigaction	act;
	
	act.sa_handler = &launch_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	main_simple_signals(void)
{
	struct sigaction	act;

	act.sa_handler = &main_simple_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
