/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:00:58 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/22 14:00:58 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_s(va_list args)
{
	char	*content;
	size_t	len;

	content = va_arg(args, char *);
	if (!content)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(content, 1);
	len = ft_strlen(content);
	return (len);
}
