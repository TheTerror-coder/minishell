/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:01:20 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/26 06:52:29 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	try_to_getcwd(t_vars *v, size_t buf_size)
{
	char	*buf;

	buf = malloc(sizeof(char) * buf_size);
	v->pwd = getcwd(buf, buf_size);
	if (!(v->pwd) && errno == ERANGE)
	{
		free(buf);
		return (0);
	}
	return (1);
}
	
		
t_bool	ft_set_pwd(t_vars *v)
{
	size_t	buf_size;

	buf_size = 2;
	t_bool	ret;
	ret = 0;
	while (ret == 0)
	{
		if (!try_to_getcwd(v, buf_size))		
			buf_size++;
		else
			ret = 1;
	}
	return (1);
}

