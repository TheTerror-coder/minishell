/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:43:07 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/21 18:47:56 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit_status_hdoc(char *line, size_t *start_index);
char	*expand_word_inside_line(t_vars *v, char *line, size_t *start_index);
char	*first_join(char *line, char *expand_content, size_t start_index);
char	*second_join(char *line, char *ret, size_t end_index);

char	*expand_words_of_line(t_vars *v, char *line)
{
	char	*linedup;
	size_t	l_index;

	linedup = NULL;
	l_index = 0;
	while (line && line[l_index] != '\0')
	{
		linedup = line;
		if (line[l_index] == '$' \
				&& expand_conditions(line[l_index + 1], __FALSE))
		{
			if (line[l_index + 1] == '?')
				line = expand_exit_status_hdoc(line, &l_index);
			else
				line = expand_word_inside_line(v, line, &l_index);
			if (!line)
				return (ft_freestr(&linedup), NULL);
		}
		else
			l_index++;
	}
	return (line);
}

char	*expand_exit_status_hdoc(char *line, size_t *start_index)
{
	char	*expand_number;
	char	*ret;

	expand_number = NULL;
	expand_number = ft_itoa(exitstatus);
	if (!expand_number)
		return (ft_leave(EXIT_FAILURE, "expand_exit_status_hdoc(): ft_itoa() failed", __PRINT), NULL);
	ret = first_join(line, expand_number, *start_index);
	ret = second_join(line, ret, *start_index + 2);
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
		return (ft_leave(EXIT_FAILURE, \
				"expand_word_inside_line(): ft_substr() failed", __PRINT), NULL);
	expand_content = check_env_var_set(v, expand_name);
	if (!expand_content)
		return (ft_freestr(&expand_name), NULL);
	ret = first_join(line, expand_content, *start_index);
	ret = second_join(line, ret, *start_index + 1 + j);
	if (expand_content)
		*start_index += ft_strlen(expand_content);
	free(expand_content);
	return (ret);
}

char	*first_join(char *line, char *expand_content, size_t start_index)
{
	char	*ret;
	char	*cpy;

	if (!expand_content)
		return (NULL);
	ret = ft_substr(line, 0, start_index);
	if (!ret)
		return (ft_leave(EXIT_FAILURE, "first_join(): ft_substr() failed", \
				__PRINT), NULL);
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	ft_freestr(&cpy);
	if (!ret)
		return (ft_leave(EXIT_FAILURE, "first_join(): ft_strjoin() failed", __PRINT), NULL);
	return (ret);
}

char	*second_join(char *line, char *ret, size_t end_index)
{
	char	*sub;
	char	*cpy;

	if (!ret)
		return (NULL);
	sub = ft_substr(line, end_index, ft_strlen(line));
	if (!sub)
		return (free(ret), \
		ft_leave(EXIT_FAILURE, "second_join(): ft_substr() failed", __PRINT), \
		NULL);
	cpy = ret;
	ret = ft_strjoin(ret, sub);
	if (!ret)
		ft_leave(EXIT_FAILURE, "second_join(): ft_strjoin() failed", __PRINT);
	free(cpy);
	free(sub);
	return (ret);
}