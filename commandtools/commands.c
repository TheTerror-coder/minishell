/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/29 21:45:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freetokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens->next;
		ft_freestr(&(tokens->content));
		free(tokens);
		tokens = tmp;
	}
}

void	ft_freecommands(t_vars *v)
{
	t_commands	*commands;
	t_commands	*commands_cpy;

	commands = v->commands;
	while (commands != NULL)
	{
		if (commands->tokens)
			ft_freetokens(commands->tokens);
		ft_fclose(v, &commands->hdoc_fd);
		ft_free2str(&(commands->arguments));
		commands_cpy = commands;
		commands = commands->next;
		free(commands_cpy);
	}
	v->commands = NULL;
}

int	get_main_command(t_commands *commands)
{
	t_token	*tokens_cpy;

	tokens_cpy = commands->tokens;
	commands->main_command = NULL;
	tokens_cpy = commands->tokens;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type == 1)
			tokens_cpy = tokens_cpy->next->next;
		else if (tokens_cpy->content != NULL)
		{
			commands->main_command = tokens_cpy->content;
			return (0);
		}
		else
			tokens_cpy = tokens_cpy->next;
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

	v->flg_parsing_is_ok = __TRUE;
	commands = NULL;
	tokens = break_input_into_tokens(v);
	if (v->flg_parsing_is_ok == __FALSE)
	{
		ft_freetokens(tokens);
		return (NULL);
	}
	commands = create_commands(tokens);
	clear_commands(commands);
	return (commands);
}
