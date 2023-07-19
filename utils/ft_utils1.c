/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/16 14:32:24 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_goprompt(char *msg, t_typ action)
{
	if (!msg)
		return (__FALSE);
	if (action == PRINT_ERROR)
		ft_putendl_fd(msg, 1);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_isseperator(char c, char *suite)
{
	if (c == ' ')
		return (__TRUE);
	if (c == "'"[0])
	{
		if (ft_strchr(suite, "'"[0]))
			return (__TRUE);
		return (__FALSE);
	}
	if (c == '"') 
	{
		if (ft_strchr(suite, '"'))
			return (__TRUE);
		return (__FALSE);
	}
	return (__FALSE);
}

void	ft_skip_partquoted(char *line, int *i)
{
	char	c;

	c = line[*i];
	*i = *i + 1;
	while (line[*i] != c)
		*i = *i + 1;
}

char	*ft_setofquote(t_vars *v, char c)
{
	char	*set;

	set = ft_calloc(2, sizeof(char));
	if (!set)
		return (NULL);
	set[0] = c;
	set[1] = 0;
	if (v->set)
		free(v->set);
	v->set = set;
	return (set);
}
