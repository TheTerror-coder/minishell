/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_expand_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:23:24 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/30 14:50:07 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	test_one_expand_null(t_vars *v, size_t l_index);

size_t	test_expand_null_content(t_vars *v, size_t l_index, int is_hdoc_deli)
{
	size_t	j;

	if (is_hdoc_deli)
		return (0);
	if (is_whitespace_or_operator_or_nul((v->line)[l_index]))
		return (0);
	while (!is_whitespace_or_operator_or_nul((v->line)[l_index]))
	{
		j = test_one_expand_null(v, l_index);
		if (!j)
			return (0);
		l_index += j;
	}
	return (l_index);
}

size_t	test_one_expand_null(t_vars *v, size_t l_index)
{
	size_t	j;
	char	*expand_name;

	if ((v->line)[l_index] != '$')
		return (0);
	if ((v->line)[l_index + 1] != '_' && !ft_isalpha((v->line)[l_index + 1]))
		return (0);
	j = 1;
	while (ft_isalnum((v->line)[l_index + j]) || (v->line)[l_index + j] == '_')
		j++;
	expand_name = ft_substr((v->line), l_index + 1, j - 1);
	if (!expand_name)
	{
		v->flg_parsing_is_ok = __FALSE;
		return (ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR), 0);
	}
	if (check_env_var_set(v->my_env, expand_name))
		return (free(expand_name), 0);
	free(expand_name);
	return (j);
}
