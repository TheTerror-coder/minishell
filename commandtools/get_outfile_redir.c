/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/27 01:32:05 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_outfile_redir(char next_char);

char	*get_outfile_redir(char *line, size_t *l_index)
{
	size_t	j;
	char	*outfile_redir;

	if (check_operator_after_outfile_redir(line[*l_index + 1]))
		return (NULL);
	j = 1;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		ft_putstr_fd("minishell: syntax error: missing outfile after \">\"\n", 2);
		exitstatus = 2;
		return (NULL);
	}
	(*l_index) += 1;
	outfile_redir = ft_strdup(">");
	if (!outfile_redir)
	{
		exitstatus = 1;
		perror("minishell: get_outfile_redir: ");
	}
	return (outfile_redir);
}

int	check_operator_after_outfile_redir(char next_char)
{
	if (next_char == '<')
	{
		ft_putstr_fd("minishell: syntax error: >< detected\n", 2);
		exitstatus = 2;
		return (1);
	}
	if (next_char == '|')
	{
		ft_putstr_fd("minishell: syntax error: >| detected\n", 2);
		exitstatus = 2;
		return (1);
	}
	return (0);
}
