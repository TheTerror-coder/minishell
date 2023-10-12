/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/12 14:03:29 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool ft_prompt(t_vars *v)
{
	
	v->line = readline("minishell$ ");
// ft_putnbr_fd(ft_strlen(v->line), 1);
// ft_putendl_fd("hello", 1);
	while (!ft_strlen(v->line) || ft_strncmp(v->line, "exit", 5))
	{
		ft_razflags(v);
		if ((v->line)[0])
			add_history(v->line);
		ft_minishell(v);
		ft_freestr(&v->line);
		v->line = readline("minishell$ ");
	}
	ft_freestr(&v->line);
	return (__TRUE);
}

t_bool ft_minishell(t_vars *v)
{
//	char	**split_path;
	int	i;
	//char	*test_cmd;
	
	v->commands = get_commands(v);
	/*split_path = ft_split(check_env_var_set(v, "PATH"), ':');
	i = 0;
	while (split_path[i] != NULL)
	{
		test_cmd = ft_strjoin(ft_strjoin(split_path[i], "/"), v->commands->main_command);
		if (access(test_cmd, 0) == 0)
			break ;
		i++;
	}
	if (split_path[i] == NULL)
		test_cmd = v->commands->main_command;
	execve(test_cmd, v->commands->arguments, v->envp);*/
/*	printf("%s\n", v->commands->tokens->next->content);
	while (v->commands)
	{
		i = 0;
		if (v->commands->main_command)
			printf("main command : %s\n", v->commands->main_command);
		printf("arguments: \n");
		while ((v->commands->arguments)[i] != NULL)
		{
			printf("%s\n", (v->commands->arguments)[i]);
			i++;
		}
		v->commands = v->commands->next;
	}
	exit(0);*/
	if (!ft_lmanager(v))
		return (__FALSE);
	if (!ft_launcher(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool ft_lmanager(t_vars *v)
{
	if (!ft_setargv(v))
		return (__FALSE);
	if (!ft_parseargv(v))
		return (__FALSE);
	if (v->flg_pipeline)
		if (!ft_setpipeline(v))
			return (__FALSE);
	return (__TRUE);
}
