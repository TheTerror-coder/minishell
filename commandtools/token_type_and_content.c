/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_and_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:36:31 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/05 02:46:41 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_case(char *input, size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;
	char	*cpy;

	ret = join_s1_with_sub_s2(ret, input, *i, *j);
	if (!ret)
		return (NULL);
	*i += *j + 1;
	*j = 0;
	if (input[*i + *j] <= '9' && input[*i + *j] >= '0')
		return (ret);
	while ((input[*i + *j] <= 'z' && input[*i + *j] >= 'a') \
		|| (input[*i + *j] <= 'Z' && input[*i + *j] >= 'A') \
		|| (input[*i + *j] >= '0' && input[*i + *j] <= '9'))
		(*j)++;
	expand_name = ft_substr(input, *i, *j);
	*i += *j;
	*j = 0;
	if (!check_env_var_set(v, expand_name))
	{
		free(expand_name);
		return (ret);
	}
	cpy = ret;
	ret = ft_strjoin(ret, check_env_var_set(v, expand_name));
	free(cpy);
	free(expand_name);
	return (ret);
}

char	*double_quote_case(size_t *i, size_t *j, char *ret, t_vars *v, int heredoc)
{
	ret = join_s1_with_sub_s2(ret, v->line, *i, *j);
	if (!ret)
		return (NULL);
	*i += *j + 1;
	*j = 0;
	while ((v->line)[*i + *j] != '"' && (v->line)[*i + *j] != '\0')
	{
		if (heredoc == 0 && (v->line)[*i + *j] == '$' \
			&& !is_whitespace((v->line)[*i + *j + 1]) \
			&& !is_operator((v->line)[*i + *j + 1]))
			ret = expand_case(v->line, i, j, ret, v);
		else
			(*j)++;
	}
	if ((v->line)[*i + *j] != '"')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = join_s1_with_sub_s2(ret, v->line, *i, *j);
	*i += *j + 1;
	*j = 0;
	return (ret);
}

char	*single_quote_case(char *input, size_t *i, size_t *j, char *ret)
{
	ret = join_s1_with_sub_s2(ret, input, *i, *j);
	*i += *j + 1;
	*j = 0;
	while (input[*i + *j] != '\'' && input[*i + *j] != '\0')
		(*j)++;
	if (input[*i + *j] != '\'')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = join_s1_with_sub_s2(ret, input, *i, *j);
	*i += *j + 1;
	*j = 0;
	return (ret);
}

int	is_whitespace_or_operator_or_nul(char c)
{
	return (is_whitespace(c) || is_operator(c) || (c == '\0'));
}

int	expand_conditions(char c, int is_hdoc_deli)
{
	return (!(is_whitespace(c) || is_operator(c) || is_hdoc_deli));
}

char	*get_word(t_vars *v, size_t *index_start, int is_hdoc_deli, char **ret)
{
	size_t	j;

	j = 0;
	while (!is_whitespace_or_operator_or_nul((v->line)[*index_start + j]))
	{
		if ((v->line)[*index_start + j] == '$' \
			&& expand_conditions((v->line)[*index_start + j + 1], is_hdoc_deli))
				*ret = expand_case((v->line), index_start, &j, *ret, v);
		else if ((v->line)[*index_start + j] == '"')
			*ret = double_quote_case(index_start, &j, *ret, v, is_hdoc_deli);
		else if ((v->line)[*index_start + j] == '\'')
			*ret = single_quote_case(v->line, index_start, &j, *ret);
		else
			j++;
		if (!(*ret))
			return (NULL);
	}
	*ret = join_s1_with_sub_s2(*ret, v->line, *index_start, j);
	*index_start += j;
	return (*ret);
}
