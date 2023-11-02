/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parsing0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:36:24 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 15:39:30 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clear_expand_content(t_vars *v, char *expand_content, char *ret);

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
