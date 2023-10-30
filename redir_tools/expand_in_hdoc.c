/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:43:07 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/30 15:34:02 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit_status_hdoc(t_vars *v, char *line, size_t *start_index);
char	*expand_word_inside_line(t_vars *v, char *line, size_t *start_index);
char	*first_join(t_vars *v, char *line, char *expand_content, \
						size_t start_index);
char	*second_join(t_vars *v, char *line, char *ret, size_t end_index);

char	*expand_words_of_line(t_vars *v, char *line)
{
	char	*linedup;
	size_t	l_index;

	linedup = NULL;
	l_index = 0;
	while (line && line[l_index] != '\0')
	{
		linedup = line;
		if (expand_conditions(line + l_index, __FALSE))
		{
			if (line[l_index + 1] == '?')
				line = expand_exit_status_hdoc(v, line, &l_index);
			else
				line = expand_word_inside_line(v, line, &l_index);
			ft_freestr(&linedup);
			if (!line)
				return (NULL);
		}
		else
			l_index++;
	}
	return (line);
}

char	*expand_exit_status_hdoc(t_vars *v, char *line, size_t *start_index)
{
	char	*expand_number;
	char	*ret;

	expand_number = NULL;
	expand_number = ft_itoa(v->exitstatus);
	if (!expand_number)
		return (ft_leave(v, EXIT_FAILURE, "expand_exit_status_hdoc(): ft_itoa() failed", __PRINT), NULL);
	ret = first_join(v, line, expand_number, *start_index);
	ret = second_join(v, line, ret, *start_index + 2);
	ft_freestr(&expand_number);
	return (ret);
}

char	*expand_word_inside_line(t_vars *v, char *line, size_t *start_index)
{
	char	*expand_name;
	char	*expand_content;
	char	*ret;
	size_t	j;

	if (line[*start_index + 1] <= '9' && line[*start_index + 1] >= '0')
		return (*start_index += 1, line);
	j = 0;
	while (ft_isalnum(line[*start_index + 1 + j]))
		j++;
	expand_name = ft_substr(line, *start_index + 1, j);
	if (!expand_name)
		return (ft_leave(v, EXIT_FAILURE, \
				"expand_word_inside_line(): ft_substr() failed", __PRINT), NULL);
	if (!check_env_var_set(v->my_env, expand_name))
		return (NULL);
	expand_content = get_env_var_content(v, v->my_env, expand_name);
	ft_freestr(&expand_name);
	if (!expand_content)
		return (NULL);
	ret = first_join(v, line, expand_content, *start_index);
	ret = second_join(v, line, ret, *start_index + 1 + j);
	if (expand_content)
		*start_index += ft_strlen(expand_content);
	free(expand_content);
	return (ret);
}

char	*first_join(t_vars *v, char *line, char *expand_content, size_t start_index)
{
	char	*ret;
	char	*cpy;

	if (!expand_content)
		return (NULL);
	ret = ft_substr(line, 0, start_index);
	if (!ret)
		return (ft_leave(v, EXIT_FAILURE, "first_join(): ft_substr() failed", \
				__PRINT), NULL);
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	ft_freestr(&cpy);
	if (!ret)
		return (ft_leave(v, EXIT_FAILURE, "first_join(): ft_strjoin() failed", __PRINT), NULL);
	return (ret);
}

char	*second_join(t_vars *v, char *line, char *ret, size_t end_index)
{
	char	*sub;
	char	*cpy;

	if (!ret)
		return (NULL);
	sub = ft_substr(line, end_index, ft_strlen(line));
	if (!sub)
		return (free(ret), \
		ft_leave(v, EXIT_FAILURE, "second_join(): ft_substr() failed", __PRINT), \
		NULL);
	cpy = ret;
	ret = ft_strjoin(ret, sub);
	if (!ret)
		ft_leave(v, EXIT_FAILURE, "second_join(): ft_strjoin() failed", __PRINT);
	free(cpy);
	free(sub);
	return (ret);
}
