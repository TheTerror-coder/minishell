/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:36:31 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/27 00:35:07 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expand_content(t_vars *v, char *expand_name, char *ret)
{
	char	*cpy;
	char	*expand_content;

	expand_content = check_env_var_set(v, expand_name);
	if (!expand_content)
	{
		free(expand_name);
		return (ret);
	}
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	if (!ret)
	{
		exitstatus = 1;
		perror("minishell: expand_case: ");
	}
	free(cpy);
	free(expand_content);
	free(expand_name);
	return (ret);
}

char	*expand_exit_status(size_t *i, size_t *j, char *ret)
{
	char	*expand_number;
	char	*cpy;

	*i += 2;
	*j = 0;
	expand_number = ft_itoa(exitstatus);
	if (!expand_number)
	{
		exitstatus = 1;
		perror("minishell: expand_case: ");
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, expand_number);
	free(expand_number);
	free(cpy);
	if (!ret)
	{
		exitstatus = 1;
		perror("minishell: expand_case: ");
	}
	return (ret);
}

char	*expand_case(size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;

	ret = join_s1_with_sub_s2(ret, v->line, i, j);
	if (!ret)
		return (NULL);
	if ((v->line)[*i + *j + 1] == '?')
		return (expand_exit_status(i, j, ret));
	*i += 1;
	if (((v->line)[*i + *j] <= '9' && (v->line)[*i + *j] >= '0') \
		|| (v->line)[*i + *j] == '\'' || (v->line)[*i + *j] == '"')
		return (ret);
	while (ft_isalnum((v->line)[*i + *j]))
		(*j)++;
	expand_name = ft_substr((v->line), *i, *j);
	if (!expand_name)
	{
		perror("minishell: expand_case: ");
		exitstatus = 1;
		free(ret);
		return (NULL);
	}
	*i += *j;
	*j = 0;
	return (get_expand_content(v, expand_name, ret));
}

char	*double_quote_case(size_t *i, char *ret, t_vars *v, int heredoc)
{
	size_t	j;

	j = 0;
	while ((v->line)[*i + j] != '"' && (v->line)[*i + j] != '\0')
	{
		if ((v->line)[*i + j] == '$' && v->line[*i + j + 1] != '"'\
			&& v->line[*i + j + 1] != '\'' \
			&& expand_conditions((v->line)[*i + j + 1], heredoc))
		{
			ret = expand_case(i, &j, ret, v);
			if (!ret)
				return (NULL);
		}
		else
			j++;
	}
	if ((v->line)[*i + j] != '"')
	{
		printf("minishell: syntax error: unclosed quote\n");
		exitstatus = 2;
		free(ret);
		return (NULL);
	}
	ret = join_s1_with_sub_s2(ret, v->line, i, &j);
	*i += 1;
	return (ret);
}

char	*single_quote_case(char *input, size_t *i, size_t *j, char *ret)
{
	ret = join_s1_with_sub_s2(ret, input, i, j);
	if (!ret)
		return (NULL);
	*i += 1;
	while (input[*i + *j] != '\'' && input[*i + *j] != '\0')
		(*j)++;
	if (input[*i + *j] != '\'')
	{
		printf("minishell: syntax error: unclosed quote\n");
		free(ret);
		exitstatus = 2;
		return (NULL);
	}
	ret = join_s1_with_sub_s2(ret, input, i, j);
	*i += 1;
	return (ret);
}

int	get_word(t_vars *v, size_t *index_start, int is_hdoc_deli, char **ret)
{
	size_t	j;

	j = 0;
	while (!is_whitespace_or_operator_or_nul((v->line)[*index_start + j]))
	{
		if ((v->line)[*index_start + j] == '$' \
			&& expand_conditions((v->line)[*index_start + j + 1], is_hdoc_deli))
			*ret = expand_case(index_start, &j, *ret, v);
		else if ((v->line)[*index_start + j] == '"')
		{
			*ret = join_s1_with_sub_s2(*ret, v->line, index_start, &j);
			if (!(*ret))
				return (__FALSE);
			*index_start += 1;
			*ret = double_quote_case(index_start, *ret, v, is_hdoc_deli);
		}
		else if ((v->line)[*index_start + j] == '\'')
			*ret = single_quote_case(v->line, index_start, &j, *ret);
		else
			j++;
		if (!(*ret) && j == 0)
			return (__FALSE);
	}
	*ret = join_s1_with_sub_s2(*ret, v->line, index_start, &j);
	return (__TRUE);
}
