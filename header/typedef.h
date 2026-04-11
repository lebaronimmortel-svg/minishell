/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:34:35 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/08 13:34:37 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct s_token
{
	char	type;
	char	*value;

}	t_token;

typedef struct s_redir
{
	char	type;
	char	*file;
	int		malloced;
	int		fd;

}	t_redir;

typedef struct s_exec
{
	char	**all_path;
	char	**command;
	char	*w_path;
	char	*path;
	char	*input;
	char	**env;
	pid_t	*pid;
	int		fd[1024][2];
	t_redir	*redir;
	int		redir_count;
}	t_exec;

typedef struct s_data
{
	int	error_code;
}	t_data;

typedef struct s_exec_ctx
{
	t_exec	*exec;
	t_data	*data;
	int		cmd_index;
	int		cmd_count;
}	t_exec_ctx;

#endif
