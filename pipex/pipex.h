/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:44:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 23:27:42 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"

# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __SKIP 2
# define __WHANG 0

void	ft_run_pipeline(t_vars *v, t_commands *commands);
t_ppex	*ft_init_tvars(t_vars *v, t_commands *commands);
void	ft_free_tvars(t_vars *v, t_ppex *var);
t_bool	ft_close_tvars(t_vars *v, t_ppex *var);
t_bool	ft_inittab_int(t_ppex *var);
t_bool	ft_pcloser(t_vars *v);
t_bool	ft_perror(t_vars *v, int code, const char *msg, t_typ action);
void	ft_exitpipe(t_vars *v);
t_bool	ft_ioset(t_vars *v);
t_bool	ft_plumber(t_vars *v);
t_bool	ft_waitingroom(t_vars *v);

#endif
