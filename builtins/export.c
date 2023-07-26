/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:55:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/25 05:16:34 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *adding_equal(char *s)
{
	int	i;
	char	*cpy;

	cpy = malloc(sizeof(char) * ft_strlen(s) + 2);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '=';
	cpy[i + 1] = '\0';
	return (cpy);
}

t_bool ft_export(t_vars *v, char *env_variable, char *new_txt)
{
	int	i;
	char	*s;

	i = 0;
	s = adding_equal(env_variable);

	while (strncmp((v->envp)[i], s, ft_strlen(s)))
		i++;
	

int main(void)
{
	t_vars *v;

	ft_export(v, "SALUT :)");
}
