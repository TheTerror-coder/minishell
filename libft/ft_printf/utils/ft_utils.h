/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:36:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/07 23:15:21 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../ft_local.h"

int		ft_hexlen(unsigned long long int nbr);
int		ft_nbrlen(long long int nbr);
int		ft_iswidth(char c);
int		ft_isflag(char c);
int		ft_is_optional(char c);
int		ft_isnbr_type(char c);
int		ft_istype(char c);
void	ft_raz_flags(t_vars *var);
void	ft_free_var(t_vars *var);
t_vars	*ft_init_var(const char *format);
void	ft_checkflags(t_vars *v);
void	ft_checkwidth(t_vars *v);
t_bool	ft_checkoptionals(t_vars *v);

#endif
