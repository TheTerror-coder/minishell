/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/05 00:01:55 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./preminishell.h"
# include<errno.h>
# include<string.h>
# include<stdio.h>
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<sys/wait.h>
# include<bsd/string.h>

# include "./libft/ft_printf/ft_printf.h"
# include "./pipex/pipex.h"

int	is_whitespace(char c);
int is_operator(char c);

t_commands *get_commands(t_vars *v);
void	ft_freecommands(t_vars *v);
t_token	*break_input_into_tokens(t_vars *v);

char	*get_word(t_vars *v, size_t *i, int heredoc);
char	*get_redirection(char *line, size_t *l_index);
char	*get_pipe(char *line, size_t *l_index);
char	*get_heredoc(char *line, size_t *l_index);
char	*get_infile_redir(char *line, size_t *l_index);
char	*get_outfile_redir(char *line, size_t *l_index);
char	*get_outfile_append_redir(char *line, size_t *l_index);

t_bool	ft_minishell(t_vars *v);
t_bool	ft_prompt(t_vars *v);
t_bool	ft_lmanager(t_vars *v);
t_vars	*ft_initvars(void);
void	ft_exitprocss(t_vars *v, int status);

t_bool	ft_setargv(t_vars *v);
t_bool	ft_goprompt(char *msg, t_typ action);
t_bool	ft_leave(char *msg, t_typ action);

char	**env_list_to_tab(t_vars *v);
char	*check_env_var_set(t_vars *v, char *var);
t_bool	ft_setenv(t_vars *v);
t_bool	add_env_var(t_vars *v, char *var);
t_bool	ft_freeenv(t_vars *v);

t_bool	ft_checkio(t_vars *v);
void	ft_freetvars(t_vars *v);
t_bool	ft_lnch_executable(t_vars *v);
t_bool	ft_launcher(t_vars *v);
t_bool	ft_pwait(t_vars *var, int pid, int option);
t_bool	ft_fclose(int *fd);
int		ft_set_cmdpath(t_vars *v);
t_bool	ft_setpath2(t_vars *v);
t_bool	ft_isseperator(char c, char *suite);
char	*ft_setofquote(t_vars *v, char c);
void	ft_skip_partquoted(char *line, int *i);
void	ft_freesecondaries(t_vars *v);
void	ft_free_lst(t_vars *v);

t_bool	ft_ioset_op(int *infd, int *outfd);
t_bool	ft_parseargv(t_vars *v);
void	ft_razflags(t_vars *v);
t_bool	ft_inredir(t_vars *v, int *outfd);
t_bool	ft_outredir(t_vars *v, int *infd);
t_bool	ft_outappendredir(t_vars *v, int *infd);
t_bool	ft_heredocredir(t_vars *v, int *outfd);
t_bool	ft_setpipeline(t_vars *v);
t_bool	ft_heredoc(t_vars *v);
t_bool	ft_adjustargv(t_vars *v, int a, int b);
t_bool	ft_redirections(t_vars *v);
t_bool	ft_openatemp(t_vars *v);

t_bool	ft_export(t_vars *v, char *str);
t_bool	ft_echo(t_vars *v, t_bool n_option);
t_bool	ft_cd(t_vars *v);
t_bool	ft_cd_no_args(t_vars *v);
t_bool	ft_cd_oldpwd_case(t_vars *v);
t_bool	testing_split_cdpath(t_vars *v, char **split_cdpath);
t_bool	ft_pwd(void);
t_bool	ft_env(t_vars *v);


t_bool	ft_unset(t_vars *v);
#endif
