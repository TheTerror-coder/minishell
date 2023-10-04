/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:58:39 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/05 00:02:58 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redirection(char *line, size_t *l_index)
{
	if (line[*l_index] == '<' && line[*l_index + 1] == '<')
		return (get_heredoc(line, l_index));
	if (line[*l_index] == '<')
		return (get_infile_redir(line, l_index));
	if (line[*l_index] == '>' && line[*l_index + 1] == '>')
		return (get_outfile_append_redir(line, l_index));
	if (line[*l_index] == '>')
		return (get_outfile_redir(line, l_index));
	return (NULL);
}
