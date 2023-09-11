/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/09/11 06:36:14 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirections(t_commands *command)
{
	t_token *token;

	token = command->tokens;
	while (token != NULL)
	{
		if (token->type == 1 && (token->next == NULL || token->next->type == 1))
		{
			printf("parsing error");
			return (0);
		}
		token = token->next;
	}
	return (1);
}

t_commands	*create_command(t_token *tokens)
{
	t_commands	*command;
	t_token		*tokens_previous;

	command = malloc(sizeof(t_commands));
	command->tokens = tokens;
	command->next = NULL;
	while (tokens != NULL && !(tokens->type == 1 && (tokens->content)[0] == '|'))
	{
		tokens_previous = tokens;
		tokens = tokens->next;
	}
	if (tokens != NULL)
	{
		command->next = create_command(tokens->next);
		tokens_previous->next = NULL;
		free(tokens->content);
		free(tokens);
	}
	return (command);
}

void	ft_freecommands(t_vars *v)
{
	t_commands *commands;
	t_commands *commands_cpy;
	t_token	*tokens;

	commands = v->commands;
	while (commands != NULL)
	{
		if (commands->tokens != NULL)
		{
			tokens = commands->tokens;
			free(tokens->content);
			commands->tokens = commands->tokens->next;
			free(tokens);
		}
		commands_cpy = commands;
		commands = commands->next;
		free(commands_cpy);
	}
}

t_commands *get_commands(t_vars *v)
{
	t_commands *commands;
	t_token *tokens;

	commands = NULL;
	tokens = break_input_into_token(v);
	commands = create_command(tokens);
	check_redirections(commands);
	return (commands);
}
