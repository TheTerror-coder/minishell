/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_and_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:36:31 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 05:02:42 by lmohin           ###   ########.fr       */
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

char	*get_pipe(size_t *i, char *input)
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
	(*i)++;
	return (ft_strdup("|"));
}

char	*get_redirection(char *input, size_t *i)
{
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
/*
char	*get_operator_or_word(size_t *i, t_vars *v, int heredoc)
{
	if ((v->line)[*i] == '|')
		return (get_operator_pipe(i, v->line));
	if ((v->line)[*i] == '<' || (v->line)[*i] == '>')
		return (get_operator_redirection(v->line, i));
	return (get_word(v, i, heredoc));
}*/
