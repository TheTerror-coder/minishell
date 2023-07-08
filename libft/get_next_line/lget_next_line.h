/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lget_next_line.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 02:06:01 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:09:13 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LGET_NEXT_LINE_H
# define LGET_NEXT_LINE_H

# include "get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define RES_BUFFER -999
# define SET_BUFFER -998

# define __ERROR -1
# define __READY -111
# define __N_T_R -100//Nothing To Report

# define __A_LEFTOVER -1111
# define __NO_LEFTOVER -1110

char	*ft_lloc(int len);
int		ft_size(char *str);
int		ft_gappend(char *line, char *buf, int end_buf);
int		ft_check_endl(char *str);

#endif