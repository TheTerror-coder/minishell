/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:57:36 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 15:19:13 by lmohin           ###   ########.fr       */
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

int	expand_conditions(char *c, int is_hdoc_deli)
{
	if (c[0] != '$')
		return (__FALSE);
	if ((c[1] == '?' || ft_isalpha(c[1])) && !is_hdoc_deli)
		return (__TRUE);
	if (c[1] == '"' || c[1] == '\'' || c[1] == '_')
		return (__TRUE);
	else
		return (__FALSE);
}

char	*join_s1_with_sub_line(char *s1, t_vars *v, size_t *start, size_t *end)
{
	char	*cpy;
	char	*subinput;

	subinput = ft_substr(v->line, *start, *end);
	*start += *end;
	*end = 0;
	if (!subinput)
	{
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
		return (free(s1), NULL);
	}
	cpy = s1;
	if (!s1)
		return (subinput);
	s1 = ft_strjoin(s1, subinput);
	if (!s1)
	{
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
	}
	free(cpy);
	free(subinput);
	return (s1);
}
