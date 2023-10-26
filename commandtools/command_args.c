/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 01:57:18 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 21:46:28 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_first_redirection(t_commands *commands)
{
	t_token	*token_cpy;
	t_token	*token_to_free;

	token_cpy = commands->tokens;
	while (token_cpy != NULL && token_cpy->type == 0)
	{
		token_to_free = token_cpy;
		token_cpy = token_cpy->next;
		free(token_to_free);
	}
	commands->tokens = token_cpy;
}

void	clear_token_list(t_commands *commands)
{
	t_token	*token_cpy;
	t_token	*token_to_free;

	get_first_redirection(commands);
	if (commands->tokens == NULL)
		return ;
	token_cpy = commands->tokens->next;
	while (token_cpy->next != NULL)
	{
		if (token_cpy->next->type == 0)
		{
			token_to_free = token_cpy->next;
			token_cpy->next = token_cpy->next->next;
			free(token_to_free);
		}
		else
			token_cpy = token_cpy->next->next;
	}
}

void	fill_command_arguments(t_commands *commands)
{
	size_t	arg_c;
	t_token	*token_cpy;

	token_cpy = commands->tokens;
	arg_c = 0;
	while (token_cpy != NULL)
	{
		if (token_cpy->type == 0)
		{
			commands->arguments[arg_c] = (token_cpy)->content;
			arg_c++;
			token_cpy = token_cpy->next;
		}
		else
			token_cpy = token_cpy->next->next;
	}
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
	clear_token_list(commands);
	return (0);
}
