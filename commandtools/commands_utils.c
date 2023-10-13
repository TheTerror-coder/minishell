/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:57:36 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/14 00:52:08 by lmohin           ###   ########.fr       */
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

int	is_whitespace_or_operator_or_nul(char c)
{
	return (is_whitespace(c) || is_operator(c) || (c == '\0'));
}

int	expand_conditions(char c, int is_hdoc_deli)
{
	if (c == '\0')
		return (__FALSE);
	return (!(is_whitespace(c) || is_operator(c) || is_hdoc_deli));
}

char	*join_s1_with_sub_s2(char *s1, char *s2, size_t *start, size_t *end)
{
	char	*cpy;
	char	*subinput;

	subinput = ft_substr(s2, *start, *end);
	*start += *end;
	*end = 0;
	if (!subinput)
	{
		perror("minishell: join_s1_with_sub_s2: ");
		free(s1);
		return (NULL);
	}
	cpy = s1;
	if (!s1)
		return (subinput);
	s1 = ft_strjoin(s1, subinput);
	if (!s1)
		perror("minishell: join_s1_with_sub_s2: ");
	free(cpy);
	free(subinput);
	return (s1);
}
