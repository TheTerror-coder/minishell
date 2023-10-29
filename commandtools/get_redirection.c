/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:58:39 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/29 21:23:37 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redirection(t_vars *v, char *line, size_t *l_index)
{
	if (line[*l_index] == '<' && line[*l_index + 1] == '<')
		return (get_heredoc(v, line, l_index));
	if (line[*l_index] == '<')
		return (get_infile_redir(v, line, l_index));
	if (line[*l_index] == '>' && line[*l_index + 1] == '>')
		return (get_outfile_append_redir(v, line, l_index));
	if (line[*l_index] == '>')
		return (get_outfile_redir(v, line, l_index));
	return (NULL);
}
