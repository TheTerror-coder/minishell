/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/11 19:54:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "preprocss.h"
#include<stdio.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "libft/libft.h"
#include <sys/wait.h>


t_bool	ft_minishell(t_vars *v);
t_bool	ft_prompt(t_vars *v);
t_bool	ft_lmanager(t_vars *v);
t_vars	*ft_initvars(void);
void	ft_exitprocss(t_vars *v, int status);


t_bool	ft_setargv(t_vars *v);
t_bool	ft_goprompt(char *msg, t_typ action);


t_bool	ft_checkessentials(t_vars *v);
void	ft_freetvars(t_vars *v);
t_bool	ft_lnch_executable(t_vars *v);
t_bool	ft_launcher(t_vars *v);
t_bool	ft_fwait(t_vars *var, int pid, int option);
t_bool	ft_fclose(int *fd);
int	ft_setcmdpath(t_vars *v);
t_bool	ft_setpath(t_vars *v);

#endif