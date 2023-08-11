/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preprcss.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:26:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:37 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PREPRCSS_H
# define FT_PREPRCSS_H

# include<stdarg.h>

typedef enum e_bool
{
	__FALSE = 0,
	__TRUE = -111111
}				t_bool;

typedef struct s_vars
{
	unsigned int	i;
	int				len;
	const char		*fmt;
	int				width;
	int				precision;
	t_bool			_noflag;
	t_bool			_minus;
	t_bool			_zero;
	t_bool			_dot;
	t_bool			_sharp;
	t_bool			_space;
	t_bool			_plus;
}				t_vars;

#endif
