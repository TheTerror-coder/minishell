/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/01 00:38:41 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_first_token(t_vars *v, size_t *l_index, int *is_hdoc_deli);
t_token	*get_one_token(t_vars *v, size_t *l_index, int is_hdoc_deli);
t_token	*create_token(t_vars *v, char *content, int type, int expand_in_hdoc);
char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli);

t_token	*break_input_into_tokens(t_vars *v, size_t l_index)
{
	t_token	*token;
	t_token	*init_token;
	int		is_hdoc_deli;

	is_hdoc_deli = __FALSE;
	token = get_first_token(v, &l_index, &is_hdoc_deli);
	if (!token)
		return (NULL);
	init_token = token;
	while ((v->line)[l_index] != '\0')
	{
		while (is_whitespace((v->line)[l_index]))
			l_index++;
		if ((v->line)[l_index] == '\0')
			return (init_token);
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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		v->exitstatus = 2;
		free(init_token->content);
		free(init_token);
		v->flg_parsing_is_ok = __FALSE;
		return (NULL);
	}
	return (init_token);
}

t_token	*get_one_token(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	int		type;
	int		expand_in_hdoc;
	char	*content;

	v->expand_start = 0;
	v->expand_end = 0;
	expand_in_hdoc = ((v->line)[*l_index] != '"' \
			&& (v->line)[*l_index] != '\'' && is_hdoc_deli == __TRUE);
	type = ((v->line)[*l_index] == '|' || (v->line)[*l_index] == '<' \
			|| (v->line)[*l_index] == '>');
	content = get_token_content(v, l_index, is_hdoc_deli);
	if (!v->flg_parsing_is_ok)
		return (NULL);
	return (create_token(v, content, type, expand_in_hdoc));
}

char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	size_t	expand_nbr;
	char	*content;

	v->flg_parsing_is_ok = __TRUE;
	expand_nbr = test_expand_null_content(v, *l_index, is_hdoc_deli);
	if (v->flg_parsing_is_ok == __FALSE)
		return (NULL);
	if (expand_nbr)
	{
		*l_index = expand_nbr;
		return (NULL);
	}
	if ((v->line)[*l_index] == '|')
		content = get_pipe(v, v->line, l_index);
	else if ((v->line)[*l_index] == '<' || (v->line)[*l_index] == '>')
		content = get_redirection(v, v->line, l_index);
	else
		content = get_word(v, l_index, is_hdoc_deli);
	if (!content)
		v->flg_parsing_is_ok = __FALSE;
	return (content);
}

t_token	*allocate_token(t_vars *v)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_leave(v, EXIT_FAILURE, "minishell: malloc", __PERROR);
	return (token);
}

t_token	*split_in_expand(t_vars *v, char *content)
{
	char	*expand_content;
	char	*new_content;
	size_t	i;

	expand_content = ft_substr(content, v->expand_start, v->expand_end);
	i = 0;
	while (expand_content[i])	
	{
		if (is_whitespace(expand_content[i]))
		{
			new_content = ft_substr(content, 0, v->expand_start + i);
			ft_putstr_fd(new_content, 2);
			return (0);
		}
		i++;
	}
	return (NULL);
}

t_token	*create_token(t_vars *v, char *content, int type, int expand_in_hdoc)
{
	t_token	*token;

	if (v->expand_start != v->expand_end)
	
		/*return*/ (split_in_expand(v, content));
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(content);
		v->exitstatus = 1;
		return (NULL);
	}
	token->content = content;
	token->type = type;
	token->expand_in_hdoc = expand_in_hdoc;
	token->next = NULL;
	return (token);
}
