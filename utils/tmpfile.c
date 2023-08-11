/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:56:42 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/06 16:58:22 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_setftemp(t_vars *v, int n);

t_bool	ft_openatemp(t_vars *v)
{
	int		n;
	
	n = 9999999;
	ft_setftemp(v, n);
	while (n > 0 && !access(v->ftemp1, F_OK))
	{
		n--;
		ft_setftemp(v, n);
	}
	if (!n)
		return (ft_goprompt("temp file already exits", PRINT_ERROR));
	ft_fclose(&v->outfd);
	v->outfd = open(v->ftemp1, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd < 0)
		return (ft_goprompt(v->ftemp1, __PERROR));
	return (__TRUE);
}

t_bool	ft_setftemp(t_vars *v, int n)
{
	char	*strnum;

	strnum = NULL;
	ft_freestr(&v->ftemp1);
	strnum = ft_itoa(n);
	if (!strnum)
		return (ft_goprompt("failed allocation", PRINT_ERROR));
	v->ftemp1 = ft_strjoin(__RADICAL, strnum);
	if (!v->ftemp1)
	{
		ft_freestr(&strnum);
		return (ft_goprompt("failed allocation", PRINT_ERROR));
	}
	return (__TRUE);
}
