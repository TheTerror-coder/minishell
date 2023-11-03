/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:51:38 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/03 11:18:54 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	do_chdir(t_vars *v, char *var);

t_bool	ft_cd_no_args(t_vars *v)
{
	char	*home;
	t_bool	ret;

	if (!check_env_var_set(v->my_env, "HOME"))
	{
		ft_leave(v, EXIT_FAILURE, "minishell: cd: HOME no set", __PRINT);
		return (__FALSE);
	}
	home = get_env_var_content(v, v->my_env, "HOME");
	if (!home)
		return (__FALSE);
	if (home[0] == '\0')
	{
		free(home);
		return (__TRUE);
	}
	ret = do_chdir(v, home);
	free(home);
	return (ret);
}

t_bool	ft_cd_oldpwd_case(t_vars *v)
{
	char	*oldpwd;

	if (!check_env_var_set(v->my_env, "OLDPWD"))
	{
		ft_leave(v, EXIT_FAILURE, "cd: OLDPWD not set", __PRINT);
		return (__FALSE);
	}
	oldpwd = get_env_var_content(v, v->my_env, "OLDPWD");
	if (!oldpwd)
		return (__FALSE);
	if (oldpwd[0] == '\0')
		return (free(oldpwd), __TRUE);
	if (do_chdir(v, oldpwd))
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
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		free(path);
		return (__TRUE);
	}
	free(path);
	return (__FALSE);
}

t_bool	leave_error_cdpath(t_vars *v)
{
	ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR);
	return (__FALSE);
}

t_bool	testing_split_cdpath(t_vars *v, char **split_cdpath, char *dir)
{
	int		i;
	char	*cdpath;
	char	*cdpath_slash;

	i = 0;
	while (split_cdpath[i++])
	{
		cdpath = ft_strjoin(split_cdpath[i - 1], dir);
		if (!cdpath)
			return (leave_error_cdpath(v));
		if (talking_chdir(cdpath))
			return (__TRUE);
		cdpath_slash = ft_strjoin(split_cdpath[i - 1], "/");
		if (!cdpath_slash)
			return (leave_error_cdpath(v));
		cdpath = ft_strjoin(cdpath_slash, dir);
		free(cdpath_slash);
		if (!cdpath)
			return (leave_error_cdpath(v));
		if (talking_chdir(cdpath))
			return (__TRUE);
	}
	return (__FALSE);
}
