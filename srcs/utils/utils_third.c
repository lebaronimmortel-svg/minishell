/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_third.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:42:51 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/13 08:43:07 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	is_built_in(char *input)
{
	if (!input)
		return (0);
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "unset ", 6))
		return (1);
	if (!ft_strncmp(input, "echo ", 5))
		return (1);
	if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
		return (1);
	if (!ft_strncmp(input, "exit ", 5))
		return (1);
	if (!ft_strncmp(input, "cd ", 3))
		return (1);
	if (!ft_strncmp(input, "cd", 2) && ft_strlen(input) == 2)
		return (1);
	if (!ft_strncmp(input, "export", 6) && ft_strlen(input) == 6)
		return (1);
	if (!ft_strncmp(input, "export ", 7))
		return (1);
	return (0);
}
