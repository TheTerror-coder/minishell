/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srcs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:23:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/07 23:15:21 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SRCS_H
# define FT_SRCS_H

# include "../ft_local.h"

char	*ft_hexa_base(char up_low);
int		ft_islowcase(int c);
int		ft_isupcase(int c);
t_bool	ft_op_char(t_vars *v, int c);
t_bool	ft_op_int(t_vars *v, int n);
t_bool	ft_op_unsign(t_vars *v, unsigned int n);
t_bool	ft_op_hex(t_vars *v, unsigned int n, char up_low);
t_bool	ft_op_str(t_vars *v, char *str);
t_bool	ft_op_adr(t_vars *v, unsigned long long int n);
t_bool	ft_print_char(t_vars *v, int c);
t_bool	ft_print_int(t_vars *v, int n);
t_bool	ft_print_unsign(t_vars *v, unsigned int n);
t_bool	ft_print_hex(t_vars *v, unsigned int n, char up_low);
t_bool	ft_print_str(t_vars *v, char *str);
t_bool	ft_print_adr(t_vars *v, unsigned long long int n);

#endif
