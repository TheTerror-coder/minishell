/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/09/09 19:08:36 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*clear_redirections(t_commands *command)
{
	t_token *token;

	while ((command->tokens) != NULL && (command->tokens)->type == 1)
	{
		if ((command->tokens)->next == NULL || (command->tokens)->next->type == 1)
		{
			printf("parsing error");
			exit(0);
		}
		if (!ft_strncmp(command->tokens->content, "<", 2))
		{
			command->infile = command->tokens->next->content;
			command->tokens = command->tokens->next->next;
		}
		if (!ft_strncmp(command->tokens->content, ">", 1))
		{
			command->outfile = command->tokens->next->content;
			command->tokens = command->tokens->next->next;
		}
	}
	token = command->tokens;
	if (token == NULL)
		return (command);
	while (token->next != NULL)
	{
		if (token->next->type == 1)
		{
			if (token->next->next == NULL || token->next->next->type == 1)
			{
				printf("parsing error");
				exit(0);
			}
			if (!ft_strncmp(token->next->content, "<", 2))
			{
				command->infile = token->next->next->content;
				token->next = token->next->next->next;
			}
			if (!ft_strncmp(token->next->content, ">", 1))
			{
				command->outfile = token->next->next->content;
				token->next = token->next->next->next;
			}
		}
		else
			token->next = token->next->next;
	}
	return (command);
}

t_commands	*create_command(t_token *tokens)
{
	t_commands	*command;
	t_token		*tokens_previous;

	command = malloc(sizeof(t_commands));
	command->tokens = tokens;
	command->next = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	while (tokens != NULL && !(tokens->type == 1 && (tokens->content)[0] == '|'))
	{
		tokens_previous = tokens;
		tokens = tokens->next;
	}
	if (tokens != NULL)
	{
		command->next = create_command(tokens->next);
		tokens_previous->next = NULL;
	}
	return (command);
}

int main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_vars	*v;
	t_commands *commands;

	v = ft_initvars();
	v->envp = envp;
	ft_setenv(v);
	if (argc == 1)
		return (0);
	tokens = break_input_into_token(argv[1], v);
	commands = create_command(tokens);
	while (commands != NULL)
	{
		commands = clear_redirections(commands);
		while (commands->tokens != NULL)
		{
			printf("%s ", commands->tokens->content);
			commands->tokens = commands->tokens->next;
		}
		printf("///////// %s INFILE", commands->infile);
		printf("///////// %s OUTFILE", commands->outfile);
		printf("\n");
		commands = commands->next;
	}
}
