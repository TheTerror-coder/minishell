/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 02:44:42 by lmohin           ###   ########.fr       */
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

int	get_main_command(t_commands *commands)
{
	t_token *tokens_cpy;

	tokens_cpy = commands->tokens;
	commands->main_command = NULL;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type == 1)
			tokens_cpy = tokens_cpy->next->next;
		else
		{
			commands->main_command = tokens_cpy->content;
			return (0);
		}
	}
	return (0);
}

int	fill_command_arguments(t_commands *commands)
{
	int	args_nbr;
	t_token	*tokens_cpy;
	t_token	*previous_token;

	args_nbr = 0;
	tokens_cpy = commands->tokens;
	previous_token = NULL;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type != 1)
		{
			(commands->arguments)[args_nbr] = tokens_cpy->content;
			args_nbr++;
			if (previous_token != NULL)
				previous_token->next = tokens_cpy->next;
			else
				commands->tokens = tokens_cpy->next;
			free(tokens_cpy);
			if (previous_token != NULL)
				tokens_cpy = previous_token->next;
			else
				tokens_cpy = commands->tokens;
		}
		else
		{
			previous_token = tokens_cpy->next;
			tokens_cpy = tokens_cpy->next->next;
		}
	}
	(commands->arguments)[args_nbr] = NULL;
	return (0);
}
int	get_command_arguments(t_commands *commands)
{
	int	args_nbr;
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
	commands->arguments = malloc(sizeof(char *) * (args_nbr + 1));
	fill_command_arguments(commands);
	return (0);
}

int	clear_commands(t_commands *commands)
{
	t_commands *commands_cpy;

	commands_cpy = commands;
	while (commands_cpy != NULL)
	{
		get_main_command(commands_cpy);
		get_command_arguments(commands_cpy);
		commands_cpy = commands_cpy->next;
	}
	return (0);
}

t_commands *get_commands(t_vars *v)
{
	t_commands *commands;
	t_token *tokens;

	commands = NULL;
	tokens = break_input_into_tokens(v);
	commands = create_command(tokens);
	check_redirections(commands);
	clear_commands(commands);
	return (commands);
}
