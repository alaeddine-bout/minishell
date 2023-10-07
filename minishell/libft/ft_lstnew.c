/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:10:18 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/12 19:37:51 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;
	t_list	*temp;

	temp = content;
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = temp;
	node->next = NULL;
	return (node);
}
