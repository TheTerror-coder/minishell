/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:37:59 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 17:41:53 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	print_not_valid_identifier(t_vars *v, char *str)
{
	v->exitstatus = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (__TRUE);
}

char	*fill_ret_after_equal(char *ret, char *s, size_t i)
{
	ret[i] = '=';
	i++;
	ret[i] = '"';
	while (s[i])
	{
		ret[i + 1] = s[i];
		i++;
	}
	ret[i + 1] = '"';
	ret[i + 2] = '\0';
	return (ret);
}

char	*adding_quotes(char *s, t_vars *v)
{
	char	*ret;
	size_t	i;

	ret = malloc(sizeof(char) * (ft_strlen(s) + 3));
	if (!ret)
		return (ft_leave(v, EXIT_FAILURE, "malloc", __PERROR), NULL);
	i = 0;
	while (s[i] != '=' && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	if (s[i] == '\0')
	{
		ret[i] = '\0';
		return (ret);
	}
	return (fill_ret_after_equal(ret, s, i));
}

void	order_tab(char **s)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
		if (s[i] != NULL && ft_strncmp(s[i], s[i - 1], ft_strlen(s[i])) < 0)
		{
			tmp = s[i];
			s[i] = s[i - 1];
			s[i - 1] = tmp;
			i = 0;
		}
	}
}

t_bool	print_export(t_vars *v)
{
	char	**s;
	char	*quoted_var;
	size_t	i;

	if (!v->my_env->var)
		return (__TRUE);
	s = env_list_to_tab(v);
	if (!s)
		return (__FALSE);
	i = 1;
	order_tab(s);
	while (s[++i])
	{
		if (ft_strncmp(s[i], "_", 2) && ft_strncmp(s[i], "_=", 3))
		{
			quoted_var = adding_quotes(s[i], v);
			if (!quoted_var)
				return (ft_free2str(&s), __FALSE);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(quoted_var, 1);
			ft_putstr_fd("\n", 1);
			free(quoted_var);
		}
	}
	return (ft_free2str(&s), __TRUE);
}
