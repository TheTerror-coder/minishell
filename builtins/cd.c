/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/03 10:25:11 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env_var_set(t_vars *v, char *var)
{
	t_env	*tmp;
	char	*sub_home;
	char	*var_equal;
	size_t	length_var;

	length_var = ft_strlen(var) + 1;
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		return (NULL);
	tmp = v->my_env;
	while (tmp->next && strncmp(tmp->var, var_equal, length_var))
		tmp = tmp->next;
	if (strncmp(tmp->var, var_equal, length_var))
	{
		free(var_equal);
		return (NULL);
	}
	sub_home = ft_substr(tmp->var, length_var, ft_strlen(tmp->var) - length_var + 1);
	if (!sub_home)
		return (NULL);
	free(var_equal);
	return (sub_home);
}

t_bool	ft_cd_no_args(t_vars *v)
{
	char	*home;
	char	*message_to_print;

	home = check_env_var_set(v, "HOME");
	if (!home)
	{
		if (errno == ENOMEM)
			perror("minishell: cd");
		else
			printf("minishell: cd: HOME not set\n");
		free(home);
		return (__FALSE);
	}
	if (home[0] == '\0')
	{
		free(home);
		return (__FALSE);
	}
	if ((chdir(home) == -1))
	{
		message_to_print = ft_strjoin("minishell: cd: ", home);
		if (message_to_print)
			perror(message_to_print);
		else
			perror("minishell: cd");
		free(home);
		free(message_to_print);
		return (__FALSE);
	}
	free(home);
	return (__TRUE);
}

t_bool	set_pwd_and_oldpwd(t_vars *v, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	new_pwd = ft_strjoin("PWD=", new_pwd);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (!new_pwd || !old_pwd)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	ft_export(v, new_pwd);
	ft_export(v, old_pwd);
	/*if (!ft_export(v, new_pwd) || !ft_export(v, old_pwd))
		return (__FALSE);*/
	free(new_pwd);
	free(old_pwd);
	return (__TRUE);
}

t_bool	ft_cd_oldpwd_case(t_vars *v)
{
	char	*oldpwd;
	char	*message_to_print;

	oldpwd = check_env_var_set(v, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		if (errno == ENOMEM)
			perror("minishell: cd");
		else
			printf("minishell: cd: OLDPWD not set\n");
		free(oldpwd);
		return (__FALSE);
	}
	if (chdir(oldpwd) == -1)
	{
		message_to_print = ft_strjoin("minishell: cd: ", oldpwd);
		if (message_to_print)
			perror(message_to_print);
		else
			perror("minishell: cd");
		free(oldpwd);
		free(message_to_print);
		return (__FALSE);
	}
	printf("%s\n", oldpwd);
	free(oldpwd);
	return (__TRUE);
}

t_bool	testing_split_cdpath(t_vars *v, char **split_cdpath)
{
	int	i;
	char	*cdpath;
	char	*cdpath_slash;

	i = 0;
	while (split_cdpath[i])
	{
		cdpath = ft_strjoin(split_cdpath[i], v->argv[1]);
		if (chdir(cdpath) != -1)
		{
			printf("%s\n", cdpath);
			return (__TRUE);
		}
		free(cdpath);
		cdpath_slash = ft_strjoin(split_cdpath[i], "/");
		cdpath = ft_strjoin(cdpath_slash, v->argv[1]);
		if (chdir(cdpath) != -1)
		{
			printf("%s\n", cdpath);
			return (__TRUE);
		}
		free(cdpath);
		free(cdpath_slash);
		i++;
	}
	return (__FALSE);
}

t_bool	ft_cd_cdpath_set(t_vars *v)
{
	char	*cdpath;
	char	**split_cdpath;

	if ((v->argv[1])[0] == '/' || !ft_strncmp((v->argv[1]), "..", 3) || !ft_strncmp((v->argv[1]), "./", 2))
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
	return (testing_split_cdpath(v, split_cdpath));
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
	if (!(v->argv[1]) && !(ft_cd_no_args(v)))
		return (__FALSE);
	else if (v->argv[1] && v->argv[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (__FALSE);
	}
	else if ((v->argv[1]) && !ft_strncmp(v->argv[1], "-", 2) && !ft_cd_oldpwd_case(v))
		return (__FALSE);
	else if ((v->argv[1]) && ft_strncmp(v->argv[1], "-", 2) && ft_cd_cdpath_set(v))
		return (__TRUE);
	else if ((v->argv[1]) && ft_strncmp(v->argv[1], "-", 2)  && chdir(v->argv[1]) == -1)
	{
		perror("minishell: cd");
		return (__FALSE);
	}
	if (!set_pwd_and_oldpwd(v, old_pwd))
		return (__FALSE);
	return (__TRUE);
}
