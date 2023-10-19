/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/19 23:39:49 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freecommands(t_vars *v)
{
	t_commands	*commands;
	t_commands	*commands_cpy;
	t_token		*tokens;
	int		i;

	commands = v->commands;
	while (commands != NULL)
	{
		while (commands->tokens != NULL)
		{
			tokens = commands->tokens;
			free(tokens->content);
			commands->tokens = commands->tokens->next;
			free(tokens);
		}
		ft_fclose(&commands->hdoc_fd);
		i = 0;
		while (commands->arguments[i])
		{
			free(commands->arguments[i]);
			i++;
		}
		free(commands->arguments);
		commands_cpy = commands;
		commands = commands->next;
		free(commands_cpy);
	}
}

int	get_main_command(t_commands *commands)
{
	t_token	*tokens_cpy;

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

int	clear_commands(t_commands *commands)
{
	t_commands	*commands_cpy;

	commands_cpy = commands;
	while (commands_cpy != NULL)
	{
		get_main_command(commands_cpy);
		get_command_arguments(commands_cpy);
		commands_cpy = commands_cpy->next;
	}
	return (0);
}

t_commands	*get_commands(t_vars *v)
{
	t_commands	*commands;
	t_token		*tokens;

	commands = NULL;
	tokens = break_input_into_tokens(v);
	commands = create_commands(tokens);
	clear_commands(commands);
	return (commands);
}
