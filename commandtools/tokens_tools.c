/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:00:35 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 17:06:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_word_after_token_buffer(t_vars *v, size_t *l_index, char *ret)
{
	char	*word;
	char	*join;

	word = get_word(v, l_index, 0);
	if (!word)
		v->flg_parsing_is_ok = __FALSE;
	if (!ret)
		return (word);
	join = ft_strjoin(ret, word);
	if (!join)
	{
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
	}
	free(word);
	free(ret);
	return (join);
}

char	*treat_token_buffer(t_vars *v, size_t *l_index, char *ret)
{
	size_t	expand_nbr;

	if (v->line[*l_index] == '\0')
		return (ret);
	expand_nbr = test_expand_null_content(v, *l_index, 0);
	if (v->flg_parsing_is_ok == __FALSE)
		return (NULL);
	if (expand_nbr)
	{
		*l_index = expand_nbr;
		return (ret);
	}
	if ((v->line)[*l_index] == '|' \
		|| (v->line)[*l_index] == '<' || (v->line)[*l_index] == '>')
		return (ret);
	else
		return (get_word_after_token_buffer(v, l_index, ret));
}

char	*prepare_next_expand_token(t_vars *v, size_t i)
{
	char	*ret;

	ret = ft_substr(v->token_buffer, 0, i);
	if (!ret)
	{
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
		return (free(v->token_buffer), NULL);
	}
	while (is_whitespace(v->token_buffer[i]))
		i++;
	v->token_buffer = get_end_expand_content(v, v->token_buffer, i);
	if (!v->token_buffer)
		return (free(ret), NULL);
	return (ret);
}

char	*clear_token_buffer(t_vars *v, size_t *l_index)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (!is_whitespace(v->token_buffer[i]) && v->token_buffer[i] != '\0')
		i++;
	if (v->token_buffer[i] == '\0')
	{
		ret = v->token_buffer;
		if (v->token_buffer[0] == '\0')
		{
			free(v->token_buffer);
			ret = NULL;
		}
		v->token_buffer = NULL;
		return (treat_token_buffer(v, l_index, ret));
	}
	else
		return (prepare_next_expand_token(v, i));
}
