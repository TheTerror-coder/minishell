/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:19:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 21:10:37 by lmohin           ###   ########.fr       */
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

void	launch_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	main_simple_handler(int signal)
{
	if(signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		ft_putstr_fd("\n", 2);
}
