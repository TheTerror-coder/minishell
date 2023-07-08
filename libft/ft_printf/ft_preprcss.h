/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preprcss.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:26:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:00:02 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PREPRCSS_H
# define FT_PREPRCSS_H

# include<stdarg.h>

typedef enum e_bool__
{
	_FALSE_ = 0,
	_TRUE_ = -111111
}				t_bool__;

typedef struct s_vars
{
	unsigned int	i;
	int				len;
	const char		*fmt;
	int				width;
	int				precision;
	t_bool__		_noflag;
	t_bool__		_minus;
	t_bool__		_zero;
	t_bool__		_dot;
	t_bool__		_sharp;
	t_bool__		_space;
	t_bool__		_plus;
}				t_vars;

#endif
