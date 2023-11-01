/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:36:31 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/01 09:31:13 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_unclosed_double_quote(t_vars *v, size_t i, size_t j)
{
	if ((v->line)[i + j] != '"')
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		v->exitstatus = 2;
		v->flg_parsing_is_ok = __FALSE;
		return (__TRUE);
	}
	return (__FALSE);
}

char	*double_quote_case(size_t *i, char *ret, t_vars *v, int heredoc)
{
	size_t	j;

	j = 0;
	if (!ret)
		return (NULL);
	*i += 1;
	while ((v->line)[*i + j] != '"' && (v->line)[*i + j] != '\0')
	{
		if (expand_conditions((v->line) + *i + j, heredoc) \
			&& v->line[*i + j + 1] != '"' && v->line[*i + j + 1] != '\'')
		{
			ret = expand_case_double_quote(i, &j, ret, v);
			if (!ret)
				return (NULL);
		}
		else
			j++;
	}
	if (check_unclosed_double_quote(v, *i, j))
		return (free(ret), NULL);
	ret = join_s1_with_sub_line(ret, v, i, &j);
	*i += 1;
	return (ret);
}

char	*single_quote_case(t_vars *v, size_t *i, size_t *j, char *ret)
{
	ret = join_s1_with_sub_line(ret, v, i, j);
	if (!ret)
		return (NULL);
	*i += 1;
	while (v->line[*i + *j] != '\'' && v->line[*i + *j] != '\0')
		(*j)++;
	if (v->line[*i + *j] != '\'')
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		v->exitstatus = 2;
		v->flg_parsing_is_ok = __FALSE;
		free(ret);
		return (NULL);
	}
	ret = join_s1_with_sub_line(ret, v, i, j);
	*i += 1;
	return (ret);
}

t_bool	parsing_break_condition(t_vars *v, size_t j, char *ret)
{
	if (!ret && j == 0)
		return (__TRUE);
	if (v->token_buffer)
		return (__TRUE);
	if (!v->flg_parsing_is_ok)
		return (__TRUE);
	return (__FALSE);
}

char	*get_word(t_vars *v, size_t *index_start, int is_hdoc_deli)
{
	size_t	j;
	char	*ret;

	ret = NULL;
	j = 0;
	while (!is_whitespace_or_operator_or_nul((v->line[*index_start + j])))
	{
		if (expand_conditions((v->line) + *index_start + j, is_hdoc_deli))
			ret = expand_case(index_start, &j, ret, v);
		else if ((v->line)[*index_start + j] == '"')
		{
			ret = join_s1_with_sub_line(ret, v, index_start, &j);
			ret = double_quote_case(index_start, ret, v, is_hdoc_deli);
		}
		else if ((v->line)[*index_start + j] == '\'')
			ret = single_quote_case(v, index_start, &j, ret);
		else
			j++;
		if (parsing_break_condition(v, j, ret))
			return (ret);
	}
	ret = join_s1_with_sub_line(ret, v, index_start, &j);
	if (!ret)
		v->exitstatus = EXIT_FAILURE;
	return (ret);
}
