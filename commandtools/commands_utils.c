/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:57:36 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/05 02:49:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*join_s1_with_sub_s2(char *s1, char *s2, size_t start, size_t end)
{
	char	*cpy;
	char	*subinput;

	subinput = ft_substr(s2, start, end);
	if (!subinput)
	{
		free(s1);
		return (NULL);
	}
	cpy = s1;
	s1 = ft_strjoin(s1, subinput);
	free(cpy);
	free(subinput);
	return (s1);
}
