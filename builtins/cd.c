/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/13 15:44:53 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	set_pwd_and_oldpwd(t_vars *v, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp_pwd;

	tmp_pwd = getcwd(NULL, 0);
	if (!tmp_pwd)
	{
		free(old_pwd);
		perror("minishell: cd");
		return (__FALSE);
	}
	new_pwd = ft_strjoin("PWD=", tmp_pwd);
	free(tmp_pwd);
	tmp_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (!new_pwd || !old_pwd)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	ft_export(v, new_pwd);
	ft_export(v, tmp_pwd);
	/*if (!ft_export(v, new_pwd) || !ft_export(v, old_pwd))
		return (__FALSE);*/
	free(new_pwd);
	free(tmp_pwd);
	return (__TRUE);
}

t_bool	ft_cd_cdpath_set(t_vars *v)
{
	char	*cdpath;
	char	**split_cdpath;
	t_bool	ret;

	if ((v->argv[1])[0] == '/' || !ft_strncmp((v->argv[1]), "..", 3) \
			|| !ft_strncmp((v->argv[1]), "./", 3))
		return (__FALSE);
	cdpath = check_env_var_set(v, "CDPATH");
	if (!cdpath && errno == ENOMEM)
		perror("minishell: cd");
	if (!cdpath)
		return (__FALSE);
	split_cdpath = ft_split(cdpath, ':');
	if (!split_cdpath)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	free(cdpath);
	ret = testing_split_cdpath(v, split_cdpath);
	if (errno == ENOMEM)
		perror("minishell: cd");
	ft_freesplit(split_cdpath);
	return (ret);
}

t_bool	ft_cd_special_cases(t_vars *v, char *old_pwd)
{
	if (!(v->argv[1]))
	{
		if (ft_cd_no_args(v))
			return (set_pwd_and_oldpwd(v, old_pwd));
		free(old_pwd);
		return (__FALSE);
	}
	if (v->argv[2])
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (__FALSE);
	}
	if (!ft_strncmp(v->argv[1], "-", 2))
	{
		if (ft_cd_oldpwd_case(v))
			return (set_pwd_and_oldpwd(v, old_pwd));
		free(old_pwd);
		return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_cd(t_vars *v)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	if (!(v->argv[1]) || (v->argv[2]) || (!ft_strncmp(v->argv[1], "-", 2)))
		return (ft_cd_special_cases(v, old_pwd));
	if (ft_cd_cdpath_set(v))
		return (set_pwd_and_oldpwd(v, old_pwd));
	if (errno == ENOMEM)
		return (__FALSE);
	if (chdir(v->argv[1]) == -1)
	{
		free(old_pwd);
		perror("minishell: cd");
		return (__FALSE);
	}
	return (set_pwd_and_oldpwd(v, old_pwd));
}
