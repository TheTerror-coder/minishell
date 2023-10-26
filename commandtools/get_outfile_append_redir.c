/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile_append_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 23:38:09 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_outfile_append_redir(char next_char);

char	*get_outfile_append_redir(char *line, size_t *l_index)
{
	size_t	j;
	char	*outfile_append_redir;

	if (check_operator_after_outfile_append_redir(line[*l_index + 2]))
		return (NULL);
	j = 2;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		printf("minishell: syntax error: missing outfile after \">>\"\n");
		exitstatus = 2;
		return (NULL);
	}
	(*l_index) += 2;
	outfile_append_redir = ft_strdup(">>");
	if (!outfile_append_redir)
	{
		exitstatus = 2;
		perror("minishell: get_outfile_append_redir: ");
	}
	return (outfile_append_redir);
}

int	check_operator_after_outfile_append_redir(char next_char)
{
	if (next_char == '<')
	{
		printf("minishell: syntax error: >>< detected\n");
		exitstatus = 2;
		return (1);
	}
	if (next_char == '>')
	{
		printf("minishell: syntax error: >>> detected\n");
		exitstatus = 2;
		return (1);
	}
	if (next_char == '|')
	{
		printf("minishell: syntax error: >>| detected\n");
		exitstatus = 2;
		return (1);
	}
	return (0);
}
