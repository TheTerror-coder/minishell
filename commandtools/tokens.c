/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/01 10:54:27 by lmohin           ###   ########.fr       */
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

	v->token_buffer = NULL;
	is_hdoc_deli = __FALSE;
	token = get_first_token(v, &l_index, &is_hdoc_deli);
	if (!token)
		return (NULL);
	init_token = token;
	while ((v->line)[l_index] != '\0' || v->token_buffer)
	{
		while (is_whitespace((v->line)[l_index]))
			l_index++;
		if ((v->line)[l_index] == '\0' && !v->token_buffer)
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

	expand_in_hdoc = ((v->line)[*l_index] != '"' \
			&& (v->line)[*l_index] != '\'' && is_hdoc_deli == __TRUE);
	type = ((v->line)[*l_index] == '|' || (v->line)[*l_index] == '<' \
			|| (v->line)[*l_index] == '>');
	content = get_token_content(v, l_index, is_hdoc_deli);
	if (!v->flg_parsing_is_ok)
		return (NULL);
	return (create_token(v, content, type, expand_in_hdoc));
}

char	*get_word_after_token_buffer(t_vars *v, size_t *l_index, char *ret)
{
	char	*word;
	char	*join;

	word = get_word(v, l_index, 0);
	if (!word)
		v->flg_parsing_is_ok = __FALSE;
	if (!ret)
		return (word);
	join = ft_strjoin(ret, word);
	if (!join)
	{
		ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
	}
	free(word);
	free(ret);
	return (join);
}

char	*treat_token_buffer(t_vars *v, size_t *l_index, char *ret)
{
	size_t	expand_nbr;

	if (v->line[*l_index] == '\0')
		return (ret);
	expand_nbr = test_expand_null_content(v, *l_index, 0);
	if (v->flg_parsing_is_ok == __FALSE)
		return (NULL);
	if (expand_nbr)
	{
		*l_index = expand_nbr;
		return (ret);
	}
	if ((v->line)[*l_index] == '|' \
		|| (v->line)[*l_index] == '<' || (v->line)[*l_index] == '>')
		return (ret);
	else
		return (get_word_after_token_buffer(v, l_index, ret));
}

char	*prepare_next_expand_token(t_vars *v, size_t i)
{
	char	*ret;

	ret = ft_substr(v->token_buffer, 0, i);
	if (!ret)
	{
		ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
		return (free(v->token_buffer), NULL);
	}
	while (is_whitespace(v->token_buffer[i]))
		i++;
	v->token_buffer = get_end_expand_content(v, v->token_buffer, i);
	if (!v->token_buffer)
		return (free(ret), NULL);
	return (ret);
}

char	*clear_token_buffer(t_vars *v, size_t *l_index)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (!is_whitespace(v->token_buffer[i]) && v->token_buffer[i] != '\0')
		i++;
	if (v->token_buffer[i] == '\0')
	{
		ret = v->token_buffer;
		if (v->token_buffer[0] == '\0')
		{
			free(v->token_buffer);
			ret = NULL;
		}
		v->token_buffer = NULL;
		return (treat_token_buffer(v, l_index, ret));
	}
	else
		return (prepare_next_expand_token(v, i));
}

char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	size_t	expand_nbr;
	char	*content;

	content = NULL;
	v->flg_parsing_is_ok = __TRUE;
	if (v->token_buffer)
		return (clear_token_buffer(v, l_index));
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

t_token	*allocate_token(t_vars *v, char *content, int type, int expand_in_hdoc)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		ft_leave(v, EXIT_FAILURE, "minishell: malloc", __PERROR);
		v->flg_parsing_is_ok = __FALSE;
		return (NULL);
	}
	token->content = content;
	token->type = type;
	token->expand_in_hdoc = expand_in_hdoc;
	token->next = NULL;
	return (token);
}

t_token	*create_token(t_vars *v, char *content, int type, int expand_in_hdoc)
{
	t_token	*token;

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
