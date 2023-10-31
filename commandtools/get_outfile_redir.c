/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/31 15:34:00 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_operator_after_outfile_redir(t_vars *v, char next_char);

char	*get_outfile_redir(t_vars *v, char *line, size_t *l_index)
{
	size_t	j;
	char	*outfile_redir;

	if (check_operator_after_outfile_redir(v, line[*l_index + 1]))
		return (NULL);
	j = 1;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error: missing outfile after \">\"\n", 2);
		v->exitstatus = 2;
		return (NULL);
	}
	(*l_index) += 1;
	outfile_redir = ft_strdup(">");
	if (!outfile_redir)
		ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
	return (outfile_redir);
}

t_bool	check_operator_after_outfile_redir(t_vars *v, char next_char)
{
	if (next_char == '<')
	{
		ft_putstr_fd("minishell: syntax error: >< detected\n", 2);
		v->exitstatus = 2;
		return (__TRUE);
	}
	if (next_char == '|')
	{
		ft_putstr_fd("minishell: syntax error: >| detected\n", 2);
		v->exitstatus = 2;
		return (__TRUE);
	}
	return (__FALSE);
}
