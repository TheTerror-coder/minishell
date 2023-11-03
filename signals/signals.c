/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 06:04:28 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/03 14:26:35 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	readline_handler(int signal);
void	heredoc_handler(int signal);
void	launch_handler(int signal);

t_bool	set_readline_signals(void)
{
	struct sigaction	act;

	act.sa_handler = &readline_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
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
