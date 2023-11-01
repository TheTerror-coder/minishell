/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/31 23:41:48 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	set_pwd_and_oldpwd(t_vars *v, t_commands *command, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp_pwd;
	char	**pwd_list;

	tmp_pwd = getcwd(NULL, 0);
	if (!tmp_pwd)
	{
		free(old_pwd);
		perror("minishell: cd");
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	new_pwd = ft_strjoin("PWD=", tmp_pwd);
	free(tmp_pwd);
	tmp_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (!new_pwd || !old_pwd)
	{
		perror("minishell: cd");
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	pwd_list = malloc(sizeof(char *) * 4);
	if (pwd_list)
	{
		pwd_list[1] = new_pwd;
		pwd_list[2] = tmp_pwd;
		pwd_list[3] = NULL;
		ft_export(v, command, pwd_list);
		free(pwd_list);
	}
	free(new_pwd);
	free(tmp_pwd);
	return (__TRUE);
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
	if (!cdpath && errno == ENOMEM)
	{
		v->exitstatus = EXIT_FAILURE;
		perror("minishell: cd");
	}
	if (!cdpath)
		return (__FALSE);
	split_cdpath = ft_split(cdpath, ':');
	if (!split_cdpath)
	{
		perror("minishell: cd");
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	free(cdpath);
	ret = testing_split_cdpath(v, split_cdpath, dir);
	if (errno == ENOMEM)
	{
		v->exitstatus = EXIT_FAILURE;
		perror("minishell: cd");
	}
	ft_freesplit(split_cdpath);
	return (ret);
}

t_bool	ft_cd_special_cases(t_vars *v, t_commands *command, char *old_pwd)
{
	if (!(command->arguments[1]) || !ft_strncmp(command->arguments[1], "--", 3))
	{
		if (ft_cd_no_args(v))
			return (set_pwd_and_oldpwd(v, command, old_pwd));
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
			return (set_pwd_and_oldpwd(v, command, old_pwd));
		free(old_pwd);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	return (__TRUE);
}

t_bool	check_cd_options(t_vars *v, char *first_arg)
{
	if (first_arg && first_arg[0] == '-' && first_arg[1] != '\0' \
		&& (first_arg[1] != '-' || first_arg[2] != '\0'))
	{
		ft_putstr_fd("minishell: cd: no option expected\n", 2);
		v->exitstatus = __BUILTIN_ERROR;
		return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_cd(t_vars *v, t_commands *command)
{
	char	*old_pwd;

	if (!check_cd_options(v, command->arguments[1]))
		return (__FALSE);
	old_pwd = getcwd(NULL, 0);
	// changer old pwd doit etre $PWD
	if (!old_pwd)
		return (ft_leave(v, EXIT_FAILURE, "getcwd", __PERROR), __FALSE);
	if (!(command->arguments[1]) || (command->arguments[2]) \
		|| (!ft_strncmp(command->arguments[1], "-", 1)))
		return (ft_cd_special_cases(v, command, old_pwd));
	if (ft_cd_cdpath_set(v, command->arguments[1]))
		return (set_pwd_and_oldpwd(v, command, old_pwd));
	if (errno == ENOMEM)
		return (__FALSE);
	if (chdir(command->arguments[1]) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(command->arguments[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(NULL);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	return (set_pwd_and_oldpwd(v, command, old_pwd));
}
