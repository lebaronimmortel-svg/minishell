/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:34:14 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/08 13:34:16 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

t_token	*lexer(char *str, t_data *data);
int		exists(char *str, t_data *data, int *i);
int		parser(t_token *lexer);
int		add_var(char *str, t_data *data);
char	**split_dup(char **envp);
int		is_alphanum(char c);
void	unset(char **split, t_data *data);
void	ft_export(char *input, t_data *data);
void	check_quote(char *str);
void	export_single(t_data *data);
void	free_split(char **split, int flag);
int		split_len(char **split);
int		exec_main(char **split, int i, int cmd_index, t_data *data);
int		pipe_and_pid_init(t_exec *exec, int cmd_count);
int		count_cmds(char **split);
void	infile_redir(char **split, int *i, int check);
void	free_split_exec(t_exec *exec);
void	collect_redirs(t_exec *exec, char **split, int cmd_pos, char **envp);
void	end_collect_redir(t_exec *exec, char **envp);
int		space_pos(char *str);
int		second_part_apply_redir(char type, t_exec *exec, int i);
int		first_part_apply_redir(char type, t_exec *exec, int i, int fd);
int		apply_redirs(t_exec *exec);
int		handle_heredoc(char *delimiter, char **envp);
void	fork_created(t_exec *exec, int cmd_index, int cmd_count);
void	execve_error(char *str, char *command);
int		end_exec(t_exec *exec, int cmd_count, t_data *data);
void	free_redir(t_exec *exec);
void	close_fd(t_exec *exec, int cmd_count);
void	main_loop(char **split, t_token *lex, t_data *data);
void	print_lexer(t_token *lexer);
void	print_icon(int flag);
void	loop(t_token *lexer, char **split);
void	expand(char **split, char **envp);
int		are_var_handled(char *str);
void	remove_quotes(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*change_var(char *str, char **envp);
int		update_flag(int flag);
int		is_valid_var(char *str, int flag);
int		is_ok_quote(char *str, int index);
void	move_one(char *str);
void	handle_single(char *str);
char	*expand_code(char *str, t_data *data);
void	echo(char *input);
int		my_memlen(char **split);
void	exec_built_in(char *input, t_data *data);
void	print_split(char **split);

#endif
