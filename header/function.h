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

t_token	*lexer(char *str, char **envp, t_data *data);
int		parser(t_token *lexer);
void	check_quote(char *str);
void	free_split(char **split, int flag);
int		split_len(char **split);
int		exec_main(char **envp, char **split);
void	free_split_exec(t_exec *exec);
void	main_loop(char **split, t_token *lex, char **envp, t_data *data);
void	print_lexer(t_token *lexer);
void	print_icon(int flag);
void	loop(t_token *lexer, char **split);
void	expand(char **split, char **envp);
void	remove_quotes(char *str);
char	*change_var(char *str, char **envp);
int		update_flag(int flag);
int		is_valid_var(char *str);
int		is_ok_quote(char *str, int index);
void	move_one(char *str);
void	handle_single(char *str);
char	*expand_code(char *str, t_data *data);

#endif
