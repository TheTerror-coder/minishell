/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:18:18 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 16:28:18 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_pipe(t_vars *v, char next_char);

char	*get_pipe(t_vars *v, char *line, size_t *l_index)
{
	size_t	j;
	char	*pipe;

	if (check_operator_after_pipe(v, line[*l_index + 1]))
		return (NULL);
	j = 1;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		v->exitstatus = 2;
		return (NULL);
	}
	pipe = ft_strdup("|");
	if (!pipe)
		ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
	*l_index += 1;
	return (pipe);
}

int	check_operator_after_pipe(t_vars *v, char next_char)
{
	if (next_char == '|')
	{
		ft_putstr_fd("minishell: syntax error: || detected\n", 2);
		v->exitstatus = 2;
		return (__TRUE);
	}
	return (__FALSE);
}
