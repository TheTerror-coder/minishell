/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parsing1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:49:59 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/02 18:27:53 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_end_expand_content(t_vars *v, char *expand_content, size_t i)
{
	char	*sub_content;

	sub_content = ft_substr(expand_content, i, ft_strlen(expand_content));
	if (!sub_content)
	{
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
	}
	free(expand_content);
	expand_content = NULL;
	return (sub_content);
}

char	*join_ret_with_sub_content(t_vars *v, char *ret, char *sub_content)
{
	char	*join;

	join = ft_strjoin(ret, sub_content);
	if (!join)
	{
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
	}
	free(ret);
	free(sub_content);
	return (join);
}

char	*no_whitespace_start(t_vars *v, char *expand_content, char *ret)
{
	size_t	i;
	char	*sub_content;

	i = 0;
	while (!is_whitespace(expand_content[i]) && expand_content[i] != '\0')
		i++;
	sub_content = ft_substr(expand_content, 0, i);
	if (!sub_content)
	{
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
		free(ret);
		return (free(expand_content), NULL);
	}
	while (is_whitespace(expand_content[i]))
		i++;
	if (expand_content[i] != '\0')
	{
		v->token_buffer = get_end_expand_content(v, expand_content, i);
		if (!v->token_buffer)
			return (free(ret), NULL);
	}
	else
		free(expand_content);
	return (join_ret_with_sub_content(v, ret, sub_content));
}

char	*clear_expand_content(t_vars *v, char *expand_content, char *ret)
{
	size_t	i;

	i = 0;
	if (expand_content[0] == '\0')
		return (free(expand_content), ret);
	if (is_whitespace(expand_content[0]))
	{
		while (is_whitespace(expand_content[i]))
			i++;
		if (ret && ret[0] != '\0')
		{
			v->token_buffer = get_end_expand_content(v, expand_content, i);
			return (ret);
		}
		expand_content = get_end_expand_content(v, expand_content, i);
		if (!expand_content)
			return (free(ret), NULL);
	}
	return (no_whitespace_start(v, expand_content, ret));
}
