/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 09:37:38 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 09:37:39 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

t_token	*lexer(char *str, t_data *data);

int		parser(t_token *lexer);
void	handle_single(char *str);
void	check_quote(char *str);
int		is_ok_quote(char *str, int index);

char	*expand_code(char *str, t_data *data);
char	*change_var(char *str, char **envp);
char	*convert_var(char *str, int index, char **envp);

int		is_valid_var(char *str, int flag);
int		is_ok_quote(char *str, int index);

int		exec_built_in(char *input, t_data *data, char **split, int i);
int		echo(char *input, int k);
int		cd(char *input, t_data *data);

int		unset(char **split, t_data *data);

int		exists(char *str, char **env, int *i);
int		ft_export(char *input, t_data *data, int j, int i);
void	export_single(t_data *data);

int		add_var(char *str, t_data *data);
int		change_path(int flag, char *path, t_data *data);

int		exec_main(char **split, int i, t_data *data, int cmd_count);
int		exec_main_sequel(char **split, int *i, t_exec_ctx *ctx);

void	execve_error(char *str, char *command);

void	fork_created(t_exec *exec, int cmd_index, int cmd_count);
int		end_exec(t_exec_ctx *ctx, int exit_code, int status, int i);
int		end_exec_sig(t_exec_ctx *ctx, int exit_code, int last_pid_status);

int		is_pipe(char *s);
int		skip_redirection(char **split, int i);
int		should_skip_empty(char **split, int i);
int		is_redir_argument(char **split, int i);
int		has_redir_after_empty(char **split, int i);
int		count_cmds(char **split, int i, int count);

void	check_dir(t_exec *exec);
int		find_env_loop(t_exec *exec, int i);
int		do_built_in_part( char **split, int *i, t_exec_ctx *ctx);
int		should_skip_token(char **split, int *i);
void	process_exec_loop(char **split, int *i, t_exec_ctx *ctx);

char	*get_path(char **env);
void	ctx_innit(t_exec_ctx *ctx, t_exec *exec, t_data *data, int cmd_count);
void	process_built_in(t_exec_ctx *ctx);
int		handle_exec_result(int ret, int built_in, t_exec_ctx *ctx);

void	preprocess_split(char **split, int i, int cmd_pos);
int		exec_cmd(t_exec *exec, t_data *data, char **split);

void	free_data_split(t_exec *exec);
void	free_split_exec(t_exec *exec);
void	free_redir(t_exec *exec);

void	free_exec_failed(t_exec *exec, int exit_code);
void	free_exec_cmd(t_exec *exec);
void	fork_and_free_exec(t_exec *exec, int *cmd_index, int cmd_count);

void	collect_redirs(t_exec *exec, char **split, int cmd_pos, char **envp);
void	end_redir_sequel(t_exec *exec, char **split, int i, char type);

int		handle_heredoc(t_exec *exec, char *delimiter, char **envp, int expand, int len);
int		first_part_apply_redir(char type, t_exec *exec, int i, int fd);
int		second_part_apply_redir(char type, t_exec *exec, int i);
int		apply_redirs(t_exec *exec);

int		pipe_and_pid_init(t_exec *exec, int cmd_count);
int		count_redirs(char **split, int cmd_pos);
int		init_redirs(t_exec *exec, int count);
void	infile_redir(char **split, int *i, int check);
void	end_collect_redir(t_exec *exec, char **envp);

int		handle_input_redir(t_exec *exec, int i);
int		handle_output_redir(t_exec *exec, int i);
void	append_to_cmd(char **split, int cmd_pos, char *extra);
void	handle_redir_sequel(t_exec *exec, char **split, int cmd_pos, int i);
int     execute_prompt(char **split, t_token *lex, t_data *data);

void	main_loop(char **split, t_token *lex, t_data *data);
void	handler0(int sig);

void	loop(t_token *lexer, char **split);

int		split_len(char **split);
int		update_flag(int flag);
void	move_one(char *str);
void	remove_quotes(char *str);
void	free_split(char **split, int flag);

int		ft_strcmp(char *s1, char *s2);
int		print_split(char **split);
char	**split_dup(char **envp);
int		my_memlen(char **split);
int		is_alphanum(char c);

int		is_built_in(char *input);
int		are_var_hd(char *str);
int		are_var_handled(char *str);
int		space_pos(char *str);
void	close_fd(t_exec *exec, int cmd_count);

char	*my_get_pid(void);
void	unmask_spaces(char *str);
char	**quote_clean(char **split);
char	*change_var_hd(char *str, char **envp);
int		is_path(char **env);

void	exit_cleanly(int code, t_data *data, char **split);


#endif
