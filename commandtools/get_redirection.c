/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:58:39 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 06:16:07 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_heredoc(char *line, size_t *l_index);

char	*get_redirection(char *line, size_t *l_index)
{
	if (line[*l_index] == '<' && line[*l_index + 1] == '<')
		return (get_heredoc(line, l_index));
	if (line[*l_index] == '<')
	{
		if (line[*l_index + 1] == '>' || line[*l_index + 1] == '|')
		{
			printf("parsing error");
			exit(0);
		}
		(*l_index)++;
		return (ft_strdup("<"));
	}
	if (line[*l_index] == '>' && line[*l_index + 1] == '>')
	{
		if (line[*l_index + 2] == '>' || line[*l_index + 2] == '<' || line[*l_index + 2] == '|')
		{
			printf("parsing error");
			return (NULL);
		}
		(*l_index) += 2;
		return (ft_strdup(">>"));
	}
	if (line[*l_index + 1] == '<' || line[*l_index + 1] == '|')
	{
		printf("parsing error");
		return (NULL);
	}
	(*l_index)++;
	return (ft_strdup(">"));
}

char	*get_heredoc(char *line, size_t *l_index)
{
	if (line[*l_index + 2] == '<')
	{
		printf("minishell: parsing error: <<< detected\n");
		return (NULL);
	}
	if (line[*l_index + 2] == '>')
	{
		printf("minishell: parsing error: <<> detected\n");
		return (NULL);
	}
	if (line[*l_index + 2] == '|')
	{
		printf("minishell: parsing error: <<| detected\n");
		return (NULL);
	}
	(*l_index) += 2;
	return (ft_strdup("<<"));
/*
	check next character is not < > | or \0
*/
}
