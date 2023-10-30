/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:36:31 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/30 15:19:35 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expand_content(t_vars *v, char *expand_name, char *ret)
{
	char	*cpy;
	char	*expand_content;

	if (!check_env_var_set(v->my_env, expand_name))
		return (free(expand_name), ret);
	expand_content = get_env_var_content(v, v->my_env, expand_name);
	if (!expand_content)
	{
		free(expand_name);
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	if (!ret)
	{
		v->exitstatus = 1;
		perror("minishell: expand_case: ");
	}
	free(cpy);
	free(expand_content);
	free(expand_name);
	return (ret);
}

char	*expand_exit_status(t_vars *v, size_t *i, size_t *j, char *ret)
{
	char	*expand_number;
	char	*cpy;

	*i += 2;
	*j = 0;
	expand_number = ft_itoa(v->exitstatus);
	if (!expand_number)
	{
		v->exitstatus = 1;
		perror("minishell: expand_case: ");
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, expand_number);
	free(expand_number);
	free(cpy);
	if (!ret)
	{
		v->exitstatus = 1;
		perror("minishell: expand_case: ");
	}
	return (ret);
}

char	*expand_case(size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;

	ret = join_s1_with_sub_s2(ret, v->line, i, j);
	if (!ret)
		return (v->exitstatus = EXIT_FAILURE, NULL);
	if ((v->line)[*i + *j + 1] == '?')
		return (expand_exit_status(v, i, j, ret));
	*i += 1;
	if (((v->line)[*i + *j] <= '9' && (v->line)[*i + *j] >= '0') \
		|| (v->line)[*i + *j] == '\'' || (v->line)[*i + *j] == '"')
		return (ret);
	while (ft_isalnum((v->line)[*i + *j]) || (v->line)[*i + *j] == '_')
		(*j)++;
	expand_name = ft_substr((v->line), *i, *j);
	if (!expand_name)
	{
		perror("minishell: expand_case: ");
		v->exitstatus = 1;
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
		if (expand_conditions((v->line)[*i + j], (v->line)[*i + j + 1], heredoc) && v->line[*i + j + 1] != '"'\
			&& v->line[*i + j + 1] != '\'')
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
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		v->exitstatus = 2;
		free(ret);
		return (NULL);
	}
	ret = join_s1_with_sub_s2(ret, v->line, i, &j);
	if (!ret)
		v->exitstatus = EXIT_FAILURE;
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
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		free(ret);
		return (NULL);
	}
	ret = join_s1_with_sub_s2(ret, input, i, j);
	*i += 1;
	return (ret);
}

char	*get_word(t_vars *v, size_t *index_start, int is_hdoc_deli)
{
	size_t	j;
	char	*ret;

	ret = NULL;
	j = 0;
	while (!is_whitespace_or_operator_or_nul((v->line)[*index_start + j]))
	{
		if (expand_conditions((v->line)[*index_start + j], (v->line)[*index_start + j + 1], is_hdoc_deli))
			ret = expand_case(index_start, &j, ret, v);
		else if ((v->line)[*index_start + j] == '"')
		{
			ret = join_s1_with_sub_s2(ret, v->line, index_start, &j);
			if (!ret)
				return (v->exitstatus = EXIT_FAILURE, NULL);
			*index_start += 1;
			ret = double_quote_case(index_start, ret, v, is_hdoc_deli);
		}
		else if ((v->line)[*index_start + j] == '\'')
			ret = single_quote_case(v->line, index_start, &j, ret);
		else
			j++;
		if (!ret && j == 0)
			return (v->exitstatus = __BUILTIN_ERROR, NULL);	
	}
	ret = join_s1_with_sub_s2(ret, v->line, index_start, &j);
	if (!ret)
		v->exitstatus = EXIT_FAILURE;
	return (ret);
}
