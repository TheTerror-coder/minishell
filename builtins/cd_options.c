/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:51:38 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/04 18:01:27 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	do_chdir(char *var)
{
	char	*message_to_print;

	if (chdir(var) == -1)
	{
		message_to_print = ft_strjoin("minishell: cd: ", var);
		if (message_to_print)
			perror(message_to_print);
		else
			perror("minishell: cd");
		free(message_to_print);
		return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_cd_no_args(t_vars *v)
{
	char	*home;
	t_bool	ret;

	home = check_env_var_set(v, "HOME");
	if (!home)
	{
		if (errno == ENOMEM)
			perror("minishell: cd");
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(home);
		return (__FALSE);
	}
	if (home[0] == '\0')
	{
		free(home);
		return (__FALSE);
	}
	ret = do_chdir(home);
	free(home);
	return (ret);
}

t_bool	ft_cd_oldpwd_case(t_vars *v)
{
	char	*oldpwd;

	oldpwd = check_env_var_set(v, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		if (errno == ENOMEM)
			perror("minishell: cd");
		else
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		free(oldpwd);
		return (__FALSE);
	}
	if (do_chdir(oldpwd))
	{
		ft_putstr_fd(oldpwd, 2);
		ft_putchar_fd('\n', 2);
		free(oldpwd);
		return (__TRUE);
	}
	else
		free(oldpwd);
	return (__FALSE);
}

t_bool	talking_chdir(char *path)
{
	if (chdir(path) != -1)
	{
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		free(path);
		return (__TRUE);
	}
	free(path);
	return (__FALSE);
}

t_bool	testing_split_cdpath(t_vars *v, char **split_cdpath)
{
	int		i;
	char	*cdpath;
	char	*cdpath_slash;

	i = 0;
	while (split_cdpath[i++])
	{
		cdpath = ft_strjoin(split_cdpath[i - 1], v->argv[1]);
		if (!cdpath)
			return (__FALSE);
		if (talking_chdir(cdpath))
			return (__TRUE);
		cdpath_slash = ft_strjoin(split_cdpath[i - 1], "/");
		if (!cdpath_slash)
			return (__FALSE);
		cdpath = ft_strjoin(cdpath_slash, v->argv[1]);
		free(cdpath_slash);
		if (!cdpath)
			return (__FALSE);
		if (talking_chdir(cdpath))
			return (__TRUE);
	}
	return (__FALSE);
}
