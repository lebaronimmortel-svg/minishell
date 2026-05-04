/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:42:51 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/13 08:43:07 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	is_built_in1(char *input)
{
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "pwd ", 4))
		return (1);
	if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "env ", 4))
		return (1);
	if (!ft_strncmp(input, "unset", 5) && ft_strlen(input) == 5)
		return (1);
	if (!ft_strncmp(input, "unset ", 6))
		return (1);
	return (0);
}

int	is_built_in2(char *input)
{
	if (!ft_strncmp(input, "echo ", 5)
		|| (!ft_strncmp(input, "echo", 4) && ft_strlen(input) == 4))
		return (1);
	if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
		return (1);
	if (!ft_strncmp(input, "exit ", 5))
		return (1);
	if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
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

int	is_built_in(char *input)
{
	if (!input)
		return (0);
	if (is_built_in1(input))
		return (1);
	if (is_built_in2(input))
		return (1);
	return (0);
}

int	are_var_hd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_var(&str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

int	are_var_handled(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_var(&str[i], 0) && is_ok_quote(str, i))
			return (0);
		i++;
	}
	return (1);
}
