/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memtools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:02:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/06 14:01:36 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMTOOLS_H
# define FT_MEMTOOLS_H

# include "../ft_pipex.h"

t_vars	*ft_init_tvars(int argc, char **argv);
void	ft_free_tvars(t_vars *var);
t_bool	ft_fclose(int *fd);
t_bool	ft_close_tvars(t_vars *var);
t_bool	ft_inittab_int(t_vars *var);
t_bool	ft_pcloser(t_vars *var);

#endif