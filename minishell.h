/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:26 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/02 13:56:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./preminishell.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <bsd/string.h>

# include "./libft/ft_printf/ft_printf.h"
# include "./pipex/pipex.h"

int			is_whitespace(char c);
int			is_whitespace_or_operator_or_nul(char c);
int			expand_conditions(char *c, int is_hdoc_deli);
int			is_operator(char c);
char		*join_s1_with_sub_line(char *s1, t_vars *v, size_t *st, \
													size_t *end);

t_commands	*create_commands(t_token *tokens);
int			get_command_arguments(t_commands *commands);
t_commands	*get_commands(t_vars *v);
void		ft_freecommands(t_vars *v);
t_token		*break_input_into_tokens(t_vars *v, size_t l_index);

char		*get_word(t_vars *v, size_t *i, int is_hdoc_deli);
size_t		test_expand_null_content(t_vars *v, size_t l_index, \
				int is_hdoc_deli);
char		*expand_case(size_t *i, size_t *j, char *ret, t_vars *v);
char		*expand_case_double_quote(size_t *i, size_t *j, char *ret, \
															t_vars *v);
char		*get_end_expand_content(t_vars *v, char *expand_content, size_t i);
char		*get_redirection(t_vars *v, char *line, size_t *l_index);
char		*get_pipe(t_vars *v, char *line, size_t *l_index);
char		*get_heredoc(t_vars *v, char *line, size_t *l_index);
char		*get_infile_redir(t_vars *v, char *line, size_t *l_index);
char		*get_outfile_redir(t_vars *v, char *line, size_t *l_index);
char		*get_outfile_append_redir(t_vars *v, char *line, size_t *l_index);

t_bool		ft_prompt(t_vars *v);
t_vars		*ft_initvars(void);
void		ft_exitmainprocss(t_vars *v, int code);
void		ft_exitbackprocss(t_vars *v, int code);

t_bool		ft_leave(t_vars *v, int code, char *msg, t_typ action);

char		**env_list_to_tab(t_vars *v);
t_bool		var_env_compare(t_env *env_tmp, char *name, size_t length_name);
t_bool		check_env_var_set(t_env *my_env, char *var);
char		*get_env_var_content(t_vars *v, t_env *my_env, char *var);
t_bool		ft_setenv(t_vars *v, char **envp);
t_bool		add_env_var(t_vars *v, char *var);
t_bool		free_env(t_vars *v);

void		ft_freetvars(t_vars *v);
t_bool		ft_lnch_executable(t_vars *v);
t_bool		ft_launcher(t_vars *v);
t_bool		ft_pwait(t_vars *var, int pid, int option);
t_bool		ft_fclose(t_vars *v, int *fd);
char		*ft_set_cmdpath(t_vars *v, char *command);
t_bool		ft_set_path_variable(t_vars *v);
void		ft_freesecondaries(t_vars *v);
t_bool		ft_closetvars(t_vars *v);

t_bool		ft_ioset_op(t_vars *v, int *infd, int *outfd);
t_bool		ft_raz(t_vars *v);
t_bool		ft_inredir(t_vars *v, char *infile);
t_bool		ft_outredir(t_vars *v, char *outfile);
t_bool		ft_outappendredir(t_vars *v, char *outfile);
t_bool		ft_heredocredir(t_vars *v, t_commands *command);
t_bool		ft_launch_heredoc(t_vars *v, char *limiter);
t_bool		ft_heredoc(t_vars *v);
t_bool		ft_openatemp(t_vars *v);
t_bool		ft_clear_created_tempfiles(t_vars *v);
t_bool		ft_set_io(t_vars *v, t_commands *command);
t_bool		ft_run_heredocs(t_vars *v, t_commands *command);
char		*expand_words_of_line(t_vars *v, char *line);

t_bool		ft_export(t_vars *v, t_commands *command, char **arguments);
t_bool		export_one_arg(t_vars *v, char *var);
t_bool		print_not_valid_identifier(t_vars *v, char *str);
t_bool		print_export(t_vars *v);
t_bool		ft_echo(t_vars *v, t_commands *command);
t_bool		ft_cd(t_vars *v, t_commands *command);
t_bool		ft_cd_no_args(t_vars *v);
t_bool		ft_cd_oldpwd_case(t_vars *v);
t_bool		testing_split_cdpath(t_vars *v, char **split_cdpath, char *dir);
t_bool		ft_pwd(t_vars *v, char *first_arg);
t_bool		ft_env(t_vars *v, t_commands *command);
int			ft_run_builtin(t_vars *v, t_commands *command);

t_bool		ft_exit(t_vars *v, t_commands *command);
t_bool		ft_unset(t_vars *v, t_commands *command);

t_bool		set_readline_signals(t_vars *v);
void		ignore_signals(void);
void		heredoc_signals(void);
void		main_simple_signals(void);
void		launch_signals(void);
#endif
