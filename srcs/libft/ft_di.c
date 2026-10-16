/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:01:12 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/22 14:01:13 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_di(va_list args)
{
	int		content;
	size_t	len;
	char	*str;

	content = va_arg(args, int);
	ft_putnbr_fd(content, 1);
	str = ft_itoa(content);
	len = ft_strlen(str);
	free(str);
	return (len);
}
