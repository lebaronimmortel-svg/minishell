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

typedef struct s_exec
{
	char	**all_path;
	char	**command;
	char	*w_path;
	char	*path;
	char	*input;
	char	**env;
	pid_t	pid[2];
}	t_exec;

// this structure is to be completed
typedef struct s_data
{
	int	error_code;
}	t_data;

#endif
