/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:50:35 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:10:19 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lget_next_line.h"

char	*ft_op_cat(char **line, char *buf, int len_buf)
{
	char	*newline;
	int		i;
	int		len_line;

	i = 0;
	newline = 0;
	len_line = ft_size(*line);
	if (len_line)
		newline = ft_lloc(len_line + len_buf + 1);
	else
		newline = ft_lloc(len_buf + 1);
	if (newline)
	{
		i = ft_gappend(newline, *line, len_line);
		i += ft_gappend(&newline[i], buf, len_buf);
		newline[i] = 0;
		if (*line)
			free(*line);
		*line = NULL;
		return (newline);
	}
	if (*line)
		free(*line);
	return (*line = NULL);
}

int	ft_set_buf(char *buf, int endl, int role)
{
	int	i;

	i = 0;
	if (role == RES_BUFFER)
	{
		while (i < endl)
		{
			buf[i] = 0;
			i++;
		}
		return (-99);
	}
	while (buf[endl])
	{
		buf[i] = buf[endl];
		i++;
		endl++;
	}
	while (buf[i])
	{
		buf[i] = 0;
		i++;
	}
	return (-99);
}

int	ft_cat(char **line, char *buf, int len_buf, int *endl)
{
	*endl = ft_check_endl(buf);
	if (*endl)
	{
		*line = ft_op_cat(&(*line), buf, *endl);
		if (!(*line))
			return (__ERROR);
		ft_set_buf(buf, *endl, SET_BUFFER);
		*endl = __A_LEFTOVER;
		return (__READY);
	}
	*endl = __NO_LEFTOVER;
	*line = ft_op_cat(&(*line), buf, len_buf);
	ft_set_buf(buf, BUFFER_SIZE + 1, RES_BUFFER);
	if (!(*line))
		return (__ERROR);
	return (__N_T_R);
}

int	ft_op_gnl(int fd, char **line, char *buf, int *endl)
{
	int			len_read;
	int			flag;

	len_read = 999;
	if (*endl == __A_LEFTOVER)
		return (__A_LEFTOVER);
	while (len_read && len_read != -1)
	{
		if (buf[0])
		{
			flag = ft_cat(&(*line), buf, len_read, endl);
			if (flag == __ERROR)
				return (__ERROR);
			if (flag == __READY)
				return (__READY);
		}
		len_read = read(fd, buf, BUFFER_SIZE);
		if (len_read == -1)
			return (__ERROR);
		if (len_read == 0)
			return (__READY);
		buf[len_read] = 0;
	}
	return (__N_T_R);
}

char	*get_next_line(int fd)
{
	int			flag;
	static int	endl = 0;
	static int	flg_buf = 0;
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (!flg_buf)
		flg_buf = ft_set_buf(buff, BUFFER_SIZE + 1, RES_BUFFER);
	flag = ft_op_gnl(fd, &line, buff, &endl);
	if (flag == __A_LEFTOVER)
	{
		flag = __N_T_R;
		endl = __NO_LEFTOVER;
		if (ft_size(buff))
			flag = ft_cat(&line, buff, ft_size(buff), &endl);
		if (flag == __N_T_R)
			flag = ft_op_gnl(fd, &line, buff, &endl);
	}
	if (flag == __READY)
		return (line);
	if (line)
		free(line);
	line = NULL;
	return (line);
}
