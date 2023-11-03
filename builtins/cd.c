/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/03 11:17:58 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	print_chdir_error(t_vars *v, char *old_pwd, t_commands *command);
t_bool	check_cd_options(t_vars *v, char *first_arg);
t_bool	unset_one_arg(t_vars *v, char *arg);

t_bool	set_oldpwd(t_vars *v, char *old_pwd)
{
	char	*tmp_old_pwd;

	if (!old_pwd)
		return (unset_one_arg(v, "OLDPWD"));
	tmp_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (!tmp_old_pwd)
		return (ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR));
	if (!export_one_arg(v, tmp_old_pwd))
		return (free(tmp_old_pwd), __FALSE);
	return (free(tmp_old_pwd), __TRUE);
}

t_bool	set_pwd_and_oldpwd(t_vars *v, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp_pwd;

	tmp_pwd = getcwd(NULL, 0);
	if (!tmp_pwd)
	{
		free(old_pwd);
		perror("minishell: getcwd");
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	new_pwd = ft_strjoin("PWD=", tmp_pwd);
	free(tmp_pwd);
	if (!new_pwd)
	{
		free(old_pwd);
		return (ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR));
	}
	if (!export_one_arg(v, new_pwd))
		return (free(new_pwd), free(old_pwd), __FALSE);
	free(new_pwd);
	return (set_oldpwd(v, old_pwd));
}

t_bool	ft_cd_cdpath_set(t_vars *v, char *dir)
{
	char	*cdpath;
	char	**split_cdpath;
	t_bool	ret;

	if (dir[0] == '/' || !ft_strncmp(dir, "..", 3) || !ft_strncmp(dir, "./", 3))
		return (__FALSE);
	if (!check_env_var_set(v->my_env, "CDPATH"))
		return (__FALSE);
	cdpath = get_env_var_content(v, v->my_env, "CDPATH");
	if (!cdpath)
		return (__FALSE);
	split_cdpath = ft_split(cdpath, ':');
	if (!split_cdpath)
	{
		perror("minishell: ft_split");
		free(cdpath);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	free(cdpath);
	ret = testing_split_cdpath(v, split_cdpath, dir);
	ft_freesplit(split_cdpath);
	return (ret);
}

t_bool	ft_cd_special_cases(t_vars *v, t_commands *command, char *old_pwd)
{
	if (!(command->arguments[1]) || !ft_strncmp(command->arguments[1], "--", 3))
	{
		if (ft_cd_no_args(v))
			return (set_pwd_and_oldpwd(v, old_pwd));
		free(old_pwd);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	if (command->arguments[2])
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	if (!ft_strncmp(command->arguments[1], "-", STDERR_FILENO))
	{
		if (ft_cd_oldpwd_case(v))
			return (set_pwd_and_oldpwd(v, old_pwd));
		free(old_pwd);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	return (__TRUE);
}

t_bool	ft_cd(t_vars *v, t_commands *command)
{
	char	*old_pwd;

	if (!check_cd_options(v, command->arguments[1]))
		return (__FALSE);
	if (!check_env_var_set(v->my_env, "PWD"))
		old_pwd = NULL;
	else
	{
		old_pwd = get_env_var_content(v, v->my_env, "PWD");
		if (!old_pwd)
			return (__FALSE);
	}
	if (!(command->arguments[1]) || (command->arguments[2]) \
		|| (!ft_strncmp(command->arguments[1], "-", 1)))
		return (ft_cd_special_cases(v, command, old_pwd));
	if (ft_cd_cdpath_set(v, command->arguments[1]))
		return (set_pwd_and_oldpwd(v, old_pwd));
	if (errno == ENOMEM)
		return (__FALSE);
	if (chdir(command->arguments[1]) == -1)
		return (print_chdir_error(v, old_pwd, command), __FALSE);
	return (set_pwd_and_oldpwd(v, old_pwd));
}
