/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:47:21 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/18 16:47:22 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnd;

	newnd = malloc(sizeof(t_list));
	if (!newnd)
		return (NULL);
	newnd->content = content;
	newnd->next = NULL;
	return (newnd);
}
