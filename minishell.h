/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/22 03:22:41 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "preprocss.h"
# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<readline/readline.h>
# include<readline/history.h>
# include <sys/wait.h>
# include "libft/ft_printf/ft_printf.h"

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
t_bool	ft_isseperator(char c, char *suite);
char	*ft_setofquote(t_vars *v, char c);
void	ft_skip_partquoted(char *line, int *i);
void	ft_freesecondaries(t_vars *v);
t_bool	ft_ioset_op(int *infd, int *outfd);
t_bool	ft_fclose(int *fd);
t_bool	ft_parseargv(t_vars *v);
void	ft_razflags(t_vars *v);
t_bool	ft_inredir(t_vars *v);
t_bool	ft_outredir(t_vars *v);
t_bool	ft_outappendredir(t_vars *v);
t_bool	ft_heredocredir(t_vars *v);

t_bool	ft_echo(t_vars *v, t_bool n_option);

#endif