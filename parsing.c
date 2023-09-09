/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/09/09 16:34:36 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token	*create_token(char *content, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}

char	*get_operator_pipe(size_t *i, char *input, int *type)
{
	size_t	j;
	
	j = 1;
	while (input[*i + j] != '\0' && is_whitespace(input[*i + j]))
		j++;
	if (input[*i + 1] == '<' || input[*i + 1] == '>' || input[*i + j] == '\0' || input[*i + j] == '|')
	{
		printf("parsing error");
		exit(0);
	}
	*type = 1;
	(*i)++;
	return (ft_strdup("|"));
}

char	*get_operator_redirection(char *input, size_t *i, int *type)
{
	*type = 1;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		if (input[*i + 2] == '<' || input[*i + 2] == '>' || input[*i + 2] == '|')
		{
			printf("parsing error");
			exit(0);
		}
		(*i) += 2;
		return (ft_strdup("<<"));
	}
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '>' || input[*i + 1] == '|')
		{
			printf("parsing error");
			exit(0);
		}
		(*i)++;
		return (ft_strdup("<"));
	}
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		if (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|')
		{
			printf("parsing error");
			return (NULL);
		}
		(*i) += 2;
		return (ft_strdup(">>"));
	}
	if (input[*i + 1] == '<' || input[*i + 1] == '|')
	{
		printf("parsing error");
		return (NULL);
	}
	(*i)++;
	return (ft_strdup(">"));
}

char	*expand_case(char *input, size_t *i, size_t *j, char *ret, t_vars *v)
{
	char	*expand_name;

	ret = ft_strjoin(ret, ft_substr(input, *i, *j));
	*i += *j + 1;
	*j = 0;
	if (input[*i + *j] <= '9' && input[*i + *j] >= '0')
		return (ret);
	while ((input[*i + *j] <= 'z' && input[*i + *j] >= 'a') || (input[*i + *j] <= 'Z' && input[*i + *j] >= 'A') || (input[*i + *j] >= '0' && input[*i + *j] <= '9'))
		(*j)++;
	expand_name = ft_substr(input, *i, *j);
	*i += *j;
	*j = 0;
	if (!check_env_var_set(v, expand_name))
		return (ret);
	return (ft_strjoin(ret, check_env_var_set(v, expand_name)));
}

char	*double_quote_case(char *input, size_t *i, size_t *j, char *ret, t_vars *v)
{
	ret = ft_strjoin(ret, ft_substr(input, *i, *j));
	*i += *j + 1;
	*j = 0;
	while (input[*i + *j] != '"' && input[*i + *j] != '\0')
	{
		if (input[*i + *j] == '$' && !is_whitespace(input[*i + *j + 1]) && !is_operator(input[*i + *j + 1]))
			ret = expand_case(input, i, j, ret, v);
		(*j)++;
	}
	if (input[*i + *j] != '"')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = ft_strjoin(ret, ft_substr(input, *i, *j));
	*i += *j + 1;
	*j = 0;
	return (ret);
}

char	*single_quote_case(char *input, size_t *i, size_t *j, char *ret, t_vars *v)
{
	ret = ft_strjoin(ret, ft_substr(input, *i, *j));
	*i += *j + 1;
	*j = 0;
	while (input[*i + *j] != '\'' && input[*i + *j] != '\0')
		(*j)++;
	if (input[*i + *j] != '\'')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = ft_strjoin(ret, ft_substr(input, *i, *j));
	*i += *j + 1;
	*j = 0;
	return (ret);
}

char	*get_word(char *input, size_t *i, int *type, t_vars *v)
{
	char	*ret;
	size_t	j;

	ret = malloc(sizeof(char) * 0);
	ret[0] = '\0';
	j = 0;
	if (input[*i] == '|')
		return (get_operator_pipe(i, input, type));
	if (input[*i] == '<' || input[*i] == '>')
		return (get_operator_redirection(input, i, type));
	while (!is_whitespace(input[*i + j]) && !is_operator(input[*i + j]) && input[*i + j] != '\0')
	{
		if (input[*i + j] == '$' && !is_whitespace(input[*i + j + 1]) && !is_operator(input[*i + j + 1]))
		{
			ret = expand_case(input, i, &j, ret, v);
			if (is_whitespace(input[*i + j]) || is_operator(input[*i + j]))
				return (ret);
		}
		if (input[*i + j]  == '"')
			ret = double_quote_case(input, i, &j, ret, v);
		else if (input[*i + j] == '\'')
			ret = single_quote_case(input, i, &j, ret, v);
		else
			j++;
	}
	ret = ft_strjoin(ret, ft_substr(input, *i, j));
	*i += j;
	return (ret);
}

t_token	*get_one_token(char *input, t_vars *v, size_t *i)
{
	int	type;
	char	*s;
	t_token	*token;

	while (is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] == '\0')
		return (NULL);
	type = 0;
	s = get_word(input, i, &type, v);
	if (!s)
		return (NULL);
	token = create_token(s, type);
	return (token);
}

t_token	*break_input_into_token(char *input, t_vars *v)
{
	size_t	i;
	t_token	*token;
	t_token	*init_token;

	i = 0;
	token = get_one_token(input, v, &i);
	init_token = token;
	while (input[i] != '\0')
	{
		token->next = get_one_token(input, v, &i);
		if (token->next == NULL)
			return (init_token);
		token = token->next;
	}
	return (init_token);
}
