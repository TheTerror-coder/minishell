/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipetools.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:04:18 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 15:18:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPETOOLS_H
# define FT_PIPETOOLS_H

# include "../ft_pipex.h"

t_bool	ft_plumber(t_vars *var);
t_bool	ft_setpath(t_vars *var);
t_bool	ft_ioset(t_vars *var);
int		ft_setcmdpath(t_vars *var);

#endif
