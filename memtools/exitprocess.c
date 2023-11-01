/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 13:37:28 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exitmainprocss(t_vars *v, int code)
{
	ft_clear_created_tempfiles(v);
	ft_closetvars(v);
	ft_fclose(v, &v->stdin);
	ft_fclose(v, &v->stdout);
	ft_freetvars(v);
	exit(code);
}

void	ft_exitbackprocss(t_vars *v, int code)
{
	ft_closetvars(v);
	ft_fclose(v, &v->stdin);
	ft_fclose(v, &v->stdout);
	ft_freetvars(v);
	close(0);
	close(1);
	exit(code);
}
