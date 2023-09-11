/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/09/11 06:47:30 by lmohin           ###   ########.fr       */
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
	int	i;

	i = 0;
//
// v->commands : liste chainee contenant les commandes a executer dans l'ordre
// 
//            "ls -la | echo > ewrerrer$USERrwr were  er er eer "|" rrwe | > salut" devient ->
//												  ls -la     (commande 1)
// 	       											  echo > ewrerrerlmohinrwr were  er er eer | rrwe    (commande 2)
//                                                                                                > salut    (commande 3)
//   
//      
// v->commands->tokens est la liste chainee contenant chaque mot de la commande.
//			"echo > ewrerrerlmohinrwr were   "|" rrwe" devient ->
//												echo    -    	0
//												>	-	1
//												ewrerrerlmohinrwr	-	0
//												|		-	0
//    												rrwe		-	0
//	une vrai redirection sera indexe par un type '1', alors qu'une redirection entre quote sera indexe par un type '0'. Seuls les redirections avec type '1' sont donc a traiter comme des redirections.
//	Parsing d'erreurs de redirections deja effectue: quand plusieurs redirections se suivent
                                     
	v->commands = get_commands(v);	
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
