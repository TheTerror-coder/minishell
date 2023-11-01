/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:36:24 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/01 10:52:35 by lmohin           ###   ########.fr       */
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

char	*get_expand_content(t_vars *v, char *expand_name, char *ret)
{
	char	*expand_content;

	if (!check_env_var_set(v->my_env, expand_name))
		return (free(expand_name), ret);
	expand_content = get_env_var_content(v, v->my_env, expand_name);
	free(expand_name);
	if (!expand_content)
		return (free(ret), NULL);
	return (clear_expand_content(v, expand_content, ret));
}

char	*expand_exit_status(t_vars *v, size_t *i, size_t *j, char *ret)
{
	char	*expand_number;
	char	*cpy;

	*i += 2;
	*j = 0;
	expand_number = ft_itoa(v->exitstatus);
	if (!expand_number)
		return (ft_leave(v, EXIT_FAILURE, "ft_itoa", __PERROR), NULL);
	cpy = ret;
	ret = ft_strjoin(ret, expand_number);
	free(expand_number);
	free(cpy);
	if (!ret)
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
	return (ret);
}

char	*expand_case(size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;

	ret = join_s1_with_sub_line(ret, v, i, j);
	if (!ret)
		return (NULL);
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
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		return (free(ret), NULL);
	}
	*i += *j;
	*j = 0;
	return (get_expand_content(v, expand_name, ret));
}

char	*get_expand_content_quote(t_vars *v, char *expand_name, char *ret)
{
	char	*cpy;
	char	*expand_content;

	if (!check_env_var_set(v->my_env, expand_name))
		return (free(expand_name), ret);
	expand_content = get_env_var_content(v, v->my_env, expand_name);
	if (!expand_content)
	{
		free(expand_name);
		free(ret);
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	if (!ret)
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
	free(cpy);
	free(expand_content);
	free(expand_name);
	return (ret);
}

char	*expand_case_double_quote(size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;

	ret = join_s1_with_sub_line(ret, v, i, j);
	if (!ret)
		return (NULL);
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
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		return (free(ret), NULL);
	}
	*i += *j;
	*j = 0;
	return (get_expand_content_quote(v, expand_name, ret));
}
