/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:56:42 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/27 17:23:12 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_setftemp(t_vars *v, int n);
t_bool	ft_clear_loop(char *strnum, char *name, int n);

t_bool	ft_openatemp(t_vars *v)
{
	int		n;
	
	n = __MAX_ATTEMPTS;
	if (!ft_setftemp(v, n))
		return (__FALSE);
	while (n > 0 && !access(v->ftemp1, F_OK))
	{
		n--;
		if (!ft_setftemp(v, n))
			return (__FALSE);
	}
	if (!n)
		return (ft_leave(EXIT_FAILURE, \
		"ft_openatemp() temp file already exits, \
		expand a little bit __MAX_ATTEMPTS", \
		__PRINT));
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(v->ftemp1, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd < 0)
		return (ft_leave(EXIT_FAILURE, v->ftemp1, __PERROR));
	return (__TRUE);
}

t_bool	ft_setftemp(t_vars *v, int n)
{
	char	*strnum;

	strnum = NULL;
	ft_freestr(&v->ftemp1);
	strnum = ft_itoa(n);
	if (!strnum)
		return (ft_leave(EXIT_FAILURE, "ft_setftemp(): ft_itoa() failed", PRINT_ERROR));
	v->ftemp1 = ft_strjoin(__RADICAL, strnum);
	if (!v->ftemp1)
	{
		ft_freestr(&strnum);
		return (ft_leave(EXIT_FAILURE, "ft_setftemp(): ft_strjoin() failed", PRINT_ERROR));
	}
	return (__TRUE);
}

t_bool	ft_clear_created_tempfiles(t_vars *v)
{
	char	*name;
	char	*strnum;
	int		n;

	if (!ft_closetvars(v))
		return (__FALSE);
	n = __MAX_ATTEMPTS;
	strnum = ft_itoa(n);
	if (!strnum)
		return (ft_leave(EXIT_FAILURE, "ft_clear_created_tempfiles(): ft_itoa() failed", __PRINT));
	name = ft_strjoin(__RADICAL, strnum);
	if (!name)
		return (ft_freestr(&strnum), ft_leave(EXIT_FAILURE, "ft_clear_created_tempfiles(): ft_strjoin() failed", __PRINT));
	if (!ft_clear_loop(strnum, name, n))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_clear_loop(char *strnum, char *name, int n)
{
	while (n > 0 && !access(name, F_OK))
	{
		unlink(name);
		n--;
		ft_freestr(&strnum);
		ft_freestr(&name);
		strnum = ft_itoa(n);
		if (!strnum)
			return (ft_leave(EXIT_FAILURE, "ft_clear_loop(): ft_itoa() failed", __PRINT));
		name = ft_strjoin(__RADICAL, strnum);
		if (!name)
			return (ft_freestr(&strnum), ft_leave(EXIT_FAILURE, "ft_clear_loop(): ft_strjoin() failed", __PRINT));
	}
	ft_freestr(&strnum);
	ft_freestr(&name);
	return (__TRUE);
}
