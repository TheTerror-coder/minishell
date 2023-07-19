/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:08:36 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/07 15:47:31 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../ft_pipex.h"

# ifndef FT_BONUS_H

t_bool	ft_checkargs(t_vars *var);
t_bool	ft_heredoc(t_vars *var);
# endif

t_bool	ft_checkinfile(t_vars *var);
t_bool	ft_perror(t_vars *var, int status, const char *msg, t_typ action);
void	ft_exitprocss(int status, t_vars *var);
t_bool	ft_set_cmdlist(t_vars *var);
t_bool	ft_ioset(t_vars *var);
t_bool	ft_setwch(t_vars *var);
t_bool	ft_fwait(t_vars *var, int pid, int option);

#endif