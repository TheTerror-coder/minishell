/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 04:14:54 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/15 18:04:49 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*previous_token;

	while (tokens != NULL)
	{
		free(tokens->content);
		previous_token = tokens;
		tokens = tokens->next;
		free(previous_token);
	}
}

int	get_commands_recursively(t_commands *command, t_token **tokens)
{
	command->next = create_commands((*tokens)->next);
	free((*tokens)->content);
	free((*tokens));
	if (!command->next)
	{
		free_tokens(command->tokens);
		free(command);
		return (0);
	}
	return (1);
}

t_commands	*create_commands(t_token *tokens)
{
	t_commands	*command;
	t_token		*token_previous;

	if (tokens == NULL)
		return (NULL);
	command = malloc(sizeof(t_commands));
	if (!command)
	{
		free_tokens(tokens);
		return (NULL);
	}
	command->tokens = tokens;
	command->hdoc_fd = __CLOSED_FD;
	command->next = NULL;
	while (tokens != NULL \
		&& !(tokens->type == 1 && (tokens->content)[0] == '|'))
	{
		token_previous = tokens;
		tokens = tokens->next;
	}
	if (tokens != NULL && !get_commands_recursively(command, &tokens))
		command = NULL;
	token_previous->next = NULL;
	return (command);
}
