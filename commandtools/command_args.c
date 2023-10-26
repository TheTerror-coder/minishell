/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 01:57:18 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 03:31:14 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	add_arg(t_token **tokens, t_token *previous_token, t_commands *cmds)
{
	if (previous_token != NULL)
		previous_token->next = (*tokens)->next;
	else
		cmds->tokens = (*tokens)->next;
	free(*tokens);
	if (previous_token != NULL)
		*tokens = previous_token->next;
	else
		*tokens = cmds->tokens;
}

int	fill_command_arguments(t_commands *commands)
{
	int		arg_c;
	t_token	*tokens_cpy;
	t_token	*previous_token;

	arg_c = 0;
	tokens_cpy = commands->tokens;
	previous_token = NULL;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type != 1)
		{
			(commands->arguments)[arg_c] = (tokens_cpy)->content;
			arg_c++;
			add_arg(&tokens_cpy, previous_token, commands);
		}
		else
		{
			previous_token = tokens_cpy->next;
			tokens_cpy = tokens_cpy->next->next;
		}
	}
	(commands->arguments)[arg_c] = NULL;
	return (0);
}*/

void	fill_command_arguments(t_commands *commands)
{
	size_t	arg_c;
	t_token	*tokens_cpy;
	t_token	*tokens_redir;
	t_bool	first_redir;
	t_token	*start_tokens_redir;
	t_token	*old_cpy;

	arg_c = 0;
	first_redir = __TRUE;
	start_tokens_redir = NULL;
	tokens_cpy = commands->tokens;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type == 0)
		{
			(commands->arguments)[arg_c] = (tokens_cpy)->content;
			arg_c++;
			old_cpy = tokens_cpy;
			tokens_cpy = tokens_cpy->next;
			free(old_cpy);
			old_cpy = NULL;
		}
		else
		{
			if (first_redir == __TRUE)
			{
				start_tokens_redir = tokens_cpy;
				tokens_redir = tokens_cpy;
				tokens_redir->next = tokens_cpy->next;
				tokens_redir = tokens_redir->next;
				first_redir = __FALSE;
			}
			else
			{
				tokens_redir->next = tokens_cpy;
				tokens_redir->next->next = tokens_cpy->next;
				tokens_redir = tokens_redir->next->next;
			}
			tokens_cpy = tokens_cpy->next->next;
		}
	}
	commands->tokens = start_tokens_redir;
	commands->arguments[arg_c] = NULL;
}

int	get_command_arguments(t_commands *commands)
{
	int		args_nbr;
	t_token	*tokens_cpy;

	args_nbr = 0;
	tokens_cpy = commands->tokens;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type != 1)
		{
			args_nbr++;
			tokens_cpy = tokens_cpy->next;
		}
		else
			tokens_cpy = tokens_cpy->next->next;
	}
	commands->arguments = NULL;
	commands->arguments = malloc(sizeof(char *) * (args_nbr + 1));
	fill_command_arguments(commands);
	return (0);
}
