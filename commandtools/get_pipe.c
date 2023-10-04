/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:18:18 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 06:06:13 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_pipe(char next_char)
{
	if (next_char == '<')
	{
		printf("minishell: syntax error: |< detected\n");
		return (1);
	}
	if (next_char == '>')
	{
		printf("minishell: syntax error: |> detected\n");
		return (1);
	}
	if (next_char == '|')
	{
		printf("minishell: syntax error: || detected\n");
		return (1);
	}
	return (0);
}

char	*get_pipe(char *line, size_t *l_index)
{
	size_t	j;

	if (check_operator_after_pipe(line[*l_index + 1]))
		return (NULL);
	j = 1;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0')
	{
		printf("minishell: syntax error: unclosed pipe detected\n");
		return (NULL);
	}
	return (ft_strdup("|"));
}
