/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:31:09 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/16 08:31:10 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	execve_error(char *str, char *command)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
}
