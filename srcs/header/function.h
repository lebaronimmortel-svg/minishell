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

t_token	*lexer(char *str);
int		parser(t_token *lexer);
void	check_quote(char *str);
void	free_split(char **split);
int		split_len(char **split);
void	exec_main(char **envp, char **split, int i, int cmd_index);
void	collect_redirs(t_exec *exec, char **split, int cmd_pos, int count);
int		space_pos(char *str);
int		second_part_apply_redir(char type, t_exec *exec, int i);
int		first_part_apply_redir(char type, t_exec *exec, int i, int fd);
int		apply_redirs(t_exec *exec);
void	fork_created(t_exec *exec, int cmd_index, int cmd_count);
void	execve_error(char *str, char *command);
void	end_exec(t_exec *exec, int cmd_count);
void	free_split_exec(t_exec *exec);
void	free_redir(t_exec *exec);
void	close_fd(t_exec *exec, int cmd_count);
void	main_loop(char **split, t_token *lex, char **envp);
void	print_lexer(t_token *lexer);
void	print_icon(int flag);
void	loop(t_token *lexer, char **split);
int		ft_strcmp(char *s1, char *s2);

#endif
