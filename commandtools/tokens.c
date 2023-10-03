/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 01:30:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *content, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token *get_one_token(t_vars *v, size_t *i, int heredoc)
{
	int	type;
	char	*s;
	t_token	*token;

	while (is_whitespace((v->line)[*i]))
		(*i)++;
	if ((v->line)[*i] == '\0')
		return (NULL);
	type = 0;
	s = get_operator_or_word(i, &type, v, heredoc);
	if (!s)
		return (NULL);
	token = create_token(s, type);
	return (token);
}

t_token	*get_first_token(t_vars *v, size_t *i, int *heredoc)
{
	t_token	*init_token;

	init_token = get_one_token(v, i, *heredoc);
	if (!init_token)
		return (NULL);
	*heredoc = ((init_token->type == 1) && !ft_strncmp(init_token->content, "<<", 3));
	return (init_token);
}

int	get_other_tokens(t_vars *v, size_t i, int heredoc, t_token *token)
{
	while ((v->line)[i] != '\0')
	{
		token->next = get_one_token(v, &i, heredoc);
		if (!(token->next))
			return (0);
		heredoc = (token->next->type == 1 && !ft_strncmp(token->next->content, "<<", 3));
		token = token->next;
	}
	return (1);
}	

t_token	*break_input_into_token(t_vars *v)
{
	t_token	*token;
	t_token	*init_token;
	size_t	i;
	int	heredoc;

	heredoc = 0;
	i = 0;
	token = get_first_token(v, &i, &heredoc);
	if (!token)
		return (NULL);
	init_token = token;
	get_other_tokens(v, i, heredoc, token);
	return (init_token);
}
