/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:14:02 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/02 01:28:50 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_ret_with_subinput(char *ret, char *input, size_t start, size_t end)
{
	char	*cpy;
	char	*subinput;

	subinput = ft_substr(input, start, end);
	if (!subinput)
	{
		free(ret);
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, subinput);
	free(cpy);
	free(subinput);
	return (ret);
}

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
	if (!token)
		return (NULL);
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
	char	*cpy;

	ret = join_ret_with_subinput(ret, input, *i, *j);
	if (!ret)
		return (NULL);
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
	{
		free(expand_name);
		return (ret);
	}
	cpy = ret;
	ret = ft_strjoin(ret, check_env_var_set(v, expand_name));
	free(cpy);
	free(expand_name);
	return (ret);
}

char	*double_quote_case(size_t *i, size_t *j, char *ret, t_vars *v, int heredoc)
{
	ret = join_ret_with_subinput(ret, v->line, *i, *j);
	if (!ret)
		return (NULL);
	*i += *j + 1;
	*j = 0;
	while ((v->line)[*i + *j] != '"' && (v->line)[*i + *j] != '\0')
	{
		if (heredoc == 0 && (v->line)[*i + *j] == '$' && !is_whitespace((v->line)[*i + *j + 1]) && !is_operator((v->line)[*i + *j + 1]))
			ret = expand_case(v->line, i, j, ret, v);
		else
			(*j)++;
	}
	if ((v->line)[*i + *j] != '"')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = join_ret_with_subinput(ret, v->line, *i, *j);
	*i += *j + 1;
	*j = 0;
	return (ret);
}

char	*single_quote_case(char *input, size_t *i, size_t *j, char *ret)
{
	ret = join_ret_with_subinput(ret, input, *i, *j);
	*i += *j + 1;
	*j = 0;
	while (input[*i + *j] != '\'' && input[*i + *j] != '\0')
		(*j)++;
	if (input[*i + *j] != '\'')
	{
		printf("UNCLOSED QUOTE");
		exit(0);
	}
	ret = join_ret_with_subinput(ret, input, *i, *j);
	*i += *j + 1;
	*j = 0;
	return (ret);
}

char	*get_word(t_vars *v, size_t *i, int heredoc)
{
	char	*ret;
	size_t	j;

	ret = malloc(sizeof(char) * 1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	j = 0;
	while (!is_whitespace((v->line)[*i + j]) && !is_operator((v->line)[*i + j]) && (v->line)[*i + j] != '\0')
	{
		if ((v->line)[*i + j] == '$' && !is_whitespace((v->line)[*i + j + 1]) && !is_operator((v->line)[*i + j + 1]) && heredoc == 0)
			ret = expand_case((v->line), i, &j, ret, v);
		else if ((v->line)[*i + j] == '"')
			ret = double_quote_case(i, &j, ret, v, heredoc);
		else if ((v->line)[*i + j] == '\'')
			ret = single_quote_case(v->line, i, &j, ret);
		else
			j++;
		if (!ret)
			return (NULL);
	}
	ret = join_ret_with_subinput(ret, v->line, *i, j);
	*i += j;
	return (ret);
}

char	*get_operator_or_word(size_t *i, int *type, t_vars *v, int heredoc)
{
	if ((v->line)[*i] == '|')
		return (get_operator_pipe(i, v->line, type));
	if ((v->line)[*i] == '<' || (v->line)[*i] == '>')
		return (get_operator_redirection(v->line, i, type));
	return (get_word(v, i, heredoc));
}

t_token	*get_one_token(t_vars *v, size_t *i, int heredoc)
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

t_token	*break_input_into_token(t_vars *v)
{
	size_t	i;
	t_token	*token;
	t_token	*init_token;
	int	heredoc;

	heredoc = 0;
	i = 0;
	token = get_one_token(v, &i, heredoc);
	if (!token)
		return (NULL);
	if (token->type == 1 && !ft_strncmp(token->content, "<<", 3))
		heredoc = 1;
	init_token = token;
	while ((v->line)[i] != '\0')
	{
		token->next = get_one_token(v, &i, heredoc);
		if (!(token->next))
			return (NULL);
		if (token->next->type == 1 && !ft_strncmp(token->next->content, "<<", 3))
			heredoc = 1;
		else
			heredoc = 0;
		if (token->next == NULL)
			return (init_token);
		token = token->next;
	}
	return (init_token);
}
