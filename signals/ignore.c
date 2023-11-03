/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:20:54 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/03 13:56:51 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		return ;
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

void	ignore_sigpipe(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGPIPE, &act, NULL);
}
