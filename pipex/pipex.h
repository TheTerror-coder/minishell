/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:44:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 22:47:27 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"

t_bool	ft_pipeline(t_vars *v, int nbcmd, char ***cmdlst);
t_ppex	*ft_init_tvars(int nbcmd, char ***cmdlst);
void	ft_free_tvars(t_ppex *var);
t_bool	ft_fclose0(int *fd);
t_bool	ft_close_tvars(t_ppex *var);
t_bool	ft_inittab_int(t_ppex *var);
t_bool	ft_pcloser(t_vars *v);
t_bool	ft_checkargs(t_vars *v);
t_bool	ft_perror(t_vars *v, int status, const char *msg, t_typ action);
void	ft_exitpipe(int status, t_vars *v);
t_bool	ft_set_cmdlist(t_vars *v);
t_bool	ft_ioset(t_vars *v);
t_bool	ft_fwait(t_vars *v, int pid, int option);
t_bool	ft_plumber(t_vars *v);
t_bool	ft_setpath(t_vars *v);
int		ft_setcmdpath(t_vars *v);

#endif