/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/27 06:13:32 by lmohin           ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
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
	if (!content && !v->flg_var_is_null)
	{
		v->flg_parsing_is_ok = __FALSE;
		return (NULL);
	}
	token = create_token(content, type, expand_in_hdoc);
	if (!token)
		v->flg_parsing_is_ok = __FALSE;
	return (token);
}

size_t	test_expand_null_content(t_vars *v, size_t l_index, int is_hdoc_deli)
{
	size_t	j;
	char	*expand_name;
	char	*env_var;

	if (is_hdoc_deli)
		return (0);
	j = 0;
	while (!(is_whitespace((v->line)[l_index])) && (v->line)[l_index] != '\0')
	{
		if ((v->line)[l_index] != '$')
			return (0);
		j = 1;
		if ((v->line)[l_index + j] != '_' && !ft_isalpha((v->line)[l_index + j]))
			return (0);
		while (ft_isalnum((v->line)[l_index + j]) || (v->line)[l_index + j] == '_')
			j++;
		expand_name = ft_substr((v->line), l_index + 1, j - 1);
		if (!expand_name)
			return (0);
		env_var = check_env_var_set(v, expand_name);
		free(expand_name);
		if (env_var)
		{
			free(env_var);
			return (0);
		}
		l_index += j;
	}
	return (l_index);
}

char	*get_token_content(t_vars *v, size_t *l_index, int is_hdoc_deli)
{
	char	*content;
	char	*word;
	size_t	expand_nbr;

	v->flg_var_is_null = __FALSE;
	expand_nbr = test_expand_null_content(v, *l_index, is_hdoc_deli);
	if (expand_nbr)
	{
		v->flg_var_is_null = __TRUE;
		*l_index = expand_nbr;
		return (NULL);
	}
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
