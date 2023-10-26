/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:31:19 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 21:47:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freetokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}

void	ft_freecommands(t_vars *v)
{
	t_commands	*commands;
	t_commands	*commands_cpy;
	size_t		i;

	commands = v->commands;
	while (commands != NULL)
	{
		ft_freetokens(commands->tokens);
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
	char	*void_content;

	tokens_cpy = commands->tokens;
	void_content = NULL;
	commands->main_command = NULL;
	while (tokens_cpy != NULL)
	{
		if (tokens_cpy->type == 1)
			tokens_cpy = tokens_cpy->next->next;
		else if (tokens_cpy->content[0] != '\0')
		{
			commands->main_command = tokens_cpy->content;
			return (0);
		}
		else
		{
			void_content = tokens_cpy->content;
			tokens_cpy = tokens_cpy->next;
		}
	}
	commands->main_command = void_content;
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
