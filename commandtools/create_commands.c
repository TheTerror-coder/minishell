/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 04:14:54 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 19:33:36 by lmohin           ###   ########.fr       */
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

t_bool	get_cmds_recursively(t_vars *v, t_commands *command, t_token **tokens)
{
	command->next = create_commands(v, (*tokens)->next);
	free((*tokens)->content);
	free((*tokens));
	if (!command->next)
	{
		free_tokens(command->tokens);
		free(command);
		return (__FALSE);
	}
	return (__TRUE);
}

t_commands	*create_commands(t_vars *v, t_token *tokens)
{
	t_commands	*command;
	t_token		*token_previous;

	if (tokens == NULL)
		return (NULL);
	command = malloc(sizeof(t_commands));
	if (!command)
	{
		free_tokens(tokens);
		return (ft_leave(v, EXIT_FAILURE, "malloc", __PERROR), NULL);
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
	if (tokens != NULL && !get_cmds_recursively(v, command, &tokens))
		command = NULL;
	token_previous->next = NULL;
	v->commands = command;
	return (command);
}
