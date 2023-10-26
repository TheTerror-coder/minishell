/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 23:26:59 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_first_token(t_vars *v, size_t *l_index, int *is_hdoc_deli);
t_token	*get_one_token(t_vars *v, size_t *l_index, int is_hdoc_deli);
t_token	*create_token(char *content, int type, int expand_in_hdoc);
char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli);

t_token	*break_input_into_tokens(t_vars *v)
{
	t_token	*token;
	t_token	*init_token;
	size_t	l_index;
	int		is_hdoc_deli;

	is_hdoc_deli = __FALSE;
	l_index = 0;
	token = get_first_token(v, &l_index, &is_hdoc_deli);
	if (!token)
		return (NULL);
	init_token = token;
	while ((v->line)[l_index] != '\0')
	{
		token->next = get_one_token(v, &l_index, is_hdoc_deli);
		if (!(token->next))
			return (init_token);
		is_hdoc_deli = (token->next->type == 1 && \
				!ft_strncmp(token->next->content, "<<", 3));
		token = token->next;
	}
	return (init_token);
}

t_token	*get_first_token(t_vars *v, size_t *l_index, int *is_hdoc_deli)
{
	t_token	*init_token;

	init_token = get_one_token(v, l_index, *is_hdoc_deli);
	if (!init_token)
		return (NULL);
	if ((init_token->type == 1) && !ft_strncmp(init_token->content, "<<", 3))
		*is_hdoc_deli = 1;
	if ((init_token->type == 1) && !ft_strncmp(init_token->content, "|", 2))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		exitstatus = 2;
		free(init_token->content);
		free(init_token);
		v->flg_parsing_is_ok = __FALSE;
		return (NULL);
	}
	return (init_token);
}

t_token	*create_token(char *content, int type, int expand_in_hdoc)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(content);
		exitstatus = 1;
		return (NULL);
	}
	token->content = content;
	token->type = type;
	token->expand_in_hdoc = expand_in_hdoc;
	token->next = NULL;
	return (token);
}

t_token	*get_one_token(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	int		type;
	int		expand_in_hdoc;
	char	*content;
	t_token	*token;

	while (is_whitespace((v->line)[*l_index]))
		(*l_index)++;
	expand_in_hdoc = ((v->line)[*l_index] != '"' \
			&& (v->line)[*l_index] != '\'' && is_hdoc_deli == __TRUE);
	if ((v->line)[*l_index] == '\0')
		return (NULL);
	if ((v->line)[*l_index] == '|' || (v->line)[*l_index] == '<' \
			|| (v->line)[*l_index] == '>')
		type = 1;
	else
		type = 0;
	content = get_token_content(v, l_index, is_hdoc_deli);
	if (!content)
	{
		v->flg_parsing_is_ok = __FALSE;
		return (NULL);
	}
	token = create_token(content, type, expand_in_hdoc);
	if (!token)
		v->flg_parsing_is_ok = __FALSE;
	return (token);
}

char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	char	*content;
	char	*word;

	if ((v->line)[*l_index] == '|')
	{
		content = get_pipe(v->line, l_index);
		(*l_index)++;
		return (content);
	}
	if ((v->line)[*l_index] == '<' || (v->line)[*l_index] == '>')
		return (get_redirection(v->line, l_index));
	word = NULL;
	if (!get_word(v, l_index, is_hdoc_deli, &word))
		return (NULL);
	return (word);
}
