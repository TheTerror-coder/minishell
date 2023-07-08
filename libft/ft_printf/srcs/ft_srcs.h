/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srcs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:23:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:02:34 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SRCS_H
# define FT_SRCS_H

# include "../ft_lprintf.h"

char		*ft_hexa_base(char up_low);
int			ft_islowcase(int c);
int			ft_isupcase(int c);
t_bool__	ft_op_char(t_vars *v, int c);
t_bool__	ft_op_int(t_vars *v, int n);
t_bool__	ft_op_unsign(t_vars *v, unsigned int n);
t_bool__	ft_op_hex(t_vars *v, unsigned int n, char up_low);
t_bool__	ft_op_str(t_vars *v, char *str);
t_bool__	ft_op_adr(t_vars *v, unsigned long long int n);
t_bool__	ft_print_char(t_vars *v, int c);
t_bool__	ft_print_int(t_vars *v, int n);
t_bool__	ft_print_unsign(t_vars *v, unsigned int n);
t_bool__	ft_print_hex(t_vars *v, unsigned int n, char up_low);
t_bool__	ft_print_str(t_vars *v, char *str);
t_bool__	ft_print_adr(t_vars *v, unsigned long long int n);

#endif
