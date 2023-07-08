/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:10:36 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 01:59:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BONUS_H
# define FT_BONUS_H

# include "../ft_lprintf.h"

t_bool__	ft_print_first(t_vars *v, int len);
t_bool__	ft_print_last(t_vars *v, int len);
t_bool__	ft_put_zeros(t_vars *v, int len);
t_bool__	ft_put_spaces(t_vars *v, int len);

#endif
